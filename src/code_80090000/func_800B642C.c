/* @header
 * func_800B642C
 * VRAM 0x800B642C | ROM 0x62B9C | size 0xC0
 * asm: asm/nonmatchings/code_80090000/func_800B642C.s
 */
#include "common.h"

typedef struct { s32 a; s32 b; s32 c; s32 d; } N;
extern N D_800E6BA0[];
#ifndef TARGET_PC /* on PC, port.h declares the loader functions */
void lookupResourceDescriptor(void *, u16);
#endif
s32 allocateHeap(s32);
#ifndef TARGET_PC /* on PC, port.h declares the loader functions */
void func_80003684(void *, u16, s32);
#endif

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
