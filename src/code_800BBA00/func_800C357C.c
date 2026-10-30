/* @header
 * func_800C357C
 * VRAM 0x800C357C | ROM 0xB6A1C | size 0x380
 * asm: asm/nonmatchings/code_800BBA00/func_800C357C.s
 */
#include "common.h"

extern u8 D_800E59D0[]; extern s16 D_800F9D12[]; extern s16 D_800F9D1A[];

/* Collects up to four candidate entities (their indices) into outTargets, the
 * list terminated with -1.  For mode 0 it also excludes the linked entity at
 * entity[0x355].  Each mode picks a (skipMask, matchMask) flag pair and a target
 * state v; a live slot (not self, not dead) qualifies when its state field
 * D_800F9D1A equals v, or otherwise when its u64 flags pass !(flags & skipMask)
 * and (flags & matchMask).  Finally, if the linked entity entity[0x353] is in
 * the list it is swapped to the front. */
void func_800C357C(u8 *entity, s16 mode, s8 *outTargets) {
    s64 matchMask; u64 skipMask; s32 v; s8 i; s8 foundCount; s16 target;
    i = 0; do { outTargets[i] = -1 - (matchMask + ~matchMask) - 1; i++; } while (i < 4);
    switch (mode) {
    case 0:
        if (*(s32*)(entity+0x2C) & 4) { skipMask = 0x603000000080ULL; matchMask = 0x100000ULL; v = -1; }
        else if (*(s32*)(entity+0x2C) & 0x10) { skipMask = 0x3000000180ULL; matchMask = 0xFFFFFFFFULL; v = -1; }
        else { if (*(u64*)(entity+0x20) & 0x40) skipMask = 0x3000000100ULL; else skipMask = 0x3000000000ULL;
               matchMask = 0xFFFFFFFFULL; v = 0x46; }
        break;
    case 1: case 3: case 10: case 13: case 21: skipMask = 0x5000400000ULL; matchMask = 0xFFFFFFFFULL; v = -1; break;
    case 5: case 8: case 9: case 12:
        if (*(s16*)(entity+6) >= (s32)entity[0x370] && *(s16*)(entity+6) < (s32)entity[0x371]) { skipMask = 0x5000400000ULL; matchMask = 0xFFFFFFFFULL; v = -1; }
        else if (*(s16*)(entity+6) == (s32)entity[0x371]) { skipMask = 0x5000000000ULL; matchMask = 0x400000ULL; v = -1; }
        else return;
        break;
    case 15: case 16: skipMask = 0x5000000000ULL; matchMask = 0xFFFFFFFFULL; v = 0x75; break;
    case 17: skipMask = 0x5000400180ULL; matchMask = 0xFFFFFFFFULL; v = -1; break;
    case 18: skipMask = 0x5000000140ULL; matchMask = 0xFFFFFFFFULL; v = -1; break;
    case 19: skipMask = 0x50004000C0ULL; matchMask = 0xFFFFFFFFULL; v = -1; break;
    case 2: case 4: skipMask = 0x5000000000ULL; matchMask = 0x400000ULL; v = -1; break;
    case 6: case 7: case 11: case 14: skipMask = 0x5000000000ULL; matchMask = 0x400000ULL; v = -1; break;
    case 20:
        skipMask = 0x400005000000000ULL; matchMask = 0x600000000000ULL; v = -1; break;
    }
    target = v; foundCount = 0;
    for (i = 0; i < 4; i++) {
        s32 idx;
        if (i == (s8)entity[0]) continue;
        idx = i * 0x3B0;
        if (*(s16*)((u8*)D_800F9D12 + idx) == -1) continue;
        if (*(s16*)((u8*)D_800F9D1A + idx) != target) {
            u64 flags = *(u64*)((u8*)D_800F9D30 + idx);
            if (flags & skipMask) continue;
            if ((flags & matchMask) == 0) continue;
        }
        if (mode == 0 && i == (s8)entity[0x355]) continue;
        outTargets[foundCount] = i; foundCount++;
    }
    if (outTargets[0] != -1) { for (i = 0; outTargets[i] != -1; i++) { if (outTargets[i] == (s8)entity[0x353]) { if (i != 0) { s8 t = outTargets[0]; outTargets[0] = outTargets[i]; outTargets[i] = t; } break; } } }
}
