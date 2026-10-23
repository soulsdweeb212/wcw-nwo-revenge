#include "common.h"

typedef struct {u8 width,height;u16 colors;u8 pad[4];u8 pixels[1];} MaskTexture;
typedef struct {u8 pad[24];MaskTexture *image;u16 *palette;} MaskObject;
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
 if(image->colors==256) {
 obj->palette[255]=color;
 for(row=0;row<64;row++,mask+=4) {
 u32 *p;
 flag=0x80000000;bit=0;p=(u32*)mask;
 for(;bit<32;bit++,flag>>=1) {if(!(*p&flag)) pixels[(row<<5)+bit]=255;}
 }
 } else {
 obj->palette[15]=color;
 if(image->width*image->height>2048) {
 if(image->width>64) {
 for(row=0,reverseOuter=3;row<32;row++,reverseOuter+=4) {
 s32 reverse; u32 row2,row4;
 half=0;row2=row<<1;row4=row<<2;reverse=reverseOuter;
 do {
 u32 *q; s32 front,back;
 flag=0x80000000;bit=0;q=(u32*)((row2+half)*4+(u32)mask);
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
 if(D_800307A0==1) convertRgba16ToGrayscale(obj->palette+image->colors-1,1);
}
