/* @header
 * func_800AC3A0
 * VRAM 0x800AC3A0 | ROM 0x9F840 | size 0x8A8
 * asm: asm/nonmatchings/code_8009D7A0/func_800AC3A0.s
 */
#include "common.h"

extern s8 D_800FADB8;
extern u16 D_800FABE6;
extern u16 D_800FAF8A;
extern s8 D_800FAF78;
extern s16 D_800FAF8E[];
extern s16 D_800EB420[];
extern s16 D_800EB428[];
extern s16 D_800EB438[];
extern s16 D_800EB448[];
extern u16 D_800F9B78[];

void func_800A7C40(void *, s8, s16);
s16 func_800D5438(void *, s32);
void func_800D427C(void *, s16, s32);
s32 func_800AD218(void *, u16, u16, s8, s16 *);
void func_800AD6D0(void *);
void func_800D4AD0(void *);
void func_800AD2C4(void *, void *, u16, s16);
void func_800D7E80(void *, void *);
void func_800A7328(void *);
void func_800D43B4(void *, s16, s32);
s32 func_800D3E40(void *, f32 *, s32, f32 *);
void func_800D3838(void *, f32 *, s16, f32 *);
void translateEntityXZ(void *, void *);
s32 func_800D35B0(s32, s32);
s32 func_800D3684(s32, s32);
void func_800D8D74(void *, s32);
void func_800A6BE0(void *, s32);

