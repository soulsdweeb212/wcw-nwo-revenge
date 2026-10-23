#include "common.h"

typedef struct {
    s8 kind;          /* entity kind: index into D_800E3AA0/D_800E3AA4 and D_800FAF50/D_800EB4B8 */
    u8 pad[0xF];
    s16 timer;        /* current countdown */
    s16 max;          /* countdown clamp */
    u8 pad14[0xA];
    u64 flags;        /* 0x20: 0x1000000000000000 set when the countdown was started negative */
} Ent;

extern u8 D_8007E228[];
extern u16 D_800E3AA0[];
extern u16 D_800E3AA4[];
extern u16 D_800FADD0;
extern u16 D_800FAF50[];
extern u16 D_800EB4B8[];
s8 func_800D4198(s16);

/* Adjust a per-entity countdown by `amount`, clamped to `max`. When it hits zero,
 * optionally arm the shared D_800FADD0 flag bits for low entity kinds (behind a
 * random gate). `mode` then starts the countdown (records it in the per-kind
 * table; a negative amount also raises the entity flag and sets a 30-tick
 * reload), does nothing, or clears the per-kind entry. */
void func_800BF338(Ent *ent, s16 amount, s16 mode) {
    ent->timer += amount;
    if (ent->timer > ent->max) ent->timer = ent->max;

    if (ent->timer <= 0) {
        ent->timer = 0;
        if ((*(u16 *)(D_8007E228 + 0x58) & 0x100) && ent->kind < 2) {
            if (*(u16 *)(D_8007E228 + 0x58) & 0x1000) {
                if (!(D_800FADD0 & D_800E3AA4[ent->kind])) {
                    if (func_800D4198(0xFA)) {
                        D_800FADD0 |= D_800E3AA0[ent->kind];
                    }
                    D_800FADD0 |= D_800E3AA4[ent->kind];
                }
            } else {
                if (func_800D4198(0x1F4)) {
                    D_800FADD0 |= D_800E3AA0[ent->kind];
                }
            }
        }
    }
    switch ((s16)mode) {
    case 0: /* start countdown */
        D_800FAF50[ent->kind] = func_800D3550(amount);
        if (amount < 0) {
            ent->flags |= 0x1000000000000000ULL;
            D_800EB4B8[ent->kind] = 0x1E;
        }
        break;
    case 1: /* leave as-is */
        break;
    case 2: /* clear */
        D_800FAF50[ent->kind] = 0;
        break;
    }
}
