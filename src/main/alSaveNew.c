/* @header
 * alSaveNew  (originally func_8001D6D8)
 * VRAM 0x8001D6D8 | ROM 0x1E2D8 | size 0x44
 * asm: asm/nonmatchings/main/alSaveNew.s
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

/* Initialize a 3-callback node, clearing +0x14 and setting +0x18 = 1. */
void alSaveNew(u8 *arg0) {
    alFilterNew(arg0, alSavePull, alSaveParam, 3);
    *(s32 *)(arg0 + 0x14) = 0;
    *(s32 *)(arg0 + 0x18) = 1;
}
