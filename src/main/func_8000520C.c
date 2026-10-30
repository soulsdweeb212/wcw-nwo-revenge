/* @header
 * func_8000520C
 * VRAM 0x8000520C | ROM 0x5E0C | size 0xF8
 * asm: asm/nonmatchings/main/func_8000520C.s
 */
#include "common.h"

s32 releaseHeapBlock(s32);
s32 func_800015AC(void *, s32);

typedef struct {
    u8 pad0[0x10];
    s32 f10;   /* @0x10: buffer owned by arg0 */
} Holder520C;

typedef struct {
    u8 active;     /* @0x0: block-in-use flag */
    u8 pad1[0xB];
    s32 fC;        /* @0xC */
    s32 f10;       /* @0x10 */
    s32 f14;       /* @0x14 */
    s32 f18;       /* @0x18 */
    s32 f1C;       /* @0x1C */
    u8 pad20[8];
    s32 f28;       /* @0x28: shared-ownership flag */
} ResBlock520C;

/* If the resource block arg1 is active, deactivate it, free arg0's buffer at
 * +0x10 and clear it, run func_800015AC(arg0, 0), then free each of arg1's
 * buffer pointers (+0xC/+0x10/+0x14/+0x18/+0x1C) and clear it. Pointers whose
 * block has the shared-ownership flag +0x28 set are left alone. */
void func_8000520C(Holder520C *arg0, ResBlock520C *arg1) {
    s32 temp;

    if (arg1->active != 0) {
        arg1->active = 0;
        temp = arg0->f10;
        if (temp != 0) {
            releaseHeapBlock(temp);
            arg0->f10 = 0;
        }
        func_800015AC(arg0, 0);
        temp = arg1->fC;
        if (temp != 0) {
            if (arg1->f28 == 0) {
                releaseHeapBlock(temp);
            }
            arg1->fC = 0;
        }
        temp = arg1->f10;
        if (temp != 0) {
            if (arg1->f28 == 0) {
                releaseHeapBlock(temp);
            }
            arg1->f10 = 0;
        }
        temp = arg1->f14;
        if (temp != 0) {
            if (arg1->f28 == 0) {
                releaseHeapBlock(temp);
            }
            arg1->f14 = 0;
        }
        temp = arg1->f18;
        if (temp != 0) {
            releaseHeapBlock(temp);
            arg1->f18 = 0;
        }
        temp = arg1->f1C;
        if (temp != 0) {
            releaseHeapBlock(temp);
            arg1->f1C = 0;
        }
    }
}
