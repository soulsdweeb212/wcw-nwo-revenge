/* @header
 * fillNibblePixelLevels  (originally func_80029E94)
 * VRAM 0x80029E94 | ROM 0x2AA94 | size 0x168
 * asm: asm/nonmatchings/main/fillNibblePixelLevels.s
 */
#include "common.h"

typedef struct {u8 pad0[4]; u8 *buf; u8 pad8[4]; s16 w,h;} Nw2Grid29E94;
s32 countNibblePixelNeighbors(void *,s32,s32,s32,s32);
/* Flood-fills a packed-nibble grid (two pixels per byte): for levels 6 down to
 * 1, any pixel whose nibble is empty but whose neighbors (via
 * countNibblePixelNeighbors) belong to the level gets that level written into
 * its high and/or low nibble. */
void fillNibblePixelLevels(Nw2Grid29E94 *o) {
 s32 x,y,level; u8 c; s32 r;
 for(level=6;level>0;level--) {
 for(y=0;y<o->h;y++) {
 for(x=0;x<o->w/2;x++) {
 c=o->buf[x+y*o->w/2];
 if(!(c&0xf0)||!(c&0xf)) {
 r=countNibblePixelNeighbors(o,x,y,(u8)(level+1),(u8)c);
 if(r&0xff) {
 if(r&0xf0) c|=level<<4;
 if(r&0xf) c|=level;
 o->buf[x+y*o->w/2]=c;
 }
 }
 }
 }
 }
}
