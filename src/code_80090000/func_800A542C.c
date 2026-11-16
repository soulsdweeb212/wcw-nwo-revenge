/* @header
 * func_800A542C
 * VRAM 0x800A542C | ROM 0x51B9C | size 0x180
 * asm: asm/nonmatchings/code_80090000/func_800A542C.s
 */
#include "common.h"

#ifdef TARGET_PC
typedef Gfx G; /* PC: a command is port.h's 16-byte Gfx */
#else
typedef struct { u32 w0, w1; } G;
#endif
extern u16 D_800C9210[], D_800C9224[];
void func_800A5264(G **, s32);
u8 *func_800B6FE0(G **, s32);

void func_800A542C(G **dl, u8 *t) {
    G *g = *dl;
#ifdef TARGET_PC
    /* PC: +0x20 of the menu object is a 16-bit value (func_8009FE3C's Obj: f20, the screen in its high byte and the
     * item in its low byte). The N64 takes the low byte at +0x21, its second byte; on PC the low byte comes first, so
     * the u16 is read whole. */
    u8 a = *(u16 *)(t + 0x20);
#else
    u8 a = t[0x21];
#endif

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
