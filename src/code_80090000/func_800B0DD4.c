/* @header
 * func_800B0DD4
 * VRAM 0x800B0DD4 | ROM 0x5D544 | size 0xF0
 * asm: asm/nonmatchings/code_80090000/func_800B0DD4.s
 */
#include "common.h"

typedef struct { u8 id; u8 pad1[5]; u16 flags; u8 pad8[0xC]; } Cup;
typedef struct {
    u8 pad0[8];
    u16 mode;
    u8 padA[2];
    s16 fC;
    u8 padE[2];
    s16 f10;
    u8 pad12[6];
    s16 f18;
    u8 pad1A[0x12];
    u8 *f2C;
    Cup *cup;
} Game;
typedef struct { u16 f0; u8 pad2[6]; s32 best[10]; } Rec;
extern Game D_8007EF30;
extern Cup D_8003A484[];
extern u8 lookupSubTables[];
extern s16 D_80038A90;
extern Rec D_8007F0A0;
void func_800AEF28(s32);

s32 func_800B0DD4(s32 i) {
    s32 r;
    s32 k;
    u16 f;

    D_8007EF30.cup = &D_8003A484[i];
    D_8007EF30.f2C = &lookupSubTables[D_8007EF30.f10 * 8];
    /* Placeholder: an if/else that only cse1 can fold (k is known 0 there). It ends cse1's block,
       so the mode/fC stores are related to the cup-store address in cse2 (base a1, -0x28/-0x24)
       instead of being folded back to symbols, without the sched barrier a do { } while (0) adds. */
    k = 0;
    if (k == 0) {
        f = D_8007EF30.cup->flags | 0x8000;
    } else {
        f = 0;
    }
    r = D_80038A90;
    D_8007EF30.mode = f;
    D_8007EF30.fC = (f & 0x20) ? 2 : 1;
    if (D_8007EF30.mode & 0x2000) {
        D_8007EF30.f10 = 0xB;
    } else {
        D_8007EF30.f10 = 0;
    }
    D_8007EF30.f18 = 8;
    for (k = 9; k >= 0; k--) {
        D_8007F0A0.best[k] = 0;
    }
    func_800AEF28(0);
    return r;
}
