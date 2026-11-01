/* @header
 * func_800C1F24
 * VRAM 0x800C1F24 | ROM 0x6E694 | size 0x2C
 * asm: asm/nonmatchings/code_80090000/func_800C1F24.s
 */
#include "common.h"

extern u8 D_800DF220[];
void func_80001DC4(void *);

void func_800C1F24(void) {
    func_80001DC4(D_800DF220);
}
