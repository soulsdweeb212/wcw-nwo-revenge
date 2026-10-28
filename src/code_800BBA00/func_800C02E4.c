#include "common.h"

typedef union { f32 f; s32 i; } NwFI;
typedef struct { NwFI e[4]; } NwV4;

f32 nw2Sqrtf(f32);
f32 func_80003A3C(f32, f32);

extern f64 D_800E6BA8;
extern f64 D_800E68D0;

/* Clears the entity's 0x20 flag when it is flagged 2 and 0x20 and its counter
 * (+0x12) is below 0xF8. */
void func_800C02E4(u8 *arg0) {
    u64 flags = *(u64 *)(arg0 + 0x20);
    if ((flags & 0x2) && (flags & 0x20) && (*(s16 *)(arg0 + 0x12) < 0xF8)) {
        *(u64 *)(arg0 + 0x20) = flags & ~0x20;
    }
}
