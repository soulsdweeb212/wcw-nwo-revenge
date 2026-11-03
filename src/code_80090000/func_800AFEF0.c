/* @header
 * func_800AFEF0
 * VRAM 0x800AFEF0 | ROM 0x5C660 | size 0x518
 * asm: asm/nonmatchings/code_80090000/func_800AFEF0.s
 */
#include "common.h"

typedef struct { s16 f0; s16 id; u8 f4; u8 f5; u8 f6; u8 pad7[9]; } Pl;
typedef struct {
    u8 pad0[8];
    u16 mode;
    u8 padA[0x42];
    Pl pl[4];
    u8 pad8C[0xC90 - 0x8C];
    union { struct { u16 v; } one[8]; u16 two[4][2]; } opp;
} Game;
typedef struct {
    u8 pad0[8];
    s32 type[4];
    u8 pad18[0x48];
    u8 rec[4][8];
    u8 pad80[0x610 - 0x80];
    s32 f610[4];
    u8 pad620[0x688 - 0x620];
    s32 ids[4];
} Cfg;
typedef struct { s32 f0[4]; u8 pad10[0x60]; s32 f70[4]; } Cfg2;
typedef struct { u8 pad0[0xA]; u16 flags; u8 padC[0x148 - 0xC]; } El;
typedef struct { void *items; s16 cur; u8 pad6[0xE]; El *el; u8 pad18[0x138 - 0x18]; } Menu;

extern Game D_8007EF30;
extern Cfg D_8007E228;
extern Cfg2 D_8007E8C0;
extern s32 D_80038AA8;
extern Menu D_800E8230[];
void func_800AEA7C(void);
void func_800A973C(void);
void func_800A90DC(void *);
void func_800AF978(void);

static inline void human(s32 n, s32 t) {
    D_8007E228.type[n] = t;
    D_8007E228.ids[n] = D_8007EF30.pl[n].id;
    D_8007E8C0.f0[n] = D_8007EF30.pl[n].f5;
    D_8007E228.f610[n] = D_8007EF30.pl[n].f6;
    D_8007E8C0.f70[n] = D_8007EF30.pl[n].f4;
}

static inline void cpu(s32 n, u16 v) {
    D_8007E8C0.f0[n] = 0;
    D_8007E228.f610[n] = 5;
    D_8007E228.type[n] = 0;
    D_8007E228.ids[n] = v & 0xFFF;
    D_8007E8C0.f70[n] = (v >> 12) & 3;
}

s32 func_800AFEF0(s32 a) {
    s32 i, m, r;
    s32 pad[2];

    func_800AEA7C();
    if (D_8007EF30.mode & 0x8000) {
        if (D_8007EF30.mode & 0x20) {
            human(0, 0);
            human(1, 1);
            cpu(2, D_8007EF30.opp.two[D_80038AA8][0]);
            cpu(3, D_8007EF30.opp.two[D_80038AA8][1]);
        } else {
            human(0, 0);
            cpu(1, D_8007EF30.opp.one[D_80038AA8].v);
        }
    } else {
        switch (D_8007EF30.mode & 0xF0) {
        case 0x20:
            human(3, 3);
        case 0x40:
            human(2, 2);
            human(1, 1);
            human(0, 0);
            break;
        case 0x80:
            human(3, 3);
            human(2, 2);
        case 0x10:
            human(0, 0);
            human(1, 1);
            break;
        }
    }
    func_800A973C();
    func_800A90DC(D_8007E228.rec[0]);
    func_800A90DC(D_8007E228.rec[1]);
    func_800A90DC(D_8007E228.rec[2]);
    func_800A90DC(D_8007E228.rec[3]);
    D_800E8230[12].el[2].flags &= ~1;
    if (a) {
        m = -1;
        for (i = 3; i >= 0; i--) {
            D_8007E8C0.f0[i] = m;
        }
        r = 0;
    } else {
        r = 0;
    }
    func_800AF978();
    return r;
}
