/* @header
 * func_800276F0
 * VRAM 0x800276F0 | ROM 0x282F0 | size 0x54
 * asm: asm/nonmatchings/main/func_800276F0.s
 */
#include "common.h"

typedef s32 M2C_UNK;
M2C_UNK func_8001C890(M2C_UNK *, M2C_UNK *, M2C_UNK);
M2C_UNK func_8001CAC0(M2C_UNK *, M2C_UNK, M2C_UNK);
extern s32 D_800388A0;
extern M2C_UNK D_80064AB0;
extern M2C_UNK D_8007E210;

/* Initializes the controller/Pak message queue. */
void func_800276F0(void) {
    D_800388A0 = 1;
    func_8001C890(&D_8007E210, &D_80064AB0, 1);
    func_8001CAC0(&D_8007E210, 0, 0);
}
