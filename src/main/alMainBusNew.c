/* @header
 * alMainBusNew  (originally func_8001D67C)
 * VRAM 0x8001D67C | ROM 0x1E27C | size 0x5C
 * asm: asm/nonmatchings/main/alMainBusNew.s
 */
/* SDK: libultra 2.0I, ultralib src/audio/drvrnew.c (same code as the SDK source). */
#include "common.h"

extern void alFilterNew(void *obj, void *f1, void *f2, s32 n);
extern s32 alSavePull();
extern s32 alSaveParam();
extern s32 alMainBusPull();
extern s32 alMainBusParam();
extern s32 alAuxBusPull();
extern s32 alAuxBusParam();

/* Initialize a 7-callback node, storing arg2/arg1 at +0x18/+0x1C. */
void alMainBusNew(u8 *arg0, s32 arg1, s32 arg2) {
    alFilterNew(arg0, alMainBusPull, alMainBusParam, 7);
    *(s32 *)(arg0 + 0x14) = 0;
    *(s32 *)(arg0 + 0x18) = arg2;
    *(s32 *)(arg0 + 0x1C) = arg1;
}
