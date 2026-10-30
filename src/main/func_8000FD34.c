/* @header
 * func_8000FD34
 * VRAM 0x8000FD34 | ROM 0x10934 | size 0x98
 * asm: asm/nonmatchings/main/func_8000FD34.s
 */
#include "common.h"

extern f64 D_8003B250;

/* Initialise a motion/tween record: store the duration (+4) and the goal
 * coordinates (+0x14 = inX, +0x18 = inY), precompute their scaled copies at
 * +8/+12 (multiplied by D_8003B250), then derive the per-frame velocity at
 * +0x20/+0x24 as (goal - scaled)/frames (zero when frames == 0). Finally store
 * the record id (+0) and frame count (+2). */
void func_8000FD34(void *motion, s16 id, s16 frames, s32 duration, f32 inY, f32 inX) {
    f32 scaledX=(f64)inX*D_8003B250;
    f32 scaledY=(f64)inY*D_8003B250;
    f32 framesF;
    *(s32 *)((u8 *)motion+4)=duration;
    *(f32 *)((u8 *)motion+0x14)=inX;
    *(f32 *)((u8 *)motion+0x18)=inY;
    *(f32 *)((u8 *)motion+8)=scaledX;
    *(f32 *)((u8 *)motion+12)=scaledY;
    if(frames!=0) {
        framesF=(f32)frames;
        *(f32 *)((u8 *)motion+0x20)=(*(f32 *)((u8 *)motion+0x14)-*(f32 *)((u8 *)motion+8))/framesF;
        *(f32 *)((u8 *)motion+0x24)=(*(f32 *)((u8 *)motion+0x18)-*(f32 *)((u8 *)motion+12))/framesF;
    } else {
        *(f32 *)((u8 *)motion+0x20)=0;
        *(f32 *)((u8 *)motion+0x24)=0;
    }
    *(s16 *)motion=id;
    *(s16 *)((u8 *)motion+2)=frames;
}
