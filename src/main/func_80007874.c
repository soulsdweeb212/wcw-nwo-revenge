/* @header
 * func_80007874
 * VRAM 0x80007874 | ROM 0x8474 | size 0xAC
 * asm: asm/nonmatchings/main/func_80007874.s
 */
#include "common.h"

void func_800015AC(void *, s8);

/* Initializes the object and its sub-record from descriptor arg3, copying the
 * packed descriptor bytes into the sub-record's size/offset fields. */
#ifdef TARGET_PC
/* PC: not ported yet. The display record side is ready (arg1 is an array of Nw2Descr4BA8, common.h), but this
 * function stores the record's vertices (fC) into the 0xDC-byte object's 4-byte field +0xC, and the vertices and arg2,
 * a display list, into its work block's 4-byte fields +0x30 and +0x34. That object and its work block have no PC
 * layout yet (docs/port.md, "Shared records on PC"), and a 64-bit address does not fit a 4-byte field, so
 * the PC stops the program here instead of storing half an address. */
void func_80007874(u8 *arg0, s32 arg1, s32 arg2, s16 arg3) {
    (void)arg0;
    (void)arg1;
    (void)arg2;
    (void)arg3;
    port_fatal("func_80007874: the 0xDC-byte object record has no PC layout yet");
}
#else
void func_80007874(u8 *arg0, s32 arg1, s32 arg2, s16 arg3) {
    u8 *t = (u8 *)(arg3 * 0x2C + arg1);
    s32 *p;
    s32 v;

    arg0[0x1A] = t[6];
    *(s32 *)(arg0 + 0xC) = *(s32 *)(t + 0xC);
    func_800015AC(arg0, t[2]);
    p = *(s32 **)(arg0 + 0x14);
    p[0] = 1;
    p[0xC] = 0;
    p[0xD] = 0;
    *(s16 *)((u8 *)p + 0x2C) = (s8)t[2];
    *(s16 *)((u8 *)p + 0x2E) = (s8)t[3];
    v = *(s32 *)(t + 0xC);
    *(s32 *)((u8 *)p + 0x34) = arg2;
    *(s32 *)((u8 *)p + 0x30) = v;
}
#endif
