/* @header
 * func_800219B0
 * VRAM 0x800219B0 | ROM 0x225B0 | size 0x94
 * asm: asm/nonmatchings/main/func_800219B0.s
 */
#include "common.h"

typedef struct {
    u8 b0, b1, b2, b3, b4, b5, b6, b7;
} Cmd8;

extern Cmd8 D_8006A260[];
extern u8 D_80070A98;
extern u8 D_8007BD30;
extern Cmd8 D_8007DFD0[];
extern s32 D_8007E00C;
extern s32 D_80037600;

s32 func_80027950(void);
s32 func_80026E60(s32, void *, s32);
s32 func_8001CAC0(s32, void *, s32);

/* Sends the controller command arg1 (of type arg2, channel arg0) to the
 * controller queue. Returns -1 when the controller system is unavailable. */
s32 func_800219B0(s32 arg0, u8 *arg1, s32 arg2) {
    if (D_80037600 == 0) {
        return -1;
    }
    *(s32 *)(arg1 + 0x14) = arg0;
    if (arg2 == 0) {
        *(s16 *)arg1 = 0xF;
    } else {
        *(s16 *)arg1 = 0x10;
    }
    if (arg1[2] != 1) {
        return func_8001CAC0(func_80027950(), arg1, 0);
    }
    return func_80026E60(func_80027950(), arg1, 0);
}
