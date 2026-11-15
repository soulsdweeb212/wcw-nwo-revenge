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
#ifdef TARGET_PC
/* PC: a command is port.h's 16-byte Gfx, which the emitters this one calls also write on PC. The draw list is a
 * picture list of common.h (Nw2MenuPicList of Nw2MenuPic, 16 bytes each on PC), whose key is a MenuKey (port.h): the
 * N64's sign test is MENU_KEY_IS_RES, and the tag 0x10000000 is stripped only from a number. A key of 0x122 to 0x134
 * is drawn as the name that func_80099734 looks up (port_decls.h: its address, a key of the resource-name cache by
 * MENU_KEY_NAME). The u16 table of the 0x01xx family, read at D_800C9014 + 0x44 (D_800C9058) indexed by the key, is
 * named by the address the keys 0x100 and up reach, 0x800C9258, so the PC reads it as u16 values (its 16-bit values
 * then take the PC's byte order). func_8002B528 returns a u16 (its definition); func_80097E1C takes the cursor as a
 * void ** (its PC definition). */
extern u16 D_800C9258[];
u16 func_8002B528(s32);
void func_80097E1C(void **, s32, s32, s32, s32, s32, s32);
void emitSpriteCommand(Gfx **, MenuKey, s32, s32, s32, s32, s32);
void func_80098804(Gfx **, s32, s32, s32, s32, s32);
void func_80098C40(Gfx **out, Nw2MenuPicList *list, s32 color, s32 mode) {
    Gfx *p; Nw2MenuPic *e; u32 i; MenuKey key, id;
    p = *out;
    { Gfx *q = p++; q->w0 = 0xFA000000; q->w1 = color & 255; }
    { Gfx *q = p++; q->w0 = 0xFB000000; q->w1 = 0xFFFFFF00; }
    e = list->pics;
    for (i = 0; i < list->count; i++, e++) {
        key = e->key;
        id = MENU_KEY_IS_RES(key) ? key : (key & 0xEFFFFFFF);
        if (MENU_KEY_IS_RES(id)) emitSpriteCommand(&p, id, e->x, e->y, color, e->match, mode);
        else if (id - 0x122 < 0x13) emitSpriteCommand(&p, MENU_KEY_NAME(func_80099734((s32)id)), e->x, e->y, color, e->match, mode);
        else switch (key & 0xFF00) {
        case 0x100: func_80097E1C((void **)&p, D_800C9258[id - 0x100], e->x, e->y, color, e->match, mode); break;
        case 0x5100: func_80098804(&p, func_8002B528(key & 255), ((u32)id >> 16) & 3, e->x, e->y, color); break;
        }
    }
    *out = p;
}
#else
typedef struct { s32 id; s16 x, y; s32 extra; } DrawEntry98;
typedef struct { DrawEntry98 *entries; u32 count; } DrawList98;
extern u8 D_800C9014[];
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
        case 0x100: func_80097E1C(&p, ((u16 *)(D_800C9014 + 0x44))[id], e->x, e->y, color, e->extra, mode); break;
        case 0x5100: func_80098804(&p, func_8002B528(e->id & 255), ((u32)id >> 16) & 3, e->x, e->y, color); break;
        }
    }
    *out = p;
}
#endif
