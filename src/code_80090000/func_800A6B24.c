/* @header
 * func_800A6B24
 * VRAM 0x800A6B24 | ROM 0x53294 | size 0x60C
 * asm: asm/nonmatchings/code_80090000/func_800A6B24.s
 */
#include "common.h"


typedef struct { u32 w0, w1; } G;
typedef struct { s16 ob[3]; u16 flag; s16 tc[2]; u8 cn[4]; } V;
typedef struct {
    u8 pad0[0x16];
    u8 f16;
    u8 pad17[9];
    u16 f20;
    u16 f22;
} Obj;

extern s32 D_800D5F1C;
extern u16 D_800C9200[];
extern V D_800CCD48[][3];
extern s32 D_800E9F98[]; /* [4][16], indexed m * 16 + i */
extern u16 D_800CCF6C[]; /* pairs {a, b}; read as [lo * 2] / [lo * 2 + 1] */
extern u16 D_800CCF58[];
u32 func_8001CE80(void *);
void func_800B6FE0(G **, s32);
void func_800B7260(G **, s32, s32, s32);
u8 *func_800B600C(s32, s32);

#define EMIT(a, b) { G *_g = g++; _g->w0 = (a); _g->w1 = (b); }
#define PHYS(x) ((u32)(x) - 0x80000000)

void func_800A6B24(G **dl, Obj *o) {
    G *g = *dl;
    s32 m = (o->f20 >> 4) & 3;
    s32 i, v, hi, lo;
    V *p = D_800CCD48[0];
    u8 *t;

    EMIT(0xE7000000, 0);
    if (m >= D_800D5F1C) {
        EMIT(0xFC51FEA3, 0x44FE773B);
        EMIT(0xE7000000, 0);
        EMIT(0xFA000000, o->f16 >> 2);
        EMIT(0x07080A0E, 0x00080E0C);
        *dl = g;
        return;
    }
    EMIT(0xFC5196A3, 0x112CFE7F);
    func_800B6FE0(&g, D_800C9200[m]);
    EMIT(0xE7000000, 0);
    EMIT(0xFA000000, o->f16 >> 1);
    EMIT(0x07080A0E, 0x00080E0C);
    EMIT(0xE7000000, 0);
    EMIT(0xFA000000, o->f16);
    func_800B7260(&g, (m + 1) << 4, 0x10, 0x58);
    EMIT(0x07000206, 0x604);
    EMIT(0x0100600C, func_8001CE80(&p[(o->f22 & 0xF) * 3]));
    EMIT(0x02140004, 0x0BE00000);
    EMIT(0x02140006, 0x1E0);
    EMIT(0x0214000A, 0x0BE001E0);
    func_800B6FE0(&g, 0xFE);
    EMIT(0x0700040A, 0xA06);
    for (i = 0; i < 10; i++) {
        v = D_800E9F98[m * 16 + i];
        hi = v >> 4;
        lo = v & 0xF;
        EMIT(0x0100600C, func_8001CE80(&p[i * 3]));
        if (hi >= 2) {
            t = func_800B600C(D_800CCF6C[lo * 2 + 1], 0);
            if (t) {
                EMIT(0xFD100000, PHYS(t + 0x10));
                EMIT(0xE8000000, 0);
                EMIT(0xF5000100, 0x07000000);
                EMIT(0xE6000000, 0);
                EMIT(0xF0000000, 0x0703C000);
                EMIT(0xE7000000, 0);
            }
            t = func_800B600C(D_800CCF58[hi], 0);
            if (t) {
                EMIT(0xFD500000, PHYS(t + 0x30));
                EMIT(0xF5500000, 0x07000000);
                EMIT(0xE6000000, 0);
                EMIT(0xF3000000, 0x0713F19A);
                EMIT(0xE7000000, 0);
                EMIT(0xF5400A00, 0);
                EMIT(0xF2000000, 0x0013C03C);
            }
            EMIT(0x02140006, 0x1E0);
            EMIT(0x0214000A, 0x0A0001E0);
            EMIT(0x0700040A, 0xA06);
            func_800B6FE0(&g, D_800CCF6C[lo * 2]);
            EMIT(0x02140004, 0x02000000);
            EMIT(0x02140008, 0x200);
            EMIT(0x0214000A, 0x02000200);
            EMIT(0x0702040A, 0x00020A08);
        } else {
            func_800B6FE0(&g, D_800CCF58[hi]);
            EMIT(0x02140006, 0x200);
            EMIT(0x0214000A, 0x0A000200);
            EMIT(0x0700040A, 0xA06);
        }
    }
    *dl = g;
}
