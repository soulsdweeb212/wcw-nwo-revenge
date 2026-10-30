/* @header
 * func_80017F5C
 * VRAM 0x80017F5C | ROM 0x18B5C | size 0x60
 * asm: asm/nonmatchings/main/func_80017F5C.s
 */
#include "common.h"

s32 func_8002021C(s32, void *);
s32 func_8002023C(s32);
extern void *D_80036F54;

/* Move every node chained at D_80036F54+0x14 onto the list head at D_80036F54+4. */
void func_80017F5C(void) {
    s32 node;

    node = *(s32 *)((s8 *)D_80036F54 + 0x14);
    if (node != 0) {
        do {
            func_8002023C(node);
            func_8002021C(node, (s8 *)D_80036F54 + 4);
            node = *(s32 *)((s8 *)D_80036F54 + 0x14);
        } while (node != 0);
    }
}
