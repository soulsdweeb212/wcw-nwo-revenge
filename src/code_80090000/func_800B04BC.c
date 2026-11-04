/* @header
 * func_800B04BC
 * VRAM 0x800B04BC | ROM 0x5CC2C | size 0x68
 * asm: asm/nonmatchings/code_80090000/func_800B04BC.s
 */
#include "common.h"

typedef struct { u8 id; u8 pad1[5]; u16 flags; u8 pad8[8]; u8 *list; } Cup;
typedef struct { s16 f0; s16 id; u8 pad4[0xC]; } Pl;
typedef struct {
    u8 pad0[8];
    u16 mode;
    u8 padA[0x26];
    Cup *cup;
    u8 pad34[0x18];
    Pl pl[4];
    u8 pad8C[0x14E - 0x8C];
    u16 f14E[5];
    u16 f158;
    u16 f15A[5];
    u16 f164;
} Game;

extern Game D_8007EF30;

s32 func_800B04BC(s32 id) {
    u8 k;
    if (!(D_8007EF30.mode & 0x8000)) {
        return 0;
    }
    k = D_8007EF30.cup->id;
    if ((D_8007EF30.f14E[k] & 0xFFF) == id) {
        return -1;
    }
    if (k == 2 && (D_8007EF30.f158 & 0xFFF) == id) {
        return 1;
    }
    return 0;
}
