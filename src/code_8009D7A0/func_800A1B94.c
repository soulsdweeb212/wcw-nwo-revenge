/* @header
 * func_800A1B94
 * VRAM 0x800A1B94 | ROM 0x95034 | size 0x1A0
 * asm: asm/nonmatchings/code_8009D7A0/func_800A1B94.s
 */
#include "common.h"

#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D2B64 */
s32 func_800D2B64(void *, f32, u16, s32);
#endif
void func_800D427C(void *, s32, s32);
void func_800D4AD0(void *);
void beginEntityActionA8D8C(void *);
void func_8000C784(s8);
extern s8 D_800FADB8;
extern s16 D_800E3262[];

/* State machine (state D_800EB408->step) that picks an animation action for the entity
 * at D_800EB408 based on its flags (u64 +0x20) and byte at +0x35. */
void func_800A1B94(void) {
    s16 id;
    u8 b;

    func_800D2B64(D_800EB408, 2.0f, 0, 0xFFFFE);
    switch (D_800EB408->step) {
    case 0:
        D_800EB408->flags |= 0x1400000000ULL;
        func_8000C784(D_800FADB8);
        b = D_800EB408->koFlags;
        if (b & 4) {
            func_800D427C(D_800EB408, 0x105D, 3);
            D_800EB408->step = 2;
        } else if (b & 8) {
            func_800D427C(D_800EB408, D_800E3262[(s8)D_800EB408->pose], 1);
            D_800EB408->step++;
        } else {
            if (D_800EB408->flags & 0x8000000) {
                id = 0x105D;
            } else {
                id = 0x105C;
            }
            func_800D427C(D_800EB408, id, 3);
            D_800EB408->step = 2;
        }
        break;
    case 1:
        if (D_800EB408->flags & 0x200000) {
            id = 0x1062;
        } else {
            id = 0x1061;
        }
        func_800D427C(D_800EB408, id, 6);
        D_800EB408->step++;
        break;
    case 2:
        if (D_800EB408->animFramesLeft <= 0) {
            func_800D4AD0(D_800EB408);
            beginEntityActionA8D8C(D_800EB408);
        }
        break;
    }
}
