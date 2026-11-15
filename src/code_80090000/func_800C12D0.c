/* @header
 * func_800C12D0
 * VRAM 0x800C12D0 | ROM 0x6DA40 | size 0xA0
 * asm: asm/nonmatchings/code_80090000/func_800C12D0.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: the picture sets D_800D4930 hold addresses, so they have their PC layout (common.h's Nw2MenuShot); T names a
 * set's res and max a and m. */
typedef struct { void *pic[4]; u16 n[4]; u16 a; u16 m; u8 q[4]; } T;
_Static_assert(offsetof(T, a) == offsetof(Nw2MenuShot, res) && offsetof(T, m) == offsetof(Nw2MenuShot, max) &&
                   sizeof(T) == sizeof(Nw2MenuShot),
               "T follows common.h's Nw2MenuShot");
#else
typedef struct { u8 p[0x18]; u16 a; u16 m; u8 q[4]; } T;
#endif
extern T D_800D4930[];
#ifdef TARGET_PC
/* PC: D_800E81F8 holds the address of a resource (the heap block that func_800B600C, port_decls.h, hands back for
 * resource id t->a), which func_8009A02C and func_8009A878 read as a pointer; an s32 would cut it in half. */
extern s32 D_800E79C4, D_800E81E4;
extern u8 *D_800E81F8;
#else
extern s32 D_800E79C4, D_800E81F8, D_800E81E4;
s32 func_800B600C(s32, s32);
#endif
void func_800C0680(s32);

s32 func_800C12D0(s32 a) {
    T *t = &D_800D4930[D_800E79C4];
    if (t->a) {
        D_800E81F8 = func_800B600C(t->a, 0);
    } else {
        D_800E81F8 = 0;
    }
    if (a < 0) {
        a = 0;
    }
    if (a >= t->m) {
        a = t->m;
    }
    func_800C0680(a);
    D_800E81E4 = D_800E79C4;
    return a;
}
