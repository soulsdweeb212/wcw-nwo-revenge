/* @header
 * func_800A01B0
 * VRAM 0x800A01B0 | ROM 0x93650 | size 0xE4C
 * asm: asm/nonmatchings/code_8009D7A0/func_800A01B0.s
 */
#include "common.h"

extern s32 D_800EB3F0[];
#ifdef TARGET_PC
/* PC: D_800F9B0C is a float (the distance to the opponent), and func_800DF3E4's last parameter is a float (its
 * definition: s32 func_800DF3E4(Wrestler *, Wrestler *, s32, f32)). The N64 code reads the float's bits as an s32
 * (D_800F9B0C[0]) and passes them in a3, an integer register, where the N64 callee reads them as a float. On the PC an
 * s32 argument would be converted to a float of another value, so the PC declares the elements f32 and D_800F9B0C[0]
 * reads the float. f32 and s32 are both 4 bytes, so D_800F9B0C - 1 below names the same address as with the N64
 * type. */
extern f32 D_800F9B0C[];
#else
extern s32 D_800F9B0C[];
#endif
extern s16 D_800FABD4;
extern u32 D_800FABD8;
extern s8 D_800FABDC;
extern u16 D_800FABE6;
extern s8 D_800FADB8;
extern u8 D_800FADCF;
extern s8 D_800FAF78;
extern u16 D_800FAF8A;
extern s16 D_800FAF9E;

void func_800A6BE0(void *, s32);
void func_800A7828(void *, void *);
void func_800A7C40(void *, s32, s32);
void func_800A7F6C(void *, s32);
void func_800A837C(void *);
s8 func_800A9128(void *);
void func_800A9488(void *, void *);
void func_800B68A0(void *, void *, void *);
void func_800D25D0(void *, f32);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D2B64 */
void func_800D2B64(void *, f32, s32, s32);
#endif
s32 func_800D36E8(f32, f32);
void func_800D427C(void *, s16, s32);
void func_800D4AD0(void *);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D4D44 and func_800D5438 */
s32 func_800D4D44(void *, s32, s32);
s32 func_800D5438(void *, s32);
#endif
s8 func_800DF214(void *, u16);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800DF3E4 */
s8 func_800DF3E4(void *, void *, u16, s32);
#endif
s8 func_800DF99C(void *, void *, u16, s32 *);
s8 func_800DFDD4(void *, void *, u16, s32 *);
s8 func_800E022C(void *, void *, u16, s32 *);
void func_800E212C(void *);

