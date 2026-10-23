#include "common.h"

void func_800015AC(void *, s8);

/* Initialize `obj` from the 0x2C-byte descriptor `index` in the table at
 * descriptorBase: copy the descriptor's +0xC into the object's +0xC, set the
 * object's +0x10 to arg2, attach the work block with the descriptor's mode byte,
 * then clear the work block's first word. */
void func_80007818(u8 *obj, s32 descriptorBase, s32 arg2, s16 index) {
    u8 *t = (u8 *)(index * 0x2C + descriptorBase);
    s32 v = *(s32 *)(t + 0xC);

    *(s32 *)(obj + 0x10) = arg2;
    *(s32 *)(obj + 0xC) = v;
    func_800015AC(obj, t[2]);
    *(s32 *)(*(s32 **)(obj + 0x14)) = 0;
}

/* As func_80007818, but also record the descriptor's +6 byte at obj+0x1A and seed
 * the work block's flags/counts from the descriptor. */
void func_80007874(u8 *obj, s32 descriptorBase, s32 arg2, s16 index) {
    u8 *t = (u8 *)(index * 0x2C + descriptorBase);
    s32 *p;
    s32 v;

    obj[0x1A] = t[6];
    *(s32 *)(obj + 0xC) = *(s32 *)(t + 0xC);
    func_800015AC(obj, t[2]);
    p = *(s32 **)(obj + 0x14);
    p[0] = 1;
    p[0xC] = 0;
    p[0xD] = 0;
    *(s16 *)((u8 *)p + 0x2C) = (s8)t[2];
    *(s16 *)((u8 *)p + 0x2E) = (s8)t[3];
    v = *(s32 *)(t + 0xC);
    *(s32 *)((u8 *)p + 0x34) = arg2;
    *(s32 *)((u8 *)p + 0x30) = v;
}

/* Convert 16 16-bit color words according to mode (arg1 & 0xFF): mode 1 shifts the
 * red channel, mode 0 the green channel, otherwise a 4-bit expansion; the result
 * keeps the low byte and sets 0xFF00. */
void func_80007960(u16 *arg0, s32 arg1) {
    s32 mode = arg1 & 0xFF;
    u32 i;
    u32 v;

    i = 0;
    do {
        switch (mode) {
        case 1:
            v = *arg0 >> 3;
            break;
        case 0:
            v = *arg0 >> 8;
            break;
        default:
            v = *arg0 << 2;
            break;
        }
        v &= 0xF8;
        if (v & 0xFFFF) {
            v += 7;
        }
        *arg0 = v | 0xFF00;
        i++;
        arg0++;
    } while (i < 16);
}
