/* @header
 * func_800B75D4
 * VRAM 0x800B75D4 | ROM 0x63D44 | size 0x214
 * asm: asm/nonmatchings/code_80090000/func_800B75D4.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: a command is port.h's 16-byte Gfx (common.h's Nw2GfxCommand is the N64's 8 bytes), which
 * appendPaletteSetupDisplayList also writes on PC, and the texture's address goes into its command as the whole
 * pointer (port.h's DL_ADDR); the N64 subtracts 0x80000000 in 32 bits. The key is a MenuKey (port.h; port_decls.h declares the
 * function): only a key of the resource-name cache (MENU_KEY_IS_RES, the N64's sign test) draws a picture, a name's
 * address (MENU_KEY_NAME) as its callers pass it. The result is the cache's entry, a pointer.
 * func_800B600C (port_decls.h) hands back the entry of the resource-name cache, common.h's Nw2ResourceEntryHashed:
 * the texture, at +4 on the N64, is its allocation at +8, and w and h are reserved's +4 and +6, as the assert
 * checks. */
typedef struct { u8 pad0[8]; void *img; u8 pad10[4]; s16 w; s16 h; } T;
_Static_assert(offsetof(T, img) == offsetof(Nw2ResourceEntryHashed, allocation) &&
                   offsetof(T, w) == offsetof(Nw2ResourceEntryHashed, reserved) + 4 &&
                   offsetof(T, h) == offsetof(Nw2ResourceEntryHashed, reserved) + 6,
               "T must follow the PC layout of Nw2ResourceEntryHashed");
void appendPaletteSetupDisplayList(Gfx **);

#define E(a, b) { Gfx *q = g++; q->w0 = (u32)(a); q->w1 = (u32)(b); }

void *func_800B75D4(Gfx **dl, MenuKey id, u32 b) {
    Gfx *g = *dl;
    T *t;
    if (!MENU_KEY_IS_RES(id)) {
        return NULL;
    }
    t = func_800B600C(id, b);
    if (t == NULL) {
        return NULL;
    }
    if (!(b & 0x80000000)) {
        appendPaletteSetupDisplayList(&g);
    }
    { Gfx *q = g++; q->w0 = 0xFD500000; q->w1 = DL_ADDR(t->img); }
    E(0xF5500000, 0x07000000);
    E(0xE6000000, 0);
    { Gfx *q = g++;
        s32 n, c;
        q->w0 = 0xF3000000;
        n = t->w / 16 > 0 ? t->w / 16 + 0x7FF : 0x800;
        c = ((t->w * t->h + 3) >> 2) - 1;
        if (c >= 0x800) {
            c = 0x7FF;
        }
        q->w1 = ((c & 0xFFF) << 12) | 0x07000000 | ((t->w / 16 > 0 ? n / (t->w / 16) : n) & 0xFFF);
    }
    E(0xE7000000, 0);
    E(0xF5400000 | ((((t->w >> 1) + 7) >> 3 & 0x1FF) << 9), 0);
    E(0xF2000000, (((t->w - 1) * 4 & 0xFFF) << 12) | ((t->h - 1) * 4 & 0xFFF));
    *dl = g;
    return t;
}
#else
typedef struct { u8 pad0[4]; u32 f4; u8 pad8[4]; s16 w; s16 h; } T;
T *func_800B600C(s32, s32);
void appendPaletteSetupDisplayList(Nw2GfxCommand **);

#define E(a, b) { Nw2GfxCommand *q = g++; q->w0 = (u32)(a); q->w1 = (u32)(b); }

T *func_800B75D4(Nw2GfxCommand **dl, s32 id, u32 b) {
    Nw2GfxCommand *g = *dl;
    T *t;
    u32 m = 0x80000000;
    if (!(id & m)) {
        return 0;
    }
    t = func_800B600C(id, b);
    if (t == 0) {
        return 0;
    }
    if (!(b & m)) {
        appendPaletteSetupDisplayList(&g);
    }
    E(0xFD500000, t->f4 - m);
    E(0xF5500000, 0x07000000);
    E(0xE6000000, 0);
    { Nw2GfxCommand *q = g++;
        s32 n, c;
        s32 pad[1];
        q->w0 = 0xF3000000;
        n = t->w / 16 > 0 ? t->w / 16 + 0x7FF : 0x800;
        c = ((t->w * t->h + 3) >> 2) - 1;
        if (c >= 0x800) {
            c = 0x7FF;
        }
        q->w1 = ((c & 0xFFF) << 12) | 0x07000000 | ((t->w / 16 > 0 ? n / (t->w / 16) : n) & 0xFFF);
    }
    E(0xE7000000, 0);
    E(0xF5400000 | ((((t->w >> 1) + 7) >> 3 & 0x1FF) << 9), 0);
    E(0xF2000000, (((t->w - 1) * 4 & 0xFFF) << 12) | ((t->h - 1) * 4 & 0xFFF));
    *dl = g;
    return t;
}
#endif
