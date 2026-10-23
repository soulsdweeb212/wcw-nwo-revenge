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

/* Returns 1 when arg1's +0x37 bit0 is set, arg0/arg1 share the 0x40 flag and
 * arg2 is below D_800E68D0. */
s32 func_800C7870(u8 *arg0, u8 *arg1, f32 arg2) {
    if ((arg1[0x37] & 1) && ((*(u64 *)(arg0 + 0x20) & *(u64 *)(arg1 + 0x20)) & 0x40) &&
        ((f64)arg2 < D_800E68D0)) {
        return 1;
    }
    return 0;
}

/* XY-plane distance/heading between arg0 and arg1: stores dx, dy, the distance
 * and the heading into a 4-word result, copies to arg2 when given, returns the
 * distance. */
f32 func_800D39C4(void *arg0, void *arg1, void *arg2) {
    f32 *p0 = arg0, *p1 = arg1;
    NwFI v[4];
    f32 dx, dy, dist;

    dx = p1[0] - p0[0]; v[0].f = dx;
    dy = p1[1] - p0[1]; v[1].f = dy;
    dist = nw2Sqrtf(dx * dx + dy * dy); v[2].f = dist;
    v[3].i = (s32)((f64)func_80003A3C(dx, dy) * D_800E6BA8);
    if (arg2 != NULL) *(NwV4 *)arg2 = *(NwV4 *)v;
    return v[2].f;
}

/* Applies the entity's mode byte (+0x36F): mode 7 clears and mode 8 sets the
 * 0x200000 flag; returns 1 when the mode is >= 7. */
s32 func_800D4CC4(u8 *arg0) {
    switch (arg0[0x36F]) {
    case 7:
        *(u64 *)(arg0 + 0x20) &= ~0x200000;
        break;
    case 8:
        *(u64 *)(arg0 + 0x20) |= 0x200000;
        break;
    }
    return arg0[0x36F] >= 7;
}
