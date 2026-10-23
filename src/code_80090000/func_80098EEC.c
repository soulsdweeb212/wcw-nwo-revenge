#include "common.h"

/* func_80098EEC: accumulates a resource request. It finds an entry with the
 * same key and flags and bumps its amount (255 when flag 1 is set, +16 for
 * flag 2, +32 for flag 4, otherwise +32*D_800E8208), clamping at 255;
 * otherwise it takes the first free slot and initialises it the same way.
 * Returns -1 on success, 0 when no slot is free. */
extern Nw2ResourceRequest *D_800E7518;
extern s32 D_800E8208;

s32 func_80098EEC(s32 key, s32 flags) {
    s32 i;
    Nw2ResourceRequest *p;

    for (i = 0, p = D_800E7518; i < 96; i++, p++) {
        if (p->key == key && p->flags == flags) {
            p->flags = flags;
            if (flags & 1)
                p->amount = 255;
            else if (flags & 2)
                p->amount += 16;
            else if (flags & 4)
                p->amount += 32;
            else
                p->amount += D_800E8208 << 5;
            if (p->amount >= 255)
                p->amount = 255;
            p->active = 1;
            return -1;
        }
    }
    for (i = 0, p = D_800E7518; i < 96; i++, p++) {
        if (p->key == 0) {
            p->key = key;
            p->flags = flags;
            p->active = 1;
            if (p->flags & 1)
                p->amount = 255;
            else if (p->flags & 2)
                p->amount = 16;
            else if (p->flags & 4)
                p->amount = 32;
            else
                p->amount = D_800E8208 << 5;
            return -1;
        }
    }
    return 0;
}
