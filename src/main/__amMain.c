/* @header
 * __amMain  (originally func_80016EDC)
 * VRAM 0x80016EDC | ROM 0x17ADC | size 0x13C
 * asm: asm/nonmatchings/main/__amMain.s
 */
/* SDK: the SDK demo audio manager (n64-demos simple/src/main/audiomgr.c) as adapted in this old libmus (SDK code
 * with changes, see docs/sdk_functions.md). */
#include "common.h"

extern s32 D_80036F34, D_80036F44, D_80062558;
extern u8 D_8006E370[], D_8006E3E0[];
void osScAddClient(s32, void *, void *);
s32 osRecvMesg(void *, void *, s32);
s32 __amHandleFrameMsg(s32, s32);
void n_alClose(void *);
typedef struct { s16 type, pad; s32 value; } AudioMessage;

void __amMain(void) {
    u8 client[8];
    AudioMessage *msg;
    s32 done = 0;
    s32 type;

    osScAddClient(D_80062558, client, D_8006E370);
    do {
        osRecvMesg(D_8006E370, &msg, 1);
        osRecvMesg(D_8006E370, 0, 0);
        type = msg->type;
        switch ((s16)type) {
        case 1:
            if (__amHandleFrameMsg(((s32 *)(D_8006E370 - 0x1C0))[D_80036F34], D_80036F44)) {
                osRecvMesg(D_8006E370 + 0x38, &msg, 1);
                D_80036F34 = (D_80036F34 + 1) & 3;
                D_80036F44 = msg->value;
            }
            break;
        case 4:
            break;
        case 10:
            done = 1;
            break;
        }
    } while (!done);
    n_alClose(D_8006E3E0);
}
