#include "common.h"

extern s32 *D_80036F54;
s32 *func_80017F18(void);
s32 func_80018C24(s32 *, s32, s32 *);
s32 func_80018044(s32, s32);

/* Sends command 0xC with the byte payload arg1 to the node referenced by arg0[2]. */
void func_80017860(s32 *arg0, s32 arg1) {
    s32 *p;
    if (arg0[2] != 0) {
        p = func_80017F18();
        if (p != 0) {
            s32 g = D_80036F54[7];
            s32 off = *(s32 *)((u8 *)arg0[2] + 0x88);
            *(s16 *)((u8 *)p + 8) = 0xC;
            p[3] = arg1 & 0xFF;
            p[0] = 0;
            p[1] = g + off;
            func_80018C24((s32 *)arg0[2], 3, p);
        }
    }
}
