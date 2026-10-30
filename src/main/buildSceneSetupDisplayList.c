/* @header
 * buildSceneSetupDisplayList  (originally func_80002664)
 * VRAM 0x80002664 | ROM 0x3264 | size 0x250
 * asm: asm/nonmatchings/main/func_80002664.s
 */
#include "common.h"

/* Appends the scene render setup to the current display list
 * D_80044590[D_8002EEBC] and returns the new end pointer.
 * Emits two 0xDB segment loads (the second from the D_8007E228 heap block),
 * the 0xDB texture load for arg0->f8, a 0xDE tile load (func_8001CE80's
 * address), and when arg1 is set the 0xFF light word for arg0->f0 plus, once
 * (guarded by D_8002EEC6), a 0x3C-entry 0xF6 gradient ramp with its 0xE3/0xE2/
 * 0xF7/0xE7 bracketing. It finishes with the standard RDP setup words
 * (0xD7/0xD9/0xE3/0xFB/0xE3) and returns the advanced pointer. */
typedef union { u64 align; struct { u32 w0; u32 w1; } w; } Dl;
typedef struct { s32 f0; s32 f4; u16 f8; } Obj2664;
extern Dl *D_80044590[];
extern s16 D_8002EEBC;
extern s16 D_8002EEC6;
extern s32 D_8007E228;
extern u8 D_1000010[];
u32 func_8001CE80(void *);
#define C(a, b) { Dl *g = dl++; g->w.w0 = (a); g->w.w1 = (b); }

Dl *buildSceneSetupDisplayList(Obj2664 *arg0, s16 arg1) {
    Dl *dl;
    u32 i;

    dl = D_80044590[D_8002EEBC];
    C(0xDB060000, 0);
    C(0xDB060004, func_8001CE80((void *)D_8007E228));
    C(0xDB0E0000, arg0->f8);
    C(0xDE000000, (u32)func_8001CE80 - 0x7F01CE70);
    if (arg1) {
        C(0xFF1001DF, (u32)(arg0->f0 - 0x80000000));
        if (D_8002EEC6) {
            C(0xE3000A01, 0x300000);
            D_8002EEC6 = 0;
            C(0xE200001C, 0);
            C(0xF7000000, 0x10001);
            for (i = 0; i < 0x3C; i++) {
                Dl *g = dl++;
                g->w.w0 = 0xF677C000 | ((((i + 1) * 4 - 1) & 0x3FF) << 2);
                g->w.w1 = (i << 4) & 0xFF0;
            }
            C(0xE7000000, 0);
        }
    }
    C(0xD7000002, 0xFFFFFFFF);
    C(0xD9C0F9FA, 0);
    C(0xD9FFFFFF, 0x200404);
    C(0xE3000A01, 0);
    C(0xFB000000, 0xFF);
    C(0xE3001001, 0x8000);
    return dl;
}
