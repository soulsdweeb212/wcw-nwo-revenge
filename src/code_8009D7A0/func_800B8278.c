#include "common.h"

typedef struct {
    s8 id;
    u8 pad1;
    s16 f2;
    u8 pad4[0x1C];
    u64 flags;
    u8 pad28[0x388];
} Ent3B0;

extern Ent3B0 D_800F9D10[];

/* Builds a bitmask over the 4 entity slots from their flag words: for each live
 * slot (f2 != -1), flag 0x8000 sets bit 6+i, else flag 0x200 sets bit i and
 * adds 0x10 (flag 0x600000000000) and 0x20 (flag 0x100). */
/* The loop body is wrapped in do { } while (0), as a macro would be: without it the delay slots are filled differently. */
u16 func_800B8278(void) {
    s16 i;
    u16 r;
    s32 lo;
    s32 hi;

    r = 0;
    lo = 1;
    hi = 0x40;
    for (i = 0; i < 4; lo <<= 1, i++, hi <<= 1) {
        do {
            if (D_800F9D10[i].f2 != -1) {
                u64 f = D_800F9D10[i].flags;

                if (D_800F9D10[i].flags & 0x8000) {
                    r |= hi;
                } else if (f & 0x200) {
                    r |= lo;
                    if (f & 0x600000000000ULL) {
                        r |= 0x10;
                    }
                    if (D_800F9D10[i].flags & 0x100) {
                        r |= 0x20;
                    }
                }
            }
        } while (0);
    }
    return r;
}
