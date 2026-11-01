/* @header
 * func_800C51A0
 * VRAM 0x800C51A0 | ROM 0x71910 | size 0x74
 * asm: asm/nonmatchings/code_80090000/func_800C51A0.s
 */
#include "common.h"

extern s32 D_800DF3C0;
extern s32 D_800E79B8;
void func_8000CD84(s16);
void func_80008AF0(void);
void func_80011264(void);
void func_8000EDE0(void);
void releaseHeapBlock(s32);

void func_800C51A0(void) {
    s32 i;
    for (i = 0; i < D_800DF3C0; i++) {
        func_8000CD84(i);
    }
    func_80008AF0();
    func_80011264();
    func_8000EDE0();
    releaseHeapBlock(D_800E79B8);
}
