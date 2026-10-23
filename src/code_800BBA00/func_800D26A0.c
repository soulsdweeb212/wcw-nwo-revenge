#include "common.h"

void translateEntityXZ(void *, void *);
s8 func_800D2758(void *, void *, void *, s8, s32);

/* Translate the entity by an offset (zero if arg1 is 0), run func_800D2758,
 * then translate it back. Returns func_800D2758's result. */
s8 func_800D26A0(void *arg0, s32 arg1, s8 arg2) {
    Nw2DirectionResult offset;
    s8 result;
    if (arg1 == 0) {
        offset.x = 0.0f;
        offset.z = 0.0f;
    } else {
        offset = *(Nw2DirectionResult *)arg1;
    }
    translateEntityXZ(arg0, &offset);
    result = func_800D2758(arg0, NULL, NULL, arg2, 0);
    offset.x = -offset.x;
    offset.z = -offset.z;
    translateEntityXZ(arg0, &offset);
    return result;
}
