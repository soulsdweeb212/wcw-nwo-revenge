/* @header
 * func_80007818
 * VRAM 0x80007818 | ROM 0x8418 | size 0x5C
 * asm: asm/nonmatchings/main/func_80007818.s
 */
#include "common.h"

void func_800015AC(void *, s8);

/* Initialize `obj` from the 0x2C-byte descriptor `index` in the table at
 * descriptorBase: copy the descriptor's +0xC into the object's +0xC, set the
 * object's +0x10 to arg2, attach the work block with the descriptor's mode byte,
 * then clear the work block's first word. */
#ifdef TARGET_PC
/* PC: not ported yet. The display record side is ready (descriptorBase is an array of Nw2Descr4BA8, common.h), but this
 * function stores the record's vertices (fC) and arg2, a display list, into the 0xDC-byte object's 4-byte fields +0xC
 * and +0x10, and clears the first word of its work block (+0x14). That object has no PC layout yet (docs/port.md,
 * "Shared records on PC"), and a 64-bit address does not fit a 4-byte field, so the PC stops the program here instead
 * of storing half an address. */
void func_80007818(u8 *obj, s32 descriptorBase, s32 arg2, s16 index) {
    (void)obj;
    (void)descriptorBase;
    (void)arg2;
    (void)index;
    port_fatal("func_80007818: the 0xDC-byte object record has no PC layout yet");
}
#else
void func_80007818(u8 *obj, s32 descriptorBase, s32 arg2, s16 index) {
    u8 *t = (u8 *)(index * 0x2C + descriptorBase);
    s32 v = *(s32 *)(t + 0xC);

    *(s32 *)(obj + 0x10) = arg2;
    *(s32 *)(obj + 0xC) = v;
    func_800015AC(obj, t[2]);
    *(s32 *)(*(s32 **)(obj + 0x14)) = 0;
}
#endif
