#include "common.h"

s8 func_800D7B54(void *, s32, s32, s32);
void func_800C4610(u8 *, u8 *);
void playEntitySound(s8, s32);
void func_800A6C48(void *, s32);

/* Attempts to start a grab: reorients arg1 toward arg0, bails if they are
 * already the same entity, then (when arg0 is flagged 0x8000000) requires a
 * clear proximity check before playing the grab sound and starting action 0x5C.
 * Otherwise, unless arg0 is in state 0x40 with a low counter, it also needs the
 * proximity check; entities already flagged 9 cannot be grabbed. On success it
 * cross-links the two ids, starts action 0x40 and sets state 3. Returns 1 when
 * a grab started. */
s32 tryBeginEntityGrab(u8 *arg0, u8 *arg1) {
    func_800C4610(arg1, arg0);
    if (*(s8 *)(arg1 + 0x355) == *(s8 *)(arg0 + 0)) {
        return 0;
    }
    if (*(u64 *)(arg0 + 0x20) & 0x8000000LL) {
        if (!func_800D7B54(arg0, 0, 0, 2)) {
            return 0;
        }
        playEntitySound(*(s8 *)(arg0 + 0), 0x12C);
        func_800A6C48(arg0, 0x5C);
        return 1;
    }
    if (!(*(s16 *)(arg0 + 0xA) == 0x40 && *(s16 *)(arg0 + 0x16) < 3)) {
        if (!func_800D7B54(arg0, 0, 0, 2)) {
            return 0;
        }
    }
    if (*(u64 *)(arg0 + 0x20) & 9) {
        return 0;
    }
    playEntitySound(*(s8 *)(arg0 + 0), 0x12C);
    *(u8 *)(arg0 + 0x353) = *(u8 *)(arg1 + 0);
    *(u8 *)(arg1 + 0x351) = *(u8 *)(arg0 + 0);
    *(u8 *)(arg1 + 0x353) = *(u8 *)(arg0 + 0);
    func_800A6C48(arg0, 0x40);
    *(s16 *)(arg0 + 0xC) = 3;
    return 1;
}
