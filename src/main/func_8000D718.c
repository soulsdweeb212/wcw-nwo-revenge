/* @header
 * func_8000D718
 * VRAM 0x8000D718 | ROM 0xE318 | size 0x58
 * asm: asm/nonmatchings/main/func_8000D718.s
 */
#include "common.h"

#ifndef TARGET_PC /* on PC, port_decls.h declares func_8000520C */
s32 func_8000520C(s32, s32);
#endif

/* Apply func_8000520C to 20 record pairs (destination stride 0xDC, source stride
 * 0x2C). */
#ifdef TARGET_PC
/* PC: the types of port_decls.h's line. objs (the N64's dst) is an array of 0xDC-byte objects (Nw2SceneObj, which
 * keeps its N64 size, common.h) and recs (src) an array of display records, whose PC layout is Nw2Descr4BA8 (0x50
 * bytes, common.h). So the records step by sizeof(Nw2Descr4BA8), not by 0x2C, and both addresses travel as
 * pointers. */
void func_8000D718(void *objs, void *recs) {
    u32 n;

    for (n = 0; n < 20; n++) {
        func_8000520C((u8 *)objs + n * sizeof(Nw2SceneObj), (Nw2Descr4BA8 *)recs + n);
    }
}
#else
void func_8000D718(s32 dst, s32 src) {
    s32 i;
    s32 s;
    u32 n;

    n = 0;
    s = src;
    i = dst;
    do {
        func_8000520C(i, s);
        s += 0x2C;
        n += 1;
        i += 0xDC;
    } while (n < 0x14U);
}
#endif
