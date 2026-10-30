/* @header
 * func_80017FBC
 * VRAM 0x80017FBC | ROM 0x18BBC | size 0x38
 * asm: asm/nonmatchings/main/func_80017FBC.s
 */
#include "common.h"

typedef s32 M2C_UNK;
M2C_UNK func_8002021C(s32, s32);
M2C_UNK func_8002023C(void);
extern s32 D_80036F54;

/* Moves the arg0 node to the audio list head at D_80036F54+0x14. */
void func_80017FBC(s32 arg0) {
    func_8002023C();
    func_8002021C(arg0, D_80036F54 + 0x14);
}
