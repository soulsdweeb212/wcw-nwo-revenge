/* @header
 * setViSpecialFeatures  (originally func_80020F20)
 * VRAM 0x80020F20 | ROM 0x21B20 | size 0x164
 * asm: asm/nonmatchings/main/setViSpecialFeatures.s
 */
#include "common.h"

/* setViSpecialFeatures: applies a set of VI control-bit changes inside a
 * disabled-interrupts critical section. Each input bit clears/sets one bit
 * of the next VI context's control word; bit 0x40 replaces the 0x300 field
 * with 0x10000, and bit 0x80 copies that 0x300 field out of the next
 * display-list command word. Finally it marks the VI state's special-
 * features bit and restores interrupts. */
s32 nw2DisableInterrupts(void);
void nw2RestoreInterrupts(s32);

extern Nw2ViContext *__osViNext;

void setViSpecialFeatures(u32 features) {
    s32 mask;
    Nw2ViContext *p;
    s32 value;
    void *mode;

    mask = nw2DisableInterrupts();
    if (features & 1) {
        __osViNext->control |= 8;
    }
    if (features & 2) {
        __osViNext->control &= ~8;
    }
    if (features & 4) {
        __osViNext->control |= 4;
    }
    if (features & 8) {
        __osViNext->control &= ~4;
    }
    if (features & 0x10) {
        __osViNext->control |= 0x10;
    }
    if (features & 0x20) {
        __osViNext->control &= ~0x10;
    }
    if (features & 0x40) {
        __osViNext->control = (__osViNext->control | 0x10000) & ~0x300;
    }
    if (features & 0x80) {
        p = __osViNext;
        value = p->control;
        mode = p->mode;
        value &= ~0x10000;
        p->control = value;
        p->control = value | (*(s32 *)((u8 *)mode + 4) & 0x300);
    }
    __osViNext->state |= 8;
    nw2RestoreInterrupts(mask);
}
