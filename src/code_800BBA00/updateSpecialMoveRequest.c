#include "common.h"

/* Paired-action special-move request handler (called from the AI action code).
 * Both D_800FAF5C and D_800F9B00 objects are the same Nw2Entity3B0-style record;
 * here `entity` is that record. Bit meanings in the u64 flag word at +0x20:
 *   0x80                  partner/opponent slot usable (cleared => no request)
 *   0x8000000000000       request pending
 *   0x10000000000000      request granted
 *   0x20000000000000      request rejected/blocked
 * Returns 1 when the request is granted, else 0. */
s8 func_800D8DF0(void *);
extern s16 D_800E3FA0[], D_800E3FA2[];

#define ENTITY_FLAGS (*(u64 *)(entity + 0x20))

s32 updateSpecialMoveRequest(u8 *entity) {
    if (func_800D8DF0(entity)) {
        ENTITY_FLAGS &= ~0x28000000000000ULL;
        return 0;
    }
    if (*(s16 *)(entity + 0xA) == 10 && *(s16 *)(entity + 0xC) >= 4) {
        ENTITY_FLAGS |= 0x8000000000000ULL;
        if (ENTITY_FLAGS & 0x10000000000000ULL)
            return 1;
        return 0;
    }
    if (ENTITY_FLAGS & 0x80) {
        s32 tagIndex = (entity[0] * 2) & 4;
        if (*(s16 *)(entity + 0x3C) == *(s16 *)((u8 *)D_800E3FA0 + tagIndex) ||
            *(s16 *)(entity + 0x3C) == *(s16 *)((u8 *)D_800E3FA2 + tagIndex)) {
            ENTITY_FLAGS &= ~0x28000000000000ULL;
            return 0;
        }
        ENTITY_FLAGS |= 0x8000000000000ULL;
        if (ENTITY_FLAGS & 0x10000000000000ULL)
            return 1;
        return 0;
    }
    ENTITY_FLAGS |= 0x8000000000000ULL;
    if (ENTITY_FLAGS & 0x10000000000000ULL)
        return 1;
    return 0;
}
