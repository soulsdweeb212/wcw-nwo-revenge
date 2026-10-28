#include "common.h"

extern u8 D_80070A98;
extern u8 D_8007BD30;
extern s32 D_8006A298;
extern s32 D_8006A29C;

typedef struct {
    u8 b0, b1, b2, b3, b4, b5, b6, b7;
} Cmd8;
extern Cmd8 D_8006A260[];

extern void func_80027744(void);
extern void func_800277B0(void);
extern s32 func_80024640(s32, s32);
extern s32 readControllerPakId(void *);
extern s32 osPfsChecker(void *);

/* Initializes a Controller Pak handle arg1 for channel arg0: records the channel
 * and query id, reads the Pak id and runs the file-system checker. Returns the
 * first error encountered. */
s32 func_800215A0(s32 arg0, u8 *arg1, s32 arg2) {
    s32 ret;

    func_80027744();
    ret = func_80024640(arg0, arg2);
    func_800277B0();
    if (ret != 0) {
        return ret;
    }
    *(s32 *)(arg1 + 4) = arg0;
    *(s32 *)(arg1 + 8) = arg2;
    *(s32 *)(arg1 + 0) = 0;
    arg1[0x65] = 0xFF;
    ret = readControllerPakId(arg1);
    if (ret != 0) {
        return ret;
    }
    ret = osPfsChecker(arg1);
    *(s32 *)arg1 |= 1;
    return ret;
}
