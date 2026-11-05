/* @header
 * __osSiCreateAccessQueue  (originally func_800276F0)
 * VRAM 0x800276F0 | ROM 0x282F0 | size 0x54
 * asm: asm/nonmatchings/main/__osSiCreateAccessQueue.s
 */
/* SDK: libultra 2.0I, ultralib src/io/siacs.c (same code as the SDK source). */
#include "common.h"

typedef s32 M2C_UNK;
M2C_UNK osCreateMesgQueue(M2C_UNK *, M2C_UNK *, M2C_UNK);
M2C_UNK osSendMesg(M2C_UNK *, M2C_UNK, M2C_UNK);
extern s32 D_800388A0;
extern M2C_UNK D_80064AB0;
extern M2C_UNK D_8007E210;

/* Initializes the controller/Pak message queue. */
void __osSiCreateAccessQueue(void) {
    D_800388A0 = 1;
    osCreateMesgQueue(&D_8007E210, &D_80064AB0, 1);
    osSendMesg(&D_8007E210, 0, 0);
}
