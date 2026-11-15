/* @header
 * func_800B11BC
 * VRAM 0x800B11BC | ROM 0x5D92C | size 0xDC
 * asm: asm/nonmatchings/code_80090000/func_800B11BC.s
 */
#include "common.h"

typedef struct { u8 *p; u16 n; u16 c; } L;
extern L lookupSubTables[];
extern u8 D_8007EF30[];
#ifdef TARGET_PC
/* PC: the type of func_8002B668's definition, which returns a u16: read as an s32, the PC result's upper bits would
 * be unset. */
u16 func_8002B668(u32, s32);
#else
s32 func_8002B668(s32, s32);
#endif
s32 func_8002B710(s32);

static inline s32 chk(s32 x) {
    s32 v = func_8002B710(x);
    s32 r;
    if (v) {
        r = -((D_8007EF30[0x14C] >> (v - 1)) & 1);
    } else {
        r = -1;
    }
    return r;
}

s32 func_800B11BC(s32 a, s32 b) {
    L *t = &lookupSubTables[a];
    s32 r = 0;
    s32 i;
    s32 v;
    for (i = 0; i < t->n; i++) {
        v = func_8002B668(a, i);
        if (chk(v)) {
            if (v == b) {
                return r;
            }
            r++;
        }
    }
    return 0;
}
