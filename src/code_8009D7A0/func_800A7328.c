/* @header
 * func_800A7328
 * VRAM 0x800A7328 | ROM 0x9A7C8 | size 0x3C
 * asm: asm/nonmatchings/code_8009D7A0/func_800A7328.s
 */
#include "common.h"

void func_800D3838(void *, void *, s16, void *);

void func_800D36B4(void *, void *, void *);
void translateEntityXZ(void *, void *);

/* Takes the delta from the root position (x, y, z) to the pelvis joint (jointA[1]) and passes it to
 * translateEntityXZ, which shifts the root x/z and the joints by its XZ part: the root lands under where the
 * pelvis was. */
void func_800A7328(Wrestler *w) {
    u8 sp10[0x10];

    func_800D36B4(&w->x, &w->jointA[1], sp10);
    translateEntityXZ(w, sp10);
}

s32 func_800D3550(s32);
s32 func_800D35B0(s32, s32);
s32 func_800D3684(s32, s32);
