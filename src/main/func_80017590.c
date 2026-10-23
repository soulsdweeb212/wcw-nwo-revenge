#include "common.h"

extern u8 D_80062520;
extern s32 D_80062524;
extern s32 D_80062528;
extern s32 D_8006255C;
extern s32 D_80036F38;
extern f64 D_8003B3E8;
extern void *D_80036F54;
void func_800171B4(void);
s32 func_8001C740(s32);

/* Decode a 7-bit or 14-bit value into arg0+0xCC (7-bit: one byte; 14-bit: two). */
u8 *func_800164FC(void *arg0, u8 *arg1) {
    u32 v = *arg1++;
    if (v < 0x80) {
        *(u16 *)((u8 *)arg0 + 0xCC) = v;
    } else {
        u32 t = (v & 0x7F) << 8;
        *(u16 *)((u8 *)arg0 + 0xCC) = t;
        t += *arg1++;
        *(u16 *)((u8 *)arg0 + 0xCC) = t;
    }
    return arg1;
}

/* Decode a signed delta into the float at arg0+0xAC and advance the float at
 * arg0+0x44 by it. */
u8 *func_8001656C(void *arg0, u8 *arg1) {
    s32 v = *arg1++;
    f32 f, d;

    if (v & 0x80) {
        v |= 0xFFFFFF00;
    }
    f = (f32)v / D_8003B3E8;
    d = *(f32 *)((u8 *)arg0 + 0x44) - *(f32 *)((u8 *)arg0 + 0xAC);
    d += f;
    *(f32 *)((u8 *)arg0 + 0xAC) = f;
    *(f32 *)((u8 *)arg0 + 0x44) = d;
    return arg1;
}

/* Lazily initialize the shared node list D_80062520 and hand back its head pointer
 * plus the update callback func_800171B4. */
void *func_800173C0(void **arg0) {
    if (D_80062520 == 0) {
        D_80062524 = 0;
        D_80062520 = 1;
        D_80062528 = D_8006255C;
    }
    D_80036F38 = 0;
    *arg0 = &D_80062520;
    return (void *)func_800171B4;
}

/* Push arg0 onto the list at D_80036F54, copying that list's +0x20 into arg0+0x10. */
void func_80017590(void *arg0) {
    s32 v = func_8001C740(1);
    void *p = D_80036F54;

    *(s32 *)((u8 *)arg0 + 0x10) = *(s32 *)((u8 *)p + 0x20);
    *(void **)arg0 = *(void **)p;
    *(void **)p = arg0;
    func_8001C740(v);
}
