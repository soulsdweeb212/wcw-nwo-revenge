#include "common.h"

typedef struct { s32 f0; s16 f4; s16 f6; s32 f8; s16 fC; s16 fE; } T_F408;
extern void *D_800EB408;
extern s32 D_800EB40C;
extern s16 D_800EB37A;
extern s32 *D_800F99D4;
extern s32 D_800F99C0;

extern void buildColorOverlayDisplayList(void *, s32, s32, s32, s32);
extern void func_800D2B64(void *, s32, s32, s32);
extern void func_800D93DC(void *);
extern void func_800D427C(void *, s32, s32);
extern void func_800A6C48(void *, s32);
extern void func_800D2BEC(void *, s32, s32, s32, s32, s32);
extern void func_800D4AD0(void *);
extern void beginEntityActionA8D8C(void *);
extern void func_800C472C(s32, void *, s32);

/* Two-state action on D_800EB408 (state +0xC): runs boundary correction, then
 * state 0 plays animation 0x109D and advances; state 1 waits for the timer and
 * then switches to action 1. */
void func_8009F774(void) {
    T_F408 *o;
    s16 v;

    func_800D2B64(D_800EB408, 0x40000000, 0, 0xFFFFE);
    func_800D93DC(D_800EB408);
    o = (T_F408 *)D_800EB408;
    v = o->fC;
    switch (v) {
    case 0:
        func_800D427C(o, 0x109D, 2);
        ((T_F408 *)D_800EB408)->fC = (s16)((u16)((T_F408 *)D_800EB408)->fC + 1);
        return;
    case 1:
        if (o->f4 > 0) return;
        func_800A6C48(o, 1);
        return;
    }
}

/* Steps the overlay fade-out by 8 (down to 0x11), rebuilding the colour overlay
 * display list; sets the overlay's 0x80 flag when the fade is complete. Returns
 * 1 while it advanced. */
s32 func_8009D844(s32 arg0, s32 arg1, s32 arg2) {
    s16 temp_v0;

    if (D_800EB37A >= 0x11) {
        temp_v0 = D_800EB37A - 8;
        D_800EB37A = temp_v0;
        buildColorOverlayDisplayList(&D_800F99C0, arg0 & 0xFF, arg1 & 0xFF, arg2 & 0xFF, temp_v0 & 0xFF);
        return 1;
    }
    *D_800F99D4 |= 0x80;
    return 0;
}

/* Runs boundary correction on the entity and, once its timer expires, tears the
 * action down, restarts the entity action and notifies the linked entity. */
void func_800A3E54(void) {
    func_800D2BEC(D_800EB408, D_800EB40C, 0, 0x40800000, 0, 0xFFFFE);
    if (((T_F408 *)D_800EB408)->f4 <= 0) {
        func_800D4AD0(D_800EB408);
        beginEntityActionA8D8C(D_800EB408);
        func_800C472C(D_800EB40C, D_800EB408, 2);
    }
}
