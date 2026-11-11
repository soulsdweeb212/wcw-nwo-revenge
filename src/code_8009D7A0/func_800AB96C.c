/* @header
 * func_800AB96C
 * VRAM 0x800AB96C | ROM 0x9EE0C | size 0x2D4
 * asm: asm/nonmatchings/code_8009D7A0/func_800AB96C.s
 */
#include "common.h"

extern u8 *D_800FABD0;
extern s16 D_800FAF50[];
extern s16 D_800E35D8[];
#ifdef TARGET_PC
/* PC: tables of {s16 threshold, u16 action, u16 bits} that func_800ADA38 reads as s16. The PC starts game
 * variables in its own byte order by the width their declarations give (port/game_vars.tsv), so they are
 * declared with that width here; the N64 code only takes their addresses. */
extern s16 D_800E35B4[];
#else
extern u8 D_800E35B4[];
#endif
extern f64 D_800E4E20;
extern f64 D_800E4E28;
s8 func_800D4198(s16);
s8 func_800AB43C(void);
void func_800AD958(s32);
void func_800ADA38(void *);

void func_800AB96C(void) {
    if ((D_800FAF58->flags & WR_FLAG_SPIRIT_FULL) || (!(D_800FAF58->flags & WR_FLAG_SPECIAL) && *(s16 *)(D_800FABD0 + 0x28) >= 0x79 && func_800D4198(((s16)(D_800FAF50[D_800F9B60->id] / 3) + 1) * 40))) {
        func_800AD958(0x22); return;
    }
    if (!func_800AB43C()) {
        if (*(f32 *)(D_800FABD0 + 0x34) > D_800E4E20 && func_800D4198(*(s16 *)(D_800FABD0 + 0x12))
            && func_800D4198(D_800E35D8[(s8)*(u8 *)(D_800FAF58->profile + 0x18) / 3])) {
            func_800AD958(7); return;
        }
        if (*(s16 *)(D_800FABD0 + 0x22) == 0xD) { func_800AD958(0x27); return; }
        if (*(f32 *)(D_800FABD0 + 0x3C) > D_800E4E28) { func_800AD958(0x21); return; }
        if (D_800FAF58->flags & WR_FLAG_SPECIAL) goto two;
        if (!func_800D4198(*(s16 *)(D_800FABD0 + 0x12))) goto ada;
        if (func_800D4198(*(s16 *)(D_800FABD0 + 0x24) < 0x28 ? 0x2EE : 0x1F4)) {
two:
            func_800AD958(2); return;
        }
        if (func_800D4198(500)) { func_800AD958(6); return; }
        if (func_800D4198(500)) { func_800AD958(3); return; }
        func_800AD958(1); return;
ada:
        func_800ADA38(D_800E35B4);
    }
}
