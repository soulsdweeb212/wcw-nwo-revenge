/* @header
 * func_80004290
 * VRAM 0x80004290 | ROM 0x4E90 | size 0x2C
 * asm: asm/nonmatchings/main/func_80004290.s
 */
#include "common.h"

/* identical to func_80005C28 in WWF No Mercy (matched), with its names changed by decompdecomp */
/* identical to func_80004290 in WCW / nWo  REVENGE (matched), with its names changed by decompdecomp */
s32 func_80022FD0(s32 *);
extern s32 D_800482F0;
extern s8 D_800484F2;

/* Read the controllers using the D_800482F0 work area as the message queue,
 * then clear the D_800484F2 input flag. */
void func_80004290(void) {
    func_80022FD0(&D_800482F0);
    D_800484F2 = 0;
}
