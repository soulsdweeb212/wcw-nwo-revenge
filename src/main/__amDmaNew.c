/* @header
 * __amDmaNew  (originally func_800173C0)
 * VRAM 0x800173C0 | ROM 0x17FC0 | size 0x48
 * asm: asm/nonmatchings/main/__amDmaNew.s
 */
/* SDK: the SDK demo audio manager (n64-demos simple/src/main/audiomgr.c) as adapted in this old libmus (SDK code
 * with changes, see docs/sdk_functions.md). */
#include "common.h"

extern u8 D_80062520;
extern s32 D_80062524;
extern s32 D_80062528;
extern s32 D_8006255C;
extern s32 D_80036F38;
void __amDMA(void);

/* Lazily initialize the shared node list D_80062520 and hand back its head pointer
 * plus the update callback __amDMA. */
void *__amDmaNew(u8 **arg0) {
    u8 *p = &D_80062520;

    if (*p == 0) {
        D_80062524 = 0;
        *p = 1;
        D_80062528 = D_8006255C;
    }
    D_80036F38 = 0;
    *arg0 = p;
    return (void *)__amDMA;
}
