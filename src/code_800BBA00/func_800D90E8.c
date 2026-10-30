/* @header
 * func_800D90E8
 * VRAM 0x800D90E8 | ROM 0xCC588 | size 0xD8
 * asm: asm/nonmatchings/code_800BBA00/func_800D90E8.s
 */
#include "common.h"

extern s8 D_8007EF30[];
extern s16 D_800E3FA8[];
extern u16 D_800F9840[];

/* Per-entity counter that arms a flag once it passes a threshold.
 * While the entity u64 flag 0x0008000000000000 is set, bump the counter for this
 * entity (indexed by its s8 id at +0); once the count exceeds
 * D_800E3FA8[D_8007EF30[0xCFC]] set flag 0x0010000000000000. Otherwise clear that
 * flag and reset the entity's counter to zero. */
void func_800D90E8(void *arg0)
{
    u8 *entity = (u8 *)arg0;

    if (*(u64 *)(entity + 0x20) & 0x0008000000000000ULL) {
        D_800F9840[*(s8 *)entity]++;
        if ((s16)D_800F9840[*(s8 *)entity] > D_800E3FA8[D_8007EF30[0xCFC]]) {
            *(u64 *)(entity + 0x20) |= 0x0010000000000000ULL;
        }
    } else {
        *(u64 *)(entity + 0x20) &= ~0x0010000000000000ULL;
        D_800F9840[*(s8 *)entity] = 0;
    }
}
