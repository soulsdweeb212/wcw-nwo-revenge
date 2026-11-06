/* @header
 * isEntityActionAllowedC2870  (originally func_800C2870)
 * VRAM 0x800C2870 | ROM 0xB5D10 | size 0x2A8
 * asm: asm/nonmatchings/code_800BBA00/isEntityActionAllowedC2870.s
 */
#include "common.h"

/* Predicate deciding whether `entity` may start or continue a special action. Depends
 * on the global mode word (D_8007E228+0x58), the entity's flags, its partnerFlags, how
 * many of the four records carry the matching flag pairs, and
 * func_800DA6DC. Returns 1 to allow, 0 otherwise. */
extern u8 D_8007E228[];
s8 func_800DA6DC(void *);

s32 isEntityActionAllowedC2870(Wrestler *entity) {
    u16 mode;
    u64 flags, flags2;
    s16 count;
    s16 i;

    mode = *(u16 *)(D_8007E228 + 0x58);
    if (!(mode & 0x400)) goto not400;
reload:
    flags = entity->flags;
common:
    flags = flags & WR_FLAG_LEGAL;
    if (flags) return 1;
    return 0;
not400:
    if (mode & 0x100) {
        count = 0;
        for (i = 0; i < 4; i++) {
            if (D_800F9D10[i].characterId != -1) {
                u64 recordFlags = D_800F9D10[i].flags;
                if (recordFlags & WR_FLAG_LEGAL) { if (recordFlags & WR_FLAG_ON_FLOOR) count++; }
                else if (recordFlags & 0x2ULL) { if (recordFlags & 0x20ULL) count++; }
            }
        }
        flags2 = entity->flags;
        if (flags2 & 1ULL) {
            if ((entity->partnerFlags & 0x600000000000ULL) || count) return 1;
        }
        flags = entity->flags;
        if (flags & 2ULL) {
            flags = entity->flags;
            if (flags & 0x20ULL) return 1;
            if ((entity->partnerFlags & 0x600000000000ULL) || count) goto ret1;
            goto reload;
        }
        goto common;
    }
    if (mode & 0x200) {
        flags = entity->flags;
        if (flags & WR_FLAG_LEGAL) return 1;
        if (flags & WR_FLAG_ON_FLOOR) { if (entity->state != 3) return 1; }
        if ((s8)func_800DA6DC(entity)) return 1;
    }
    return 0;
ret1:
    return 1;
}
