/* @header
 * func_800906D8
 * VRAM 0x800906D8 | ROM 0x83B78 | size 0x84
 * asm: asm/nonmatchings/ovl2_80090000/func_800906D8.s
 */
#include "common.h"

void func_80004F80(void *, s16, s16);
void func_80007960(s32, s32);

typedef struct {
    u32 w0;
    u32 w1;
} Gfx2;

typedef struct {
    u8 pad0[0x10];
    Gfx2 *dl;
    u8 pad14[0x8];
    s32 f1C;
} Node;

void func_800906D8(Node *n, s16 a, s16 b, s32 c) {
    Gfx2 *g;

    func_80004F80(n, a, b);
    func_80007960(n->f1C, c & 0xFF);
    g = n->dl;
    {
        Gfx2 *d = g++;
        d->w0 = 0xE200001C;
        d->w1 = 0x504240;
    }
    {
        Gfx2 *d = g++;
        d->w0 = 0xFC121824;
        d->w1 = 0xFF33FFFF;
    }
}
