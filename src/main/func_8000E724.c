#include "common.h"

/*
 * Service effect/particle timers.  arg0 != 0 selects an effect (and stores it
 * as the current selection); arg0 == 0 walks every 4-byte effect slot, ticking
 * the countdown byte at +3 down.  When a countdown expires the slot's active
 * bit (0x80 of the value at +0) is toggled, the matching start/stop helper is
 * called and the countdown is reloaded from the constant table at
 * D_80075459/D_8007545A.
 */
s32 func_8000327C(s32);
void func_8000439C(s16);
void func_800043CC(s16);
void func_8000440C(s16);
extern s32 D_80036738;
extern s16 D_800507F0;
extern s32 D_80056948;
extern u8 D_80075458, D_80075459, D_8007545A;
void func_8000E724(s16 arg0) {
    u8 *entry, *slot, *tableEnd;
    s8 *entryTimer;
    s32 reloadIdx;
    s32 index;
    s32 n;
    s32 *dst;
    if (arg0) {
        if (D_800507F0 != arg0) func_8000440C(1);
    } else {
        slot = &D_80075458;
        index = 0;
        entryTimer = (s8 *)&D_80075458 + 3;
        entry = &D_80075458;
        reloadIdx = 0;
        do { tableEnd = entry + 0x13; } while (0);
    loop:
        {
            u8 value = *entry;
            u8 count = value & 0x7f;
            if (count) {
                s8 ticks = *entryTimer;
                if (ticks <= 0) {
                    if (value & 0x80) {
                        *entry = count;
                        *entryTimer = *(&D_8007545A + reloadIdx);
                        func_800043CC(index >> 16);
                        slot[0] = *entry - 1;
                    } else {
                        *entry = value | 0x80;
                        *entryTimer = *(&D_80075459 + reloadIdx);
                        func_8000439C(index >> 16);
                    }
                } else {
                    slot[3] = ticks - 1;
                }
            }
        }
        slot += 4;
        index += 0x10000;
        entryTimer += 4;
        entry += 4;
        reloadIdx += 4;
        if ((u32)entryTimer < (u32)tableEnd) goto loop;
        if (!D_80036738) {
            D_80036738 = func_8000327C(0x34);
            n = 0x96;
            dst = &D_80056948;
            do { *dst = 0; n--; dst--; } while (n >= 0);
        }
    }
    D_800507F0 = arg0;
}
