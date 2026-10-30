/* @header
 * func_8001A400
 * VRAM 0x8001A400 | ROM 0x1B000 | size 0x78
 * asm: asm/nonmatchings/main/func_8001A400.s
 */
#include "common.h"

extern s32 D_80036F54;
typedef struct { u8 pad00[0x30]; u8 *f30; } Nw2Obj36F54;
typedef struct { u8 pad0[4]; s32 *(*fn)(s32, s32 *); } Nw2Tbl36F54;

s32 *func_8001A400(s32 arg0, s32 *arg1) {
    Nw2Obj36F54 *obj = (Nw2Obj36F54 *)D_80036F54;
    s32 *p;
    s32 *q;
    arg1[0] = 0x020004E0;
    arg1[1] = 0x2E0;
    p = ((Nw2Tbl36F54 *)obj->f30)->fn(arg0, arg1 + 2);
    do { q = p; p = p + 2; } while (0);
    q[0] = 0x0C007FFF;
    arg0 = 0x07C004E0;
    q[1] = arg0;
    p[0] = 0x0C007FFF; p[1] = 0x09300650;
    return p + 2;
}
