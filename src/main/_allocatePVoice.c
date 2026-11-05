/* @header
 * _allocatePVoice  (originally func_80017700)
 * VRAM 0x80017700 | ROM 0x18300 | size 0xC0
 * asm: asm/nonmatchings/main/_allocatePVoice.s
 */
/* SDK: n_audio, libnaudio/src/n_synallocvoice.c (same code as the SDK source). */
#include "common.h"

extern s32 *D_80036F54;
void alUnlink(void *);
void alLink(void *, void *);

/* Pick a free audio voice node for arg1 and return it via *arg0: prefer the reserved
 * D_80036F54[5] node, else D_80036F54[1], and move it onto the busy list via
 * alUnlink/alLink; otherwise scan the free list at D_80036F54[3] for the first
 * node whose descriptor id ((*node-to-be)+0x16) is <= arg1 and whose +0x88 time is zero,
 * updating arg1 to that node's id and returning 1 on success (0 if none found). */
s32 _allocatePVoice(void **arg0, s16 arg1) {
    s32 r = 0;
    u8 *p;

    p = (u8 *)D_80036F54[5];
    if (p != NULL || (p = (u8 *)D_80036F54[1]) != NULL) {
        *arg0 = p;
        alUnlink(p);
        alLink(p, (u8 *)D_80036F54 + 12);
    } else {
        p = (u8 *)D_80036F54[3];
        while (p != NULL) {
            if (arg1 >= *(s16 *)(*(u8 **)(p + 8) + 0x16) && *(s32 *)(p + 0x88) == 0) {
                *arg0 = p;
                r = 1;
                arg1 = *(u16 *)(*(u8 **)(p + 8) + 0x16);
            }
            p = *(u8 **)p;
        }
    }
    return r;
}
