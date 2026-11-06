/* @header
 * tryEntityAttackDEF84  (originally func_800DEF84)
 * VRAM 0x800DEF84 | ROM 0xD2424 | size 0x290
 * asm: asm/nonmatchings/code_800DE9C0/tryEntityAttackDEF84.s
 */
#include "common.h"

/* Melee hit test for a wrestler against target flags.
 * w the wrestler, arg1 attacker direction flags, arg2 attack mode bits,
 * arg3 target's received-direction flags. Returns 1 when the attack lands
 * (and starts action 0x60 or 0x61), else 0.
 * Three independent cases, each gated on a zone bit of w->flags:
 *  - WR_FLAG_IN_RING: "attack allowed" table D_800E3CEE[func_800D7A68(arg3)]
 *    matches the filtered flags -> set dirIndex and run the hit;
 *  - WR_FLAG_ON_APRON: dirIndex = quadrant of the pelvis (jointA[1]), test
 *    against D_800E3CD8, with an extra parry/dodge branch when
 *    D_8007E228+0x58 bit 0x200 is set, plus a D_800E3CD0 test that re-runs
 *    func_800A76FC;
 *  - WR_FLAG_ON_FLOOR: simpler D_800E3CD8 quadrant test. */
extern u16 D_800E3CD0[], D_800E3CD8[], D_800E3CEE[];
extern u8 D_8007E228[];
s16 func_800D7A68(u16);
s16 func_800D7A2C(u16);
s8 checkEntityAttackHit(Wrestler *, u16);
s8 isEntityActionAllowedC2870(Wrestler *);
s8 func_800C2830(Wrestler *);
s8 func_800D9568(Wrestler *);
void func_800DA778(Wrestler *);
s16 func_800A76FC(Wrestler *, u16);

s32 tryEntityAttackDEF84(Wrestler *w, u16 arg1, u16 arg2, u16 arg3) {
    u16 filtered = arg1;
    u16 mask;
    s16 quad;
    if ((w->flags & WR_FLAG_IN_RING) && (arg2 & 8)) {
        filtered &= arg3;
        if (D_800E3CEE[func_800D7A68(arg3)] & filtered) {
            mask = filtered;
            w->dirIndex = func_800D7A2C(mask);
            if (checkEntityAttackHit(w, arg1))
                return 1;
            func_800A6C48(w, 0x60);
            return 1;
        }
    }
    if (w->flags & WR_FLAG_ON_APRON) {
        quad = getXZDirectionQuadrant(&w->jointA[1].x);
        w->dirIndex = quad;
        if (arg2 & 8) {
            if (D_800E3CD8[quad] & (arg1 & arg3)) {
                if (*(u16 *)(D_8007E228 + 0x58) & 0x200) {
                    if (checkEntityAttackHit(w, arg1))
                        return 1;
                    if (isEntityActionAllowedC2870(w))
                        func_800DA778(w);
                    else if (func_800D9568(w))
                        return 1;
                }
                if (isEntityActionAllowedC2870(w)) {
                    func_800A6C48(w, 0x61);
                    return 1;
                }
            }
            if ((D_800E3CD0[w->dirIndex] & (arg1 & arg3)) && func_800C2830(w)) {
                w->dirIndex = func_800A76FC(w, arg3);
                func_800A6C48(w, 0x60);
                return 1;
            }
        }
    }
    if ((w->flags & WR_FLAG_ON_FLOOR) && (arg2 & 8)) {
        quad = getXZDirectionQuadrant(&w->jointA[1].x);
        w->dirIndex = quad;
        if ((D_800E3CD8[quad] & (arg1 & arg3)) && isEntityActionAllowedC2870(w)) {
            func_800A6C48(w, 0x61);
            return 1;
        }
    }
    return 0;
}
