/* @header
 * func_800A7D1C
 * VRAM 0x800A7D1C | ROM 0x9B1BC | size 0x48
 * asm: asm/nonmatchings/code_8009D7A0/func_800A7D1C.s
 */
#include "common.h"

s32 func_800D36E8(f32, f32);
void unpackAnimationParameters(void *, void *);
extern u8 D_8007BD64[];
void func_800D4AD0(void *);
void func_800D3890(void *, void *, void *);
/* Sets the wrestler's current move: moveId = moveId, moveOwnerId = its own id, and unpacks the 0x18-byte entry
 * D_8007BD64 + 0x14 + moveId*0x18 into w->move. */
void func_800A7D1C(Wrestler *w, s16 moveId) {
    w->moveId = moveId;
    w->moveOwnerId = w->id;
    unpackAnimationParameters(&w->move, D_8007BD64 + 0x14 + moveId * 0x18);
}
