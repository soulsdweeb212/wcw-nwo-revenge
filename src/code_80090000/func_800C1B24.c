/* @header
 * func_800C1B24
 * VRAM 0x800C1B24 | ROM 0x6E294 | size 0x128
 * asm: asm/nonmatchings/code_80090000/func_800C1B24.s
 */
#include "common.h"

typedef struct { u8 pad[8]; s16 a; s16 b; } H;
extern H D_800D4ED8;
extern s32 D_800DF2FC, D_800E74C8, D_800DF3A0, D_800DF30C, D_800DF300, D_800DF304, D_800DF318, D_800DF314, D_800DF310, D_800DF308;
extern H *D_800DF31C;
extern u8 D_8007E228[];
extern s32 D_80038AA4, D_800E79C4, D_800E9F70, D_800E74E8, D_800EA0B4, D_800DF3A8, D_800DF3AC;
extern void *D_800DF210, *D_800DF224;
extern s32 D_800DF218;
extern u8 D_800DF220[];
void *allocateHeap(s32);
void initializeTransformNode(void *, s32, f32, f32, f32);
void *initPairedTransformNodes(void *, void *);
void func_800B807C(s32, s32, s32);

/* z is a one-element array (a one-field struct or an s32/f32 union works too): it gets an SImode
   pseudo, so the arguments are (subreg:SF ...), not REGs. calls.c then does not copy them into an SF
   pseudo, and CSE replaces the folded 0.0f (cost 12) with the cheaper stack-argument slot it just
   stored (cost 4): `sw zero,16(sp); lw a2,16(sp); move a3,a2`. A plain f32 or 0.0f literal gives
   mtc1/mfc1. */
void func_800C1B24(void) {
    f32 z[1];

    D_800DF2FC = 0;
    D_800E74C8 = 0xFF;
    D_800DF218 = 0;
    D_800DF210 = allocateHeap(0x10000);
    z[0] = 0.0f;
    initializeTransformNode(D_800DF220, 0, z[0], z[0], z[0]);
    /* Same address as D_800DF220, spelled as an offset from D_800DF210 so the two call arguments are
       different RTL and CSE does not keep the address in s0 across the first call. */
    D_800DF224 = initPairedTransformNodes((u8 *)&D_800DF210 + 0x10, 0);
    D_800DF3A0 = -1;
    D_800DF30C = -1;
    D_800DF300 = 0;
    D_800DF304 = 0;
    D_800DF318 = 0;
    D_800DF314 = 0;
    D_800DF310 = 0;
    D_800DF308 = 0;
    D_800DF31C = &D_800D4ED8;
    *(s32 *)(D_8007E228 + 0x60C) = 0;
    D_80038AA4 = 0;
    D_800E79C4 = D_800D4ED8.a;
    D_800E9F70 = D_800D4ED8.b;
    func_800B807C(0x80, 0x80, D_800D4ED8.b);
    D_800E74E8 = 1;
    D_800EA0B4 = 0;
    D_800DF3A8 = 1;
    D_800DF3AC = 0;
}
