/* @header
 * func_800A9C80
 * VRAM 0x800A9C80 | ROM 0x563F0 | size 0x1C0
 * asm: asm/nonmatchings/code_80090000/func_800A9C80.s
 */
#include "common.h"

extern u8 D_8007EF30[];
s32 func_8002B4A4(s32);
#define F(t, o, i) (*(t *)(D_8007EF30 + (o) + ((i) << 4)))

static inline s32 taken(s32 a, s32 i) {
    s32 j;
    if (i < 0 || i >= func_8002B4A4(a)) {
        return 0;
    }
    for (j = 0; j < 4; j++) {
        if (F(s16, 0x4E, j) == a && (F(u8, 0x50, j) == i || (*(u16 *)(D_8007EF30 + 8) & 0x8000))) {
            return -1;
        }
    }
    return 0;
}

static inline s32 freeSlot(s32 a) {
    s32 n, i;
    if ((*(u16 *)(D_8007EF30 + 8) & 0x8000) && *(s16 *)(D_8007EF30 + 0x4E) == a) {
        return -1;
    }
    n = func_8002B4A4(a);
    for (i = 0; i < n; i++) {
        if (!taken(a, i)) {
            return i;
        }
    }
    return -1;
}

s32 func_800A9C80(s32 id, s32 cur, s32 step) {
    s32 n, i;

    if (freeSlot(id) < 0) {
        return cur;
    }
    i = cur;
    n = func_8002B4A4(id);
    do {
        i += step;
        if (i >= n) {
            i = 0;
        }
        if (i < 0) {
            i = n - 1;
        }
        if (i == cur) {
            break;
        }
    } while (taken(id, i));
    return i;
}
