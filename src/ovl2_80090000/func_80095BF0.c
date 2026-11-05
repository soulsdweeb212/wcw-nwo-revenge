/* @header
 * func_80095BF0
 * VRAM 0x80095BF0 | ROM 0x89090 | size 0xC0
 * asm: asm/nonmatchings/ovl2_80090000/func_80095BF0.s
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

extern ObjDC D_800E9878[];
extern ObjDC D_800E9D70[];
extern ObjDC D_800EA268[];
extern ObjDC D_800EA758[];
extern ObjDC D_800EAC88[];
extern u8 D_800E9D38[];
extern u16 D_800EB0AA;

void func_80095BF0(void) {
    u32 i;

    for (i = 0; i < D_800EB0AA; i++) {
        D_800EA268[i].node->flags |= 0x80;
        D_800E9D70[i].node->flags |= 0x80;
        D_800EAC88[i].node->flags |= 0x80;
        D_800EA758[i].node->flags |= 0x80;
        D_800E9878[i].node->flags |= 0x80;
        D_800E9D38[i] = 0;
    }
}
