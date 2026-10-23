#include "common.h"

extern u8 *D_800FABD0, *D_800FAF58, *D_800F9B60;   /* action record, actor, target */
extern f64 D_800E5248;
#define A(o,t) (*(t *)(D_800FABD0+(o)))

/* Action-record phase machine. Phase 0 primes f6 and advances. Phase 1 waits
 * for the actor's sub-state: 3 advances only once f34 is below the threshold,
 * 4 advances directly, anything else resets. Phase 2 arms f8 for sub-states 3/4
 * and otherwise resets the record's transient fields from the target. */
void func_800B0B74(void) {
    switch (A(4, s16)) {
    case 0:
        A(6, s16) = 4;
        A(4, s16)++;
        break;
    case 1:
        switch (*(s16 *)(D_800FAF58 + 0xA)) {
        case 3:
            if ((f64)A(0x34, f32) < D_800E5248) {
                A(8, s16) = 0xF00;
                A(4, s16)++;
            }
            break;
        case 4:
            A(4, s16)++;
            break;
        default:
            goto reset;
        }
        break;
    case 2:
        switch (*(s16 *)(D_800FAF58 + 0xA)) {
        case 3:
        case 4:
            A(8, s16) = 0xF00;
            break;
        default: {
            u8 *target;
        reset:
            target = D_800F9B60;
            A(2, s16) = 0;
            A(4, s16) = 0;
            A(0x2E, u16) = *(u16 *)(target + 0xA);
            A(0x5C, u32) &= ~7;
        }
        break;
        }
        break;
    }
}
#undef A
