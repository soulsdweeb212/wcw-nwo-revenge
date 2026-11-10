/* @header
 * func_800DCFBC
 * VRAM 0x800DCFBC | ROM 0xD045C | size 0x1CC
 * asm: asm/nonmatchings/code_800BBA00/func_800DCFBC.s
 */
#include "common.h"

/* Step machine for the active wrestler (D_800FAF5C) while a move is
 * playing. Step 0 sets up the move (func_800A7C40) and turns toward the
 * opponent (func_800DACE4 into heading). Step 1 clears the action's flag bits
 * (D_800E3F20 table) and, if func_800DB4FC succeeds, moves on. Step 2 runs
 * func_800DB348 and, once animFramesLeft is non-positive, either starts action
 * 0x23 with the follow-up chain (func_800D4CC4 / addEntityHealthDelta using
 * move.spiritOnFinish) or queues action 0x2B. */
extern s32 D_800E3F20[], D_800FABD8;
extern s8 D_800FADB8;
#ifdef TARGET_PC
/* PC: port_decls.h declares func_800D5438, so the PC copy of this line leaves it out. */
void func_800A7C40(void *, s8, s16);
void func_800A7D1C(void *, s32);
void func_800A7F6C(void *, s32);
void beginEntityActionA8D8C(void *);
void func_800B68A0(void *, void *, void *);
void addEntityHealthDelta(void *, s32);
void func_800D427C(void *, s16, s32);
void func_800D4AD0(void *);
s8 func_800D4CC4(void *);
s32 func_800DACE4(void *, void *);
void func_800DB348(void *, void *);
s8 func_800DB4FC(void *, void *);
#else
void func_800A7C40(void *, s8, s16); void func_800A7D1C(void *, s32); void func_800A7F6C(void *, s32); void beginEntityActionA8D8C(void *); void func_800B68A0(void *, void *, void *); void addEntityHealthDelta(void *, s32); void func_800D427C(void *, s16, s32); void func_800D4AD0(void *); s8 func_800D4CC4(void *); s16 func_800D5438(void *, s32); s32 func_800DACE4(void *, void *); void func_800DB348(void *, void *); s8 func_800DB4FC(void *, void *);
#endif
void func_800DCFBC(void) {
    Wrestler *p;
    switch (D_800FAF5C->step) {
    case 0:
        func_800A7C40(D_800FAF5C, D_800FADB8, 0xE1);
        func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 0), 3);
        func_800A7F6C(D_800FAF5C, 0);
        D_800FAF5C->heading = func_800DACE4(D_800FAF5C, D_800F9B00);
        D_800FAF5C->step++;
        break;
    case 1:
        D_800FABD8 &= ~D_800E3F20[D_800FADB8];
        if (func_800DB4FC(D_800FAF5C, D_800F9B00)) D_800FAF5C->step++;
    case 2:
        func_800DB348(D_800FAF5C, D_800F9B00);
        if (D_800FAF5C->animFramesLeft <= 0) {
            func_800D4AD0(D_800FAF5C); p = D_800FAF5C;
            if (p->step == 1) {
                func_800A7D1C(p, 0x23); func_800B68A0(D_800FAF5C, D_800FAF5C, D_800FAF5C);
                if (func_800D4CC4(p)) addEntityHealthDelta(p, p->move.spiritOnFinish);
                beginEntityActionA8D8C(p);
            } else func_800A6C48(p, 0x2B);
        }
        break;
    }
}
