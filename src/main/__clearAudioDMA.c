/* @header
 * __clearAudioDMA  (originally func_80017408)
 * VRAM 0x80017408 | ROM 0x18008 | size 0x100
 * asm: asm/nonmatchings/main/__clearAudioDMA.s
 */
/* SDK: the SDK demo audio manager (n64-demos simple/src/main/audiomgr.c) as adapted in this old libmus (SDK code
 * with changes, see docs/sdk_functions.md). */
#include "common.h"

typedef struct Nw2Node17408 {
    struct Nw2Node17408 *next;
    struct Nw2Node17408 *f4;
    u32 pad8;
    u32 fC;
} Nw2Node17408;

extern u32 D_80036F30;
extern u32 D_80036F38;
extern Nw2Node17408 *D_80062524[2];
extern u8 D_80062540[];
s32 osRecvMesg(void *, void *, s32);
void alUnlink(void *);
void alLink(void *, void *);

void __clearAudioDMA(void) {
    u32 i;
    u32 tmp[2];
    Nw2Node17408 *node;
    Nw2Node17408 *next;
    Nw2Node17408 *second;

    for (i = 0; i < D_80036F38; i++) {
        osRecvMesg(D_80062540, tmp, 0);
    }
    node = D_80062524[0];
    while (node != NULL) {
        next = node->next;
        if (node->fC + 1 < D_80036F30) {
            if (D_80062524[0] == node) {
                D_80062524[0] = next;
            }
            alUnlink(node);
            second = D_80062524[1];
            if (second != NULL) {
                alLink(node, second);
            } else {
                D_80062524[1] = node;
                node->next = NULL;
                node->f4 = NULL;
            }
        }
        node = next;
    }
    D_80036F38 = 0;
    D_80036F30++;
}
