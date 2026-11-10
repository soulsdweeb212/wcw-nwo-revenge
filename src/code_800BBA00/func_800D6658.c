/* @header
 * func_800D6658
 * VRAM 0x800D6658 | ROM 0xC9AF8 | size 0x820
 * asm: asm/nonmatchings/code_800BBA00/func_800D6658.s
 */
#include "common.h"

extern s32 D_800E3CFC[];
extern u16 D_800E3F84[], D_800E3F8C[];
extern f64 D_800E6D60, D_800E6D68, D_800E6D70;
typedef struct { f32 x, y, z; s32 angle; } Nw2DirRes;
s8 func_800D25D0(Wrestler *, f32);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D2B64 */
void func_800D2B64(void *, f32, s32, s32);
#endif
void func_800D3890(void *, void *, void *);
void func_800D427C(Wrestler *, s32, s32);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D4D44 */
s16 func_800D4D44(Wrestler *, s32, f32);
#endif
f32 func_800D63F0(Wrestler *, void *, s32);
s16 func_800D7A68(u16);

/* Shift the root and joints 1..19 (both ends) by ofs[0] on X and ofs[2] on Z. */
static inline void moveAll(Wrestler *w, f32 *ofs) {
    s16 i;
    w->x += ofs[0];
    w->z += ofs[2];
    for (i = 1; i < 0x14; i++) {
        w->jointA[i].x += ofs[0];
        w->jointA[i].z += ofs[2];
        w->jointB[i].x += ofs[0];
        w->jointB[i].z += ofs[2];
    }
}

/* Same test as func_800D65D0: 1 when mask meets D_800E3F84[side], 2 when it meets D_800E3F8C[side], else 0. */
static inline s16 chooseDirection(s16 q, u16 mask) {
    if (mask & D_800E3F84[q]) return 1;
    if (mask & D_800E3F8C[q]) return 2;
    return 0;
}

/* Directional movement step of w (other = its opponent) for the direction bits arg2 & 0xF00 (0x800 +Z, 0x100 +X,
 * 0x400 -Z, 0x200 -X), mode arg3, timer arg4 passed on to func_800D4D44.
 * - On the apron (WR_FLAG_ON_APRON): move by the func_800D63F0 speed along the pressed axes, start animation
 *   0x1081 when chooseDirection(ringSide, arg2) is 0, else 0x108D, then push apart (func_800D25D0).
 * - Elsewhere: per axis take res[0] (func_800D63F0 X value) when moving toward the opponent's pelvis and res[2]
 *   otherwise, scale by D_800E6D60 when the func_800D7A68 group of arg2 is even (diagonals 0x900/0x500/0x600/0xA00
 *   and unlisted combinations) and by D_800E6D68 in mode 1. With flags bit 0x800000000 set: if the heading is
 *   within 0x100 of the D_800E3CFC[group] direction and the opponent is in state 0x2D, scale by D_800E6D70 and
 *   move both wrestlers; otherwise clear the bit, move w and start the func_800D4D44(w, 0, timer) animation.
 *   Without the bit: move w and, in mode 0 only, push apart; if the wrestler pushed against is the opponent, the
 *   opponent is in state 0x2D, flags bit 1 << 48 is clear, w faces the opponent's pelvis within 0x17 and the
 *   heading is within 0x100 of D_800E3CFC[group], set bit 0x800000000; then start animation 0xE5F (bit set) or
 *   func_800D4D44(w, 0, timer), with mode 3.
 * - No direction pressed: clear bit 0x800000000, func_800DECAC(w, 0, 0, 0) (only zeroes D_800F98D0[id]), push
 *   apart, and in mode 0 start 0x1081 (apron) or func_800D4D44(w, 1, timer).
 * Finally func_800D2B64(w, 1.0f, 0, 2). Declared void, but some callers use the value func_800D2B64 leaves in v0. */
#ifdef TARGET_PC
/* PC: the callers use a result (func_800C16BC, func_800C17D8, func_800C18D4 and func_8009DD60 declare it to return
 * s32 or u32): the value of the func_800D2B64 call at the end, which the N64 leaves in v0, where this function,
 * declared void, does not touch v0 before it returns. On PC the function returns it (port_decls.h declares it so). */
