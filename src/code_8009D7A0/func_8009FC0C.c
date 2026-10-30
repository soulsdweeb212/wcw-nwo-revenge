/* @header
 * func_8009FC0C
 * VRAM 0x8009FC0C | ROM 0x930AC | size 0xB0
 * asm: asm/nonmatchings/code_8009D7A0/func_8009FC0C.s
 */
#include "common.h"

s32 func_800A7D1C(void *, s32);
s32 func_800A7F6C(s32, s32);
s32 func_800A837C(s32);
s32 beginEntityActionA8D8C(void *);
s32 func_800B68A0(void *, s32, void *);
s32 func_800C472C(s32, void *, s32);
s32 func_800D427C(void *, s32, s32);
s32 func_800D4AD0(void *);
extern void *D_800EB408;
extern s32 D_800EB40C;

/* Play animation 0x1067 on the entity; once its action timer (+0x4) has expired,
 * run the detach/release sequence: stop the target's actions, transfer control,
 * then complete and hand the action off to the target. */
void func_8009FC0C(void) {
    func_800D427C(D_800EB408, 0x1067, 3);
    if (*(s16 *)((u8 *)D_800EB408 + 4) <= 0) {
        func_800A7F6C(D_800EB40C, 0x52);
        func_800A837C(D_800EB40C);
        func_800A7D1C(D_800EB408, 0xA);
        func_800B68A0(D_800EB408, D_800EB40C, D_800EB408);
        func_800D4AD0(D_800EB408);
        beginEntityActionA8D8C(D_800EB408);
        func_800C472C(D_800EB40C, D_800EB408, 2);
    }
}
