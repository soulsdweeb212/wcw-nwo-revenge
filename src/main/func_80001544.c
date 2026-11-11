/* @header
 * func_80001544
 * VRAM 0x80001544 | ROM 0x2144 | size 0x68
 * asm: asm/nonmatchings/main/func_80001544.s
 */
#include "common.h"

#ifndef TARGET_PC /* on PC, port_decls.h declares D_80046860 */
extern s32 D_80046860[];
#endif
extern s16 D_80047062;
extern u8 *D_80046858;
extern s16 D_80047060;

void guTranslateF(void *, s32, s32, f32);
void guMtxIdentF(void *);

/* Registers the transform node's +0x14 value in the D_80046860 table (no-op if
 * already present). */
#ifdef TARGET_PC
/* PC: the object's +0x14 holds a handle of its first work block (Nw2SceneObj in common.h keeps the N64 layout), and
 * the table holds the blocks' addresses as pointers (port_decls.h). So this version turns the handle back into the
 * block's address and compares and stores that. */
void func_80001544(void *arg0) {
    void *v = SLOT_TO_PTR(((Nw2SceneObj *)arg0)->work);
    u32 i;

    for (i = 0; i < D_80047062; i++) {
        if (D_80046860[i] == v) {
            return;
        }
    }
    D_80046860[D_80047062] = v;
    D_80047062++;
}
#else
void func_80001544(void *arg0) {
    s32 v = *(s32 *)((u8 *)arg0 + 0x14);
    u32 i;

    for (i = 0; i < D_80047062; i++) {
        if (D_80046860[i] == v) {
            return;
        }
    }
    D_80046860[D_80047062] = v;
    D_80047062++;
}
#endif
