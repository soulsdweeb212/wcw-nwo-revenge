/* @header
 * _n_collectPVoices  (originally func_80017F5C)
 * VRAM 0x80017F5C | ROM 0x18B5C | size 0x60
 * asm: asm/nonmatchings/main/_n_collectPVoices.s
 */
/* SDK: n_audio, libnaudio/src/n_synthesizer.c (same code as the SDK source). */
#include "common.h"

s32 alLink(s32, void *);
s32 alUnlink(s32);
extern void *n_syn;

/* Move every node chained at n_syn+0x14 onto the list head at n_syn+4. */
void _n_collectPVoices(void) {
    s32 node;

    node = *(s32 *)((s8 *)n_syn + 0x14);
    if (node != 0) {
        do {
            alUnlink(node);
            alLink(node, (s8 *)n_syn + 4);
            node = *(s32 *)((s8 *)n_syn + 0x14);
        } while (node != 0);
    }
}
