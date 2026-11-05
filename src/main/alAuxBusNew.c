/* @header
 * alAuxBusNew  (originally func_8001D620)
 * VRAM 0x8001D620 | ROM 0x1E220 | size 0x5C
 * asm: asm/nonmatchings/main/alAuxBusNew.s
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

/* Initialize a 6-callback audio-mixer node, storing arg2/arg1 at +0x18/+0x1C. */
void alAuxBusNew(u8 *arg0, s32 arg1, s32 arg2) {
    alFilterNew(arg0, alAuxBusPull, alAuxBusParam, 6);
    *(s32 *)(arg0 + 0x14) = 0;
    *(s32 *)(arg0 + 0x18) = arg2;
    *(s32 *)(arg0 + 0x1C) = arg1;
}
