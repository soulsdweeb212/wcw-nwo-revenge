/* @header
 * func_800B6334
 * VRAM 0x800B6334 | ROM 0x62AA4 | size 0xF8
 * asm: asm/nonmatchings/code_80090000/func_800B6334.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: the table of loaded pictures is D_800E6BA0_ovl1 (port_decls.h), of common.h's Nw2MenuResSlot; an entry's data is
 * freed as in func_800B6278: a heap block for a resource id, the resource-name cache's entry for a key of that cache
 * (MENU_KEY_IS_RES, port.h; the N64 tests the sign). */
void releaseHeapBlock(u8 *);
void func_8002A5F4(void *entry);
void func_8002A658(void);

void func_800B6334(void) {
    s32 i;
    Nw2MenuResSlot *e;
    i = 0;
    e = D_800E6BA0_ovl1;
    for (; i < 0x80; i++, e++) {
        if (e->key != (MenuKey)-1) {
            e->refs--;
            if (e->refs >= 3) {
                e->refs = 2;
            }
            if (e->refs < 0) {
                if (!MENU_KEY_IS_RES(e->key)) {
                    if (!(e->flags & 1)) {
                        releaseHeapBlock(e->data);
                    }
                } else {
                    func_8002A5F4(e->data);
                }
                e->key = (MenuKey)-1;
                e->flags = 0;
                e->data = NULL;
            }
        }
    }
    func_8002A658();
}
#else
typedef struct { u32 a; s32 b; s32 c; s32 d; } E;
extern E D_800E6BA0[];
void releaseHeapBlock(s32);
void func_8002A5F4(s32);
void func_8002A658(void);

void func_800B6334(void) {
    s32 i;
    E *e;
    i = 0;
    e = D_800E6BA0;
    for (; i < 0x80; i++, e++) {
        if (e->a != -1) {
            e->c--;
            if (e->c >= 3) {
                e->c = 2;
            }
            if (e->c < 0) {
                if (!(e->a & 0x80000000)) {
                    if (!(e->d & 1)) {
                        releaseHeapBlock(e->b);
                    }
                } else {
                    func_8002A5F4(e->b);
                }
                e->a = -1;
                e->d = 0;
                e->b = 0;
            }
        }
    }
    func_8002A658();
}
#endif
