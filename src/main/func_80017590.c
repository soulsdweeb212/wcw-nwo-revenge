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

/* Push arg0 onto the list at D_80036F54, copying that list's +0x20 into arg0+0x10. */
void func_80017590(void *arg0) {
    s32 v = func_8001C740(1);
    void *p = D_80036F54;

    *(s32 *)((u8 *)arg0 + 0x10) = *(s32 *)((u8 *)p + 0x20);
    *(void **)arg0 = *(void **)p;
    *(void **)p = arg0;
    func_8001C740(v);
}
