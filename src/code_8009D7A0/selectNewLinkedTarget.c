/* @header
 * selectNewLinkedTarget  (originally func_800A7B38)
 * VRAM 0x800A7B38 | ROM 0x9AFD8 | size 0x108
 * asm: asm/nonmatchings/code_8009D7A0/selectNewLinkedTarget.s
 */
#include "common.h"

/* Choose a fresh linked-target entity for arg0. When arg1 bit 0 is set it
 * gathers up to four candidate targets around arg0's position (+0x6C), strikes
 * out the two ids already stored at +0x355 and +0x353, then takes the first
 * surviving candidate: writes it to +0x353, notifies func_80096E2C with the
 * entity id and candidate id, and returns 1. Returns 0 when no candidate is
 * available. */
typedef struct { s8 id; u8 pad[11]; } Candidate;

typedef struct {
    s8 id;              /* @0x0 entity id */
    u8 pad1[0x6B];
    f32 pos6C[3];       /* @0x6C position xyz */
    u8 pad78[0x2DB];
    s8 f353;            /* @0x353 current target id */
    u8 pad354;
    s8 f355;            /* @0x355 rejected target id */
} Nw2LinkedTargetA7B38;

void collectLinkedTargets(void *, void *, void *, u64);
void func_80096E2C(s32, s32);

s8 selectNewLinkedTarget(Nw2LinkedTargetA7B38 *arg0, s32 arg1) {
    Candidate list[4];
    s16 i;

    if (arg1 & 1) {
        collectLinkedTargets(arg0, arg0->pos6C, list, 0);
        i = 0;
        do {
            if (list[i].id == arg0->f355)
                list[i].id = -1;
            if (list[i].id == arg0->f353)
                list[i].id = -1;
            i++;
        } while (i < 4);
        i = 0;
        do {
            s8 id = list[i].id;
            if (id != -1) {
                arg0->f353 = id;
                func_80096E2C(arg0->id, id);
                return 1;
            }
            i++;
        } while (i < 4);
    }
    return 0;
}
