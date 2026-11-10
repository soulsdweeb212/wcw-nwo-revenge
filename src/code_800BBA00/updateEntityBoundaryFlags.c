/* @header
 * updateEntityBoundaryFlags  (originally func_800BEB14)
 * VRAM 0x800BEB14 | ROM 0xB1FB4 | size 0x228
 * asm: asm/nonmatchings/code_800BBA00/updateEntityBoundaryFlags.s
 */
#include "common.h"

extern u16 D_800E3A90[];
extern u16 D_800E3A98[];

/* Limits the direction bits *flags (0x100/0x200/0x400/0x800) to the masks D_800E3A90 / D_800E3A98 of side
 * w->dirIndex. When none of those bits is left, it asks func_800BED3C(w, other) which of those bits are taken: for
 * each wrestler other than w and `other` that is in the ring or on the apron with its pelvis past that side's bound,
 * the bit for the side of w's pelvis it is on. If none or all are taken it picks one from the sign of w->x (sides
 * 0/2) or w->z (sides 1/3), otherwise the D_800E3A90 bits unless taken, else the D_800E3A98 bits. Returns 1 when
 * *flags has no bit of D_800E3A90[side] (state 0xD) or D_800E3A98[side] (any other state), else 0. */
s32 updateEntityBoundaryFlags(Wrestler *w, Wrestler *other, u16 *flags) {
    u16 mask;
    s32 blockedMask;
    s32 openMask;
    s32 result;

    mask = D_800E3A98[w->dirIndex] | D_800E3A90[w->dirIndex];
    *flags = *flags & mask;
    if (!(*flags & 0xF00)) {
#ifdef TARGET_PC
        /* The N64 code passes the address flags as func_800BED3C's u32 third parameter, which would cut a 64-bit
         * pointer. func_800BED3C never reads that parameter, so the PC passes 0. */
        blockedMask = func_800BED3C(w, other, 0);
#else
        blockedMask = func_800BED3C(w, other, (u32)flags);
#endif
        if (((blockedMask & 0xFFFF) == 0) | ((blockedMask & 0xFFFF) == mask)) {
            switch (w->dirIndex) {
            case 0:
                if (w->x < 0.0f) {
                    *flags = 0x200;
                } else {
                    *flags = 0x100;
                }
                break;
            case 1:
                if (0.0f < w->z) {
                    *flags = 0x800;
                } else {
                    *flags = 0x400;
                }
                break;
            case 2:
                if (0.0f < w->x) {
                    *flags = 0x100;
                } else {
                    *flags = 0x200;
                }
                break;
            case 3:
                if (w->z < 0.0f) {
                    *flags = 0x400;
                } else {
                    *flags = 0x800;
                }
                break;
            }
        } else {
            openMask = D_800E3A90[w->dirIndex];
            if (openMask & blockedMask) {
                *flags = D_800E3A98[w->dirIndex];
            } else {
                *flags = openMask;
            }
        }
    }
    if (w->state == 0xD) {
        result = *flags & D_800E3A90[w->dirIndex];
    } else {
        result = *flags & D_800E3A98[w->dirIndex];
    }
    return result == 0;
}
