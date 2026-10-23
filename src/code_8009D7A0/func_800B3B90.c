#include "common.h"

/* Choose a facing/move direction for the active move (written to the action
 * record's +6). Depends on the global state at D_800FAF58 (mode byte at +0):
 * mode 2 uses the distance thresholds D_800E5438/D_800E5440 on the state's
 * X/Z (+0x6C/+0x74) and the move subtype at +0x1E; other modes use
 * D_800E5448/D_800E5450 and the move variant at +0x1C. Some branches reset
 * the action record (clearing +2/+4, copying D_800F9B60+0xA to +0x2E, and
 * clearing flags +0x5C bits 0..2). */
extern u8 *D_800FABD0;
extern u8 *D_800F9B60;
extern u8 *D_800FAF58;
extern f64 D_800E5438;
extern f64 D_800E5440;
extern f64 D_800E5448;
extern f64 D_800E5450;

void func_800B3B90(u8 *o, u8 *g, s16 dir) {
    o = D_800FAF58;

    if (*(s8 *)o == 2) {
        g = D_800FABD0;

        switch (*(s16 *)(g + 0x1E)) {
        case 0:
            dir = 0x200;
            if ((f64)*(f32 *)(o + 0x6C) < D_800E5438) {
                dir = 0x400;
            }
            break;
        case 1:
            dir = 0x400;
            if ((f64)*(f32 *)(o + 0x74) < D_800E5440) {
                dir = 0x200;
            }
            break;
        case 2:
            dir = 0x200;
            if (*(s16 *)(g + 0x1C) != 2) {
                goto store;
            }
            goto reset;
        case 3:
            dir = 0x400;
            if (*(s16 *)(g + 0x1C) != 2) {
                goto store;
            }
            goto reset;
        }
        goto store;
    } else {
        g = D_800FABD0;

        switch (*(s16 *)(g + 0x1E)) {
        case 0:
            dir = 0x100;
            if (*(s16 *)(g + 0x1C) != 0) {
                goto store;
            }
            goto reset;
        case 1:
            dir = 0x800;
            if (*(s16 *)(g + 0x1C) != 0) {
                goto store;
            }
        reset: {
            u8 *s = D_800F9B60;
            *(s16 *)(g + 2) = 0;
            *(s16 *)(g + 4) = 0;
            *(u16 *)(g + 0x2E) = *(u16 *)(s + 0xA);
            *(u32 *)(g + 0x5C) &= ~7;
            break;
        }
        case 2:
            dir = 0x100;
            if (D_800E5448 < (f64)*(f32 *)(o + 0x6C)) {
                dir = 0x800;
            }
            goto store;
        case 3:
            dir = 0x800;
            if (D_800E5450 < (f64)*(f32 *)(o + 0x74)) {
                dir = 0x100;
            }
            goto store;
        }
    }
store:
    *(s16 *)(D_800FABD0 + 6) = dir;
}
