/* @header
 * func_80098C40
 * VRAM 0x80098C40 | ROM 0x453B0 | size 0x1DC
 * asm: asm/nonmatchings/code_80090000/func_80098C40.s
 */
#include "common.h"

/* Emit a colour/sprite batch into the display list at *out. Starts with the
 * RDP set-primitive-colour (0xFA) and set-env-colour (0xFB) commands, then
 * walks the draw list: negative IDs, IDs 0x122..0x134 (via the 0x99734
 * lookup) and 0x01xx/0x51xx families dispatch to their respective emitters;
 * other IDs are skipped. Advances *out. */
typedef struct { s32 id; s16 x, y; s32 extra; } DrawEntry98;
typedef struct { DrawEntry98 *entries; u32 count; } DrawList98;
extern u8 updateEntityAttackState[];
s32 func_8002B528(s32);
void func_80097E1C(void **, u16, s16, s16, s32, s32, s32);
void emitSpriteCommand(void **, s32, s16, s16, s32, s32, s32);
void func_80098804(void **, s32, s32, s16, s32, s32);
s32 func_80099734(s32);
void func_80098C40(void **out, DrawList98 *list, s32 color, s32 mode) {
    void *p; DrawEntry98 *e; u32 i; s32 id;
    p = *out;
    { Nw2GfxCommand *q = p; p = (u8 *)p + 8; q->w0 = 0xFA000000; q->w1 = color & 255; }
    { Nw2GfxCommand *q = p; p = (u8 *)p + 8; q->w0 = 0xFB000000; q->w1 = -256; }
    e = list->entries;
    for (i = 0; i < list->count; i++, e++) {
        id = e->id & 0xEFFFFFFF;
        if (id < 0) emitSpriteCommand(&p, id, e->x, e->y, color, e->extra, mode);
        else if ((u32)(id - 0x122) < 0x13) emitSpriteCommand(&p, func_80099734(id), e->x, e->y, color, e->extra, mode);
        else switch (e->id & 0xFF00) {
        case 0x100: func_80097E1C(&p, ((u16 *)(updateEntityAttackState + 0x44))[id], e->x, e->y, color, e->extra, mode); break;
        case 0x5100: func_80098804(&p, func_8002B528(e->id & 255), ((u32)id >> 16) & 3, e->x, e->y, color); break;
        }
    }
    *out = p;
}
