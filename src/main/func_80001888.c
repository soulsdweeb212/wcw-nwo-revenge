/* @header
 * func_80001888
 * VRAM 0x80001888 | ROM 0x2488 | size 0x3C
 * asm: asm/nonmatchings/main/func_80001888.s
 */
#include "common.h"

void calculateObjectVertexCentroid(void *);

/* Walks the node's +0x14 child list and recomputes each child's vertex
 * centroid. */
#ifdef TARGET_PC
/* PC: the object's first work block and each block's next are handles (Nw2SceneObj and Nw2SceneWork in common.h keep
 * the N64 layout), which SLOT_TO_PTR turns back into the blocks' addresses. */
void func_80001888(void *arg0) {
    Nw2SceneWork *var_s0;

    for (var_s0 = SLOT_TO_PTR(((Nw2SceneObj *)arg0)->work); var_s0 != NULL; var_s0 = SLOT_TO_PTR(var_s0->next)) {
        calculateObjectVertexCentroid(var_s0);
    }
}
#else
void func_80001888(void *arg0) {
    void *var_s0;

    var_s0 = *(void **)((u8 *)arg0 + 0x14);
    if (var_s0 != NULL) {
        do {
            calculateObjectVertexCentroid(var_s0);
            var_s0 = *(void **)((u8 *)var_s0 + 8);
        } while (var_s0 != NULL);
    }
}
#endif
