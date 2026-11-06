/* @header
 * func_800C4548
 * VRAM 0x800C4548 | ROM 0xB79E8 | size 0xC8
 * asm: asm/nonmatchings/code_800BBA00/func_800C4548.s
 */
#include "common.h"

/* {x,y,z,angle} direction record (same layout as Nw2DirectionResult). */
typedef struct {
    f32 x, y, z;
    s32 angle;
} Nw2Dir;

void func_800D3890(void *, void *, void *);

/* Facing check of w against other: clear flag bits 0x8008000000 on w, take the XZ direction from w's pelvis
 * (jointA[1]) to other's (func_800D3890), then set flag 0x08000000 when the absolute angle difference between w's
 * heading and that direction (func_800D3550(func_800D3684(heading, angle))) is >= 0x400, and set flag
 * 0x8000000000 when func_800D3684(heading, angle) is negative. */
void func_800C4548(Wrestler *w, Wrestler *other) {
    Nw2Dir dir;
    s32 d;

    w->flags &= ~0x8008000000ULL;
    func_800D3890(&w->jointA[1], &other->jointA[1], &dir);
    d = func_800D3550(func_800D3684(w->heading, dir.angle));
    if (d >= 0x400) {
        w->flags |= 0x08000000ULL;
    }
    if (func_800D3684(w->heading, dir.angle) < 0) {
        w->flags |= 0x8000000000ULL;
    }
}
