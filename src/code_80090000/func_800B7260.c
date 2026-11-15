/* @header
 * func_800B7260
 * VRAM 0x800B7260 | ROM 0x639D0 | size 0xF4
 * asm: asm/nonmatchings/code_80090000/func_800B7260.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: a command is port.h's 16-byte Gfx, which func_800B6548 writes on PC (its PC definition takes a Gfx ** and the
 * texture and palette as pointers), so the cursor is a Gfx ** here too; the N64 steps u32 words. The picture is the
 * heap block that func_800B600C (port_decls.h) hands back for a resource id: its header, then the palette at +0x10 and
 * the texture after it. */
void func_800B6548(Gfx **, s32, s32, s32, u8 *, u8 *);
#else
u8 *func_800B600C(s32, s32);
void func_800B6938(u32 **, s32, s32, u8 *, u8 *);
void func_800B6548(u32 **, s32, s32, s32, u8 *, u8 *);
#endif

static inline u8 *load(s32 x, u8 **b, u8 **c) {
    u8 *q;
    u16 n;
    q = func_800B600C(x, 0);
    if (q == 0) {
        return 0;
    }
    n = *(u16 *)(q + 0xA);
    *c = q + 0x10;
    *b = *c + n * 2;
    return q;
}

#ifdef TARGET_PC
u8 *func_800B7260(Gfx **dl, s32 x, s32 h, s32 a) {
    u8 *b;
    u8 *c;
    Gfx *g = *dl;
#else
u8 *func_800B7260(u32 **dl, s32 x, s32 h, s32 a) {
    u8 *b;
    u8 *c;
    u32 *g = *dl;
#endif
    u8 *v;
    v = load(a, &b, &c);
    if (v == 0) {
        return 0;
    }
    b += *(u16 *)(v + 4) * x * v[8] / 8;
    func_800B6548(&g, v[8] == 8, *(u16 *)(v + 4), h, b, c);
    *dl = g;
    return v;
}
