/* @header
 * osPfsInit  (originally func_800215A0)
 * VRAM 0x800215A0 | ROM 0x221A0 | size 0x9C
 * asm: asm/nonmatchings/main/osPfsInit.s
 */
/* SDK: libultra 2.0I, ultralib src/io/pfsinit.c (same code as the SDK source). */
#include "common.h"

extern u8 D_80070A98;
extern u8 D_8007BD30;
extern s32 D_8006A298;
extern s32 D_8006A29C;

typedef struct {
    u8 b0, b1, b2, b3, b4, b5, b6, b7;
} Cmd8;
extern Cmd8 D_8006A260[];

extern void __osSiGetAccess(void);
extern void __osSiRelAccess(void);
extern s32 __osPfsGetStatus(s32, s32);
extern s32 __osGetId(void *);
extern s32 osPfsChecker(void *);

/* Initializes a Controller Pak handle arg1 for channel arg0: records the channel
 * and query id, reads the Pak id and runs the file-system checker. Returns the
 * first error encountered. */
s32 osPfsInit(s32 arg0, u8 *arg1, s32 arg2) {
    s32 ret;

    __osSiGetAccess();
    ret = __osPfsGetStatus(arg0, arg2);
    __osSiRelAccess();
    if (ret != 0) {
        return ret;
    }
    *(s32 *)(arg1 + 4) = arg0;
    *(s32 *)(arg1 + 8) = arg2;
    *(s32 *)(arg1 + 0) = 0;
    arg1[0x65] = 0xFF;
    ret = __osGetId(arg1);
    if (ret != 0) {
        return ret;
    }
    ret = osPfsChecker(arg1);
    *(s32 *)arg1 |= 1;
    return ret;
}
