/* @header
 * func_800A47C4
 * VRAM 0x800A47C4 | ROM 0x97C64 | size 0xA0
 * asm: asm/nonmatchings/code_8009D7A0/func_800A47C4.s
 */
#include "common.h"

typedef struct {
    s32 f0;
    s16 f4;
    s16 f6;
    s32 f8;
    s16 fC;
    s16 fE;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    u64 flags;
    s32 f28;
    s32 f2C;
    s32 f30;
    s32 f34;
    s32 f38;
    s32 f3C;
    s32 f40;
    s32 f44;
    s32 f48;
    s32 f4C;
    s32 f50;
    s32 f54;
    s32 f58;
} Nw2ActionObj;

extern s32 func_800D2B64(void *, f32, u16, s32);
extern void func_800D427C(void *, s32, s32);
extern void func_800A7188(void *);

/* Two-phase action on the global record D_800EB408. Marks the record active
 * (flag 0x1000000000 in +0x20), then: phase 0 plays sound 0xEBD and advances to
 * phase 1; phase 1 starts sound 0xFFFFE at pitch 1.0 and hands off to
 * func_800A7188. */
void func_800A47C4(void) {
    Nw2ActionObj *p = D_800EB408;
    s16 phase;

    p->flags |= 0x1000000000ULL;
    phase = *(s16 *)((u8 *)p + 0xC);
    switch (phase) {
    case 0:
        func_800D427C(p, 0xEBD, 3);
        (*(u16 *)((u8 *)D_800EB408 + 0xC))++;
        break;
    case 1:
        func_800D2B64(p, 1.0f, 0, 0xFFFFE);
        func_800A7188(D_800EB408);
        break;
    }
}
