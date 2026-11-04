/* @header
 * func_800B6278
 * VRAM 0x800B6278 | ROM 0x629E8 | size 0xBC
 * asm: asm/nonmatchings/code_80090000/func_800B6278.s
 */
#include "common.h"

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
