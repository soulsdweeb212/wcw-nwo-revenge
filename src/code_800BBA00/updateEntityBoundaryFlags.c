/* @header
 * updateEntityBoundaryFlags  (originally func_800BEB14)
 * VRAM 0x800BEB14 | ROM 0xB1FB4 | size 0x228
 * asm: asm/nonmatchings/code_800BBA00/func_800BEB14.s
 */
#include "common.h"

/* Entity record touched by updateEntityBoundaryFlags.
 * +0x0A state id, +0x3E body-part/direction index, +0x4C/+0x54 X/Z offsets. */
typedef struct {
    u8 pad0[0xA];
    s16 state;
    u8 padC[0x32];
    s16 partIndex;
    u8 pad40[0xC];
    f32 offsetX;
    u8 pad50[4];
    f32 offsetZ;
} Nw2BoundaryEntity;

extern u16 D_800E3A90[];
extern u16 D_800E3A98[];

/* Restricts the entity's direction flags (*flags) to the masks of its body
 * part, and when no cardinal-direction bit is set picks a direction from the
 * boundary mask of nearby entities (func_800BED3C) using the X/Z offsets.
 * Returns nonzero when the resulting flag is clear for state 0xD. */
s32 updateEntityBoundaryFlags(Nw2BoundaryEntity *ent, s32 unused, u16 *flags) {
    u16 mask;
    s32 blockedMask;
    s32 openMask;
    s32 result;

    mask = D_800E3A98[ent->partIndex] | D_800E3A90[ent->partIndex];
    *flags = *flags & mask;
    if (!(*flags & 0xF00)) {
        blockedMask = ((s32 (*)(void *))func_800BED3C)(ent);
        if (((blockedMask & 0xFFFF) == 0) | ((blockedMask & 0xFFFF) == mask)) {
            switch (ent->partIndex) {
            case 0:
                if (ent->offsetX < 0.0f) {
                    *flags = 0x200;
                } else {
                    *flags = 0x100;
                }
                break;
            case 1:
                if (0.0f < ent->offsetZ) {
                    *flags = 0x800;
                } else {
                    *flags = 0x400;
                }
                break;
            case 2:
                if (0.0f < ent->offsetX) {
                    *flags = 0x100;
                } else {
                    *flags = 0x200;
                }
                break;
            case 3:
                if (ent->offsetZ < 0.0f) {
                    *flags = 0x400;
                } else {
                    *flags = 0x800;
                }
                break;
            }
        } else {
            openMask = D_800E3A90[ent->partIndex];
            if (openMask & blockedMask) {
                *flags = D_800E3A98[ent->partIndex];
            } else {
                *flags = openMask;
            }
        }
    }
    if (ent->state == 0xD) {
        result = *flags & D_800E3A90[ent->partIndex];
    } else {
        result = *flags & D_800E3A98[ent->partIndex];
    }
    return result == 0;
}
