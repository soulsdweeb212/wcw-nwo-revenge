/* @header
 * isEntityActionAllowedC2870  (originally func_800C2870)
 * VRAM 0x800C2870 | ROM 0xB5D10 | size 0x2A8
 * asm: asm/nonmatchings/code_800BBA00/isEntityActionAllowedC2870.s
 */
#include "common.h"

/* Predicate deciding whether `entity` may start or continue a special action. Depends
 * on the global mode word (D_8007E228+0x58), the entity's u64 +0x20 flags, its +0x358
 * flags, how many of the four 0x3B0-stride records carry the matching flag pairs, and
 * func_800DA6DC. Returns 1 to allow, 0 otherwise. */
extern u8 D_8007E228[];
extern u8 D_800F9D12[];
extern u8 D_800F9D30[];
s8 func_800DA6DC(void *);

s32 isEntityActionAllowedC2870(u8 *entity) {
    u16 mode;
    u64 flags, flags2;
    s16 count;
    s16 i;

    mode = *(u16 *)(D_8007E228 + 0x58);
    if (!(mode & 0x400)) goto not400;
reload:
    flags = *(u64 *)(entity + 0x20);
common:
    flags = flags & 0x200ULL;
    if (flags) return 1;
    return 0;
not400:
    if (mode & 0x100) {
        count = 0;
        for (i = 0; i < 4; i++) {
            s32 off = i * 0x3B0;
            if (*(s16 *)(D_800F9D12 + off) != -1) {
                u64 recordFlags = *(u64 *)(D_800F9D30 + off);
                if (recordFlags & 0x200ULL) { if (recordFlags & 0x100ULL) count++; }
                else if (recordFlags & 0x2ULL) { if (recordFlags & 0x20ULL) count++; }
            }
        }
        flags2 = *(u64 *)(entity + 0x20);
        if (flags2 & 1ULL) {
            if ((*(u64 *)(entity + 0x358) & 0x600000000000ULL) || count) return 1;
        }
        flags = *(u64 *)(entity + 0x20);
        if (flags & 2ULL) {
            flags = *(u64 *)(entity + 0x20);
            if (flags & 0x20ULL) return 1;
            if ((*(u64 *)(entity + 0x358) & 0x600000000000ULL) || count) goto ret1;
            goto reload;
        }
        goto common;
    }
    if (mode & 0x200) {
        flags = *(u64 *)(entity + 0x20);
        if (flags & 0x200ULL) return 1;
        if (flags & 0x100ULL) { if (*(s16 *)(entity + 0xA) != 3) return 1; }
        if ((s8)func_800DA6DC(entity)) return 1;
    }
    return 0;
ret1:
    return 1;
}
