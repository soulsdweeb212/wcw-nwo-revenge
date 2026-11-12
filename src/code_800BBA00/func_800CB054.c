/* @header
 * func_800CB054
 * VRAM 0x800CB054 | ROM 0xBE4F4 | size 0x824
 * asm: asm/nonmatchings/code_800BBA00/func_800CB054.s
 */
#include "common.h"

extern s8 D_800FADB8;
#ifndef TARGET_PC /* on PC, port_decls.h declares D_800F9B14 (an s32: the heading) */
extern u32 D_800F9B14;
#endif
extern u16 D_800FABE6;
#ifdef TARGET_PC
/* PC: D_800E3CFC is D_800E3D00 one entry back, which the code indexes from 1. Its own 4 bytes are the last two
 * u16 entries of D_800E3CF0, the eight directions' bits, so on PC no file names it: an s32 there would make the
 * port convert those bytes as one 32-bit value. Index 0 is the s32 the N64 reads there, made of those two
 * entries. */
extern s32 D_800E3D00[];
#else
extern s32 D_800E3CFC[];
#endif
extern u8 D_800FACF8[];
extern u8 D_800EB578[];
extern u8 D_800EB57C[];
extern u8 D_800EB584[];

s8 func_800A7240(void *, s32, s32, u64);
void func_800A837C(void *);
s8 func_800A83DC(void *, void *);
void func_800B68A0(void *, void *, void *);
s8 func_800CBC4C(void *, void *);
s32 func_800D2BEC(void *, void *, void *, f32, u16, s32);
s32 func_800D3550(s32);
s32 func_800D35B0(s32, s32);
s32 func_800D3684(s32, s32);
void func_800D3890(void *, void *, void *);
s32 func_800D3E40(void *, void *, s32, void *);
void func_800D427C(void *, s16, s32);
void func_800D43B4(void *, s16, s32);
void func_800D4AD0(void *);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D5438 */
s16 func_800D5438(void *, s32);
#endif
void func_800D7128(void *, void *, void *, void *);
s8 func_800D732C(void *, void *);
s32 func_800D7A68(s32);

