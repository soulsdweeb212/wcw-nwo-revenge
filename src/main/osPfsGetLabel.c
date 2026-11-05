/* @header
 * osPfsGetLabel  (originally func_80021640)
 * VRAM 0x80021640 | ROM 0x22240 | size 0x8C
 * asm: asm/nonmatchings/main/osPfsGetLabel.s
 */
/* SDK: libultra 2.0I, ultralib src/io/pfsgetlabel.c (same code as the SDK source). */
#include "common.h"

typedef struct {
    u8 b0, b1, b2, b3, b4, b5, b6, b7;
} Cmd8;

extern Cmd8 __osContPifRam[];
extern u8 __osMaxControllers;
extern u8 __osContLastCmd;
extern Cmd8 __osPfsPifRam[];
extern s32 D_8007E00C;
extern s32 __osPiDevMgr;

s32 __osCheckId(s32);
s32 osPiGetCmdQueue(void);
s32 osJamMesg(s32, void *, s32);
s32 osSendMesg(s32, void *, s32);

/* Copies the Pak's stored 32-byte name from arg0 into arg1, returning its
 * length in *arg2 (or 5/2 on bad arguments/id). */
s32 osPfsGetLabel(s32 arg0, u8 *arg1, s32 *arg2) {
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
