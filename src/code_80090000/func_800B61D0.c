/* @header
 * func_800B61D0
 * VRAM 0x800B61D0 | ROM 0x62940 | size 0xA8
 * asm: asm/nonmatchings/code_80090000/func_800B61D0.s
 */
#include "common.h"

typedef struct { s32 a; s32 b; s32 c; s32 d; } N;
extern N D_800E6BA0[];
void releaseHeapBlock(s32);
void func_8002A5F4(s32);

static inline N *find(s32 id) {
    s32 i = 0;
    N *p = D_800E6BA0;
    for (; i < 0x80; i++) {
        if (p->a == id) {
            break;
        }
        p++;
    }
    return i != 0x80 ? p : 0;
}

void func_800B61D0(s32 id) {
    N *e = find(id);
    if (e) {
        if (e->a >= 0) {
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
