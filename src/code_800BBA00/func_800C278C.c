/* @header
 * func_800C278C
 * VRAM 0x800C278C | ROM 0xB5C2C | size 0xA4
 * asm: asm/nonmatchings/code_800BBA00/func_800C278C.s
 */
#include "common.h"

extern u8 D_8007EF30[];
extern u8 D_800FABE8[], D_800FABEC[], D_800FABEE[];
extern s16 D_800EB4D0[];
void func_800D2638(void *, u16, f32);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D2B64 */
s32 func_800D2B64(void *, f32, u16, s32);
#endif

/* Pushes w along one axis: axis mask 0x300 (X), or 0xC00 (Z) when w->dirIndex
 * bit 0 is set. First func_800D2638(w, mask, 4.0f) pushes it out of the other
 * wrestlers along that axis; then, with WR_FLAG_IN_RING temporarily set in
 * w->flags (so the ring box is used), func_800D2B64(w, divisor, mask, 0xFFFFE)
 * corrects it against the boundary using the pelvis and jointA[2..19]. The
 * previous flags are restored. */
void func_800C278C(Wrestler *w, f32 divisor) {
    u16 mask = 0x300;
    u64 flags;
    if (w->dirIndex & 1) mask = 0xC00;
    func_800D2638(w, mask, 4.0f);
    flags = w->flags;
    w->flags = flags | WR_FLAG_IN_RING;
    func_800D2B64(w, divisor, mask, 0xFFFFE);
    w->flags = flags;
}
