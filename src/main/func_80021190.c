/* @header
 * func_80021190
 * VRAM 0x80021190 | ROM 0x21D90 | size 0x80
 * asm: asm/nonmatchings/main/func_80021190.s
 */
#include "common.h"

s32 func_8001C990(s32, void *, s32);
void func_80021480(s32);
s32 func_80025810(s32, void *);
void func_80027744(void);
void func_800277B0(void);
extern u8 D_8006A260[];
extern u8 D_8007BD30;

/* Reads the controllers with the buffer reset (func_80021480) first: issues the
 * command and waits, then retrieves the response. Returns the read result. */
s32 func_80021190(s32 arg0) {
    s32 temp_v0;

    func_80027744();
    if (D_8007BD30 != 0) {
        func_80021480(0);
        func_80025810(1, D_8006A260);
        func_8001C990(arg0, 0, 1);
    }
    temp_v0 = func_80025810(0, D_8006A260);
    D_8007BD30 = 0;
    func_800277B0();
    return temp_v0;
}
