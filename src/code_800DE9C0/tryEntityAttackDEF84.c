/* @header
 * tryEntityAttackDEF84  (originally func_800DEF84)
 * VRAM 0x800DEF84 | ROM 0xD2424 | size 0x290
 * asm: asm/nonmatchings/code_800DE9C0/func_800DEF84.s
 */
#include "common.h"

/* Melee hit test for an entity against target flags.
 * arg0 entity, arg1 attacker direction flags, arg2 attack mode bits,
 * arg3 target's received-direction flags. Returns 1 when the attack lands
 * (and starts action 0x60 or 0x61), else 0.
 * Three independent attack kinds, each gated on a u64 flag at +0x20:
 *  - 0x40: "attack allowed" table D_800E3CEE[quadrant(target)] matches the
 *    filtered flags -> set +0x3E quadrant and run the hit;
 *  - 0x80: quadrant test against D_800E3CD8, with an extra parry/dodge
 *    branch when D_8007E228+0x58 bit 0x200 is set, plus a D_800E3CD0 test
 *    that re-runs func_800A76FC;
 *  - 0x100: simpler D_800E3CD8 quadrant test. */
#define ENT_FLAGS (*(u64 *)(arg0 + 0x20))
#define SET_QUAD  (*(s16 *)(arg0 + 0x3E))

extern u16 D_800E3CD0[], D_800E3CD8[], D_800E3CEE[];
extern u8 D_8007E228[];
s16 func_800D7A68(u16);
s16 func_800D7A2C(u16);
s8 checkEntityAttackHit(void *, u16);
s8 isEntityActionAllowedC2870(void *);
s8 func_800C2830(void *);
s8 func_800D9568(void *);
void func_800DA778(void *);
s16 func_800A76FC(void *, u16);

s32 tryEntityAttackDEF84(u8 *arg0, u16 arg1, u16 arg2, u16 arg3) {
    u16 filtered = arg1;
    u16 mask;
    s16 quad;
    if ((ENT_FLAGS & 0x40ULL) && (arg2 & 8)) {
        filtered &= arg3;
        if (D_800E3CEE[func_800D7A68(arg3)] & filtered) {
            mask = filtered;
            SET_QUAD = func_800D7A2C(mask);
            if (checkEntityAttackHit(arg0, arg1))
                return 1;
            func_800A6C48(arg0, 0x60);
            return 1;
        }
    }
    if (ENT_FLAGS & 0x80ULL) {
        quad = getXZDirectionQuadrant((f32 *)(arg0 + 0x6C));
        SET_QUAD = quad;
        if (arg2 & 8) {
            if (D_800E3CD8[quad] & (arg1 & arg3)) {
                if (*(u16 *)(D_8007E228 + 0x58) & 0x200) {
                    if (checkEntityAttackHit(arg0, arg1))
                        return 1;
                    if (isEntityActionAllowedC2870(arg0))
                        func_800DA778(arg0);
                    else if (func_800D9568(arg0))
                        return 1;
                }
                if (isEntityActionAllowedC2870(arg0)) {
                    func_800A6C48(arg0, 0x61);
                    return 1;
                }
            }
            if ((D_800E3CD0[SET_QUAD] & (arg1 & arg3)) && func_800C2830(arg0)) {
                SET_QUAD = func_800A76FC(arg0, arg3);
                func_800A6C48(arg0, 0x60);
                return 1;
            }
        }
    }
    if ((ENT_FLAGS & 0x100ULL) && (arg2 & 8)) {
        quad = getXZDirectionQuadrant((f32 *)(arg0 + 0x6C));
        SET_QUAD = quad;
        if ((D_800E3CD8[quad] & (arg1 & arg3)) && isEntityActionAllowedC2870(arg0)) {
            func_800A6C48(arg0, 0x61);
            return 1;
        }
    }
    return 0;
}
