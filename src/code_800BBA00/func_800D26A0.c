/* @header
 * func_800D26A0
 * VRAM 0x800D26A0 | ROM 0xC5B40 | size 0xB8
 * asm: asm/nonmatchings/code_800BBA00/func_800D26A0.s
 */
#include "common.h"

void translateEntityXZ(void *, void *);
s8 func_800D2758(Wrestler *, f32, u16, s8, s16);

/* Look for another wrestler close to w as if w stood moved by the XZ offset arg1 (none if arg1 is NULL): translate
 * w by the offset, run func_800D2758(w, 0, 0, ignoreId, mode 0), which only tests and does not push, then
 * translate w back. Returns func_800D2758's result: the first wrestler id found close, or -1. */
s8 func_800D26A0(Wrestler *w, Nw2DirectionResult *arg1, s8 ignoreId) {
    Nw2DirectionResult offset;
    s8 result;
    if (arg1 == NULL) {
        offset.x = 0.0f;
        offset.z = 0.0f;
    } else {
        offset = *arg1;
    }
    translateEntityXZ(w, &offset);
    result = func_800D2758(w, 0.0f, 0, ignoreId, 0);
    offset.x = -offset.x;
    offset.z = -offset.z;
    translateEntityXZ(w, &offset);
    return result;
}
