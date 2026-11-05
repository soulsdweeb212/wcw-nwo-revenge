/* @header
 * func_800B4EFC
 * VRAM 0x800B4EFC | ROM 0x6166C | size 0x1D0
 * asm: asm/nonmatchings/code_80090000/func_800B4EFC.s
 */
#include "common.h"

extern u8 D_8007EF30[], D_8007E8C0[];
extern u8 D_800E9958[];
extern u16 D_800E9962;
extern s32 D_800E73A4, D_800E73A8, D_800E73AC, D_800E74D4, D_800EA348;
u8 *func_8002AD04(s32, s32);
u8 *func_8002AD34(s32, s32);
void func_8002BB98(s32, s32, void *);
void func_800BA1A4(s32, s32);
void bcopy(void *, void *, s32);
#define F(t, o, i) (*(t *)(D_8007EF30 + (o) + ((i) << 4)))

s32 func_800B4EFC(void) {
    u8 buf[0x30];
    u8 *d;
    u8 *s = D_800E9958;
    s32 r = 0;
    s32 i;
    u8 c;
    u8 *q;

    q = func_8002AD04(F(s16, 0x4E, D_800E9962), F(u8, 0x50, D_800E9962));
    for (i = 0; i < 0x18; i++) {
        c = D_8007E8C0[0xB8 + i];
        if (c == 0 && q[i] == 0) {
            break;
        }
        if (c != q[i]) {
            r = 1;
            break;
        }
    }
    q = func_8002AD34(F(s16, 0x4E, *(u16 *)(s + 0xA)), F(u8, 0x50, *(u16 *)(s + 0xA)));
    for (i = 0; i < 0xA; i++) {
        c = D_8007E8C0[0xDA + i];
        if (c == 0 && q[i] == 0) {
            break;
        }
        if (c != q[i]) {
            r = 1;
            break;
        }
    }
    d = D_8007E8C0 + 0xB8;
    bcopy(d, buf, 0x18);
    bcopy(d + 0x22, buf + 0x19, 0xA);
    buf[0x18] = 0;
    buf[0x23] = 0;
    buf[0x24] = D_800E74D4;
    buf[0x25] = D_800EA348;
    buf[0x26] = D_800E73A4;
    buf[0x27] = D_800E73A8;
    buf[0x28] = D_800E73AC;
    func_8002BB98(F(s16, 0x4E, *(u16 *)(s + 0xA)), F(u8, 0x50, *(u16 *)(s + 0xA)), buf);
    func_800BA1A4(F(s16, 0x4E, *(u16 *)(s + 0xA)), F(u8, 0x50, *(u16 *)(s + 0xA)));
    return r;
}
