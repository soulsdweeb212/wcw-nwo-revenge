/* @header
 * func_800CA758
 * VRAM 0x800CA758 | ROM 0xBDBF8 | size 0x8FC
 * asm: asm/nonmatchings/code_800BBA00/func_800CA758.s
 */
#include "common.h"

extern s8 D_800FADB8;
extern u16 D_8007EF30[];
extern u16 D_800EB570[];
extern s16 D_800F9B80[];
extern u16 D_800FADD2[];
extern s8 D_800FAF78;
extern u16 D_800FAF8A;

s16 func_800D7690(void *, s32, s16);
s32 func_800D5438(void *, s16);
void func_800D427C(void *, s16, s32);
u16 func_800B6DEC(void *, void *, s32);
s8 func_800D4198(s16);
s16 func_800BF2FC(void *);
void func_800A7D1C(void *, s32);
void func_800B68A0(void *, void *, void *);
void func_8009791C(void);
s32 func_800D2BEC(void *, void *, void *, f32, u16, s32);
void func_800D4AD0(void *);
void beginEntityActionA8D8C(void *);
s32 func_800D3684(s32, s32);
s32 func_800D35B0(s32, s32);
void func_800A7240(void *, s32, s32, u64);

void func_800CA758(void) {
    s32 anim;
    switch (D_800FAF5C->step) {
    case 0: {
        u16 mask;

        D_800FAF5C->flags |= 0x400000000000ULL;
        if (D_800FAF5C->state == 0x39) {
            anim = (u16)D_800F9B00->animId + 1;
            *(s16 *)&D_800FAF5C->lastMoveTakenId = -1;
        } else {
            anim = func_800D5438(D_800F9B00, 1);
        }
        func_800D427C(D_800FAF5C, (s16)anim, 1);

        mask = D_8007EF30[0xB8];
        D_800EB570[D_800FADB8] = 0;
        if (mask & 0x20) {
            if ((D_800FAF5C->flags & 0x100) && !(mask & 0x100)) {
                D_800FAF5C->escapeTimer = 0x1E;
            } else {
                D_800FADD2[D_800FADB8]++;
                D_800FAF5C->escapeTimer = func_800B6DEC(D_800FAF5C, D_800F9B00, 1);
                if (D_800FAF5C->state == 0x3F) {
                    if ((D_800F9B00->flags & 0x80000) && func_800D4198(0x1F4)) {
                        D_800FAF5C->escapeTimer = 0x7530;
                    }
                }
                if (D_800F9B80[D_800FADB8] < 2) {
                    if ((D_800F9B00->spirit - D_800FAF5C->spirit) < 0x46 || func_800BF2FC(D_800FAF5C) > 0) {
                        if (D_800FAF5C->escapeTimer >= 0x58) D_800FAF5C->escapeTimer = 0x57;
                    }
                }
                if ((D_800FAF5C->flags & D_800F9B00->flags) & 0x200) D_800FAF5C->flags |= 0x400;
            }
            if (D_800FAF5C->escapeTimer < 0xF) D_800FAF5C->escapeTimer = 0xF;
        } else {
            D_800FAF5C->escapeTimer = 5;
        }
        func_800D7690(D_800FAF5C, 0, 0);
        D_800FAF5C->step++;
        break;
    }
    case 1: {
        s16 r;

        D_800FAF5C->flags |= 0x400000000000ULL;
        r = func_800D7690(D_800FAF5C, D_800FAF8A, 1);
        if (r != 0 && (r == 1 || r == 3)) {
            u16 t = D_800FAF5C->escapeTimer;
            D_800FAF5C->escapeTimer = t - 1;
            if (r == 3) D_800FAF5C->escapeTimer = t - 2;
        }
        D_800FAF5C->escapeTimer = D_800FAF5C->escapeTimer - 1;
        if (D_800FAF78) D_800FAF5C->escapeTimer = 1;
        if (D_800FAF5C->escapeTimer < 0) {
            if ((D_800F9B00->pairSignals & 0x1F) == 0) {
                D_800F9B00->pairSignals |= 2;
                func_800A7D1C(D_800FAF5C, 0x13);
                func_800B68A0(D_800FAF5C, D_800FAF5C, D_800F9B00);
            }
        }
        if (D_800FAF5C->state == 0x3F) {
            u16 *p = D_800EB570;
            if ((s16)++p[D_800FADB8] >= 0x1F) {
                func_800B68A0(D_800F9B00, D_800F9B00, D_800FAF5C);
                p[D_800FADB8] = 0;
            }
        }
        if (func_800D2BAC(D_800FAF5C, D_800F9B00, 4.0f, 0xFFFFE)) {
            if ((D_800F9B00->pairSignals & 0x1F) == 0) {
                if ((D_8007EF30[0xB8] & 2) && !(D_800FAF5C->flags & 0x100)) {
                    D_800F9B00->pairSignals |= 4;
                    if ((D_800FAF5C->flags & D_800F9B00->flags) & 0x200) func_8009791C();
                }
            }
        }
        if ((D_800F9B00->pairSignals & 0x1F) != 0) {
            D_800FAF5C->flags &= ~0x400ULL;
        }
        if (D_800F9B00->pairSignals & 0x20) {
            if ((D_8007EF30[0xB8] & 0x20) && (D_800F9B00->pairSignals & 2)) {
                if ((D_800FAF5C->flags & 0x40) || ((D_800FAF5C->flags & 0x100) && (D_8007EF30[0xB8] & 0x100)))
                    D_800F9B80[D_800FADB8]++;
            }
            if (D_800FAF5C->state == 0x39) {
                anim = (u16)D_800F9B00->animId + 1;
            } else {
                if (D_800F9B00->pairSignals & 0x10) anim = 7;
                else if (D_800F9B00->pairSignals & 8) anim = 5;
                else anim = 3;
                anim = func_800D5438(D_800F9B00, anim);
            }
            func_800D427C(D_800FAF5C, (s16)anim, 6);
            D_800FAF5C->step++;
        }
        break;
    }
    case 2: {
        func_800D2BEC(D_800FAF5C, D_800F9B00, 0, 2.0f, 0, 0xFFFFE);
        if (D_800FAF5C->animFramesLeft <= 0) {
            func_800D4AD0(D_800FAF5C);
            if (D_800FAF5C->state == 0x39) {
                if (D_800FAF5C->flags & 0x8000) {
                    beginEntityActionA8D8C(D_800FAF5C);
                } else {
                    D_800FAF5C->flags |= 0x80000000000000ULL;
                    func_800A6C48(D_800FAF5C, 0x2B);
                }
            } else {
                if ((D_800FAF5C->flags & 0x100) || (D_800F9B00->move.flags & 4) || (D_800FAF5C->pairSignals & 0x40) || (D_800FAF5C->flags & 0x8000)) {
                    beginEntityActionA8D8C(D_800FAF5C);
                } else {
                    D_800FAF5C->flags |= 0x80000000000000ULL;
                    func_800A6C48(D_800FAF5C, 0x2B);
                }
            }
        }
        break;
    }
    case 3:
        func_800D427C(D_800FAF5C, 0xFC6, 1);
        func_800B68A0(D_800F9B64, D_800F9B64, D_800FAF5C);
        D_800FAF5C->step++;
        break;
    case 4: {
        s32 r;

        func_800D2BAC(D_800FAF5C, D_800F9B00, 4.0f, 0xFFFFE);
        if (func_800D3684(D_800FAF5C->heading, D_800F9B00->heading) < 0)
            r = func_800D35B0(D_800F9B00->heading, -0x400);
        else
            r = func_800D35B0(D_800F9B00->heading, 0x400);
        func_800A7240(D_800FAF5C, r, 0x16, 0);
        if (D_800FAF5C->animFramesLeft <= 0 && D_800F9B00->step != 3) {
            D_800FAF5C->step = 0;
            D_800FAF5C->flags |= 0x10000000;
        }
        break;
    }
    }
}
