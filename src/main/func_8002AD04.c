/* @header
 * func_8002AD04
 * VRAM 0x8002AD04 | ROM 0x2B904 | size 0x30
 * asm: asm/nonmatchings/main/func_8002AD04.s
 */
#include "common.h"

typedef struct {
    u8 **items;
    u16 count;
    u16 pad;
} Tbl;

extern Tbl D_8003A4F8[];
extern u8 D_8003A59C[];

#ifndef TARGET_PC /* on PC, port_decls.h declares func_8002B5AC and func_8002B790 */
extern s32 func_8002B5AC(s32);
extern s32 func_8002B790(s32, s32);
#endif

/* Resolves the entry for id a and writes its variant-b record. */
#ifdef TARGET_PC
/* PC: the N64 definition is void, but it ends straight after its call of func_8002B790, so that call's result, the
 * address of the name record, is still in v0 when it returns, and the caller func_80097E34 uses it as the key of the
 * resource-name cache. On PC nothing carries a result that a function does not return, so the PC definition returns
 * that address, as a u8 * (port_decls.h declares it so). */
u8 *func_8002AD04(s32 a, s32 b) {
    return func_8002B790(func_8002B5AC(a), b);
}
#else
void func_8002AD04(s32 a, s32 b) {
    func_8002B790(func_8002B5AC(a), b);
}
#endif