s32 func_800D6658(Wrestler *w, Wrestler *other, u16 arg2, s32 arg3, f32 arg4) {
#else
void func_800D6658(Wrestler *w, Wrestler *other, u16 arg2, s32 arg3, f32 arg4) {
#endif
    f32 off[3];
    f32 res[3];
    Nw2DirRes dir;
    volatile f64 pad[3];
    f32 t;
    s16 r;
    u16 m = arg2;
    s32 f = arg3;

    if (arg2 & 0xF00) {
        off[0] = 0.0f;
        off[2] = 0.0f;
        t = func_800D63F0(w, res, 0);
        if (w->flags & WR_FLAG_ON_APRON) {
            if (arg2 & 0x800) off[2] = t;
            if (arg2 & 0x100) off[0] = t;
            if (arg2 & 0x400) off[2] = -t;
            if (arg2 & 0x200) off[0] = -t;
            moveAll(w, off);
            r = chooseDirection(w->ringSide, m);
            {
                s32 tt = r;
                s32 a = 0x1081;
                if (tt != 0) a = 0x108D + (((tt << 16) >> 16) - tt);
                func_800D427C(w, a, 0);
            }
            func_800D25D0(w, 4.0f);
        } else {
            if (m & 0x800) {
                if (other->jointA[1].z > w->jointA[1].z) off[2] = res[0];
                else off[2] = res[2];
            }
            if (m & 0x100) {
                if (other->jointA[1].x > w->jointA[1].x) off[0] = res[0];
                else off[0] = res[2];
            }
            if (m & 0x400) {
                if (other->jointA[1].z < w->jointA[1].z) off[2] = -res[0];
                else off[2] = -res[2];
            }
            if (m & 0x200) {
                if (other->jointA[1].x < w->jointA[1].x) off[0] = -res[0];
                else off[0] = -res[2];
            }
            r = func_800D7A68(m);
            if (!(r & 1)) {
                off[0] *= D_800E6D60;
                off[2] *= D_800E6D60;
            }
            if ((s16)f == 1) {
                off[0] *= D_800E6D68;
                off[2] *= D_800E6D68;
            }
            if (w->flags & 0x800000000ULL) {
                if (func_800D3550(func_800D3684(w->heading, D_800E3CFC[r])) < 0x101 && other->state == 0x2D) {
                    off[0] *= D_800E6D70;
                    off[2] *= D_800E6D70;
                    moveAll(w, off);
                    moveAll(other, off);
                } else {
                    /* raw access: a member store is scheduled differently */
                    *(u64 *)(u8 *)&w->flags &= ~0x800000000ULL;
                    moveAll(w, off);
                    func_800D427C(w, func_800D4D44(w, 0, arg4), 1);
                }
            } else {
                moveAll(w, off);
                if ((s16)f == 0) {
                    s8 cur;
                    cur = func_800D25D0(w, 4.0f);
                    if (w->opponentId == cur && other->state == 0x2D && !(w->flags & 0x1000000000000ULL)) {
                        func_800D3890(&w->jointA[1], &other->jointA[1], &dir);
                        if (func_800D3550(func_800D3684(w->heading, dir.angle)) < 0x17
                            && func_800D3550(func_800D3684(w->heading, D_800E3CFC[r])) < 0x101) {
                            w->flags |= 0x800000000ULL;
                        }
                    }
                    if (w->flags & 0x800000000ULL) func_800D427C(w, 0xE5F, 3);
                    else func_800D427C(w, func_800D4D44(w, 0, arg4), 3);
                }
            }
        }
    } else {
        w->flags &= ~0x800000000ULL;
        func_800DECAC(w, 0, 0, 0);
        func_800D25D0(w, 4.0f);
        if ((s16)arg3 == 0) {
            if (w->flags & WR_FLAG_ON_APRON) func_800D427C(w, 0x1081, 0);
            else func_800D427C(w, func_800D4D44(w, 1, arg4), 3);
        }
    }
#ifdef TARGET_PC
    /* PC: the result the callers read. */
    return func_800D2B64(w, 1.0f, 0, 2);
#else
    func_800D2B64(w, 1.0f, 0, 2);
#endif
}