void func_800A01B0(void) {
    s32 s0;
    s32 s1;
    Wrestler *o2;
    s32 v;
    s32 anim;

    func_800D93DC(D_800EB408);
    switch (D_800EB408->step) {
    case 0:
        if (D_800FADCF & 0x40) {
            func_800E212C(D_800EB408);
            D_800FADCF |= 0x20;
            D_800EB408->step = 4;
            break;
        }
        if (!(D_800EB408->flags & 0x80)) {
            if (func_800D3550(func_800D3684(0x800, func_800D36E8(D_800FABD4, D_800FAF9E))) < 0xAA) {
                D_800EB408->step = 7;
                break;
            }
        }
        if (D_800EB408->flags & 0x40000) {
            D_800EB408->flags = (D_800EB408->flags & ~0x40000) | 0x80000;
            D_800EB408->stepFlags |= 1;
            if (D_800EB408->flags & 0x80) {
                func_800A7C40(D_800EB408, D_800FADB8, 0xC2);
                s0 = func_800D5438(D_800EB408, 0);
            } else {
                func_800A7C40(D_800EB408, D_800FADB8, 0xBE);
                s0 = func_800D5438(D_800EB408, 0);
                func_800A7828(D_800EB408, D_800EB40C);
            }
            func_800D427C(D_800EB408, s0, 3);
            func_800A7F6C(D_800EB408, 0x3F);
            func_800A9488(D_800EB408, D_800EB40C);
            D_800EB408->step++;
            break;
        }
        if (D_800EB408->flags & 0x80000) {
            if (D_800EB408->flags & 0x80) {
                s1 = 0xC2;
            } else {
                s1 = 0xBE;
            }
            func_800A7C40(D_800EB408, D_800FADB8, s1);
            s0 = func_800D5438(D_800EB408, 0);
        } else if (D_800EB408->flags & 1) {
            if (D_800EB408->flags & 0x80) {
                s1 = 0xC2;
            } else {
                s1 = 0xBD;
                if (D_800EB410->flags & 0x1000000000000000ULL) {
                    s1 = 0xBE;
                }
                if (D_800F9D10[D_800EB410->opponentId].flags & 0x1000000000000000ULL) {
                    s1 = 0xBD;
                }
            }
            func_800A7C40(D_800EB408, D_800FADB8, s1);
            s0 = func_800D5438(D_800EB408, 0);
        } else {
            if (D_800EB408->flags & 0x80) {
                s1 = 0xC2;
            } else {
                s1 = 0xBD;
            }
            func_800A7C40(D_800EB408, D_800FADB8, s1);
            s0 = func_800D5438(D_800EB408, 0);
        }
        if (!(D_800EB408->flags & 0x80)) {
            o2 = D_800EB410;
            if (D_800EB408->id != o2->id && !(o2->flags & 1) && o2->state == 0x17 && o2->animFrame < 10) {
                if (D_800EB408->flags & 1) {
                    func_800A7C40(D_800EB408, D_800EB408->id, 0xC1);
                    s0 = func_800D5438(D_800EB408, 0);
                } else {
                    anim = o2->moveId;
                    if (anim == s1) {
                        func_800A7C40(D_800EB408, D_800EB408->partnerId, anim);
                        s0 = func_800D5438(D_800EB408, 0);
                    }
                }
            }
        }
        func_800D427C(D_800EB408, s0, 3);
        D_800EB3F0[D_800FADB8] = func_800D36E8(D_800FABD4, D_800FAF9E);
        func_800A7F6C(D_800EB408, 0);
        D_800EB408->step++;
        break;
    case 1:
        if (D_800EB408->flags & 0x80) {
            D_800EB408->flags |= 0x0800000000000000ULL;
        }
        if (!(D_800EB40C->flags & 1) && !(D_800EB408->stepFlags & 1) && !(D_800EB408->flags & 0x80) && D_800EB408->animFrame < 7 && D_800FAF78 != 0
            && func_800D3550(func_800D3684(D_800EB3F0[D_800FADB8], func_800D36E8(D_800FABD4, D_800FAF9E))) > 0x600) {
            if (D_800EB40C->flags & 0x80000) {
                s1 = 0xBE;
            } else {
                s1 = 0xBD;
            }
            func_800A7C40(D_800EB408, D_800EB40C->id, s1);
            func_800D427C(D_800EB408, func_800D5438(D_800EB408, 0), 3);
            D_800EB408->stepFlags |= 1;
        }
        if (func_800DF214(D_800EB408, D_800FABE6) || func_800DF3E4(D_800EB408, D_800EB40C, D_800FABE6, D_800F9B0C[0])) {
            goto block;
        }
        s0 = (s32)(D_800F9B0C - 1);
        if (func_800DFDD4(D_800EB408, D_800EB40C, D_800FABE6, (s32 *)s0)) {
            break;
        }
        if (func_800DF99C(D_800EB408, D_800EB40C, D_800FABE6, (s32 *)s0) || func_800E022C(D_800EB408, D_800EB40C, D_800FABE6, (s32 *)s0)) {
block:
            func_800A9128(D_800EB408);
            break;
        }
        func_800D25D0(D_800EB408, 4.0f);
        func_800D2B64(D_800EB408, 4.0f, 0, 0xFFFFE);
        if (D_800EB408->animFramesLeft > 0) {
            break;
        }
        if (!(D_800EB408->flags & 0x100) || (D_800EB40C->flags & 0x100)) {
            func_800B68A0(D_800EB408, D_800EB408, D_800EB40C);
        }
        func_800A7828(D_800EB408, D_800EB40C);
        func_800D4AD0(D_800EB408);
        if (func_800A9128(D_800EB408)) {
            func_800A6BE0(D_800EB408, 1);
            func_800D427C(D_800EB408, 0x108D, 2);
        } else {
            func_800A6C48(D_800EB408, 1);
        }
        func_800A837C(D_800EB408);
        break;
    case 2:
        anim = 0xBF;
        func_800A7C40(D_800EB408, D_800FADB8, anim);
        func_800D427C(D_800EB408, func_800D5438(D_800EB408, 0), 1);
        func_800A7F6C(D_800EB408, 0);
        if (D_800EB408->flags & 0x40000) {
            D_800EB408->flags = (D_800EB408->flags & ~0x40000) | 0x80000;
            func_800A9488(D_800EB408, D_800EB40C);
        }
        D_800EB408->step++;
        break;
    case 3:
        if (func_800DF214(D_800EB408, D_800FABE6)) {
            break;
        }
        if (func_800DF3E4(D_800EB408, D_800EB40C, D_800FAF8A, D_800F9B0C[0])) {
            break;
        }
        s0 = (s32)(D_800F9B0C - 1);
        if (func_800DFDD4(D_800EB408, D_800EB40C, D_800FABE6, (s32 *)s0)) {
            break;
        }
        if (func_800DF99C(D_800EB408, D_800EB40C, D_800FABE6, (s32 *)s0)) {
            break;
        }
        if (func_800E022C(D_800EB408, D_800EB40C, D_800FABE6, (s32 *)s0)) {
            break;
        }
        func_800D25D0(D_800EB408, 4.0f);
        func_800D2B64(D_800EB408, 4.0f, 0, 0xFFFFE);
        if (D_800EB408->animFramesLeft > 0) {
            break;
        }
        if (!(D_800EB408->flags & 0x100) || (D_800EB40C->flags & 0x100)) {
            func_800B68A0(D_800EB408, D_800EB408, D_800EB40C);
        }
        func_800D4AD0(D_800EB408);
        func_800A6C48(D_800EB408, 0x2B);
        func_800A7828(D_800EB408, D_800EB40C);
        func_800A837C(D_800EB408);
        break;
    case 4:
        func_800A7C40(D_800EB408, D_800EB408->id, 0xC3);
        func_800D427C(D_800EB408, func_800D5438(D_800EB408, 0), 3);
        D_800EB408->stateTimer = 0;
        D_800EB408->step++;
        break;
    case 5:
        if (++D_800EB408->stateTimer == 30 && D_800EB408->id == D_800FABDC) {
            D_800FABD8 |= 4;
        }
        func_800D25D0(D_800EB408, 4.0f);
        func_800D2B64(D_800EB408, 4.0f, 0, 0xFFFFE);
        if (D_800EB408->animFramesLeft > 0) {
            break;
        }
        v = D_800EB408->anim.frameCount;
        if (v > 0xB4) {
            v = 0xF;
        } else {
            v = 0xC3 - v;
        }
        D_800EB408->stateTimer = v;
        if (D_800EB408->id == D_800FABDC) {
            D_800FABD8 |= 4;
        }
        func_800D4AD0(D_800EB408);
        func_800D427C(D_800EB408, func_800D4D44(D_800EB408, 0xC, 0), 3);
        D_800EB408->step++;
        break;
    case 6:
        if (--D_800EB408->stateTimer == 0 && D_800EB408->id == D_800FABDC && (D_800FABD8 & 0x100)) {
            D_800FABD8 |= 1;
            D_800FADCF &= ~0x20;
        }
        if (D_800EB408->stateTimer < -29) {
            D_800EB408->stateTimer = -30;
        }
        break;
    case 7:
        D_800EB408->flags |= 0x1000000000ULL;
        func_800D427C(D_800EB408, 0xFB9, 3);
        D_800EB408->step++;
        break;
    case 8:
        D_800EB408->flags |= 0x1000000000ULL;
        func_800D25D0(D_800EB408, 4.0f);
        func_800D2B64(D_800EB408, 4.0f, 0, 0xFFFFE);
        if (D_800EB408->animFramesLeft > 0) {
            break;
        }
        func_800D4AD0(D_800EB408);
        D_800EB408->step = 2;
        break;
    }
}
