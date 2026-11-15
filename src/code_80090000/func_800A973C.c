/* @header
 * func_800A973C
 * VRAM 0x800A973C | ROM 0x55EAC | size 0x44
 * asm: asm/nonmatchings/code_80090000/func_800A973C.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: D_800E8234 is D_800E8230 + 4, the cur of the first menu, stepped by a menu. The menus hold addresses, so they
 * are common.h's Nw2Menu (0x140 bytes on PC), and the label has no PC symbol: the PC reads D_800E8230[a].cur. */
extern Nw2Menu D_800E8230[];
#else
typedef struct { u16 y; u8 p[0x136]; } S;
extern S D_800E8234[];
#endif
extern u16 D_80038A90, D_80038A92, D_80038A94;

void func_800A973C(void) {
    s16 a = D_80038A90;
    D_80038A92 = a;
#ifdef TARGET_PC
    D_80038A94 = D_800E8230[a].cur; /* PC: by name (see above) */
#else
    D_80038A94 = D_800E8234[a].y;
#endif
}
