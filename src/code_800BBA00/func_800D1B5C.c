/* @header
 * func_800D1B5C
 * VRAM 0x800D1B5C | ROM 0xC4FFC | size 0x34C
 * asm: asm/nonmatchings/code_800BBA00/func_800D1B5C.s
 */
#include "common.h"

extern s32 D_800E3C90[];
extern s32 D_800E3CB0[];
extern u8 D_800F9D12[];
extern u8 D_800F9D1A[];
extern u8 D_800F9D30[];
extern u8 D_800F9D34[];
extern u8 D_800F9D38[];
extern u8 D_800F9D4E[];
s32 func_800D3550(s32);
s32 func_800D35B0(s32, s32);
s32 func_800D3684(s32, s32);
void *func_800D6610(void *, s16);
s16 getRingBoundaryPointAlongHeading(void *, s32, void *);

s32 func_800D1B5C(u8 *arg0, s8 *arg1) {
    s16 i;
    s32 mask;
    s32 best;
    s16 bestIdx;
    s32 t;

    if (*(u32 *)(arg0 + 0x3AC) & 0x1000) {
        s8 *other = arg1;
        mask = 0;
        for (i = 0; i < 4; i++) {
            s32 off;
            s16 a1;
            if (i == (s8)arg0[0] || i == other[0]) {
                continue;
            }
            off = i * 0x3B0;
            if (*(s16 *)(D_800F9D12 + off) == -1) {
                continue;
            }
            a1 = *(s16 *)(D_800F9D1A + off);
            if (a1 == 0x14) {
                mask |= 1 << *(s16 *)(D_800F9D4E + off);
            }
            if (!(*(u64 *)(D_800F9D30 + off) & 0x40ULL)) {
                continue;
            }
            if (a1 == 0xC && (*(u16 *)(D_800F9D38 + off) & 8)) {
                mask |= 1 << *(s16 *)(D_800F9D4E + off);
            }
            off = i * 0x3B0;
            if (!(*(u64 *)(D_800F9D30 + off) & 0x100000ULL)) {
                continue;
            }
            if (*(u16 *)(D_800F9D38 + off) & 0x20) {
                if (*(u16 *)(D_800F9D38 + off) & 8) {
                    mask |= 1 << *(s16 *)(D_800F9D4E + off);
                }
            }
        }
        best = 0x800;
        for (i = 0; i < 4; i++) {
            t = func_800D3684(D_800E3CB0[i], *(s32 *)(arg0 + 0x58));
            t = func_800D3550(t);
            if (best >= t) {
                best = t;
                bestIdx = i;
            }
        }
        if (*(u32 *)(arg0 + 0x3AC) & 0x20000) {
            bestIdx = (bestIdx + 2) & 3;
        }
        if (((mask & 0xFF) >> bestIdx) & 1) {
            bestIdx = (bestIdx + 1) & 3;
            if (((mask & 0xFF) >> bestIdx) & 1) {
                bestIdx = (bestIdx - 2) & 3;
                if (((mask & 0xFF) >> bestIdx) & 1) {
                    bestIdx = (bestIdx - 1) & 3;
                }
            }
        }
        *(s16 *)(arg0 + 0x3E) = bestIdx;
        *(s16 *)(other + 0x3E) = bestIdx;
        t = (s32)func_800D6610(arg0, bestIdx);
        if (*(u32 *)(arg0 + 0x3AC) & 0x20000) {
            t = func_800D35B0(t, 0x800);
        }
        return t;
    }
    {
        s32 sp10[4];
        bestIdx = getRingBoundaryPointAlongHeading(arg0 + 0x4C, *(s32 *)(arg0 + 0x58), sp10);
    }
    if (*(u32 *)(arg0 + 0x3AC) & 0x20000) {
        *(s16 *)(arg0 + 0x3E) = (bestIdx + 2) & 3;
    } else {
        *(s16 *)(arg0 + 0x3E) = bestIdx;
    }
    return D_800E3C90[bestIdx];
}
