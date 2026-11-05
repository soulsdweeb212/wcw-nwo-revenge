/* @header
 * func_80096018
 * VRAM 0x80096018 | ROM 0x894B8 | size 0x74
 * asm: asm/nonmatchings/ovl2_80090000/func_80096018.s
 */
#include "common.h"

typedef struct {
    s32 flags;
} Node;

typedef struct {
    u8 pad0[0x14];
    Node *node;
    u8 pad18[0xC4];
} ObjDC;

extern ObjDC D_800E7DF8;
extern ObjDC D_800E7ED8;
extern s16 D_800E80C4;
extern s8 D_800F99B4;
void func_80097BB4(void);

void func_80096018(void) {
    s32 f = D_800E7DF8.node->flags;

    if (!(f & 0x80) && D_800E80C4 < 3) {
        D_800E7DF8.node->flags = f | 0x80;
        D_800E7ED8.node->flags |= 0x80;
    }
    if (D_800F99B4 == 1) {
        func_80097BB4();
    }
}
