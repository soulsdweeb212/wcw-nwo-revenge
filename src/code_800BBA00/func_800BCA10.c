/* @header
 * func_800BCA10
 * VRAM 0x800BCA10 | ROM 0xAFEB0 | size 0xA4C
 * asm: asm/nonmatchings/code_800BBA00/func_800BCA10.s
 */
#include "common.h"

extern s8 D_800FADB8;
extern f32 D_800EB480[];
extern s32 D_800E3D00[];
extern u16 D_800FAF8E[];

f32 func_800D3890(void *, void *, s32);
void func_800D427C(void *, s32, s32);
s32 func_800D35B0(s32, s32);
s32 func_800D6610(void *, s32);
s16 func_800D7A68(u16);
s8 func_800BD980(void *, void *, s16);
void func_800A7F6C(void *, s32);
void func_800BE450(void *, void *);
void func_800A837C(void *);
void func_800A7D1C(void *, s32);
void func_800B68A0(void *, void *, void *);
void func_800D3E40(void *, f32 *, s32, void *);
void func_800D2BEC(void *, void *, s32, f32, s32, s32);
void translateEntityXZ(void *, void *);
void func_800D4AD0(void *);

#define O D_800FAF5C
#define P D_800F9B00

#define FINISH() \
    func_800D4AD0(O); \
    func_800A6C48(O, 0x2B); \
    O->flags &= ~WR_FLAG_PAIR_LEADER; \
    O->attached[0] = -1;

void func_800BCA10(void)
{
    s32 a;
    s16 dir;
    s32 best;
    s16 dirA;
    s16 dirB;
    s32 t;
    s32 r;
    s32 mask;
    s16 d;
    f32 v[3];

    switch (O->step) {
    case 0:
        O->flags &= ~0x2000000ULL;
        if (*(u64 *)(O->profile + 0x38) & 0x400) {
            O->grappleCtx |= 0x800000;
        }
        if (*(u64 *)(P->profile + 0x38) & 0x400) {
            O->grappleCtx |= 0x1000000;
        }
        if (O->grappleCtx & 1) {
            if (!(P->flags & WR_FLAG_SPECIAL)) {
                O->grappleCtx &= ~0x800000;
                O->grappleCtx &= ~0x1000000;
            }
        }
        P->moveMode = 0x22;
        if (O->grappleCtx & 2) {
            P->moveMode = 0x62;
        }
        D_800EB480[D_800FADB8] = func_800D3890(&O->x, &P->x, 0);
        if (O->grappleCtx & 0x80) {
            a = 0xEE9;
        } else {
            a = 0xED9;
        }
        func_800D427C(O, a, 2);
        best = 0x800;
        if (O->grappleCtx & 0x80) {
            dir = (((s32)(P->dirIndex + 2) % 4U) << 1) | 1;
        } else {
            for (dir = 0; dir < 8; dir += 2) {
                t = func_800D3550(func_800D3684(func_800D35B0(O->heading, 0x800), D_800E3D00[dir]));
                if (t < best) {
                    best = t;
                    dirA = dir;
                }
            }
            best = 0x800;
            for (dir = 1; dir < 8; dir += 2) {
                t = func_800D3550(func_800D3684(func_800D35B0(O->heading, 0x800), func_800D6610(O, dir / 2)));
                if (t < best) {
                    best = t;
                    dirB = dir;
                }
            }
            dir = func_800D7A68(D_800FAF8E[D_800FADB8]);
            if (dir != 0) {
                dir--;
            } else {
                dir = dirA;
            }
        }
        if (func_800D3550(func_800D3684(D_800E3D00[dir], O->heading)) < 0x300) {
            if (dir & 1) {
                dir = dirB;
            } else {
                dir = dirA;
            }
        }
        if (func_800BD980(O, P, dir)) {
            break;
        }
        func_800A7F6C(O, 0x4B);
        if (O->grappleCtx & 0x1000000) {
            func_800D427C(O, (O->grappleCtx & 0x80) ? 0xEEB : 0xEE1, 2);
            O->step = 6;
            break;
        }
        if ((dir & 1) && (O->flags & WR_FLAG_IN_RING)) {
            P->moveMode = (P->moveMode & ~2) | 8;
        } else {
            a = D_800E3D00[dir];
            O->turnPerTick = func_800D3684(a, func_800D35B0(O->heading, 0x800)) / O->anim.frameCount;
        }
        P->dirIndex = dir / 2;
        O->step++;
        break;
    case 1:
        if (!(O->grappleCtx & 0x800000)) {
            if (P->moveMode & 8) {
                t = func_800D3684(func_800D6610(P, P->dirIndex), P->heading);
                d = O->animFramesLeft;
                if (O->animFramesLeft == 0) {
                    d = 1;
                }
                O->turnPerTick = t / d;
            }
            O->heading = func_800D35B0(O->heading, O->turnPerTick);
            P->heading = func_800D35B0(P->heading, O->turnPerTick);
            v[0] = 0.0f;
            v[2] = D_800EB480[D_800FADB8];
            func_800D3E40(&P->x, v, P->heading, &O->x);
        }
        if (O->animFramesLeft <= 0) {
            if (O->grappleCtx & 0x80) {
                func_800BE450(O, P);
            }
            if (P->flags & 0x2000000) {
                func_800D427C(O, 0xEDE, 0);
                break;
            }
            func_800D427C(O, (O->grappleCtx & 0x800000) ? 0xEDF : 0xEDB, 0);
            func_800A837C(O);
            O->step++;
        }
        if (!(O->grappleCtx & 0x80)) {
            func_800D2BAC(O, P, 1.0f, 2);
        }
        break;
    case 2:
        if (!(O->grappleCtx & 0x80)) {
            func_800D2BAC(O, P, 1.0f, 2);
        }
        if (O->animFramesLeft <= 0) {
            FINISH();
        }
        break;
    case 3:
        if (O->animFramesLeft <= 0) {
            func_800A7D1C(O, 4);
            func_800B68A0(O, O, P);
            O->heading = func_800D35B0(O->heading, 0x800);
            P->heading = func_800D35B0(P->heading, 0x800);
            func_800BE450(O, P);
            if (P->grappleCtx & 0x800000) {
                a = 0xEDF;
                func_800A7D1C(O, 5);
            } else {
                a = 0xEDB;
            }
            func_800D427C(O, a, 0);
            O->step--;
        }
        if (!(O->grappleCtx & 0x80)) {
            func_800D2BAC(O, P, 1.0f, 2);
        }
        break;
    case 4:
        D_800EB480[D_800FADB8] = func_800D3890(&O->x, &P->x, 0);
        O->step++;
    case 5:
        if (--O->stateTimer >= 0) {
            translateEntityXZ(O, O->moveDelta);
            O->heading = func_800D35B0(O->heading, O->turnPerTick);
            P->heading = func_800D35B0(O->heading, 0x800);
            v[0] = 0.0f;
            v[2] = D_800EB480[D_800FADB8];
            func_800D3E40(&O->x, v, O->heading, &P->x);
        }
        if (!(P->pairSignals & 4)) {
            if (O->dirIndex & 1) {
                mask = 0xC00;
            } else {
                mask = 0x300;
            }
            func_800D2BEC(O, P, 0, 2.0f, mask, 0xFFFFE);
        }
        if (O->animFramesLeft <= 0) {
            FINISH();
        }
        break;
    case 6:
        func_800D2BEC(O, P, 0, 1.0f, 0, 0xFFFFE);
        if (O->animFramesLeft <= 0) {
            func_800A7D1C(O, 6);
            func_800B68A0(O, O, O);
            FINISH();
        }
        break;
    }
}
