/* @header
 * applyTextureTransparencyMask  (originally func_8000C474)
 * VRAM 0x8000C474 | ROM 0xD074 | size 0x310
 * asm: asm/nonmatchings/main/applyTextureTransparencyMask.s
 */
#include "common.h"

typedef struct {u8 width,height;u16 colors;u8 pad[4];u8 pixels[1];} MaskTexture;
#ifdef TARGET_PC
/* PC: obj is the game's display record, whose PC layout is that of Nw2TextureDisplayObj (common.h): its pointers are 8
 * bytes, so image and palette (+0x18 and +0x1C on N64) are that struct's tex and palette fields. pad runs up to them,
 * and the assert checks that it does. */
typedef struct {u8 pad[offsetof(Nw2TextureDisplayObj, tex)];MaskTexture *image;u16 *palette;} MaskObject;
_Static_assert(offsetof(MaskObject, image) == offsetof(Nw2TextureDisplayObj, tex) &&
                   offsetof(MaskObject, palette) == offsetof(Nw2TextureDisplayObj, palette),
               "MaskObject must follow the display record's PC layout");
#else
typedef struct {u8 pad[24];MaskTexture *image;u16 *palette;} MaskObject;
#endif
extern u16 D_800307A0; void convertRgba16ToGrayscale(u16*,u16);

/* Applies a 1-bit transparency mask to a palette-indexed texture image.  For a
 * 256-colour image it sets palette[255] = color and writes index 255 for every
 * set mask bit.  Otherwise it sets palette[15] and, for images larger than 2048
 * pixels, writes nibble masks into the pixel bytes: width > 64 uses a paired,
 * reversed-row layout (two rows per outer step, front/back with alternating high
 * and low nibbles), other large images use a 64-row front/back layout, and small
 * images use a simple row*16 nibble write.  When D_800307A0 == 1 the last palette
 * entry is converted to grayscale. */
void applyTextureTransparencyMask(MaskObject *obj,u8 *mask,s16 color) {
    MaskTexture *image=obj->image; u8 *pixels=image->pixels;
    u32 row,bit,half,flag; s32 reverseOuter;
#ifdef TARGET_PC
    /* PC: the texture and its palette stay in the N64's byte order (Fast3D reads them big-endian), so the colour count
     * in the texture's header is read, and the palette entry written, big-endian. The mask is game data in the N64's
     * byte order too: 64 big-endian words, whose bit 31 is a row's first pixel. The loops below read it a word at a
     * time, so it is copied into native words first. */
    u32 maskWords[64];
    for(row=0;row<64;row++) maskWords[row]=READ_BE32(mask+row*4);
    mask=(u8 *)maskWords;
    if(READ_BE16(&image->colors)==256) {
        WRITE_BE16(&obj->palette[255],color);
#else
    if(image->colors==256) {
        obj->palette[255]=color;
#endif
        for(row=0;row<64;row++,mask+=4) {
            u32 *p;
            flag=0x80000000;bit=0;p=(u32*)mask;
            for(;bit<32;bit++,flag>>=1) {if(!(*p&flag)) pixels[(row<<5)+bit]=255;}
        }
    } else {
#ifdef TARGET_PC
        /* PC: the palette entry is written big-endian, as above. */
        WRITE_BE16(&obj->palette[15],color);
#else
        obj->palette[15]=color;
#endif
        if(image->width*image->height>2048) {
            if(image->width>64) {
                for(row=0,reverseOuter=3;row<32;row++,reverseOuter+=4) {
                    s32 reverse; u32 row2,row4;
                    half=0;row2=row<<1;row4=row<<2;reverse=reverseOuter;
                    do {
                        u32 *q; s32 front,back;
#ifdef TARGET_PC
                        /* PC: mask is an address; a u32 would cut it in half. */
                        flag=0x80000000;bit=0;q=(u32*)((row2+half)*4+(uptr)mask);
#else
                        flag=0x80000000;bit=0;q=(u32*)((row2+half)*4+(u32)mask);
#endif
                        front=(row4+half)*16;back=(reverse-half)*16+15;
                        for(;bit<32;bit++,flag>>=1) {
                            if(!(*q&flag)) {
                                if(!(bit&1)) {pixels[front+(bit>>1)]|=0xF0; pixels[back-(bit>>1)]|=0xF;}
                                else {pixels[front+(bit>>1)]|=0xF;pixels[back-(bit>>1)]|=0xF0;}
                            }
                        }
                        half++;
                    }while(half<2);
                }
            } else {
                for(row=0;row<64;row++,mask+=4) {
                    u32 *r; s32 front,back;
                    flag=0x80000000;bit=0;r=(u32*)mask;
                    front=(row^1)*16+15;back=(127-row)*16+15;
                    for(;bit<32;bit++,flag>>=1) {
                        if(!(*r&flag)) {
                            if(!(bit&1)) {pixels[front-(bit>>1)]|=0xF0;pixels[back-(bit>>1)]|=0xF0;}
                            else {pixels[front-(bit>>1)]|=0xF;pixels[back-(bit>>1)]|=0xF;}
                        }
                    }
                }
            }
        } else {
            for(row=0;row<64;row++,mask+=4) {
                u32 *s;
                flag=0x80000000;bit=0;s=(u32*)mask;
                for(;bit<32;bit++,flag>>=1) {
                    if(!(*s&flag)) {
                        if(!(bit&1)) pixels[row*16+(bit>>1)]|=0xF0;
                        else pixels[row*16+(bit>>1)]|=0xF;
                    }
                }
            }
        }
    }
#ifdef TARGET_PC
    /* PC: the colour count in the texture's header is read big-endian, as above. */
    if(D_800307A0==1) convertRgba16ToGrayscale(obj->palette+READ_BE16(&image->colors)-1,1);
#else
    if(D_800307A0==1) convertRgba16ToGrayscale(obj->palette+image->colors-1,1);
#endif
}
