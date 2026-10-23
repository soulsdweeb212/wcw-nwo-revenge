#include "common.h"

/* Quadrant from the signs of the X (+0x6C) and Z (+0x74) components: 1 or 0 when
 * X>0 (Z<=0 / Z>0), 2 or 3 when X<=0 (Z<=0 / Z>0). */
s32 func_800ADAE4(void *entity) {
    s32 q;

    if (*(f32 *)((s8 *)entity + 0x6C) > 0.0f) {
        q = 1;
        if (*(f32 *)((s8 *)entity + 0x74) > 0.0f) {
            return 0;
        }
        return q;
    }
    q = 2;
    if (*(f32 *)((s8 *)entity + 0x74) > 0.0f) {
        q = 3;
    }
    return q;
}
