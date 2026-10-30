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

extern s32 func_8002B5AC(s32);
extern s32 func_8002B790(s32, s32);

/* Resolve record a to variant b and bias the result by 0x19. */
s32 func_8002AD34(s32 a, s32 b) {
    return func_8002B790(func_8002B5AC(a), b) + 0x19;
}
