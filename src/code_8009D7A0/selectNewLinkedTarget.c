/* @header
 * selectNewLinkedTarget  (originally func_800A7B38)
 * VRAM 0x800A7B38 | ROM 0x9AFD8 | size 0x108
 * asm: asm/nonmatchings/code_8009D7A0/selectNewLinkedTarget.s
 */
#include "common.h"

/* Switch w to a new opponent. When arg1 bit 0 is set it gathers up to four candidates around w's pelvis (jointA[1],
 * collectLinkedTargets, nearest first), strikes out w->partnerId and the current w->opponentId, then takes the first
 * surviving candidate: writes it to w->opponentId, calls func_80096E2C(w->id, candidate) (an empty function in this
 * build) and returns 1. Returns 0 when no candidate is left. */
typedef struct { s8 id; u8 pad[11]; } Candidate;

void collectLinkedTargets(void *, void *, void *, u64);
void func_80096E2C(s32, s32);

s8 selectNewLinkedTarget(Wrestler *w, s32 arg1) {
    Candidate list[4];
    s16 i;

    if (arg1 & 1) {
        collectLinkedTargets(w, &w->jointA[1].x, list, 0);
        i = 0;
        do {
            if (list[i].id == w->partnerId)
                list[i].id = -1;
            if (list[i].id == w->opponentId)
                list[i].id = -1;
            i++;
        } while (i < 4);
        i = 0;
        do {
            s8 id = list[i].id;
            if (id != -1) {
                w->opponentId = id;
                func_80096E2C(w->id, id);
                return 1;
            }
            i++;
        } while (i < 4);
    }
    return 0;
}