void func_800CB054(void) {
#ifdef TARGET_PC
    /* PC: out is arr + 4 and func_800D3E40 writes out[0..2], so the array needs 7 floats; the N64's 6 leave its last
     * write in the stack space after the array. */
    f32 arr[7];
#else
    f32 arr[6];
#endif
#define vec arr
#define out (arr+4)
    s32 anim;
    s32 r;
    s32 d;
    s16 sum;
    u8 *rec;
    Wrestler *o;

    switch (D_800FAF5C->step) {
    case 0:
        anim = (D_800FAF5C->flags & 0x200000000000000ULL) ? 0xF3A : 0xFB9;
        func_800D427C(D_800FAF5C, anim, 3);
        D_800FAF5C->step++;
        break;
    case 1:
        if (D_800F9B00->flags & 0x200000ULL) {
            D_800FAF5C->unk036 |= 2;
        }
        d = func_800D3550(func_800D3684(D_800F9B00->heading, D_800F9B14));
        if (D_800F9B00->flags & 0x200000ULL) {
            if (d < 0x401) {
                goto l198;
            }
        } else {
            if (d >= 0x400) {
                goto l198;
            }
        }
        D_800FAF5C->unk036 |= 1;
l198:
        vec[0] = 0.0f;
        if (D_800FAF5C->unk036 & 1) {
            vec[2] = -130.0f;
        } else {
            vec[2] = 150.0f;
        }
        if (D_800F9B00->flags & 0x200000ULL) {
            vec[2] = -vec[2];
        }
        func_800D3E40(&D_800F9B00->x, vec, D_800F9B00->heading, out);
        rec = D_800FACF8 + (s8)D_800FADB8 * 0x30;
        func_800D7128(D_800F9B00, D_800FAF5C, out, rec);
        D_800FAF5C->step++;
        /* fall through */
    case 2:
        func_800D2C68(D_800FAF5C, D_800F9B00, 4.0f, D_800FACF8 + (s8)D_800FADB8 * 0x30,
                      0xFFFFE);
        sum = func_800D732C(D_800FAF5C, D_800FACF8 + (s8)D_800FADB8 * 0x30);
        { s32 t = D_800F9B14; sum += func_800A7240(D_800FAF5C, t, 0x155, 0x100000000ULL); }
        if (sum != 2) {
            break;
        }
        if (D_800FAF5C->animFramesLeft > 0) {
            break;
        }
        D_800FAF5C->flags |= WR_FLAG_RERUN;
        if (!(D_800FAF5C->flags & 9ULL)) {
            if (!(D_800FABE6 & 0x8000)) {
                goto inc;
            }
            if (!(D_800FABE6 & 0xF00)) {
                goto inc;
            }
        }
        func_800D3890(&D_800F9B00->x, &D_800FAF5C->x,
                      D_800EB578 + (s8)D_800FADB8 * 16);
        D_800FAF5C->step = 5;
        break;
    case 3:
        func_800D2BEC(D_800FAF5C, D_800F9B00, 0, 4.0f, 0, 0xFFFFE);
        if (func_800CBC4C(D_800FAF5C, D_800F9B00)) {
            D_800FAF5C->pairSignals |= 2;
            r = func_800D5438(D_800F9B00, 1);
            func_800D427C(D_800FAF5C, r, 2);
            break;
        }
        D_800FAF5C->pairSignals |= 1;
        r = func_800D5438(D_800FAF5C, 0);
        func_800D427C(D_800FAF5C, r, 2);
        func_800A837C(D_800FAF5C);
        D_800FAF5C->step++;
        break;
    case 4:
        func_800D2BEC(D_800FAF5C, D_800F9B00, 0, 4.0f, 0, 0xFFFFE);
        if (D_800FAF5C->animFramesLeft == 1) {
            func_800B68A0(D_800FAF5C, D_800FAF5C, D_800F9B00);
        }
        if (D_800FAF5C->animFramesLeft > 0) {
            break;
        }
        if (func_800A83DC(D_800FAF5C, D_800F9B00)) {
            break;
        }
        o = D_800FAF5C;
        o->attached[0] = -1;
        o->flags &= ~WR_FLAG_PAIR_LEADER;
        func_800D4AD0(D_800FAF5C);
        func_800A6C48(D_800FAF5C, 0x2B);
        break;
    case 5:
        D_800FAF5C->pairSignals |= 4;
        anim = 0xFC8;
        if (!(D_800FAF5C->unk036 & 1)) {
            anim = 0xFD0;
        }
        if (D_800FAF5C->unk036 & 2) {
            anim += 0x10;
        }
        func_800D427C(D_800FAF5C, anim, 0);
        func_800D2BAC(D_800FAF5C, D_800F9B00, 4.0f, 0xFFFFE);
        if (D_800FAF5C->animFramesLeft > 0) {
            break;
        }
        func_800D427C(D_800FAF5C, (s16)(D_800FAF5C->animId + 2), 0);
inc:
        D_800FAF5C->step++;
        break;
    case 6:
        if (D_800F9B00->pairSignals & 0x18) {
            goto l758;
        }
        if (D_800FABE6 & 0x8000) {
            r = (s16)func_800D7A68(D_800FABE6);
            if (r != 0) {
#ifdef TARGET_PC
                /* PC: D_800E3D00, as above; r is not 0 here. */
                d = func_800D3684(D_800FAF5C->heading, D_800E3D00[r - 1]);
#else
                d = func_800D3684(D_800FAF5C->heading, D_800E3CFC[r]);
#endif
                if (func_800D3550(d) >= 0xE3 &&
                    func_800D3550(d) < 0x71D) {
                    if (d >= 0) {
                        d = 0xB;
                    } else {
                        d = -0xB;
                    }
                    D_800FAF5C->heading = func_800D35B0(D_800FAF5C->heading, d);
                    D_800F9B00->heading = func_800D35B0(D_800F9B00->heading, d);
                    *(s32 *)(D_800EB584 + (s8)D_800FADB8 * 16) =
                        func_800D35B0(
                            *(s32 *)(D_800EB584 + (s8)D_800FADB8 * 16), d);
                }
            }
            vec[0] = 0.0f;
            vec[2] = *(f32 *)(D_800EB57C + (s8)D_800FADB8 * 16);
            func_800D3E40(&D_800F9B00->x, vec,
                          *(s32 *)(D_800EB584 + (s8)D_800FADB8 * 16),
                          &D_800FAF5C->x);
        } else {
            D_800F9B00->pairSignals |= 8;
        }
l758:
        if (D_800FAF5C->animFramesLeft <= 0) {
            if (D_800F9B00->pairSignals & 0x18) {
                D_800FAF5C->pairSignals |= 0x20;
                func_800D427C(D_800FAF5C, (s16)(D_800FAF5C->animId + 4), 1);
                D_800FAF5C->step++;
            } else {
                func_800D43B4(D_800FAF5C, (s16)D_800FAF5C->animId, 1);
            }
        }
        func_800D2BAC(D_800FAF5C, D_800F9B00, 1.0f, 0xFFFFE);
        break;
    case 7:
        func_800D2BAC(D_800FAF5C, D_800F9B00, 1.0f, 0xFFFFE);
        o = D_800FAF5C;
        if (o->animFramesLeft <= 0) {
            o->attached[0] = -1;
            o->flags &= ~WR_FLAG_PAIR_LEADER;
            func_800D4AD0(D_800FAF5C);
            func_800A6C48(D_800FAF5C, 0x2B);
        }
        break;
    }
}
