/* @header
 * func_80021640
 * VRAM 0x80021640 | ROM 0x22240 | size 0x8C
 * asm: asm/nonmatchings/main/func_80021640.s
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

s32 __osCheckId(s32);
s32 func_80027950(void);
s32 func_80026E60(s32, void *, s32);
s32 func_8001CAC0(s32, void *, s32);

/* Copies the Pak's stored 32-byte name from arg0 into arg1, returning its
 * length in *arg2 (or 5/2 on bad arguments/id). */
s32 func_80021640(s32 arg0, u8 *arg1, s32 *arg2) {
    s32 i;
    u8 c;

    if (arg1 == NULL) {
        return 5;
    }
    if (__osCheckId(arg0) == 2) {
        return 2;
    }
    for (i = 0; i < 0x20; i++) {
        c = ((u8 *)arg0)[0x2C + i];
        if (c == 0) {
            break;
        }
        *arg1++ = c;
    }
    *arg2 = i;
    return 0;
}
