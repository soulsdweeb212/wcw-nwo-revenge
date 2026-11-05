/* @header
 * osScRemoveClient  (originally func_80000D80)
 * VRAM 0x80000D80 | ROM 0x1980 | size 0x80
 * asm: asm/nonmatchings/main/osScRemoveClient.s
 */
/* SDK: libultra 2.0I, ultralib src/sched/sched.c (SDK code with changes, see docs/sdk_functions.md). */
#include "common.h"

extern void func_80090000(void);

extern void bzero(void *, s32);
extern void osEPiLinkHandle(void *);
extern u8 D_8003DDB8[];
extern u8 D_8003DDBC, D_8003DDBD, D_8003DDBE, D_8003DDBF, D_8003DDC0, D_8003DDC1;
extern s32 D_8003DDC4, D_8003DDC8;

extern s32 osSetIntMask(s32);

/* Unlinks arg1 from arg0's +0x260 listener list under the message lock. */
void osScRemoveClient(u8 *arg0, u8 *arg1) {
    u8 *v1;
    u8 *prev;
    s32 state;
    state = osSetIntMask(1);
    v1 = *(u8 **)(arg0 + 0x260);
    prev = NULL;
    if (v1 != NULL) {
        do {
            if (v1 == arg1) {
                if (prev != NULL) {
                    *(u8 **)prev = *(u8 **)v1;
                } else {
                    *(u8 **)(arg0 + 0x260) = *(u8 **)v1;
                }
                break;
            }
            prev = v1;
            v1 = *(u8 **)v1;
        } while (v1 != NULL);
    }
    osSetIntMask(state);
}

extern s32 osRecvMesg(u8 *, s32, s32);
extern s32 osViGetCurrentFramebuffer(void);
extern s32 osViGetNextFramebuffer(void);
extern u8 D_800441D8[];
