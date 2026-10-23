#include "common.h"

extern u8 gControllerPakBankBuffers[];
extern u8 D_800625FC[];
extern u8 D_8007BD30;

s32 func_8001C990(void *, void *, s32);
s32 func_80025810(s32, void *);
void func_80027744(void);
void func_800277B0(void);

typedef struct {
    u32 flags;
    void *queue;
    s32 index;
} Nw2Obj232A0;

/* Fills Controller Pak bank o->index with arg1 (a 0 or 0xEB erase value),
 * issues the read/write transaction and verifies the response. Returns 5 when
 * the object's 0x8 flag is clear, 4 on a mismatched verification byte, else 0. */
s32 writeControllerPakBank(Nw2Obj232A0 *o, s32 arg1) {
    u8 *p;
    u8 *q;
    s32 i;
    s32 ret;

    p = &gControllerPakBankBuffers[o->index << 6];
    if (!(o->flags & 8)) {
        return 5;
    }
    func_80027744();
    *(s32 *)(D_800625FC + (o->index << 6)) = 1;
    p += o->index;
    i = 0x1F;
    q = p + 0x1F;
    do {
        q[6] = arg1;
        i--;
        q--;
    } while (i >= 0);
    D_8007BD30 = 0xFE;
    func_80025810(1, &gControllerPakBankBuffers[o->index << 6]);
    func_8001C990(o->queue, NULL, 1);
    func_80025810(0, &gControllerPakBankBuffers[o->index << 6]);
    func_8001C990(o->queue, NULL, 1);
    ret = p[2] & 0xC0;
    if (ret == 0) {
        if (arg1 == 0) {
            if (p[0x26] != 0) {
                ret = 4;
            }
        } else {
            if (p[0x26] != 0xEB) {
                ret = 4;
            }
        }
    }
    func_800277B0();
    return ret;
}
