/* @header
 * func_800C4C60
 * VRAM 0x800C4C60 | ROM 0xB8100 | size 0x530
 * asm: asm/nonmatchings/code_800BBA00/func_800C4C60.s
 */
#include "common.h"

extern s8 D_800FADB8[];
extern s32 D_800F9B14;
extern s32 D_800FABD8;
extern s32 D_800E3F20[];

void func_800A7C40(void *, s32, s16);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D5438 */
s16 func_800D5438(void *, s32);
#endif
void func_800D427C(void *, s32, s32);
void func_800A7F6C(void *, s32);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D3B24 */
s8 func_800D3B24(void *, void *, f32, void *);
#endif
s32 func_800D3684(s32, s32);
s32 func_800D3550(s32);
void func_800C5FBC(void *);
s8 func_800C2CDC(void *, s32);
void func_800C3A78(void *, void *, s32);
void func_800D25D0(void *, f32);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D2B64 */
void func_800D2B64(void *, f32, s32, s32);
#endif
void func_800A7188(void *);

void func_800C4C60(void) {
    Nw2DirectionResult res;
    Wrestler *o;
    Wrestler *b;
    s16 i;
    s16 v;
    s8 r;
    s32 n;
    f32 two;

    switch (D_800FAF5C->step) {
    case 0:
#ifdef TARGET_PC
        /* PC: the N64 code reads moveMode and the u16 after it as one big-endian u32, so bits 0x280000 are moveMode's
         * bits 0x28. A little-endian PC would test the u16 instead, so the PC tests moveMode. */
        if (((D_800F9B00->flags & 0x100000ULL) && (D_800F9B00->moveMode & 0x28) == 0x28) || D_800F9B00->state == 0x14) {
#else
        if (((D_800F9B00->flags & 0x100000ULL) && (*(u32 *)&D_800F9B00->moveMode & 0x280000) == 0x280000) || D_800F9B00->state == 0x14) {
#endif
            v = 0xA5;
        } else {
            v = (D_800FAF5C->moveMode & 4) ? 0xA1 : 0xA3;
        }
        func_800A7C40(D_800FAF5C, D_800FADB8[0], v);
        D_800FAF5C->step = 2;
        D_800FAF5C->flags |= WR_FLAG_RERUN;
        break;
    case 1:
        func_800A7C40(D_800FAF5C, D_800FADB8[0], D_800FAF5C->move.moveCode);
        D_800FAF5C->heading = D_800F9B14;
        D_800FAF5C->step++;
    case 2:
        func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 0), 1);
        func_800A7F6C(D_800FAF5C, 0);
        for (i = 0; i < 4; i++) {
            if (D_800F9D10[i].characterId != -1 && (D_800F9D10[i].flags & 0x10000000000ULL)) {
                break;
            }
        }
        if (i == 4) {
            if (((D_800FAF5C->flags & WR_FLAG_IN_RING) && (D_800F9B00->flags & 0xC0ULL)) ||
                ((D_800FAF5C->flags & WR_FLAG_ON_FLOOR) && (D_800F9B00->flags & WR_FLAG_ON_FLOOR))) {
                if ((D_800FAF5C->flags & D_800F9B00->flags) & WR_FLAG_LEGAL) {
                    if (func_800D3B24(&D_800FAF5C->jointA[1], &D_800F9B00->jointA[1], 200.0f, &res)) {
                        if (func_800D3550(func_800D3684(D_800FAF5C->heading, res.angle)) < 0x72) {
                            D_800FAF5C->flags |= 0x10000000000ULL;
                        }
                    }
                }
            }
        }
        D_800FAF5C->step++;
    case 3:
        D_800FABD8 &= ~D_800E3F20[D_800FADB8[0]];
        func_800C5FBC(D_800FAF5C);
        r = func_800C2CDC(D_800FAF5C, 1);
        if (r != -1) {
            D_800FAF5C->step++;
            n = D_800FAF5C->moveId == 0xA5 ? 0x10 : 8;
            func_800C3A78(D_800FAF5C, &D_800F9D10[r], n);
        }
    case 4:
        two = 2.0f;
        func_800D25D0(D_800FAF5C, two);
        o = D_800FAF5C;
        if (o->flags & WR_FLAG_ON_FLOOR) {
            func_800D2B64(o, two, 0, 0xFFFFE);
        } else {
            switch ((s16)(o->state - 7)) {
            case 15:
                if (o->animFrame > o->anim.hitEnd) {
                    func_800D2B64(o, 2.0f, 0, 0xE);
                }
                break;
            case 0: case 24: case 25: case 26: case 29: case 30: case 31: case 78: case 79:
                if (o->animFrame > o->anim.hitEnd) {
                    func_800D2B64(o, 4.0f, 0, 0xFFFFE);
                } else {
                    func_800D2B64(o, 2.0f, 0, 0xE);
                }
                break;
            case 1: case 23: case 27: case 28: case 32:
                func_800D2B64(D_800FAF5C, 2.0f, 0, 0xE);
                break;
            }
        }
        func_800A7188(D_800FAF5C);
        break;
    }
}
