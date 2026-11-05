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
extern s32 __osSiAccessQueueEnabled;
extern M2C_UNK siAccessBuf;
extern M2C_UNK __osSiAccessQueue;

/* Initializes the controller/Pak message queue. */
void __osSiCreateAccessQueue(void) {
    __osSiAccessQueueEnabled = 1;
    osCreateMesgQueue(&__osSiAccessQueue, &siAccessBuf, 1);
    osSendMesg(&__osSiAccessQueue, 0, 0);
}
