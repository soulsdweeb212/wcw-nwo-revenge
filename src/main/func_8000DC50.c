/* @header
 * func_8000DC50
 * VRAM 0x8000DC50 | ROM 0xE850 | size 0xBC
 * asm: asm/nonmatchings/main/func_8000DC50.s
 */
#include "common.h"

typedef struct {
    s16 e0[4];
    s8 e8[8];
} Nw2D50;

extern Nw2D50 D_800566E0;
extern s8 D_800566E8[];
#ifdef TARGET_PC
/* PC: the label D_80065294 (D_800651A0 + 0xF4, each entity's object 1 draw group) has no symbol on PC; the code reads
 * it through its base D_800651A0, whose 0xDC-byte objects keep their N64 layout (Nw2SceneObj, common.h), at the N64
 * offset and stride. */
extern u8 D_800651A0[];
#else
extern u8 D_80065294[];
#endif
extern void func_8000D238(s32, s32);

/* Sets entity arg0's part-set to arg1 when the entity is not yet active: stores
 * the new set, clears its state byte and resets the entity's part flags (with
 * the 0x80 bit from D_80065294). Returns 1 when the entity is inactive. */
u32 func_8000DC50(s16 arg0, s16 arg1) {
    if (D_800566E8[arg0] < 0) {
        if ((s16)arg1 != D_800566E0.e0[arg0]) {
            D_800566E0.e0[arg0] = arg1;
            D_800566E0.e8[arg0] = 0;
#ifdef TARGET_PC
            /* PC: D_80065294 through its base (see the declarations above). */
            func_8000D238(arg0, D_800651A0[0xF4 + arg0 * 0x13C4] | 0x80);
#else
            func_8000D238(arg0, D_80065294[arg0 * 0x13C4] | 0x80);
#endif
        }
    }
    return (u32)~D_800566E8[arg0] >> 31;
}
