/* @header
 * func_800D4D44
 * VRAM 0x800D4D44 | ROM 0xC81E4 | size 0x6F4
 * asm: asm/nonmatchings/code_800BBA00/func_800D4D44.s
 */
#include "common.h"

extern s16 D_800E3E70[];
extern s16 D_800E3E80[];
extern s16 D_800E3E90[];
extern s16 D_800E3EA0[];
extern s16 D_800E3EB0[];
extern s16 D_800E3EC0[];
extern s16 D_800E3ED0[];
extern s16 D_800E3EE0[];
extern s16 D_800E3EF0[];
extern s16 D_800E3F00[];
extern s16 D_800E3F10[];
extern s16 D_800E3F18[];
extern s8 D_800FADB9[];
extern s16 func_800BF1E0(void *, s32);

/* The 64-bit ability bits at +0x38 of the character profile (profile fields are not mapped yet). */
#define PROFILE_BITS(w) (*(u64 *)((w)->profile + 0x38))

/* Picks an animation id for `action` (0..12). s1 is the highest profile
 * ability bit set among 0x4..0x100 (0..6) and indexes the per-action tables D_800E3E70..D_800E3F00.
 * Actions 0 and 1 also choose by flags bits 1 << 48 / 1 << 49 and bit 0, by the recorded weakest body part
 * D_800FADB9[id] being below 25 (read through func_800BF1E0: bodyPart[], or 50 under WR_FLAG_SPECIAL; then
 * D_800E3F10 / D_800E3F18 by part), and by timer (350..355) together with the current animId. Actions 9..11
 * choose by WR_FLAG_ON_APRON with flags bit 0x8000000000, by the same bits 48/49, and by profile bits
 * 0x100 / 0x200, moveMode bit 0x20 (running) and flags bit 0x8. */
s32 func_800D4D44(Wrestler *w, s16 action, f32 timer)
{
    s16 s1;
    s16 s2;

    if (PROFILE_BITS(w) & 4) s1 = 0;
    if (PROFILE_BITS(w) & 8) s1 = 1;
    if (PROFILE_BITS(w) & 0x10) s1 = 2;
    if (PROFILE_BITS(w) & 0x20) s1 = 3;
    if (PROFILE_BITS(w) & 0x40) s1 = 4;
    if (PROFILE_BITS(w) & 0x80) s1 = 5;
    if (PROFILE_BITS(w) & 0x100) s1 = 6;

    switch (action) {
    case 2: return D_800E3EA0[s1];
    case 3: return D_800E3EB0[s1];
    case 4: return D_800E3EC0[s1];
    case 5: return D_800E3ED0[s1];
    case 6: return D_800E3EE0[s1];
    case 7: return D_800E3EF0[s1];
    case 8: return D_800E3F00[s1];
    case 0:
        if (w->flags & 0x1000000000000ULL) {
            if (w->flags & 0x2000000000000ULL) return 0x100C;
            return 0x1004;
        }
        if (w->flags & 1) return D_800E3E70[s1];
        s2 = D_800FADB9[w->id];
        if (func_800BF1E0(w, s2) < 0x19) return D_800E3F10[s2];
        if (timer < 350.0) return D_800E3E70[s1];
        if (timer > 355.0) return 0xE72;
        {
            s32 v;
            v = w->animId;
            if ((v ^ 0xE73) == 0) return 0xE72;
            return D_800E3E70[s1];
        }
    case 1:
        if (w->flags & 0x1000000000000ULL) {
            if (w->flags & 0x2000000000000ULL) return 0x100B;
            return 0x1003;
        }
        if (w->flags & 1) return D_800E3E80[s1];
        s2 = D_800FADB9[w->id];
        if (func_800BF1E0(w, s2) < 0x19) return D_800E3F18[s2];
        if (timer < 350.0) return D_800E3E80[s1];
        if (timer > 355.0) return 0xE73;
        {
            s32 v;
            v = w->animId;
            if ((v ^ 0xE73) == 0) return 0xE73;
            return D_800E3E80[s1];
        }
    case 12: return D_800E3E80[s1];
    case 9:
        if (w->flags & WR_FLAG_ON_APRON) {
            if (w->flags & 0x8000000000ULL) return 0x1091;
            return 0x1092;
        }
        if (w->flags & 0x1000000000000ULL) {
            if (w->flags & 0x2000000000000ULL) return 0x1026;
            return 0x102A;
        }
        if (s1 == 6) return 0xE82;
        return 0xE6F;
    case 10:
        if (w->flags & WR_FLAG_ON_APRON) {
            if (w->flags & 0x8000000000ULL) return 0x108F;
            return 0x1090;
        }
        if (w->flags & 0x1000000000000ULL) {
            if (w->flags & 0x2000000000000ULL) return 0x1027;
            return 0x102B;
        }
        if (PROFILE_BITS(w) & 0x100) {
            if (w->moveMode & 0x20) return 0xE6E;
        }
        return D_800E3E90[s1];
    case 11:
        if (w->flags & WR_FLAG_ON_APRON) {
            if (w->flags & 0x8000000000ULL) return 0x1093;
            return 0x1094;
        }
        if (w->flags & 0x1000000000000ULL) {
            if (w->flags & 0x2000000000000ULL) return 0x1028;
            return 0x102C;
        }
        if (PROFILE_BITS(w) & 0x100) return 0xE83;
        if (PROFILE_BITS(w) & 0x200) return 0xE75;
        if (w->flags & 8) return 0xE75;
        return 0xE70;
    }
    return 0;
}
