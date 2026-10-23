#include "common.h"

extern s32 nw2DisableInterrupts(void);
extern void nw2RestoreInterrupts(s32);
extern s32 func_80027380(void);
extern void *__osViNext;

/* Read the pending VI framebuffer's +4 field with interrupts disabled. */
s32 func_80020E30(void) {
    s32 temp;
    s32 val;

    temp = nw2DisableInterrupts();
    val = *(s32 *)((u8 *)__osViNext + 4);
    nw2RestoreInterrupts(temp);
    return val;
}

/* Update arg0's +4 status from the hardware VI status: when status bit 0x80 is set,
 * OR in the retrace bit (bit 8) and clear bit 1; return the retrace bit. */
s32 func_80020DA0(void *arg0) {
    u32 v;
    s32 a0;

    v = func_80027380();
    a0 = (v >> 8) & 1;
    if (v & 0x80) {
        *(s32 *)((u8 *)arg0 + 4) = (*(s32 *)((u8 *)arg0 + 4) | a0) & ~2;
    }
    return a0;
}

/* Point the pending VI framebuffer at arg0, mark it ready and copy its +4 field. */
void func_80020ED0(void *arg0) {
    s32 temp;
    void *p;
    void *a1;

    temp = nw2DisableInterrupts();
    p = __osViNext;
    *(void **)((u8 *)p + 8) = arg0;
    a1 = *(void **)((u8 *)p + 8);
    *(s16 *)((u8 *)p + 0) = 1;
    *(s32 *)((u8 *)p + 0xC) = *(s32 *)((u8 *)a1 + 4);
    nw2RestoreInterrupts(temp);
}

/* Set or clear bit 0x20 of the pending VI framebuffer's status, with interrupts off. */
void func_80021130(s32 arg0) {
    s32 temp;
    u16 *p;
    u16 v;

    temp = nw2DisableInterrupts();
    if (arg0 & 0xFF) {
        p = __osViNext;
        v = *p | 0x20;
    } else {
        p = __osViNext;
        v = *p & 0xFFDF;
    }
    *p = v;
    nw2RestoreInterrupts(temp);
}
