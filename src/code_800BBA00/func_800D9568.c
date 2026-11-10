/* @header
 * func_800D9568
 * VRAM 0x800D9568 | ROM 0xCCA08 | size 0x138
 * asm: asm/nonmatchings/code_800BBA00/func_800D9568.s
 */
#include "common.h"

extern u8 D_8007E228[], D_8007EF30[];
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D9814 */
s8 func_800D9814(void);
#endif
/* Try to start state 0x81 on the wrestler (func_800A6C48(w, 0x81)):
 *  - when its state is 1, require the global D_8007E228+0x58 bit 0x200, D_8007EF30+0x170 bit 0x40 clear and
 *    func_800D9814() true (called without arguments here; its definition reads a record from a0);
 *  - otherwise require D_8007E228+0x58 bit 0x200, WR_FLAG_LEGAL clear, and dirIndex 0 with WR_FLAG_TEAM_B set or
 *    dirIndex 2 with it clear; then also set step to 2.
 * Returns 1 if the state was started, else 0. */
s32 func_800D9568(Wrestler *w) {
    if (w->state == 1) {
        if ((*(u16 *)(D_8007E228 + 0x58) & 0x200) && !(*(u16 *)(D_8007EF30 + 0x170) & 0x40)) {
#ifdef TARGET_PC
            /* func_800D9814 reads a wrestler from its first argument, which the N64 call leaves out: $a0 still held w
             * there (this function's own argument, untouched up to the call at 800D95B0). The PC passes w. */
            if (func_800D9814(w)) { func_800A6C48(w, 0x81); return 1; }
#else
            if (func_800D9814()) { func_800A6C48(w, 0x81); return 1; }
#endif
        } return 0;
    }
    if ((*(u16 *)(D_8007E228 + 0x58) & 0x200) && !(w->flags & WR_FLAG_LEGAL)) {
        if (((w->flags & WR_FLAG_TEAM_B) && w->dirIndex == 0) ||
            (!(w->flags & WR_FLAG_TEAM_B) && w->dirIndex == 2)) {
            func_800A6C48(w, 0x81); w->step = 2; return 1;
        }
    }
    return 0;
}
