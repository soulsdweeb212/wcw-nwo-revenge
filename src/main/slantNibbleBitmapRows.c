#include "common.h"

/* Shear a 4bpp bitmap horizontally one row at a time: for each row compute a
 * per-row shift (24- or 14-row period selected by flags&0x8000), copy the
 * nibbles from the shifted source (rebuilding each byte from the neighbouring
 * low nibble) and zero the vacated columns on the left. */
typedef struct { s32 f0; u8 *buf; s32 f8; s16 width; s16 height; } Nw2Bitmap;
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
