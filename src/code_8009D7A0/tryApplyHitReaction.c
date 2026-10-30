/* @header
 * tryApplyHitReaction  (originally func_800AD454)
 * VRAM 0x800AD454 | ROM 0xA08F4 | size 0x120
 * asm: asm/nonmatchings/code_8009D7A0/tryApplyHitReaction.s
 */
#include "common.h"

extern s16 D_800EB420[];
void func_800A7C40(void *, s8, s16);
s32 func_800A8D14(void *, void *);
s8 func_800D4198(s16);
#define F(p,t,o) (*(t *)((u8 *)(p)+(o)))

/* arg0: attacker  (+0x0 s8 facing, +0x6 s16 anim frame, +0x2C u32 state flags,
 *                  +0x371 u8 anim frame count, +0x386 u16 reaction id,
 *                  +0x3AC u32 hit flags)
 * arg1: victim    (+0x20 u64 flags, +0x360 u16 state word)
 *
 * If the attacker's animation is on one of its last two frames, both entities
 * pass the state/flag gates, and a random check allows it, mark the victim with
 * flag 2 and queue the hit-reaction animation (using the attack's own reaction
 * id unless the attacker has a facing-table entry). */
void tryApplyHitReaction(void *arg0, void *arg1, s32 arg2, s32 arg3) {
    s16 animFrame;
    u8 animLimit;
    animLimit = F(arg0, u8, 0x371);
    animFrame = F(arg0, s16, 6);
    if (animFrame >= animLimit - 2 && animFrame < animLimit &&
        (F(arg0, u32, 0x3AC) & 1) && !(F(arg1, u64, 0x20) & 9) && (arg3 & 0x10) &&
        (!(F(arg0, u32, 0x2C) & 1) || func_800D4198(250))) {
        F(arg1, u16, 0x360) |= 2;
        if (D_800EB420[F(arg0, s8, 0)] || (F(arg0, u32, 0x2C) & 0x400000)) {
            func_800A7C40(arg1, F(arg0, s8, 0), F(arg0, u16, 0x386) + 1);
        } else {
            s16 reaction = func_800A8D14(arg0, arg1) - 2;
            func_800A7C40(arg1, F(arg0, s8, 0), reaction);
        }
    }
}
