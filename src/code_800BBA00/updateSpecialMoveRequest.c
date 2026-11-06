/* @header
 * updateSpecialMoveRequest  (originally func_800D8F44)
 * VRAM 0x800D8F44 | ROM 0xCC3E4 | size 0x1A4
 * asm: asm/nonmatchings/code_800BBA00/updateSpecialMoveRequest.s
 */
#include "common.h"

/* Paired-action special-move request handler (called from the AI action code).
 * `entity` is a wrestler record. Bit meanings in its u64 flags:
 *   0x80                  partner/opponent slot usable (cleared => no request)
 *   0x8000000000000       request pending
 *   0x10000000000000      request granted
 *   0x20000000000000      request rejected/blocked
 * Returns 1 when the request is granted, else 0. */
s8 func_800D8DF0(void *);
extern s16 D_800E3FA0[], D_800E3FA2[];

s32 updateSpecialMoveRequest(Wrestler *entity) {
    if (func_800D8DF0(entity)) {
        entity->flags &= ~0x28000000000000ULL;
        return 0;
    }
    if (entity->state == 10 && entity->step >= 4) {
        entity->flags |= 0x8000000000000ULL;
        if (entity->flags & 0x10000000000000ULL)
            return 1;
        return 0;
    }
    if (entity->flags & 0x80) {
        s32 tagIndex = ((u8)entity->id * 2) & 4;
        if (entity->ringSide == *(s16 *)((u8 *)D_800E3FA0 + tagIndex) ||
            entity->ringSide == *(s16 *)((u8 *)D_800E3FA2 + tagIndex)) {
            entity->flags &= ~0x28000000000000ULL;
            return 0;
        }
        entity->flags |= 0x8000000000000ULL;
        if (entity->flags & 0x10000000000000ULL)
            return 1;
        return 0;
    }
    entity->flags |= 0x8000000000000ULL;
    if (entity->flags & 0x10000000000000ULL)
        return 1;
    return 0;
}
