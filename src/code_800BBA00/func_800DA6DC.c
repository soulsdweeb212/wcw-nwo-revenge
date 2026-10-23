#include "common.h"

s8 func_800D8DF0(void *);
s8 func_800D96A0(void *);

/* Return 1 when the entity is in a state that blocks normal processing:
 * either its +0x20 flag bit 0x200 is set, or its +0x358 flags have any of the
 * high-word bits 0x6000, or one of the sub-handlers func_800D8DF0 /
 * func_800D96A0 reports active. Returns 0 otherwise. */
s32 func_800DA6DC(s32 entity) {
    if (*(u64 *)(entity + 0x20) & 0x200) {
        goto ret1;
    }
    if (*(u64 *)(entity + 0x358) & ((u64)0x6000 << 32)) {
        goto ret1;
    }
    if (func_800D8DF0((void *)entity)) {
        goto ret1;
    }
    if (func_800D96A0((void *)entity)) {
        goto ret1;
    }
    return 0;
ret1:
    return 1;
}
