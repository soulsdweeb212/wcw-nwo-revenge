/* @header
 * func_800ABC40
 * VRAM 0x800ABC40 | ROM 0x9F0E0 | size 0x98
 * asm: asm/nonmatchings/code_8009D7A0/func_800ABC40.s
 */
#include "common.h"

extern u8 *D_800FABD0;
extern s16 D_800E3658[];
extern f64 D_800E4E68;
extern f64 D_800E4E70;
extern f64 D_800E4E40;
extern f64 D_800E4E38;
extern f64 D_800E4E30;
#ifdef TARGET_PC
/* PC: tables of {s16 threshold, u16 action, u16 bits} that func_800ADA38 reads as s16. The PC starts game
 * variables in its own byte order by the width their declarations give (port/game_vars.tsv), so they are
 * declared with that width here; the N64 code only takes their addresses. */
extern s16 D_800E35F8[];
extern s16 D_800E35E0[];
#else
extern u8 D_800E35F8;
extern u8 D_800E35E0;
#endif
s8 func_800D4198(s16);
void func_800AD958(s32);
void func_800ADA38(void *);

/* Requests action 7/0x21 or the fallback record from the action timer. */
void func_800ABC40(void) {
    if (D_800E4E30 < (f64)*(f32 *)(D_800FABD0 + 0x34)) {
        if (func_800D4198(*(s16 *)(D_800FABD0 + 0x12)) != 0) {
            func_800AD958(7);
            return;
        }
    }
    if ((f64)*(f32 *)(D_800FABD0 + 0x34) < D_800E4E38) {
        func_800ADA38(&D_800E35E0);
        return;
    }
    func_800AD958(0x21);
}
