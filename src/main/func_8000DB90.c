/* @header
 * func_8000DB90
 * VRAM 0x8000DB90 | ROM 0xE790 | size 0xC0
 * asm: asm/nonmatchings/main/func_8000DB90.s
 */
#include "common.h"

extern u8 D_800566E8[];
#ifdef TARGET_PC
/* PC: the label D_80065294 (D_800651A0 + 0xF4, each entity's object 1 draw group) has no symbol on PC; the code reads
 * it through its base D_800651A0, whose 0xDC-byte objects keep their N64 layout (Nw2SceneObj, common.h), at the N64
 * offset and stride. */
extern u8 D_800651A0[];
#else
extern u8 D_80065294[];
#endif
void func_8000D238(s32, s32);

/* Set or clear the enable bit 0x80 of entity arg0's record (0x13C4-byte stride in
 * D_80065294). For arg1 == 1: when the entity's D_800566E8 byte is negative, clear the bit
 * (keeping the low 7 bits) via func_8000D238 and return 1; otherwise return 0 unchanged.
 * For any other arg1, set bit 0x80 and return arg1. */
s16 func_8000DB90(s16 arg0, s16 arg1) {
    s16 r = arg1;
    if (arg1 == 1) {
        if ((s8)D_800566E8[arg0] < 0)
#ifdef TARGET_PC
            /* PC: D_80065294 through its base (see the declarations above). */
            func_8000D238(arg0, D_800651A0[0xF4 + arg0 * 0x13C4] & 0x7F);
#else
            func_8000D238(arg0, D_80065294[arg0 * 0x13C4] & 0x7F);
#endif
        else
            r = 0;
    } else
#ifdef TARGET_PC
        /* PC: D_80065294 through its base (see the declarations above). */
        func_8000D238(arg0, D_800651A0[0xF4 + arg0 * 0x13C4] | 0x80);
#else
        func_8000D238(arg0, D_80065294[arg0 * 0x13C4] | 0x80);
#endif
    return r;
}
