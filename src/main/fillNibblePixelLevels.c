/* @header
 * fillNibblePixelLevels  (originally func_80029E94)
 * VRAM 0x80029E94 | ROM 0x2AA94 | size 0x168
 * asm: asm/nonmatchings/main/fillNibblePixelLevels.s
 */
#include "common.h"

typedef struct {u8 pad0[4]; u8 *buf; u8 pad8[4]; s16 w,h;} Nw2Grid29E94;
#ifdef TARGET_PC
/* PC: o is an entry of the resource-name cache (func_8002A2FC passes it), whose PC layout is Nw2ResourceEntryHashed in
 * common.h. On PC the view's pointer field (buf) is 8 bytes and starts at a multiple of 8, so it lies at +8, the
 * entry's allocation, and w and h fall at reserved's +4 and +6 (+0x14 and +0x16), where func_80028F3C writes the row
 * width and the row count. The view needs no PC version of its own; the assert checks that it still agrees with the
 * entry. */
_Static_assert(offsetof(Nw2Grid29E94, buf) == offsetof(Nw2ResourceEntryHashed, allocation) &&
                   offsetof(Nw2Grid29E94, w) == offsetof(Nw2ResourceEntryHashed, reserved) + 4 &&
                   offsetof(Nw2Grid29E94, h) == offsetof(Nw2ResourceEntryHashed, reserved) + 6,
               "Nw2Grid29E94 must follow the PC layout of Nw2ResourceEntryHashed");
#endif
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
