/* @header
 * func_80097E34
 * VRAM 0x80097E34 | ROM 0x8B2D4 | size 0xC0
 * asm: asm/nonmatchings/ovl2_80090000/func_80097E34.s
 */
#include "common.h"

extern s16 D_800EB19C;
extern void *D_800EB1A4;
extern s16 D_800EB1A8;
extern s16 D_800EB1AA;

s16 func_8000B3C4(s32);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_8002AD04 and func_8002A2FC */
s32 func_8002AD04(s32, s32);
void *func_8002A2FC(u32 key, u16 flags);
#endif
void func_8002A5F4(void *entry);

void func_80097E34(s16 id, s16 var) {
    if (D_800EB1A8 != id) {
        D_800EB19C = -1;
        D_800EB1AA = 0;
        if (D_800EB1A4 != NULL) {
            D_800EB1A8 = 4;
            func_8002A5F4(D_800EB1A4);
            D_800EB1A4 = NULL;
        } else {
            D_800EB1A8 = id;
#ifdef TARGET_PC
            /* PC: the key is the name record's address that func_8002AD04 returns, whole (port.h's RES_KEY_NAME); a
             * 32-bit key would cut it in half. */
            D_800EB1A4 = func_8002A2FC(RES_KEY_NAME(func_8002AD04(func_8000B3C4(id), var)), 0x8008);
#else
            D_800EB1A4 = func_8002A2FC(func_8002AD04(func_8000B3C4(id), var), 0x8008);
#endif
        }
    } else if (D_800EB1A8 >= 0) {
        D_800EB1AA = 1;
    }
}
