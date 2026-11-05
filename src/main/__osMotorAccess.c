/* @header
 * __osMotorAccess  (originally func_800232A0)
 * VRAM 0x800232A0 | ROM 0x23EA0 | size 0x144
 * asm: asm/nonmatchings/main/__osMotorAccess.s
 */
/* SDK: libultra 2.0I, ultralib src/io/motor.c (same code as the SDK source). */
#include "common.h"

extern u8 gControllerPakBankBuffers[];
extern u8 D_800625FC[];
extern u8 D_8007BD30;

s32 osRecvMesg(void *, void *, s32);
s32 __osSiRawStartDma(s32, void *);
void __osSiGetAccess(void);
void __osSiRelAccess(void);

typedef struct {
    u32 flags;
    void *queue;
    s32 index;
} Nw2Obj232A0;

/* Fills Controller Pak bank o->index with arg1 (a 0 or 0xEB erase value),
 * issues the read/write transaction and verifies the response. Returns 5 when
 * the object's 0x8 flag is clear, 4 on a mismatched verification byte, else 0. */
s32 __osMotorAccess(Nw2Obj232A0 *o, s32 arg1) {
    u8 *p;
    u8 *q;
    s32 i;
    s32 ret;

    p = &gControllerPakBankBuffers[o->index << 6];
    if (!(o->flags & 8)) {
        return 5;
    }
    __osSiGetAccess();
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
    __osSiRawStartDma(1, &gControllerPakBankBuffers[o->index << 6]);
    osRecvMesg(o->queue, NULL, 1);
    __osSiRawStartDma(0, &gControllerPakBankBuffers[o->index << 6]);
    osRecvMesg(o->queue, NULL, 1);
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
    __osSiRelAccess();
    return ret;
}
