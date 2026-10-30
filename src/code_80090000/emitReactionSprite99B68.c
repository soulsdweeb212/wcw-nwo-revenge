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
 * (0xFA) then, for the three quad entries at updateEntityReactionState
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

typedef struct {
    u8 pad[0xEA];
    u16 frame;
} Nw2SpriteOwner;

extern u8 D_C9620[];
extern u8 updateEntityReactionState[];
void appendPaletteSetupDisplayList(void *);
void func_8000DEE4(s32);
void *func_800B600C(void *, s32);
s32 func_80029C40(void *, u16, s32);
void func_80096D8C(void *, void *, s32, s32, s32, s32, s32, s32, s32);

void emitReactionSprite99B68(u32 **arg0, Nw2SpriteOwner *arg1)
{
    u32 *dl;
    u32 *p;
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

    p = dl;
    dl = p + 2;
    p[0] = 0xDE000000;
    p[1] = (u32)D_C9620;
    dl = p + 4;
    p[2] = 0xE3001201;
    p[3] = 0;
    appendPaletteSetupDisplayList(&dl);
    p = dl;
    i = 0;

    entry = (Nw2QuadEntry *)(updateEntityReactionState + 0x23C);
    dl = p + 2;
    p[0] = 0xFA000000;
    p[1] = alpha & 0xFF;
    dl = p + 4;
    p[2] = 0xFB000000;
    p[3] = 0;

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
