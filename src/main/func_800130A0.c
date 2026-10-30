/* @header
 * func_800130A0
 * VRAM 0x800130A0 | ROM 0x13CA0 | size 0x68
 * asm: asm/nonmatchings/main/func_800130A0.s
 */
#include "common.h"

typedef s32 M2C_UNK;
M2C_UNK func_8001C8C0(M2C_UNK *, M2C_UNK, M2C_UNK *, s32, M2C_UNK *, s32); /* extern */
M2C_UNK startThread(M2C_UNK *);
extern s32 D_8002EE90;
extern M2C_UNK D_8005B2F0;
extern M2C_UNK D_800604A0;
extern M2C_UNK func_80013108;

/* Creates the thread whose entry point is func_80013108 and starts it once the
 * subsystem has been initialized. */
void func_800130A0(s32 arg0) {
    func_8001C8C0(&D_8005B2F0, 6, &func_80013108, arg0, &D_800604A0, 8);
    if (D_8002EE90 == 0) {
        startThread(&D_8005B2F0);
    }
}
