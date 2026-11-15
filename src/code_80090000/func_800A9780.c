/* @header
 * func_800A9780
 * VRAM 0x800A9780 | ROM 0x55EF0 | size 0x134
 * asm: asm/nonmatchings/code_80090000/func_800A9780.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: the menus D_800E8230 hold addresses, so they are common.h's Nw2Menu, read by field name: E's p is items, a is
 * cur and b is f6, and the N64's p[4] is the element list's f4. The N64's label D_800E9D0A, inside the menus, has no
 * PC symbol: it is D_800E8230[22].fA. */
typedef Nw2Menu E;
extern E D_800E8230[];
extern u8 D_8007EF30[];
extern u8 D_8007E228[];
extern s32 D_800E798C, D_80038AA8;
extern s16 D_80038A92, D_800E7CB8;
#else
typedef struct { u8 *p; s16 a; s16 b; u8 pad[0x130]; } E;
extern E D_800E8230[];
extern u8 D_8007EF30[];
extern u8 D_8007E228[];
extern s32 D_800E798C, D_80038AA8;
extern s16 D_80038A92, D_800E9D0A, D_800E7CB8;
#endif
extern u16 D_80038A94;
s32 func_800B0F08(void);
void func_800AE1E4(s32);
void func_800AEF28(s32);
void func_800A9108(void);

s32 func_800A9780(void) {
    s32 r;
    s32 v;
    u16 f = *(u16 *)(D_8007EF30 + 8);
    if (f & 0x800) {
        v = func_800B0F08();
        D_800E798C = v;
        if (v == 0) {
            v = 0x35;
        } else {
            v = 0x23;
        }
        goto set;
    }
    if (f & 0x8000) {
        if (*(s32 *)(D_8007E228 + 0x620) & 0x201) {
            v = D_80038AA8 + 1;
            D_80038AA8 = v;
            if (v < 9) {
                func_800AE1E4(0);
                func_800AEF28(1);
                D_800E7CB8 = 0;
                r = 0x17;
            } else {
                v = 0x1C;
set:
#ifdef TARGET_PC
                D_800E8230[22].fA = v; /* PC: by name (see above) */
#else
                D_800E9D0A = v;
#endif
                r = 0x16;
            }
        } else {
            r = 1;
            func_800A9108();
            D_800E7CB8 = 0;
            func_800AEF28(0);
        }
    } else {
        E *e;
        r = D_80038A92;
        e = &D_800E8230[r];
#ifdef TARGET_PC
        e->cur = D_80038A94; /* PC: by name (see above) */
        e->f6 = e->items->f4;
#else
        e->a = D_80038A94;
        e->b = e->p[4];
#endif
        r = 1;
        func_800A9108();
        D_800E7CB8 = 0;
        func_800AEF28(0);
    }
    return r;
}
