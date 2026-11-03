/* @header
 * func_800AAB64
 * VRAM 0x800AAB64 | ROM 0x572D4 | size 0xC8
 * asm: asm/nonmatchings/code_80090000/func_800AAB64.s
 */
#include "common.h"

typedef struct { u8 pad0[6]; u8 nav[4]; u8 padA[0xC]; } Item;
typedef struct { u8 pad0[0xA]; u16 flags; u8 padC[0x148 - 0xC]; } El;
typedef struct { Item **items; s16 cur; u8 pad6[0xE]; El *el; } Menu;

s32 func_800AAB64(Menu *m, s32 btn) {
    s32 n = m->cur;
    Item *it = &(*m->items)[n];

    for (;;) {
        if (btn & 0x800) {
            n = it->nav[0];
        } else if (btn & 0x400) {
            n = it->nav[1];
        } else if (btn & 0x200) {
            n = it->nav[2];
        } else if (btn & 0x100) {
            n = it->nav[3];
        } else {
            return n;
        }
        if (m->cur == n) {
            return n;
        }
        if (!(m->el[n].flags & 0x53)) {
            return n;
        }
        it = &(*m->items)[n];
    }
}
