/* @header
 * func_800B5FD0
 * VRAM 0x800B5FD0 | ROM 0x62740 | size 0x3C
 * asm: asm/nonmatchings/code_80090000/func_800B5FD0.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: the table of loaded pictures is D_800E6BA0_ovl1 (port_decls.h), of common.h's Nw2MenuResSlot, whose key and data
 * are as wide as a pointer: an entry is 0x18 bytes, so the loop steps by the struct. -1 is a free entry, as on the
 * N64. */
void func_800B5FD0(void) {
    s32 i;
    Nw2MenuResSlot *p;
    for (i = 0, p = D_800E6BA0_ovl1; i < 0x80; i++, p++) {
        p->key = (MenuKey)-1;
        p->flags = 0;
        p->data = NULL;
    }
}
#else
typedef struct { s32 a; s32 b; s32 c; s32 d; } N;
extern N D_800E6BA0[];

void func_800B5FD0(void) {
    s32 i;
    N *p;
    for (i = 0, p = D_800E6BA0; i < 0x80; i++, p++) {
        p->a = -1;
        p->d = 0;
        p->b = 0;
    }
}
#endif
