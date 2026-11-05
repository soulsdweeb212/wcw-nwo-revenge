/* @header
 * func_8009075C
 * VRAM 0x8009075C | ROM 0x83BFC | size 0x44
 * asm: asm/nonmatchings/ovl2_80090000/func_8009075C.s
 */
#include "common.h"

void func_80004F80(void *, s16, s16);

typedef struct {
    u8 pad0[0x18];
    s32 f18;
    s32 f1C;
} Node;

/* Rebuild the node with a temporary pair of values in 0x18/0x1C. */
void func_8009075C(Node *n, s32 *v) {
    n->f18 = v[0];
    n->f1C = v[1];
    func_80004F80(n, 0, 0);
    n->f18 = 0;
    n->f1C = 0;
}
