/* @header
 * slantNibbleBitmapRows  (originally func_80029FFC)
 * VRAM 0x80029FFC | ROM 0x2ABFC | size 0x1C8
 * asm: asm/nonmatchings/main/slantNibbleBitmapRows.s
 */
#include "common.h"

/* Shear a 4bpp bitmap horizontally one row at a time: for each row compute a
 * per-row shift (24- or 14-row period selected by flags&0x8000), copy the
 * nibbles from the shifted source (rebuilding each byte from the neighbouring
 * low nibble) and zero the vacated columns on the left. */
typedef struct { s32 f0; u8 *buf; s32 f8; s16 width; s16 height; } Nw2Bitmap;
#ifdef TARGET_PC
/* PC: obj is an entry of the resource-name cache (func_8002A2FC passes it), whose PC layout is Nw2ResourceEntryHashed
 * in common.h. On PC the view's pointer field (buf) is 8 bytes and starts at a multiple of 8, so it lies at +8, the
 * entry's allocation, and width and height fall at reserved's +4 and +6 (+0x14 and +0x16), where func_80028F3C writes
 * the row width and the row count.
 * The view needs no PC version of its own (f0 and f8 are not read); the assert checks that it still agrees with the
 * entry. */
_Static_assert(offsetof(Nw2Bitmap, buf) == offsetof(Nw2ResourceEntryHashed, allocation) &&
                   offsetof(Nw2Bitmap, width) == offsetof(Nw2ResourceEntryHashed, reserved) + 4 &&
                   offsetof(Nw2Bitmap, height) == offsetof(Nw2ResourceEntryHashed, reserved) + 6,
               "Nw2Bitmap must follow the PC layout of Nw2ResourceEntryHashed");
#endif
static __inline__ void putByte29(Nw2Bitmap *o,s32 x,s32 y,u32 c) { o->buf[x+y*o->width/2]=c; }
static __inline__ s32 rowShift29(s32 y,s32 flags) { if(flags&0x8000) return (23-y%24)/4; else return (13-y%14)/4; }
void slantNibbleBitmapRows(Nw2Bitmap *obj,s32 flags) {
    s32 col,row,shift,startOffset;
    u8 *src;
    u32 packed;
    for(row=0;row<obj->height;row++) {
        shift=rowShift29(row,flags);
        startOffset=shift/2+1;
        col=obj->width/2-1;
        src=obj->buf+(obj->width/2-startOffset+row*obj->width/2);
        while(shift/2<col) {
            if(src==0) packed=src[0]; else packed=src[0]|(src[-1]<<8);
            if(shift&1) putByte29(obj,col,row,packed>>4);
            else putByte29(obj,col,row,packed);
            col--;src--;
        }
        while(col>=0) { obj->buf[col+row*obj->width/2]=0;col--; }
    }
}
