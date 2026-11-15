/* @header
 * func_800B04BC
 * VRAM 0x800B04BC | ROM 0x5CC2C | size 0x68
 * asm: asm/nonmatchings/code_80090000/func_800B04BC.s
 */
#include "common.h"

#ifdef TARGET_PC
typedef Nw2Cup Cup; /* PC: common.h's layout of a cup, 0x18 bytes */
#else
typedef struct { u8 id; u8 pad1[5]; u16 flags; u8 pad8[8]; u8 *list; } Cup;
#endif
typedef struct { s16 f0; s16 id; u8 pad4[0xC]; } Pl;
typedef struct {
    u8 pad0[8];
    u16 mode;
    u8 padA[0x26];
#ifdef TARGET_PC
    u32 cup; /* PC: a handle (CUP below) */
#else
    Cup *cup;
#endif
    u8 pad34[0x18];
    Pl pl[4];
    u8 pad8C[0x14E - 0x8C];
    u16 f14E[5];
    u16 f158;
    u16 f15A[5];
    u16 f164;
} Game;

extern Game D_8007EF30;
#ifdef TARGET_PC
/* PC: D_8007EF30 keeps its N64 layout, so its +0x30, the current cup (common.h's Nw2Cup), holds a handle (port.h's
 * PTR_TO_SLOT); CUP is the cup's address. */
#define CUP ((Cup *)SLOT_TO_PTR(D_8007EF30.cup))
#endif

s32 func_800B04BC(s32 id) {
    u8 k;
    if (!(D_8007EF30.mode & 0x8000)) {
        return 0;
    }
#ifdef TARGET_PC
    k = CUP->id;
#else
    k = D_8007EF30.cup->id;
#endif
    if ((D_8007EF30.f14E[k] & 0xFFF) == id) {
        return -1;
    }
    if (k == 2 && (D_8007EF30.f158 & 0xFFF) == id) {
        return 1;
    }
    return 0;
}