void func_800AC3A0(void) {
    func_800D2BAC(D_800FAF5C, D_800F9B00, 2.0f, 0xFFFFE);

    switch (D_800FAF5C->step) {
    case 0:
        func_800A7C40(D_800FAF5C, D_800FADB8, 0xEC);
        D_800EB428[D_800FADB8] = func_800D5438(D_800FAF5C, 0);
        D_800EB428[D_800FADB8 + 4] = func_800D5438(D_800FAF5C, 1);
        func_800A7C40(D_800FAF5C, D_800FADB8, 0xED);
        D_800EB428[D_800FADB8 + 8] = func_800D5438(D_800FAF5C, 0);
        D_800EB428[D_800FADB8 + 12] = func_800D5438(D_800FAF5C, 1);
        func_800A7C40(D_800FAF5C, D_800FADB8, 0xEE);
        D_800EB428[D_800FADB8 + 16] = func_800D5438(D_800FAF5C, 0);
        D_800EB428[D_800FADB8 + 20] = func_800D5438(D_800FAF5C, 1);
        func_800D427C(D_800FAF5C, D_800EB428[D_800FADB8], 3);
        D_800EB420[D_800FADB8] = (s16)D_800F9B78[D_800FADB8] / 10;
        if (D_800FAF5C->grappleCtx & 1) {
            D_800EB420[D_800FADB8] = 0xA;
        } else {
            D_800EB420[D_800FADB8] = 6;
        }
        D_800FAF8E[D_800FADB8] = 0;
        D_800FAF5C->step++;
        break;
    case 1:
        if (D_800FAF5C->animFramesLeft == 1) {
            D_800FAF5C->step++;
        }
        break;
    case 2:
        func_800D427C(D_800FAF5C, D_800EB438[D_800FADB8], 3);
        D_800FAF5C->step++;
    case 3:
        if (D_800FAF5C->pairSignals & 1) {
            D_800FAF5C->pairSignals &= ~1;
            D_800FAF5C->step++;
            break;
        }
        if ((s8)func_800AD218(D_800FAF5C, D_800FABE6, D_800FAF8A, D_800FAF78, &D_800FAF8E[D_800FADB8])) {
            D_800FAF5C->step++;
        }
        if (D_800FAF5C->animFramesLeft > 0) {
            break;
        }
        D_800FAF5C->flags &= ~WR_FLAG_PAIR_LEADER;
        D_800FAF5C->attached[0] = -1;
        D_800F9B00->step = 3;
        func_800AD6D0(D_800FAF5C);
        func_800D4AD0(D_800FAF5C);
        func_800A6C48(D_800FAF5C, 0x2B);
        break;
    case 4:
        func_800AD2C4(D_800FAF5C, D_800F9B00, D_800FAF8E[D_800FADB8], D_800EB420[D_800FADB8]);
        if (D_800FAF5C->grappleCtx & 0x80000) {
            func_800D7E80(D_800FAF5C, D_800F9B00);
            func_800D427C(D_800FAF5C, D_800EB448[D_800FADB8], 2);
            D_800EB420[D_800FADB8]--;
            D_800FAF5C->step = 6;
            D_800F9B00->step = 7;
        } else {
            func_800A7328(D_800FAF5C);
            func_800D43B4(D_800FAF5C, (s16)func_800D5438(D_800FAF5C, 0), 2);
            D_800EB420[D_800FADB8]--;
            D_800FAF8E[D_800FADB8] = 0;
            D_800FAF5C->step++;
            D_800F9B00->step = 4;
            D_800F9B00->pairSignals &= ~2;
        }
        break;
    case 5: {
        s16 cnt;
        f32 dir[3];
        f32 out[4];
        s32 ang;
        s32 dd;

        if (D_800FAF5C->anim.hitEnd >= D_800FAF5C->animFrame) {
            cnt = D_800FAF5C->anim.hitEnd - D_800FAF5C->animFrame + 1;
            dir[0] = 0.0f;
            dir[2] = 130.0f;
            func_800D3E40(&D_800F9B00->jointA[1], dir, D_800F9B00->heading, out);
            func_800D3838(&D_800FAF5C->x, out, cnt, D_800FAF5C->moveDelta);
            translateEntityXZ(D_800FAF5C, D_800FAF5C->moveDelta);
            ang = func_800D35B0(D_800F9B00->heading, 0x800);
            dd = func_800D3684(ang, D_800FAF5C->heading) / cnt;
            D_800FAF5C->heading = func_800D35B0(D_800FAF5C->heading, dd);
        }
        if (D_800FAF5C->animFrame != D_800FAF5C->anim.hitEnd) {
            goto tail;
        }
        D_800F9B00->pairSignals |= 4;
        if (D_800F9B00->pairSignals & 2) {
            if (D_800EB420[D_800FADB8] == 0 && !(D_800FAF5C->grappleCtx & 0x400000)) {
                if (D_800F9B00->move.moveCode) {
                    func_800A7328(D_800FAF5C);
                    func_800D427C(D_800FAF5C, (s16)func_800D5438(D_800F9B00, 1), 2);
                } else {
                    func_800D427C(D_800FAF5C, (s16)func_800D5438(D_800F9B00, 1), 1);
                }
            }
        } else {
            func_800A837C(D_800FAF5C);
        }
tail:
        if (D_800FAF5C->animFrame >= D_800FAF5C->anim.frameCount - 4) {
            if ((s8)func_800AD218(D_800FAF5C, D_800FABE6, D_800FAF8A, D_800FAF78, &D_800FAF8E[D_800FADB8])) {
                D_800FAF5C->pairSignals |= 1;
            }
        }
        if (D_800FAF5C->animFramesLeft > 0) {
            break;
        }
        if (D_800EB420[D_800FADB8] == 0 || D_800F9B00->state != 0x4C || (D_800FAF5C->grappleCtx & 0x400000)) {
            func_800AD6D0(D_800FAF5C);
            func_800D4AD0(D_800FAF5C);
            func_800A6C48(D_800FAF5C, 0x2B);
            D_800FAF5C->flags &= ~WR_FLAG_PAIR_LEADER;
            D_800FAF5C->attached[0] = -1;
        } else {
            D_800FAF5C->step = 2;
            D_800FAF5C->flags |= WR_FLAG_RERUN;
        }
        break;
    }
    case 6:
        func_800D8D74(D_800FAF5C, 0);
        if (D_800FAF5C->animFramesLeft > 0) {
            break;
        }
        func_800AD6D0(D_800FAF5C);
        func_800D427C(D_800FAF5C, (s16)func_800D5438(D_800FAF5C, 0), 1);
        func_800A6BE0(D_800FAF5C, 0x51);
        break;
    }
}
