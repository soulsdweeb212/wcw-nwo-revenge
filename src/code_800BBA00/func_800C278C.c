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
s32 func_800D2B64(void *, f32, u16, s32);

/* Begin an action on `entity`: choose a channel mask (0x300, or 0xC00 when the
 * entity's +0x3E bit0 is set), open it at position 4.0 via func_800D2638 with
 * the "active" flag 0x40 set on the +0x20 u64, then run func_800D2B64 with
 * `pitch` and volume 0xFFFFE and restore the previous flags. */
void func_800C278C(void *entity, f32 pitch) {
    u16 mask = 0x300;
    u64 flags;
    if (*(u16 *)((u8 *)entity + 0x3E) & 1) mask = 0xC00;
    func_800D2638(entity, mask, 4.0f);
    flags = *(u64 *)((u8 *)entity + 0x20);
    *(u64 *)((u8 *)entity + 0x20) = flags | 0x40;
    func_800D2B64(entity, pitch, mask, 0xFFFFE);
    *(u64 *)((u8 *)entity + 0x20) = flags;
}
