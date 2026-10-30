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

/* Facing check between arg0 and arg1: clear the u64 flags 0x8008000000 on arg0, build the
 * direction record from arg0's position (+0x6C) toward arg1's, then set flag 0x08000000
 * when the absolute facing delta (from arg0's heading +0x58 to the direction angle) is
 * >= 0x400, and set flag 0x8000000000 when that delta is negative. */
void func_800C4548(void *arg0, void *arg1) {
    Nw2Dir dir;
    s32 d;

    *(u64 *)((u8 *)arg0 + 0x20) &= ~0x8008000000ULL;
    func_800D3890((u8 *)arg0 + 0x6C, (u8 *)arg1 + 0x6C, &dir);
    d = func_800D3550(func_800D3684(*(s32 *)((u8 *)arg0 + 0x58), dir.angle));
    if (d >= 0x400) {
        *(u64 *)((u8 *)arg0 + 0x20) |= 0x08000000ULL;
    }
    if (func_800D3684(*(s32 *)((u8 *)arg0 + 0x58), dir.angle) < 0) {
        *(u64 *)((u8 *)arg0 + 0x20) |= 0x8000000000ULL;
    }
}
