#include "common.h"

s8 func_800B71F8(void *, s32, s32);

/* Paired-entity action gate: applies only when arg0's u64 flags (+0x20) have bit 0x80000,
 * or arg1's do not, and arg0's flags lack mask 9. Then, if arg2 has any of the bits 0xC030
 * and arg1's byte +0x36 does not already have bit 2, set that bit on arg1 and, when
 * func_800B71F8(arg0,0,0) succeeds, also set bit 3. */
void func_800CBD5C(void *arg0, void *arg1, s32 arg2) {
    u8 bits;
    if ((*(u64 *)((u8 *)arg0+0x20) & 0x80000) || !(*(u64 *)((u8 *)arg1+0x20) & 0x80000)) {
        if (!(*(u64 *)((u8 *)arg0+0x20) & 9)) {
            bits = *(u8 *)((u8 *)arg1+0x36);
            if (!(bits & 4) && (arg2 & 0xC030)) {
                *(u8 *)((u8 *)arg1+0x36) = bits|4;
                if (func_800B71F8(arg0,0,0)) *(u8 *)((u8 *)arg1+0x36) |= 8;
            }
        }
    }
}
