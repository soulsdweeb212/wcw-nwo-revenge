/* @header
 * func_800CF3A0
 * VRAM 0x800CF3A0 | ROM 0xC2840 | size 0x6B0
 * asm: asm/nonmatchings/code_800BBA00/func_800CF3A0.s
 */
#include "common.h"

/* The 64-bit flag word at +0x38 of the character profile (Wrestler.profile). */
typedef struct { u8 pad38[0x38]; u64 flags; } Nw2Attach38;
extern u16 D_800FABE6;
extern u16 D_800FAF8A;
extern s8 D_800FAF78;
extern s8 D_800FADB8;
extern u16 D_800FAF8E[];
extern s16 D_800EB620[];
extern s32 D_800EB600[];
void setupEntityMoveCD990(void *, void *);
s32 func_800CDEE4(void *, void *);
s32 func_800CDF40(void *, u16, u16, s8, u16 *);
s32 func_800D00FC(void *, void *, u16);
void translateEntityXZ(void *, void *);
s32 func_800D35B0(s32, s32);
s32 func_800D2BEC(void *, void *, void *, f32, u16, s32);
void func_800D427C(void *, s16, s32);
void func_800D4AD0(void *);
s16 func_800D5438(void *, s32);
void func_800A6BE0(void *, s32);
void func_800A7D1C(void *, s32);
void beginEntityActionA8D8C(void *);
void func_800B68A0(void *, void *, void *);
void func_800CF3A0(void) {
    s32 ret; s32 inc;
    switch (D_800FAF5C->step) {
    case 0:
        D_800FAF5C->flags &= 0xFFFFFFFFF87FFFFFULL;
        setupEntityMoveCD990(D_800FAF5C, D_800F9B00);
        D_800FAF5C->step++;
    case 1: {
        Wrestler *o; Wrestler *b;
        o = D_800FAF5C; b = D_800F9B00;
        if (o->stateTimer >= D_800EB620[o->id]) {
            o->heading = D_800EB600[o->id];
            if (o->grappleCtx & 0x100000) o->step = 7;
            else o->stateTimer = func_800CDEE4(o, b);
            inc = 1;
        } else {
            translateEntityXZ(o, o->moveDelta);
            o->heading = func_800D35B0(o->heading, o->turnPerTick);
            if (o->grappleCtx & 0x400) func_800D2BAC(o, b, 4.0f, 0xFFFFE);
            o->stateTimer++;
            inc = 0;
        }
        { u16 res; if (res = inc) D_800FAF5C->step++; }
        break;
    }
    case 2:
        ret = func_800CDF40(D_800FAF5C, D_800FABE6, D_800FAF8A, D_800FAF78, &D_800FAF8E[(s8)D_800FADB8]);
        if ((s16)ret == 0) break;
        switch ((s16)ret) {
        case 1: D_800FAF5C->pairSignals |= 2; D_800FAF5C->step++; break;
        case 2: D_800FAF5C->step = 7; D_800FAF5C->pairSignals |= 1; break;
        case 3: D_800FAF5C->step = 0xA; D_800FAF5C->pairSignals |= 8; break;
        }
        break;
    case 3: {
        Wrestler **pp;
        pp = &D_800FAF5C;
        *(volatile s16 *)&(*pp)->step += 1;
    case 4:
        ret = func_800D00FC(D_800FAF5C, D_800F9B00, D_800FAF8E[(s8)D_800FADB8]);
        if ((s16)ret != 0) {
            if ((s16)ret == 2) { D_800FAF5C->pairSignals &= ~2; D_800FAF5C->step -= 2; }
            if ((s16)ret == 3) { D_800FAF5C->pairSignals |= 4; func_800D427C(D_800FAF5C, func_800D5438(D_800F9B00, 1), 1); }
            break;
        }
    }
        if (D_800FAF5C->grappleCtx & 0x80) {
            if (D_800FAF5C->move.flags & 0x100000) {
                s16 anim;
                if (((Nw2Attach38 *)D_800FAF5C->profile)->flags & 0x1000000000ULL) anim = 0xEC1;
                else anim = 0xEC1;
                func_800D427C((Wrestler *)(*(u32 *)&D_800FAF5C), anim, 1);
                D_800FAF5C->step++;
                break;
            }
        }
        D_800FAF5C->step = 6;
        D_800FAF5C->flags |= WR_FLAG_RERUN;
        break;
    case 5:
        if (D_800FAF5C->animFramesLeft == 1) D_800FAF5C->step++;
        break;
    case 6:
        if (D_800FAF5C->grappleCtx & 0xC0) func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 0), 1);
        else func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 0), 3);
        func_800A6BE0(D_800FAF5C, 0x49);
        break;
    case 7:
        if (!(D_800FAF5C->grappleCtx & 0x380)) func_800D2BEC(D_800FAF5C, D_800F9B00, 0, 1.0f, 0, 2);
        if (D_800FAF5C->animFramesLeft <= 0) {
            Wrestler *o;
            func_800D4AD0(D_800FAF5C);
            o = D_800FAF5C;
            o->attached[0] = -1;
            o->flags &= ~WR_FLAG_PAIR_LEADER;
            if (D_800FAF5C->grappleCtx & 0x100) { func_800D427C(D_800FAF5C, 0x102E, 3); D_800FAF5C->step = 9; }
            else beginEntityActionA8D8C(D_800FAF5C);
        }
        break;
    case 8:
        if (D_800FAF5C->animFramesLeft <= 0) {
            func_800A7D1C(D_800FAF5C, 0);
            func_800B68A0(D_800FAF5C, D_800F9B00, D_800FAF5C);
            func_800D4AD0(D_800FAF5C);
            func_800D427C(D_800FAF5C, 0xE8F, 1);
        }
        break;
    case 9:
        if (D_800FAF5C->animFramesLeft <= 0) { func_800D4AD0(D_800FAF5C); beginEntityActionA8D8C(D_800FAF5C); }
        break;
    case 10:
        func_800D427C(D_800FAF5C, 0xEA0, 3);
        D_800FAF5C->pairSignals &= ~8;
        D_800FAF5C->step++;
        break;
    case 11: {
        s16 timer;
        func_800D2BEC(D_800FAF5C, D_800F9B00, 0, 1.0f, 0, 2);
        if (D_800FAF5C->animFramesLeft <= 0) {
            func_800D4AD0(D_800FAF5C);
            D_800FAF5C->grappleCtx |= 0x40;
            if (D_800F9B00->flags & 0x80000) timer = 0x1E;
            else {
                if (D_800FAF5C->grappleCtx & 2) timer = 0x5A; else timer = 0x3C;
                if (D_800FAF5C->grappleCtx & 0x300) timer = 0x3C;
            }
            D_800FAF5C->stateTimer = timer;
            func_800D427C(D_800FAF5C, 0xE8E, 1);
            D_800FAF5C->step = 2;
        }
        break;
    }
    }
}
