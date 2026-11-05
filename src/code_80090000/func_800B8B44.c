/* @header
 * func_800B8B44
 * VRAM 0x800B8B44 | ROM 0x652B4 | size 0x108
 * asm: asm/nonmatchings/code_80090000/func_800B8B44.s
 */
#include "common.h"


typedef struct { u8 a[0x18]; u8 b[0xA]; u8 c; u8 d; u16 e; } R;
typedef struct { R r[4]; s32 chk; } Rec;
typedef struct { s32 chk; u8 pad[0x98]; } Chk;
extern u8 *D_800DCFB8;
s32 func_800B9228(void *, s32);
u8 *func_8002B790(s32, s32);
void bcopy(void *, void *, s32);

void func_800B8B44(void) {
    s32 i, j;
    Rec *p = (Rec *)(D_800DCFB8 + 0x600);
    Chk *c = (Chk *)(D_800DCFB8 + 0x698);
    u8 *r;
    for (i = 0; i < 0x40; i++, c++, p++) {
        if (c->chk != func_800B9228(p, 0x98)) {
            for (j = 0; j < 4; j++) {
                r = func_8002B790(i, j);
                bcopy(r, p->r[j].a, 0x18);
                bcopy(r + 0x19, p->r[j].b, 0xA);
                p->r[j].c = r[0x24];
                p->r[j].d = r[0x25];
                p->r[j].e = (r[0x27] & 0x1F) | ((r[0x28] & 0x1F) << 5);
            }
            c->chk = func_800B9228(p, 0x98);
        }
    }
}
