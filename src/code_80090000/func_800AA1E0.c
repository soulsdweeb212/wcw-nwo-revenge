/* @header
 * func_800AA1E0
 * VRAM 0x800AA1E0 | ROM 0x56950 | size 0x1AC
 * asm: asm/nonmatchings/code_80090000/func_800AA1E0.s
 */
#include "common.h"

extern u8 D_8007EF30[];
extern s32 D_800E74D8, D_800E6B7C;
extern s32 D_800E8200[];
extern u32 D_800EA2D0[];
#ifdef TARGET_PC
/* PC: the game functions this file calls, declared with their definitions' types (func_800B04BC.c,
 * findIdSubTableIndex.c, func_80099148.c). D_8007EF30 keeps its N64 layout (game files read it at N64 offsets, up to
 * +0xC90), so its +0x30, the address of the cup record that func_800B0DD4 stores, is 4 bytes and holds a handle
 * (port.h's PTR_TO_SLOT); CUP_ID reads the cup's id (its first byte) through it. */
s32 func_800B04BC(s32 id);
s32 findIdSubTableIndex(s32 id);
s32 func_80099148(s32 arg0, s16 arg1, s16 arg2, s32 arg3, s32 arg4);
#define CUP_ID() (*(u8 *)SLOT_TO_PTR(*(u32 *)(D_8007EF30 + 0x30)))
#endif

s32 func_800AA1E0(s32 a, s32 b, u32 c, s32 d) {
    u32 r;
    s32 x;

    if (a < 0) {
        if (c & 0x80) {
            if (func_800B04BC(b) != 0) {
#ifdef TARGET_PC
                /* PC: the cup's id through its handle, as above. */
                r = c | (CUP_ID() * 16 + 4);
#else
                r = c | (**(u8 **)(D_8007EF30 + 0x30) * 16 + 4);
#endif
            } else {
                r = c & 0x7F;
            }
        } else {
            r = c;
        }
        if (r & 4) {
            c = (r >> 4) & 7;
            if ((c == 3 && findIdSubTableIndex(b) == 0) || c == 4) {
                r += 0x10;
            }
        }
        return r;
    }
    if (d >= 6) {
        if (D_800E74D8 != -1) {
            if (D_800E74D8 == -2 && a == D_800E6B7C) {
                { s32 q = func_8002B5AC(b); s32 m = ((c & 3) << 16) | 0x5100; func_80099148(q | m, 0x15C, 0xA6, 0, 0); }
            }
            if (c & 0x80) {
                if (func_800B04BC(b) != 0) {
#ifdef TARGET_PC
                    /* PC: the cup's id through its handle, as above. */
                    r = c | (CUP_ID() * 16 + 4);
#else
                    r = c | (**(u8 **)(D_8007EF30 + 0x30) * 16 + 4);
#endif
                } else {
                    r = c & 0x7F;
                }
            } else {
                r = c;
            }
            if (r & 4) {
                c = (r >> 4) & 7;
                if ((c == 3 && findIdSubTableIndex(b) == 0) || c == 4) {
                    r += 0x10;
                }
            }
            d = 6;
            D_800E8200[a] = b;
            D_800EA2D0[a] = r;
        }
    }
    return d;
}
