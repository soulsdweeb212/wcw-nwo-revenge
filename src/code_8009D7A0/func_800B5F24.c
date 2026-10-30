/* @header
 * func_800B5F24
 * VRAM 0x800B5F24 | ROM 0xA93C4 | size 0x1A4
 * asm: asm/nonmatchings/code_8009D7A0/func_800B5F24.s
 */
#include "common.h"

typedef struct {
    u8 pad0[0x20];
    u64 flags;
    u16 f28;
    u8 pad2A[0x14];
    s16 f3E;
    u8 pad40[0x2C];
    f32 vec[3];
} Nw2Obj5F24;

extern f32 D_800E3C50[];
extern f32 D_800E3C54[];
extern f64 D_800E54F8;
extern f64 D_800E5500;

f32 func_800D3890(void *, void *, s32);
s8 func_800B71F8(void *, s32, s32);

s32 func_800B5F24(Nw2Obj5F24 *arg0, Nw2Obj5F24 *arg1, u16 arg2) {
    f32 sp10[4];
    f32 f;
    s32 bits;
    u64 fl;

    fl = arg0->flags;
    if (!(fl & 0x40ULL)) {
        return 0;
    }
    if (fl & 0x9ULL) {
        return 0;
    }
    sp10[0] = D_800E3C50[arg0->f3E * 2];
    sp10[2] = D_800E3C54[arg0->f3E * 2];
    f = func_800D3890(arg0->vec, sp10, 0);
    if (arg0->f28 & 0x20) {
        if ((arg0->flags & 0x80000ULL) || !(arg1->flags & 0x80000ULL)) {
            if ((*(u32 *)&arg0->f28 & 0x8880000) != 0x80000) {
                return 0;
            }
            if (!(arg2 & 0xC030)) {
                return 0;
            }
            if (D_800E54F8 <= f) {
                if (f <= D_800E5500) {
                    bits = 0x800;
                    if (func_800B71F8(arg0, 0, 3)) {
                        bits = 0x1000;
                        if (arg2 & 0x8000) {
                            bits = 0x2000;
                        }
                    }
                    arg0->f28 |= bits;
                }
            } else {
                return 0;
            }
        }
    }
    return 0;
}
