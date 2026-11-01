/* @header
 * func_800BB3DC
 * VRAM 0x800BB3DC | ROM 0x67B4C | size 0x58
 * asm: asm/nonmatchings/code_80090000/func_800BB3DC.s
 */
#include "common.h"

s32 func_8001C8C0(s32 *, s32, s32 *, s32, s32 *, s32);          /* extern */
s32 startThread(s32 *);                                 /* extern */
extern u8 D_800DD010[];
extern u8 D_800DE1C0[];
extern u8 func_800BB434[];

void func_800BB3DC(void) {
    func_8001C8C0(&D_800DD010, 0, &func_800BB434, 0, &D_800DE1C0, 0x20);
    startThread(&D_800DD010);
}
