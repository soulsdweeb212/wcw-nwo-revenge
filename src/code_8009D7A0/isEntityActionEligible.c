/* @header
 * isEntityActionEligible  (originally func_800A94B4)
 * VRAM 0x800A94B4 | ROM 0x9C954 | size 0x2E8
 * asm: asm/nonmatchings/code_8009D7A0/func_800A94B4.s
 */
#include "common.h"

/* Whether `actor` may start the given action toward `other`: each action checks a
 * combination of the actor's state flags (+0x2C), the actor's attachment flags
 * (+0x364 -> +0x38), its own flags (+0x20) and the other's flags/attachment. */
s32 isEntityActionEligible(u8 *actor, u8 *other, s16 action) {
    switch (action) {
    case 0x7E:
    case 0x82:
        if ((*(u32 *)(actor + 0x2C) & 0x300)
            && (*(u64 *)(*(u8 **)(actor + 0x364) + 0x38) & 0x800000000000ULL)
            && ((*(u32 *)(actor + 0x2C) & 3) == 3))
            return 1;
        break;
    case 0x6E:
    case 0x77:
        if ((*(u32 *)(actor + 0x2C) & 0x80)
            && (*(u64 *)(*(u8 **)(actor + 0x364) + 0x38) & 0x400000000000ULL)
            && ((*(u32 *)(actor + 0x2C) & 3) == 3))
            return 1;
        break;
    case 0x56:
    case 0x57:
        if ((*(u64 *)(*(u8 **)(actor + 0x364) + 0x38) & 0x100000000000ULL)
            && (*(u64 *)(actor + 0x20) & 0x80000)
            && (*(u64 *)(other + 0x20) & 0x100000)
            && (*(u16 *)(other + 0x28) & 0x420)
            && (*(u64 *)(actor + 0x20) & *(u64 *)(other + 0x20) & 0x140))
            return 1;
        break;
    case 0x58:
    case 0x59:
        if ((*(u64 *)(*(u8 **)(actor + 0x364) + 0x38) & 0x200000000000ULL)
            && (*(u64 *)(actor + 0x20) & 0x80000))
            return 1;
        break;
    case 0xE4:
        if ((*(u64 *)(*(u8 **)(actor + 0x364) + 0x38) & 0x8000000000000ULL)
            && (*(u64 *)(actor + 0x20) & 0x80000)
            && !(*(u64 *)(other + 0x20) & 0x400000))
            return 1;
        break;
    case 0xD2:
        if ((*(u64 *)(*(u8 **)(actor + 0x364) + 0x38) & 0x4000000000000ULL)
            && (*(u64 *)(actor + 0x20) & 0x80000))
            return 1;
        break;
    }
    return 0;
}
