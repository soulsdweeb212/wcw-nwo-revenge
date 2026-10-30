/* @header
 * func_80092B20
 * VRAM 0x80092B20 | ROM 0x3F290 | size 0x2C0
 * asm: asm/nonmatchings/code_80090000/func_80092B20.s
 */
#include "common.h"

typedef struct {
    u8 pad0[7];
    u8 f7;
    s16 f8;
    u8 padA[2];
    s16 fC;
} Sub92B20;

typedef struct {
    Sub92B20 *f0;
    u8 pad4[8];
    u16 fC;
    u8 padE[2];
    s16 f10;
} S92B20;

extern s32 D_800E74C4;
extern u8 D_800C5D90[];
extern u8 D_800C6568[];
extern u8 D_800C6588[];
extern s32 D_800C656C[];
extern u16 D_800C6570[];
extern u8 D_800C6574[];
extern s32 D_800C657C[];
extern s32 D_800DBD54;

void func_800927B0(void **, s32, void *);
void func_80092960(void **, s32, void *);
void func_80092554(void **, s32, s16, s16);
s32 loadResourceTexture4b(void **, void *, s32);
void accumulateColorChannels(s32, s32, s32);

#define EMIT(a, b) { Nw2GfxCommand *q = p; p = q + 1; q->w0 = (a); q->w1 = (b); }

void func_80092B20(void **out, S92B20 *s) {
    void *p;
    s32 mode;
    s32 k;
    s32 idx;

    p = *out;
    mode = D_800E74C4;
    k = s->f10;
    if (mode == 7) {
        switch (s->fC) {
        case 7:
        case 9:
            mode = 4;
            break;
        case 8:
            mode = 2;
            break;
        case 6:
            mode = 6;
            break;
        }
    }
    switch (mode) {
    case 1:
        func_800927B0(&p, k, D_800C6588);
        break;
    case 2:
        func_80092960(&p, k, D_800C6588);
        break;
    case 4:
        if (s->f10 >= 0x30) {
            s->f10 = 0;
        }
        goto case3;
    case 6:
        if (s->f10 >= 0x1C) {
            s->f10 = 0;
        }
    case 5:
        idx = s->f10;
        if (idx >= 0 && idx < D_800C6574[0]) {
            EMIT(0xDE000000, (u32)D_800C5D90);
            EMIT(0xFB000000, 0xFF0000FF);
            EMIT(0xFA000000, 0xFFFF00FF);
            { u32 hi = (D_800C6570[0] & 0xFF) << 12; u32 lo = ((D_800C6570[0] & 0x7F) << 1) | 0x01000000; EMIT(hi | lo, D_800C656C[0]); }
            if (loadResourceTexture4b(&p, D_800C6568, idx)) {
                EMIT(0x07000206, 0x604);
            }
            if (idx < 0x14 && (idx & 1)) {
                accumulateColorChannels(0xF, 0, 0);
            }
            if (idx == 0) {
                D_800DBD54 = 0x421;
            }
        }
        break;
    case 8:
        if (s->f10 >= 0x30) {
            func_80092960(&p, s->f10 - 0x30, D_800C6588);
            break;
        }
    case 3:
    case3:
        EMIT(0xDE000000, (u32)D_800C5D90);
        EMIT(0x01014028, D_800C657C[0]);
        func_80092554(&p, s->f10, s->f0->f8, s->f0->fC);
        break;
    default:
        s->f10 = ~s->f0->f7;
        break;
    }
    *out = p;
}
