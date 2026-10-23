#include "common.h"

extern void func_80090000(void);

/* No-op stub (calls func_80090000). */
void func_8000082C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_80090000();
}

extern void func_80021F60(void *, s32);
extern void func_80021A50(void *);
extern u8 D_8003DDB8[];
extern u8 D_8003DDBC, D_8003DDBD, D_8003DDBE, D_8003DDBF, D_8003DDC0, D_8003DDC1;
extern s32 D_8003DDC4, D_8003DDC8;

/* Lazily initializes the D_8003DDB8 control block (magic 0xA8000000 and its
 * field defaults) and returns its address. */
void *func_80000A40(void) {
    u8 *p = (u8 *)&D_8003DDC4;
    if (*(s32 *)p != 0xA8000000) {
        D_8003DDBC = 3;
        *(s32 *)p = 0xA8000000;
        D_8003DDBD = 5;
        D_8003DDC0 = 0xC;
        D_8003DDBE = 0xD;
        D_8003DDBF = 2;
        D_8003DDC1 = 1;
        D_8003DDC8 = 0;
        func_80021F60(p + 8, 0x60);
        p -= 0xC;
        func_80021A50(p);
    }
    return &D_8003DDB8;
}

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

/* Blocks until the RSP queue is empty and neither of the two task ids equals the
 * object's +0xC value. */
void func_800011D4(u8 *arg0) {
    s32 v = *(s32 *)(arg0 + 0xC);
    while (func_8001C990(D_800441D8, 0, 0) != -1) { }
    for (;;) {
        if (func_80020DF0() == v || func_80020E30() == v) {
            func_8001C990(D_800441D8, 0, 1);
        } else break;
    }
}
