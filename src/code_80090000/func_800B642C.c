/* @header
 * func_800B642C
 * VRAM 0x800B642C | ROM 0x62B9C | size 0xC0
 * asm: asm/nonmatchings/code_80090000/func_800B642C.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: the table of loaded pictures is D_800E6BA0_ovl1 (port_decls.h), of common.h's Nw2MenuResSlot. An entry still
 * to load (flags bit 0) has a resource id as its key, a number below 0x40000000 (port.h's MenuKey). Its data is the
 * heap block that allocateHeap returns, a pointer, sized by the descriptor's size (port.h's ResDesc, the third word of
 * the N64's s32[4]). */
void *allocateHeap(u32);

void func_800B642C(void) {
    ResDesc desc;
    u8 buf[16];
    Nw2MenuResSlot *p;
    s32 i;
    void *v;
    for (i = 0, p = D_800E6BA0_ovl1; i < 0x80; i++, p++) {
        if (p->key != (MenuKey)-1 && (p->flags & 1)) {
            lookupResourceDescriptor(&desc, (u32)p->key);
            v = allocateHeap(desc.size);
            p->data = v;
            if (v) {
                func_80003684(buf, (s32)p->key, v);
                p->flags &= ~1;
            }
        }
    }
}
#else
typedef struct { s32 a; s32 b; s32 c; s32 d; } N;
extern N D_800E6BA0[];
void lookupResourceDescriptor(void *, u16);
s32 allocateHeap(s32);
void func_80003684(void *, u16, s32);

void func_800B642C(void) {
    s32 desc[4];
    u8 buf[16];
    N *p;
    s32 i;
    s32 v;
    for (i = 0, p = D_800E6BA0; i < 0x80; i++, p++) {
        if (p->a != -1 && (p->d & 1)) {
            lookupResourceDescriptor(desc, p->a);
            v = allocateHeap(desc[2]);
            p->b = v;
            if (v) {
                func_80003684(buf, p->a, v);
                p->d &= ~1;
            }
        }
    }
}
#endif
