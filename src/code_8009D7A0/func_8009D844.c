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
