/* @header
 * func_800B68A0
 * VRAM 0x800B68A0 | ROM 0xA9D40 | size 0x54C
 * asm: asm/nonmatchings/code_8009D7A0/func_800B68A0.s
 */
#include "common.h"

/* Bytes of the 64-byte character profile (Wrestler.profile) read here; their meaning is not known. */
typedef struct {
    u8 pad0[3];
    u8 f3;      /* +0x3 spirit bonus added when the attacker has flag 0x400000000 */
    u8 pad4;
    s8 f5[5];   /* +0x5 per attack part */
    s8 fA[5];   /* +0xA per target part */
} AttrB68;

extern u8 D_8007E228[];
extern f32 D_800E37CC[];
extern f64 D_800E55C0;
extern s16 D_800F9B78[];
extern s8 D_800FADB9[];
s16 func_800BF1E0(void *, s8);
void func_800BF338(void *, s16, s32);
void func_800BF228(void *, s32, s8);
void addEntityHealthDelta(Wrestler *, s16);
s16 updateEntityStunTimer(void *, s32, s32);

/* Applies a landed move: source->move is the move used, attacker gets the credit, target takes the damage (callers
 * often pass the same record for two or all three). The damage is the sum of three pieces, each at least 0: move.power
 * scaled by func_800BF1E0(attacker, move.attackPart) (the attacker's bodyPart[] value, 50 when it has WR_FLAG_SPECIAL),
 * the profile difference attacker f5[attackPart] - target fA[targetPart], and (when power != 0) the spirit difference /
 * 20. It is scaled by D_800E55C0 (1.2) under WR_FLAG_SPECIAL, doubled for a target with flag 8 and multiplied by the
 * D_800E37CC entry picked by the attacker's word in the table at D_8007E228+0x610. func_800BF338 subtracts it from
 * target->health (mode 1 in states 0x39/0x3D/0x3F; otherwise mode 0, which also records it in D_800FAF50[target->id]),
 * healthMax drops by a quarter of it (not below 128), each bodyPart[] loses move.partDamage[], and D_800FADB9[target]
 * records targetPart when that part is now at most 50 and no part 0..3 is lower. Spirit: the attacker gains
 * move.spiritGainSelf (+3 when its health < 49 and it is not in state 0x3D, + profile byte 3 with flag 0x400000000),
 * the target gets move.spiritDeltaTarget, and updateEntityStunTimer(target, 0, 3) takes 60 ticks off its SPIRIT_FULL /
 * SPECIAL timers. Both get flag 0x40000000000; D_800F9B78[attacker] and [target] change by move.unk3A8[0] / [1],
 * clamped to 30..200. Returns the damage. */
s16 func_800B68A0(Wrestler *source, Wrestler *attacker, Wrestler *target) {
    s16 pieces[3];
    s16 base, part, i, total, min, bonus;
    s8 key;
    s32 mode;

    base = source->move.power;
    key = source->move.attackPart;
    part = source->move.targetPart;
    pieces[0] = ((func_800BF1E0(attacker, key) + 50) * base) / 100;
    pieces[1] = ((((AttrB68 *)attacker->profile)->f5[key] - ((AttrB68 *)target->profile)->fA[part]) * base) / 10;
    if (base) pieces[2] = (attacker->spirit - target->spirit) / 20;
    else pieces[2] = 0;
    total = 0;
    for (i = 0; i < 3; i++) {
        if (pieces[i] < 0) pieces[i] = 0;
        total += (u16)pieces[i];
    }
    if (attacker->flags & WR_FLAG_SPECIAL) total = (f32)total * D_800E55C0;
    if (target->flags & 8) total = (f32)total * 2.0;
    total = (f32)total * D_800E37CC[((s32 *)(D_8007E228 + 0x610))[attacker->id]];
    switch (target->state) {
    case 0x39:
    case 0x3D:
    case 0x3F:
        mode = 1;
        break;
    default:
        mode = 0;
        break;
    }
    func_800BF338(target, -total, mode);
    target->healthMax -= total / 4;
    if (target->healthMax < 129) target->healthMax = 128;
    for (i = 0; i < 5; i++) func_800BF228(target, i, -source->move.partDamage[i]);
    if (part != 4) {
        min = 50;
        for (i = 0; i < 4; i++) {
            if (target->bodyPart[i] <= min) min = target->bodyPart[i];
        }
        if (min >= target->bodyPart[part]) D_800FADB9[target->id] = part;
    }
    bonus = source->move.spiritGainSelf;
    if (attacker->state != 0x3D && attacker->health < 49) bonus += 3;
    if (attacker->flags & 0x400000000ULL) bonus += (s8)((AttrB68 *)attacker->profile)->f3;
    addEntityHealthDelta(attacker, bonus);
    addEntityHealthDelta(target, source->move.spiritDeltaTarget);
    updateEntityStunTimer(target, 0, 3);
    attacker->flags |= 0x40000000000ULL;
    target->flags |= 0x40000000000ULL;
    D_800F9B78[attacker->id] += (s8)source->move.unk3A8[0];
    if (D_800F9B78[attacker->id] < 30) D_800F9B78[attacker->id] = 30;
    if (D_800F9B78[attacker->id] > 200) D_800F9B78[attacker->id] = 200;
    D_800F9B78[target->id] += (s8)source->move.unk3A8[1];
    if (D_800F9B78[target->id] < 30) D_800F9B78[target->id] = 30;
    if (D_800F9B78[target->id] > 200) D_800F9B78[target->id] = 200;
    return total;
}
