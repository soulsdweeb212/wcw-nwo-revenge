#include "common.h"

extern void func_80090000(void);

extern void func_80021F60(void *, s32);
extern void func_80021A50(void *);
extern u8 D_8003DDB8[];
extern u8 D_8003DDBC, D_8003DDBD, D_8003DDBE, D_8003DDBF, D_8003DDC0, D_8003DDC1;
extern s32 D_8003DDC4, D_8003DDC8;

extern s32 func_8001C740(s32);

/* Unlinks arg1 from arg0's +0x260 listener list under the message lock. */
void func_80000D80(u8 *arg0, u8 *arg1) {
    u8 *v1;
    u8 *prev;
    s32 state;
    state = func_8001C740(1);
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
    func_8001C740(state);
}

extern s32 func_8001C990(u8 *, s32, s32);
extern s32 func_80020DF0(void);
extern s32 func_80020E30(void);
extern u8 D_800441D8[];
