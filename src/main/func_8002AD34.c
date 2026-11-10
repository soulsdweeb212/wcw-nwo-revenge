/* @header
 * func_8002AD34
 * VRAM 0x8002AD34 | ROM 0x2B934 | size 0x34
 * asm: asm/nonmatchings/main/func_8002AD34.s
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

/* Resolve record a to variant b and bias the result by 0x19. */
#ifdef TARGET_PC
/* PC: the result is an address, 0x19 bytes into the name record that func_8002B790 returns, and the caller,
 * func_80097EF4, reads it as a u8 *. The N64 definition returns it as an s32, which on PC would cut the address in
 * half, so the PC definition returns a u8 * (port_decls.h declares it so). */
u8 *func_8002AD34(s32 a, s32 b) {
#else
s32 func_8002AD34(s32 a, s32 b) {
#endif
    return func_8002B790(func_8002B5AC(a), b) + 0x19;
}
