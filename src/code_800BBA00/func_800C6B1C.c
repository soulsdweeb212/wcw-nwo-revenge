/* @header
 * func_800C6B1C
 * VRAM 0x800C6B1C | ROM 0xB9FBC | size 0x238
 * asm: asm/nonmatchings/code_800BBA00/func_800C6B1C.s
 */
#include "common.h"

void func_800D427C(void *, s32, s32);
void func_800A7D1C(void *, s32);
void func_800A7F6C(void *, s32);
s8 func_800C2CDC(void *, s32);
void func_800C3A78(void *, void *, s32);
void func_800D25D0(void *, f32);
void func_800D2B64(void *, f32, s32, s32);
void func_800A7188(void *);

/* Step machine driven by D_800FAF5C->step:
 *   0: pick animation id (0x1029/0x102D) from a flag, attach and start it, advance.
 *   1: look up a target record, advance and attach it with range 0x400.
 *   2: reuse scale 2.0, apply an impulse whose strength/size depends on the
 *      state (or the flags), then refresh the object. */
void func_800C6B1C(void)
{
    s32 id;
    s32 anim;
    s32 idx;
    u64 flags;
    f32 scale;
    Wrestler *p;

    switch (D_800FAF5C->step) {
    case 0:
        if (D_800FAF5C->flags & 0x2000000000000ULL) {
            id = 0x1029;
            anim = 0x2A;
        } else if ((D_800FAF5C->flags & 0x0ULL) == 0) {
            id = 0x102D;
            anim = 0x29;
        } else {
            id = 0x1029;
        }
        func_800D427C(D_800FAF5C, id, 1);
        func_800A7D1C(D_800FAF5C, anim);
        func_800A7F6C(D_800FAF5C, 0x4A);
        D_800FAF5C->step = D_800FAF5C->step + 1;
    case 1:
        idx = func_800C2CDC(D_800FAF5C, 3);
        if (idx != -1) {
            D_800FAF5C->step = D_800FAF5C->step + 1;
            func_800C3A78(D_800FAF5C, &D_800F9D10[idx], 0x400);
        }
    case 2:
        scale = 2.0f;
        func_800D25D0(D_800FAF5C, scale);
        p = D_800FAF5C;
        if ((p->flags & 0x0ULL) != 0 || (p->flags & 0x100) != 0) {
            func_800D2B64(p, scale, 0, 0xFFFFE);
        } else {
            switch ((s16)(p->state - 7)) {
            case 15:
                if (p->animFrame > p->anim.hitEnd) {
                    func_800D2B64(p, 2.0f, 0, 0xE);
                }
                break;
            case 0: case 24: case 25: case 26: case 29: case 30: case 31: case 78: case 79:
                if (p->animFrame > p->anim.hitEnd) {
                    func_800D2B64(p, 4.0f, 0, 0xFFFFE);
                } else {
                    func_800D2B64(p, 2.0f, 0, 0xE);
                }
                break;
            case 1: case 23: case 27: case 28: case 32:
                func_800D2B64(D_800FAF5C, 2.0f, 0, 0xE);
                break;
            }
        }
        func_800A7188(D_800FAF5C);
        break;
    }
}
