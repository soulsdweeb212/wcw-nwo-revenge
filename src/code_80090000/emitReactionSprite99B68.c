/* @header
 * emitReactionSprite99B68  (originally func_80099B68)
 * VRAM 0x80099B68 | ROM 0x462D8 | size 0x288
 * asm: asm/nonmatchings/code_80090000/emitReactionSprite99B68.s
 */
#include "common.h"

/* Appends the display list for one entity's reaction sprite to *arg0.
 * The sprite frame (+0xEA) selects one of three vertical bands, each with
 * its own row offset and alpha (0xFF, fading 0..0x20). It first emits a
 * texture load (0xDE), a palette setup (0xE3) and a primitive colour
 * (0xFA) then, for the three quad entries at D_800C94CC
 * +0x23C, emits each visible piece with func_80096D8C, honouring the
 * entry's alignment flag (centred / right / right-of-0xF0). The frame
 * counter is advanced and the output pointer written back. */
typedef struct {
    void *data;
    u16 start;
    u16 len;
    s16 flag;
    s16 x;
} Nw2QuadEntry;

typedef struct {
    u8 pad0[4];
    void *f4;
    u8 pad8[4];
    s16 fC;
    s16 fE;
    s16 f10;
} Nw2Sprite;
#ifdef TARGET_PC
/* PC: a Nw2Sprite is an entry of the resource-name cache (func_800B600C hands back what func_8002A2FC returns for a
 * name), whose PC layout is Nw2ResourceEntryHashed in common.h. On PC the view's pointer (f4) is 8 bytes and starts at
 * a multiple of 8, so it lies at +8, the entry's allocation, and fC, fE and f10 fall at reserved's +4, +6 and +8. The
 * view needs no PC version of its own; the assert checks that it still agrees with the entry. */
_Static_assert(offsetof(Nw2Sprite, f4) == offsetof(Nw2ResourceEntryHashed, allocation) &&
                   offsetof(Nw2Sprite, fC) == offsetof(Nw2ResourceEntryHashed, reserved) + 4 &&
                   offsetof(Nw2Sprite, fE) == offsetof(Nw2ResourceEntryHashed, reserved) + 6 &&
                   offsetof(Nw2Sprite, f10) == offsetof(Nw2ResourceEntryHashed, reserved) + 8,
               "Nw2Sprite must follow the PC layout of Nw2ResourceEntryHashed");
#endif

typedef struct {
    u8 pad[0xEA];
    u16 frame;
} Nw2SpriteOwner;

#ifdef TARGET_PC
/* PC: the display list at 0x800C9620 by its own address (port.h's DL_ADDR turns it into the command word; D_C9620 is
 * its N64 physical address, a link constant). */
extern u8 D_800C9620[];
#else
extern u8 D_C9620[];
#endif
extern u8 D_800C94CC[];
void appendPaletteSetupDisplayList(void *);
void func_8000DEE4(s32);
void *func_800B600C(void *, s32);
s32 func_80029C40(void *, u16, s32);
void func_80096D8C(void *, void *, s32, s32, s32, s32, s32, s32, s32);

#ifdef TARGET_PC
/* PC: a command is port.h's 16-byte Gfx, as appendPaletteSetupDisplayList and func_80096D8C write it, so the list is
 * a list of Gfx (the N64 writes each command as two u32 words). */
void emitReactionSprite99B68(Gfx **arg0, Nw2SpriteOwner *arg1)
{
    Gfx *dl;
    Gfx *p;
#else
void emitReactionSprite99B68(u32 **arg0, Nw2SpriteOwner *arg1)
{
    u32 *dl;
    u32 *p;
#endif
    s32 frame, alpha, row, i, color, align, bandTmp;
    Nw2QuadEntry *entry;
    Nw2Sprite *sprite;

    dl = *arg0;
    frame = arg1->frame - 1;
    alpha = 0xFF;
    if (frame < 0x80) {
        if (frame < 0) {
            bandTmp = arg1->frame + 2;
        } else {
            bandTmp = frame;
        }
        row = bandTmp >> 2;
    } else if (frame < 0xA0) {
        alpha = (0x9F - frame) << 2;
        row = 0x20;
    } else {
        alpha = 0;
        row = 0;
    }

#ifdef TARGET_PC
    /* PC: two Gfx commands; the branch target as the whole pointer (port.h's DL_ADDR). */
    p = dl;
    p[0].w0 = 0xDE000000;
    p[0].w1 = DL_ADDR(D_800C9620);
    p[1].w0 = 0xE3001201;
    p[1].w1 = 0;
    dl = p + 2;
#else
    p = dl;
    dl = p + 2;
    p[0] = 0xDE000000;
    p[1] = (u32)D_C9620;
    dl = p + 4;
    p[2] = 0xE3001201;
    p[3] = 0;
#endif
    appendPaletteSetupDisplayList(&dl);
    p = dl;
    i = 0;

    entry = (Nw2QuadEntry *)(D_800C94CC + 0x23C);
#ifdef TARGET_PC
    /* PC: two Gfx commands, as above. */
    p[0].w0 = 0xFA000000;
    p[0].w1 = alpha & 0xFF;
    p[1].w0 = 0xFB000000;
    p[1].w1 = 0;
    dl = p + 2;
#else
    dl = p + 2;
    p[0] = 0xFA000000;
    p[1] = alpha & 0xFF;
    dl = p + 4;
    p[2] = 0xFB000000;
    p[3] = 0;
#endif

    do {
        if (row >= entry->start) {
            sprite = func_800B600C(entry->data, 8);
            if (row < entry->start + entry->len) {
                u32 raw = func_80029C40(entry->data, 8, row - entry->start);
                color = (raw & 0xFFFF) + ((raw >> 16) & 0xFF);
                if (alpha == 0xFF && !(frame & 3) && *((u8 *)entry->data + (row - entry->start)) != 0x20) {
                    func_8000DEE4(0x40A);
                }
            } else {
                color = sprite->fC;
            }
            if (entry->flag == 0) {
                align = (0x1E0 - sprite->f10) / 2;
            } else if (entry->flag >= 0) {
                align = 0xF0;
            } else {
                align = 0xF0 - sprite->f10;
            }
            func_80096D8C(&dl, sprite->f4, 0, align, entry->x - (sprite->fE / 2), sprite->fC, sprite->fE, color, sprite->fE);
        }
        i += 1;
        entry += 1;
    } while (i < 3);
    arg1->frame = arg1->frame + 1;
    *arg0 = dl;
}
