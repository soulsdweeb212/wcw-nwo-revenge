/* @header
 * func_800A97A0
 * VRAM 0x800A97A0 | ROM 0x9CC40 | size 0x184
 * asm: asm/nonmatchings/code_8009D7A0/func_800A97A0.s
 */
#include "common.h"

typedef struct {
    s16 f0;
    s16 f2;
    u8 pad4[0xC];
    s16 f10;
    s16 f12;
    u8 pad14[0x1E];
    s16 f32;
    u8 pad34[0x28];
    s32 f5C;
} Nw2Rec97A0;

typedef struct {
    u8 pad[0x80];
    u16 count[4];
} Nw2Tbl97A0;

s16 func_800D4148(void);
extern Nw2Tbl97A0 D_8007E228;
extern Nw2Rec97A0 D_800F9B88[];
extern u16 D_800E3370[];

void func_800A97A0(s8 arg0) {
    s16 r;
    s16 delta;

    if (D_8007E228.count[arg0] >= 3) {
        D_8007E228.count[arg0] = 1;
    }
    D_800F9B88[arg0].f5C = 0;
    D_800F9B88[arg0].f10 = D_8007E228.count[arg0];
    D_800F9B88[arg0].f2 = 0;
    D_800F9B88[arg0].f12 = D_800E3370[D_800F9B88[arg0].f10];
    D_800F9B88[arg0].f0 = 0;
    r = func_800D4148();
    delta = r % 40 - 20;
    D_800F9B88[arg0].f12 += delta;
    if (D_800F9B88[arg0].f12 < 10) {
        D_800F9B88[arg0].f12 = 10;
    }
    if (D_800F9B88[arg0].f12 >= 0x3DF) {
        D_800F9B88[arg0].f12 = 0x3DE;
    }
    D_800F9B88[arg0].f32 = func_800D4148() % 8;
}
