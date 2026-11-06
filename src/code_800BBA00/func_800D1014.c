/* @header
 * func_800D1014
 * VRAM 0x800D1014 | ROM 0xC44B4 | size 0x710
 * asm: asm/nonmatchings/code_800BBA00/func_800D1014.s
 */
#include "common.h"

typedef struct {
    f32 x, y, z;
    s32 angle;
} Nw2Dir;

extern s8 D_800FADB8;
extern u8 D_800FABE4;
extern u16 D_800E3CD0[];
extern s32 D_800EB5C0[][4];
extern s32 D_800EB5C4[][4];
extern f32 D_800EB5C8[][4];
extern s32 D_800EB5CC[][4];

s16 func_800D5438(void *, s32);
void func_800D427C(void *, s16, s32);
s32 func_800D1B5C(void *, void *);
void func_800D1EA8(void *, void *);
f32 func_800D3890(void *, void *, void *);
s32 func_800D3E40(void *, f32 *, s32, f32 *);
void func_800D36B4(void *, void *, void *);
void translateEntityXZ(void *, void *);
s32 func_800D3684(s32, s32);
s32 func_800D35B0(s32, s32);
s32 func_800D2BEC(void *, void *, void *, f32, u16, s32);
s16 findBoundaryQuadrant(void *, s32, s32);
void func_800D43B4(void *, s16, s32);
void func_800D4AD0(void *);
s32 func_800D6610(void *, s16);
void func_800A6BE0(void *, s32);
void func_800A837C(void *);
void func_800A7C40(void *, s8, s16);
void func_800A7240(void *, s32, s32, u64);

void func_800D1014(void) {
    Nw2Dir dir;
    f32 buf[4];

    D_800FAF5C->flags |= 0x1000000000ULL;

    switch (D_800FAF5C->step) {
    case 0: {
        s32 v;
        func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 0), 2);
        D_800EB5C0[D_800FADB8][0] = 0;
        D_800EB5C8[D_800FADB8][0] = func_800D3890(&D_800FAF5C->x, &D_800F9B00->x, 0);
        v = func_800D1B5C(D_800FAF5C, D_800F9B00);
        D_800EB5CC[D_800FADB8][0] = v;
        D_800FAF5C->turnPerTick = func_800D3684(v, D_800FAF5C->heading) / D_800FAF5C->animFramesLeft;
        D_800FAF5C->step++;
    }
    case 1: {
        s32 v;
        if (!(D_800FAF5C->pairSignals & 0x40)) {
            func_800D2BAC(D_800FAF5C, D_800F9B00, 1.0f, 2);
            v = func_800D35B0(D_800FAF5C->heading, D_800FAF5C->turnPerTick);
            D_800FAF5C->heading = v;
            D_800F9B00->heading = func_800D35B0(v, 0x800);
            func_800D3E40(&D_800FAF5C->x, &D_800EB5C0[D_800FADB8][0], D_800FAF5C->heading, buf);
            buf[1] = 0;
            func_800D36B4(&D_800F9B00->x, buf, &dir);
            translateEntityXZ(D_800F9B00, &dir);
        }
        if (D_800FAF5C->animFrame == D_800FAF5C->anim.reversalFrame) {
            if (D_800F9B00->flags & 0x1000000) {
                Wrestler *p;
                func_800D427C(D_800FAF5C, func_800D5438(D_800F9B00, 1), 1);
                func_800A6BE0(D_800FAF5C, 0x4A);
                p = D_800FAF5C;
                p->heldById = D_800FABE4;
                p->pairSignals |= 8;
                break;
            }
        }
        if (D_800FAF5C->animFramesLeft > 0) break;
        func_800A7C40(D_800FAF5C, D_800FAF5C->moveOwnerId, (s16)((s8)D_800FAF5C->move.unk3A7 + 0xEF));
        func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 0), 3);
        D_800FAF5C->step++;
    }
        break;
    case 2:
        func_800D3890(&D_800FAF5C->x, &D_800F9B00->x, &dir);
        D_800EB5C8[D_800FADB8][0] = dir.y;
        D_800EB5C0[D_800FADB8][0] = 0;
        D_800EB5C4[D_800FADB8][0] = 0;
        D_800EB5CC[D_800FADB8][0] = func_800D3684(dir.angle, D_800FAF5C->heading);
        func_800D1EA8(D_800FAF5C, D_800F9B00);
        D_800FAF5C->step++;
        break;
    case 3: {
        s32 v;
        if (D_800FAF5C->animFramesLeft <= 0) {
            func_800D43B4(D_800FAF5C, func_800D5438(D_800FAF5C, 0), 0);
        }
        if ((D_800FAF5C->move.flags & 0x1000) && !(D_800FAF5C->pairSignals & 0x40)) {
            v = func_800D6610(D_800FAF5C, D_800FAF5C->dirIndex);
            if (D_800FAF5C->move.flags & 0x20000) {
                v = func_800D35B0(v, 0x800);
            }
            func_800A7240(D_800FAF5C, v, 0x16, 0);
            D_800F9B00->heading = func_800D35B0(D_800FAF5C->heading, 0x800);
            func_800D3E40(&D_800FAF5C->x, &D_800EB5C0[D_800FADB8][0], func_800D35B0(D_800FAF5C->heading, D_800EB5CC[D_800FADB8][0]), buf);
            buf[1] = 0;
            func_800D36B4(&D_800F9B00->x, buf, &dir);
            translateEntityXZ(D_800F9B00, &dir);
        }
        func_800D1EA8(D_800FAF5C, D_800F9B00);
        if (D_800FAF5C->move.flags & 0x1000) {
            if (!(D_800FAF5C->move.flags & 0x40000)) {
                s16 q = findBoundaryQuadrant(D_800FAF5C, 0, 1);
                if (q != -1 && q == D_800FAF5C->dirIndex) {
                    D_800FAF5C->pairSignals |= 1;
                }
            }
            if (!(D_800FAF5C->pairSignals & 0x40)) {
                func_800D2BAC(D_800FAF5C, D_800F9B00, 1.0f, 2);
            }
        } else {
            s32 w;
            w = func_800D2BAC(D_800FAF5C, D_800F9B00, 1.0f, 2);
            if ((w & 0xFFFF) && (D_800E3CD0[D_800FAF5C->dirIndex] & w)) {
                D_800FAF5C->pairSignals |= 1;
            }
        }
        if (D_800FAF5C->pairSignals & 1) {
            D_800FAF5C->pairSignals |= 2;
            func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 2), 3);
            func_800A837C(D_800FAF5C);
            D_800FAF5C->step++;
        }
    }
        break;
    case 4: {
        Wrestler *p;
        if (D_800FAF5C->anim.unk372[2] != 1) {
            func_800D2BEC(D_800FAF5C, D_800F9B00, 0, 4.0f, 0, 2);
        }
        p = D_800FAF5C;
        if (p->animFramesLeft <= 0) {
            p->attached[0] = -1;
            p->flags &= ~WR_FLAG_PAIR_LEADER;
            func_800D4AD0(D_800FAF5C);
            func_800A6C48(D_800FAF5C, 0x2B);
        }
        break;
    }
    }
}
