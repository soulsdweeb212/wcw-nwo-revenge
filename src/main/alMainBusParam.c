/* @header
 * alMainBusParam  (originally func_8001F1D0)
 * VRAM 0x8001F1D0 | ROM 0x1FDD0 | size 0x30
 * asm: asm/nonmatchings/main/alMainBusParam.s
 */
/* SDK: libultra 2.0I, ultralib src/audio/mainbus.c (same code as the SDK source). */
#include "common.h"

/* Audio callback: on message 2, append arg2 to the object's argument array. */
s32 alMainBusParam(u8 *arg0, s32 arg1, s32 arg2) {
    s32 idx;
    s32 *arr = *(s32 **)(arg0 + 0x1C);

    if (arg1 == 2) {
        idx = *(s32 *)(arg0 + 0x14);
        *(s32 *)(arg0 + 0x14) = idx + 1;
        arr[idx] = arg2;
    }
    return 0;
}

extern void alFilterNew(void *f1, void *f2, s32 n);
extern s32 alSavePull();
extern s32 alSaveParam();
extern s32 alMainBusPull();
extern s32 alMainBusParam();
extern s32 alAuxBusPull();
