/* @header
 * func_800BCBB4
 * VRAM 0x800BCBB4 | ROM 0x69324 | size 0x17C
 * asm: asm/nonmatchings/code_80090000/func_800BCBB4.s
 */
#include "common.h"

extern s32 D_800DF1CC, D_800E798C;
extern u8 D_8007E228[], D_8007E8C0[], D_8007EF30[];

void func_800BCBB4(s32 a) {
    if (a >= 0) {
        if (a == 0) {
            D_800DF1CC = 0x410;
        }
        if (D_800E798C != 0) {
            findOrAddCacheEntryRaw(0x107, 0xF0, 0x50, 0x18008, 0x402);
        } else {
            findOrAddCacheEntryRaw(0x101, 0xF0, 0x50, 0x18008, 0x402);
        }
    }
    if (a >= 0x80) {
        if (a == 0x80) {
            D_800DF1CC = 0x410;
        }
        if (D_800E798C != 0) {
            findOrAddCacheEntryRaw(*(u16 *)(*(u8 **)(D_8007EF30 + 0x30) + 0xC), 0xF0, 0x78, 0x18008, 0x402);
        } else {
            findOrAddCacheEntryRaw(*(u16 *)(*(u8 **)(D_8007EF30 + 0x30) + 0xA), 0xF0, 0x78, 0x18008, 0x402);
        }
    }
    if (a >= 0x100) {
        if (a == 0x100) {
            D_800DF1CC = 0x410;
        }
        if (*(u16 *)(D_8007EF30 + 8) & 0x20) {
            a = func_8002AD34(*(s32 *)(D_8007E228 + 0x688), *(s32 *)(D_8007E8C0 + 0x70));
            func_80099148(lookupPlayerNameById(a, func_8002AD34(*(s32 *)(D_8007E228 + 0x68C), *(s32 *)(D_8007E8C0 + 0x74))), 0xF0, 0xA0, 0x18008, 0x402);
        } else {
            func_80099148(func_8002AD04(*(s32 *)(D_8007E228 + 0x688), *(s32 *)(D_8007E8C0 + 0x70)), 0xF0, 0xA0, 0x18008, 0x402);
        }
    }
}
