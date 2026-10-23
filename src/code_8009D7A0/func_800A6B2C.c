#include "common.h"

typedef struct {
    s32 f0;
    s16 f4;
    s16 f6;
    s32 f8;
    u16 fC;
    u16 fE;
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
extern u16 D_800FABE6;

/* Select the action id from the D_800FABE6 flags (0x200/0x100/0x800/0x400 ->
 * 0x1344/0x1345/0x105F/0x1060, default 0x184F), start it and clear the three
 * record fields; state 1 finishes the action when the timer expires. */
void func_800A6B2C(void) {
    Nw2ActionObj *p = D_800EB408;
    s16 state = p->fC;

    switch (state) {
    case 0:
    {
        u16 flags = D_800FABE6;
        s32 id = 0x184F;

        p->f4C = 0;
        p->f54 = 0;
        p->f58 = 0;
        if (flags & 0x200) {
            id = 0x1344;
        }
        if (flags & 0x100) {
            id = 0x1345;
        }
        if (flags & 0x800) {
            id = 0x105F;
        }
        if (flags & 0x400) {
            id = 0x1060;
        }
        func_800D427C(p, id, 0);
        ((Nw2ActionObj *)D_800EB408)->fC++;
        break;
    }
    case 1:
        if (p->f4 <= 0) {
            func_800A6C48(p, 1);
        }
        break;
    }
}
