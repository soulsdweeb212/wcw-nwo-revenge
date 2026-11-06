/* @header
 * func_8009EDBC
 * VRAM 0x8009EDBC | ROM 0x9225C | size 0x6AC
 * asm: asm/nonmatchings/code_8009D7A0/func_8009EDBC.s
 */
#include "common.h"

extern s8 D_800FADB8;
extern s16 D_800FADC6[];
extern u16 D_800FAF8A;
extern s32 D_800E3C90[];
extern s32 D_800E3CA0[];
extern u16 D_800E3CD0[];

void func_800E212C(void *);
void translateEntityByActionQuadrant(void *);
void translateEntityXZ(void *, void *);
void func_800C38FC(void *, u64, s32);
void func_800D427C(void *, s16, s32);
s32 func_800D2B64(void *, s32, u16, s32);
s32 func_800D35B0(s32, s32);
s32 func_800D3684(s32, s32);
f32 func_800D63F0(void *, void *, s32);
void func_800D37C0(s32, f32, f32 *);
void func_800A7D1C(void *, s32);
void func_800A7F6C(void *, s32);
void func_800A837C(void *);
s8 func_800B71F8(void *, s32, s32);
void func_800B68A0();

void func_8009EDBC(void) {
    Wrestler *o = D_800EB408;
    o->steppedOverId = -1;
    o->flags |= 0x100000ULL;

    switch (D_800EB408->step) {
    case 0:
        func_800E212C(D_800EB408);
        func_800D427C(D_800EB408, 0xEF5, 1);
        D_800EB408->heading = D_800E3C90[D_800EB408->dirIndex];
        D_800FADC6[D_800FADB8]++;
        D_800EB408->step++;
        /* fall through */
    case 1:
        func_800C38FC(D_800EB408, 0x40001000000000ULL, 0x1000000);
        translateEntityByActionQuadrant(D_800EB408);
        if ((D_800EB408->flags & 9) == 0) {
            u16 moveMode = D_800EB408->moveMode;
            if (moveMode & 0x20) {
                if (!(moveMode & 0x480)) {
                    if ((s16)D_800FADC6[D_800FADB8] == 1) {
                        if ((D_800EB408->flags & 0x80000) != 0 ||
                            (D_800EB40C->flags & 0x80000) == 0) {
                            if ((s16)D_800EB408->animFrame < 3 && (D_800FAF8A & 0xC030) &&
                                func_800B71F8(D_800EB408, 0, 3)) {
                                func_800A7F6C(D_800EB408, 0x4D);
                                func_800A837C(D_800EB408);
                                if (D_800FAF8A & 0x8000) {
                                    D_800EB408->moveMode |= 0x400;
                                } else {
                                    func_800D427C(D_800EB408, 0xEF7, 1);
                                    D_800EB408->step = 3;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (D_800EB408->animFramesLeft > 0) {
            break;
        }
        D_800EB408->heading = D_800E3CA0[D_800EB408->dirIndex];
        func_800D427C(D_800EB408, 0xEF6, 1);
        D_800EB408->step++;
        break;
    case 2: {
        u16 v;
        f32 d;
        translateEntityByActionQuadrant(D_800EB408);
        if (D_800EB408->animFramesLeft <= 0) {
            D_800EB408->dirIndex ^= 2;
            d = func_800D63F0(D_800EB408, 0, 2);
            func_800D37C0(D_800EB408->heading, d, D_800EB408->moveDelta);
            v = D_800EB408->moveMode;
            D_800EB408->moveMode = v & 0xFF7F;
            if ((*(u32 *)&D_800EB408->moveMode & 0x04200000) == 0x00200000) {
                if ((s16)D_800FADC6[D_800FADB8] >= 2) {
                    func_800A6C48(D_800EB408, 1);
                    break;
                }
            } else {
                D_800EB408->moveMode = (v & 0xFF5B) | 3;
            }
            func_800A6C48(D_800EB408, 3);
            D_800EB408->step = 2;
            D_800EB408->flags &= 0xFFFFFFFFFEFFFFFFULL;
        }
        break;
    }
    case 3:
        translateEntityByActionQuadrant(D_800EB408);
        if (D_800EB408->animFramesLeft <= 0) {
            func_800D427C(D_800EB408, 0xEFA, 1);
            D_800EB408->heading = D_800E3CA0[D_800EB408->dirIndex];
            D_800EB408->step++;
        }
        break;
    case 4:
        translateEntityByActionQuadrant(D_800EB408);
        if (D_800EB408->animFramesLeft <= 0) {
            func_800A7D1C(D_800EB408, 0xB);
            func_800B68A0(D_800EB408, D_800EB408, D_800EB408);
            func_800A6C48(D_800EB408, 0x2B);
        }
        break;
    case 5: {
        f32 d;
        func_800D427C(D_800EB408, 0xE7F, 3);
        d = func_800D63F0(D_800EB408, 0, 2);
        func_800D37C0(D_800E3C90[D_800EB408->dirIndex], d,
                      D_800EB408->moveDelta);
        D_800EB408->turnPerTick = func_800D3684(D_800E3CA0[D_800EB408->dirIndex], D_800EB408->heading) / 6;
        D_800EB408->stateTimer = 0;
        D_800EB408->step++;
    }
    case 6: {
        s32 mask;
        D_800EB408->stateTimer++;
        if ((s16)D_800EB408->stateTimer < 7) {
            D_800EB408->heading = func_800D35B0(D_800EB408->heading, D_800EB408->turnPerTick);
        }
        translateEntityXZ(D_800EB408, D_800EB408->moveDelta);
        mask = func_800D2B64(D_800EB408, 0x3F800000, 0, 2);
        if (mask & 0xFFFF) {
            if (D_800E3CD0[D_800EB408->dirIndex] & mask) {
                func_800D427C(D_800EB408, 0xE74, 3);
                D_800EB408->heading = D_800E3CA0[D_800EB408->dirIndex];
                D_800FADC6[D_800FADB8]++;
                D_800EB408->step++;
            }
        }
        break;
    }
    case 7: {
        f32 d;
        func_800C38FC(D_800EB408, 0x40001000000000ULL, 0x1000000);
        if (D_800EB408->animFramesLeft <= 0) {
            D_800EB408->dirIndex ^= 2;
            d = func_800D63F0(D_800EB408, 0, 2);
            func_800D37C0(D_800EB408->heading, d, D_800EB408->moveDelta);
            D_800EB408->flags &= 0xFFFFFFFFFEFFFFFFULL;
            D_800EB408->moveMode = (D_800EB408->moveMode & 0xFF7F) | 3;
            func_800A6C48(D_800EB408, 3);
            D_800EB408->step = 2;
        }
        break;
    }
    }
}
