/* @header
 * _collectPVoices  (originally func_80020800)
 * VRAM 0x80020800 | ROM 0x21400 | size 0x54
 * asm: asm/nonmatchings/main/_collectPVoices.s
 */
/* SDK: libultra 2.0I, ultralib src/audio/synthesizer.c (same code as the SDK source). */
#include "common.h"

extern u8 hdwrBugFlag;

s32 osVirtualToPhysical(s32);
s32 __osAiDeviceBusy(void);
s32 alLink(s32, void *);
s32 alUnlink(s32);

/* Move every child node at arg0+0x14 onto the list head arg0+4. */
void _collectPVoices(u8 *arg0) {
    s32 node;

    node = *(s32 *)(arg0 + 0x14);
    if (node != 0) {
        do {
            alUnlink(node);
            alLink(node, arg0 + 4);
            node = *(s32 *)(arg0 + 0x14);
        } while (node != 0);
    }
}
