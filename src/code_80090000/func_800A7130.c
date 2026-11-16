/* @header
 * func_800A7130
 * VRAM 0x800A7130 | ROM 0x538A0 | size 0x78
 * asm: asm/nonmatchings/code_80090000/func_800A7130.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: a command is port.h's 16-byte Gfx, which func_800B6FE0 writes on PC, so the quad between its two calls is one Gfx
 * too (the N64 writes it as two 32-bit words, its 8-byte command). Written as 8 bytes, it shifts every command after it
 * by half a command, and the renderer reads data as commands. b is the caller's object, which this function leaves
 * alone. */
u8 *func_800B6FE0(Gfx **, s32);

void func_800A7130(Gfx **dl, void *b, s32 c, s32 d) {
    Gfx *g = *dl;

    (void)b;
    func_800B6FE0(&g, d);
    g->w0 = 0x70C0E0A;
    g->w1 = 0xC0A08;
    g++;
    func_800B6FE0(&g, c);
    *dl = g;
}
#else
void func_800B6FE0(u32 **, s32);

void func_800A7130(u32 **dl, s32 b, s32 c, s32 d) {
    u32 *g = *dl;
    u32 *p;
    func_800B6FE0(&g, d);
    p = g;
    g = p + 2;
    p[0] = 0x70C0E0A;
    p[1] = 0xC0A08;
    func_800B6FE0(&g, c);
    *dl = g;
}
#endif
