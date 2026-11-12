/* @header
 * func_800BCBB4
 * VRAM 0x800BCBB4 | ROM 0x69324 | size 0x17C
 * asm: asm/nonmatchings/code_80090000/func_800BCBB4.s
 */
#include "common.h"

extern s32 D_800DF1CC, D_800E798C;
extern u8 D_8007E228[], D_8007E8C0[], D_8007EF30[];
#ifdef TARGET_PC
/* PC: the game functions this file calls, declared with their definitions' types (findOrAddCacheEntryRaw.c,
 * func_80099148.c, lookupPlayerNameById.c; port_decls.h declares func_8002AD34 and func_8002AD04, which return the
 * address of a name). D_8007EF30 keeps its N64 layout, so its +0x30, the address of the cup record, is 4 bytes and
 * holds a handle (port.h's PTR_TO_SLOT), as func_800AA1E0 reads it; CUP_U16 reads a u16 of the cup through it. */
s32 findOrAddCacheEntryRaw(s32 arg0, s16 arg1, s16 arg2, s32 arg3, s32 arg4);
s32 func_80099148(s32 arg0, s16 arg1, s16 arg2, s32 arg3, s32 arg4);
u8 *lookupPlayerNameById(u8 *arg0, u8 *arg1);
#define CUP_U16(o) (*(u16 *)((u8 *)SLOT_TO_PTR(*(u32 *)(D_8007EF30 + 0x30)) + (o)))
#endif

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
#ifdef TARGET_PC
        /* PC: the cup's ids through its handle, as above. */
        if (D_800E798C != 0) {
            findOrAddCacheEntryRaw(CUP_U16(0xC), 0xF0, 0x78, 0x18008, 0x402);
        } else {
            findOrAddCacheEntryRaw(CUP_U16(0xA), 0xF0, 0x78, 0x18008, 0x402);
        }
#else
        if (D_800E798C != 0) {
            findOrAddCacheEntryRaw(*(u16 *)(*(u8 **)(D_8007EF30 + 0x30) + 0xC), 0xF0, 0x78, 0x18008, 0x402);
        } else {
            findOrAddCacheEntryRaw(*(u16 *)(*(u8 **)(D_8007EF30 + 0x30) + 0xA), 0xF0, 0x78, 0x18008, 0x402);
        }
#endif
    }
    if (a >= 0x100) {
        if (a == 0x100) {
            D_800DF1CC = 0x410;
        }
        if (*(u16 *)(D_8007EF30 + 8) & 0x20) {
#ifdef TARGET_PC
            /* PC: func_8002AD34 returns the address of a name, which a pointer keeps whole. func_80099148 still takes
             * its key as an s32 (its definition), which cannot hold the name's address: the key's PC type is not
             * decided yet, so these calls do not compile on PC. */
            u8 *name = func_8002AD34(*(s32 *)(D_8007E228 + 0x688), *(s32 *)(D_8007E8C0 + 0x70));
            func_80099148(lookupPlayerNameById(name, func_8002AD34(*(s32 *)(D_8007E228 + 0x68C), *(s32 *)(D_8007E8C0 + 0x74))), 0xF0, 0xA0, 0x18008, 0x402);
#else
            a = func_8002AD34(*(s32 *)(D_8007E228 + 0x688), *(s32 *)(D_8007E8C0 + 0x70));
            func_80099148(lookupPlayerNameById(a, func_8002AD34(*(s32 *)(D_8007E228 + 0x68C), *(s32 *)(D_8007E8C0 + 0x74))), 0xF0, 0xA0, 0x18008, 0x402);
#endif
        } else {
            func_80099148(func_8002AD04(*(s32 *)(D_8007E228 + 0x688), *(s32 *)(D_8007E8C0 + 0x70)), 0xF0, 0xA0, 0x18008, 0x402);
        }
    }
}
