/* @header
 * func_800B6278
 * VRAM 0x800B6278 | ROM 0x629E8 | size 0xBC
 * asm: asm/nonmatchings/code_80090000/func_800B6278.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: the table of loaded pictures is D_800E6BA0_ovl1 (port_decls.h), of common.h's Nw2MenuResSlot. An entry's key is a
 * resource id, whose data is a heap block (releaseHeapBlock takes it, a pointer), or a key of the resource-name cache
 * (MENU_KEY_IS_RES, port.h; the N64 tests the sign), whose data is the cache's entry (func_8002A5F4 takes it). */
void releaseHeapBlock(u8 *);
void func_8002A5F4(void *entry);

void func_800B6278(void) {
    Nw2MenuResSlot *p;
    s32 i;
    for (i = 0, p = D_800E6BA0_ovl1; i < 0x80; i++, p++) {
        if (p->key != (MenuKey)-1) {
            if (!MENU_KEY_IS_RES(p->key)) {
                if (!(p->flags & 1)) {
                    releaseHeapBlock(p->data);
                }
            } else {
                func_8002A5F4(p->data);
            }
            p->key = (MenuKey)-1;
            p->flags = 0;
            p->data = NULL;
        }
    }
}
#else
typedef struct { s32 a; s32 b; s32 c; s32 d; } N;
extern N D_800E6BA0[];
void releaseHeapBlock(s32);
void func_8002A5F4(s32);

void func_800B6278(void) {
    N *p;
    s32 i;
    for (i = 0, p = D_800E6BA0; i < 0x80; i++, p++) {
        if (p->a != -1) {
            if (!(p->a & 0x80000000)) {
                if (!(p->d & 1)) {
                    releaseHeapBlock(p->b);
                }
            } else {
                func_8002A5F4(p->b);
            }
            p->a = -1;
            p->d = 0;
            p->b = 0;
        }
    }
}
#endif
