/* @header
 * func_800B6334
 * VRAM 0x800B6334 | ROM 0x62AA4 | size 0xF8
 * asm: asm/nonmatchings/code_80090000/func_800B6334.s
 */
#include "common.h"

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
