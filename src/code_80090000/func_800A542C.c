/* @header
 * func_800A542C
 * VRAM 0x800A542C | ROM 0x51B9C | size 0x180
 * asm: asm/nonmatchings/code_80090000/func_800A542C.s
 */
#include "common.h"

typedef struct { u32 w0, w1; } G;
extern u16 D_800C9210[], D_800C9224[];
void func_800A5264(G **, s32);
u8 *func_800B6FE0(G **, s32);

void func_800A542C(G **dl, u8 *t) {
    G *g = *dl;
    u8 a = t[0x21];

    { G *d = g++; d->w0 = 0xFC51FEA3; d->w1 = 0x44FE773B; }
    { G *d = g++; d->w0 = 0xFA000000; d->w1 = ((t[0x16] * 2) / 3) & 0xFF; }
    { G *d = g++; d->w0 = 0x0700080A; d->w1 = 0xA04; }
    { G *d = g++; d->w0 = 0xE7000000; d->w1 = 0; }
    { G *d = g++; d->w0 = 0xFA000000; d->w1 = (t[0x17] << 24) | (t[0x17] << 16) | (t[0x17] << 8) | t[0x16]; }
    { G *d = g++; d->w0 = 0xFC5196A3; d->w1 = 0x112CFE7F; }
    if (a & 0x40) {
        func_800B6FE0(&g, D_800C9224[a & 0xF]);
    } else if (a & 0x30) {
        func_800A5264(&g, a);
        goto end;
    } else {
        func_800B6FE0(&g, D_800C9210[a]);
    }
    { G *d = g++; d->w0 = 0x07000206; d->w1 = 0x604; }
end:
    *dl = g;
}
