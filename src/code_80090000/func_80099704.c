/* @header
 * func_80099704
 * VRAM 0x80099704 | ROM 0x45E74 | size 0x30
 * asm: asm/nonmatchings/code_80090000/func_80099704.s
 */
#include "common.h"

/* identical to func_8002AD04 (matched), with its names changed by decompdecomp */
typedef struct {
    u8 **items;
    u16 count;
    u16 pad;
} Tbl;

extern Tbl D_8003A4F8[];
extern u8 D_8003A59C[];

extern s32 func_80099734(s32);
extern s32 func_800B600C(s32, s32);

/* Resolves the entry for id a and writes its variant-b record. */
void func_80099704(s32 a, s32 b) {
    func_800B600C(func_80099734(a), b);
}
