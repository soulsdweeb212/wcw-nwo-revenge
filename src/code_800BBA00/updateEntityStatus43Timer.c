/* @header
 * updateEntityStatus43Timer  (originally func_800C49B4)
 * VRAM 0x800C49B4 | ROM 0xB7E54 | size 0x78
 * asm: asm/nonmatchings/code_800BBA00/updateEntityStatus43Timer.s
 */
#include "common.h"

extern u8 D_8007EF30[];
extern u8 D_800FABE8[], D_800FABEC[], D_800FABEE[];
extern s16 D_800EB4D0[];
void func_800D2638(void *, u16, f32);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D2B64 */
s32 func_800D2B64(void *, f32, u16, s32);
#endif

/* Per-wrestler timer D_800EB4D0[id] for comboHits: mode 0 (called when a hit adds to comboHits) reloads it to 60;
 * mode 1 counts it down and, once it has reached zero, clears w->comboHits. */
void updateEntityStatus43Timer(Wrestler *w, s16 mode) {
    s16 *timer;
    s16 value;
    switch (mode) {
    case 0:
        D_800EB4D0[w->id] = 60;
        return;
    case 1:
        timer = &D_800EB4D0[w->id];
        value = *timer;
        if (value <= 0) {
            w->comboHits = 0;
            return;
        }
        *timer = value - 1;
        return;
    }
}
