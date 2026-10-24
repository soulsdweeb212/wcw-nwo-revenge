#include "common.h"

typedef struct {
    u8 pad0[0x20];
    u64 flags;
    u8 pad28[0x388];
} Nw2RecA578;

typedef struct {
    u8 pad[0x58];
    u16 f58;
} Nw2GlobA578;

extern Nw2RecA578 D_800F9D10[];
extern Nw2GlobA578 D_8007E228;

s32 func_800BA578(s8 arg0) {
    s16 i;
    s16 count;
    u16 f = D_8007E228.f58;

    D_800F9D10[arg0].flags |= 0x8000;
    if (f & 0x300) {
        return 1;
    }
    if (f & 0x400) {
        if (D_800EB478 >= D_800EB474) {
            count = 0;
            for (i = 0; i < 4; i++) {
                if (!(D_800F9D10[i].flags & 0x8000)) {
                    count++;
                }
            }
            if (count < 2) {
                return 1;
            }
        }
    }
    return 0;
}
