/* @header
 * func_80020800
 * VRAM 0x80020800 | ROM 0x21400 | size 0x54
 * asm: asm/nonmatchings/main/func_80020800.s
 */
#include "common.h"

extern u8 D_80037520;

s32 func_8001CE80(s32);
s32 ai_is_busy(void);
s32 func_8002021C(s32, void *);
s32 func_8002023C(s32);

/* Move every child node at arg0+0x14 onto the list head arg0+4. */
void func_80020800(u8 *arg0) {
    s32 node;

    node = *(s32 *)(arg0 + 0x14);
    if (node != 0) {
        do {
            func_8002023C(node);
            func_8002021C(node, arg0 + 4);
            node = *(s32 *)(arg0 + 0x14);
        } while (node != 0);
    }
}
