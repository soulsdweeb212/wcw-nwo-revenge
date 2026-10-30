/* @header
 * func_800DA850
 * VRAM 0x800DA850 | ROM 0xCDCF0 | size 0x64
 * asm: asm/nonmatchings/code_800BBA00/func_800DA850.s
 */
#include "common.h"

/* Advances a timer record: increments the sub-second counter (+4); when it
 * reaches arg1 it wraps to 0 and bumps the seconds counter (+2); at 60 seconds
 * the seconds wrap and the minutes (+0) increment. */
void func_800DA850(void *arg0, s16 arg1) {
    u16 temp_v0;
    u16 temp_v0_2;

    temp_v0 = *(u16 *)((u8 *)arg0 + 4) + 1;
    *(u16 *)((u8 *)arg0 + 4) = temp_v0;
    if ((s16) temp_v0 >= arg1) {
        *(u16 *)((u8 *)arg0 + 4) = 0U;
        temp_v0_2 = *(u16 *)((u8 *)arg0 + 2) + 1;
        *(u16 *)((u8 *)arg0 + 2) = temp_v0_2;
        if ((s16) temp_v0_2 >= 0x3C) {
            *(u16 *)((u8 *)arg0 + 2) = 0U;
            *(u16 *)((u8 *)arg0 + 0) = (u16) (*(u16 *)((u8 *)arg0 + 0) + 1);
        }
    }
}
