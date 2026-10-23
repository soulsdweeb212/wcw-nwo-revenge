#include "common.h"

extern u8 D_80062520;
extern s32 D_80062524;
extern s32 D_80062528;
extern s32 D_8006255C;
extern s32 D_80036F38;
void func_800171B4(void);

/* Decode a 7-bit or 14-bit value into arg0+0xCC (7-bit: one byte; 14-bit: two). */
u8 *func_800164FC(void *arg0, u8 *arg1) {
    s32 v = *arg1++;
    if ((u32)(v & 0xFF) < 0x80U) {
        *(s16 *)((u8 *)arg0 + 0xCC) = v;
    } else {
        s32 t = (v & 0x7F) << 8;
        *(s16 *)((u8 *)arg0 + 0xCC) = t;
        t += *arg1++;
        *(s16 *)((u8 *)arg0 + 0xCC) = t;
    }
    return arg1;
}

/* Lazily initialize the shared node list D_80062520 and hand back its head pointer
 * plus the update callback func_800171B4. */
void *func_800173C0(u8 **arg0) {
    u8 *p = &D_80062520;

    if (*p == 0) {
        D_80062524 = 0;
        *p = 1;
        D_80062528 = D_8006255C;
    }
    D_80036F38 = 0;
    *arg0 = p;
    return (void *)func_800171B4;
}
