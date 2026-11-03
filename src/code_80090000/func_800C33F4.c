/* @header
 * func_800C33F4
 * VRAM 0x800C33F4 | ROM 0x6FB64 | size 0x304
 * asm: asm/nonmatchings/code_80090000/func_800C33F4.s
 */
#include "common.h"

typedef struct {
    u8 pad0[0x40];
    u8 f40[0x650];
    u16 f690;
    s16 f692;
    u16 f694;
    u16 f696;
    s16 f698;
    u16 f69A;
    s16 f69C;
    s16 f69E;
    s16 f6A0;
    s16 f6A2;
    s16 f6A4;
    s16 f6A6;
    s16 f6A8;
    s16 f6AA;
    s16 f6AC;
    s16 f6AE;
    u8 pad6B0[0xA];
    s16 f6BA;
    u8 pad6BC[8];
    s32 f6C4;
} Wr33F4;

extern u8 *D_800E79B8;
extern s32 D_800D5E84;
extern s32 D_800E74D8;
extern u16 *D_80038A64[];
void func_80003684(void *, u16, void *);
void func_8000D210(s16, s16);
u8 *func_8002B7E0(s32, s32);
void func_8000D238(s16, u16);
void func_80012B38(s16, s32, s32);
void func_80012364(s16, s16, s32, s32);
void func_8000CFD4(s16, s16, s16, s16, s8, s8, s8);
void func_8000BB40(s16, s8, s8, s8);

void func_800C33F4(s32 a) {
    Wr33F4 *w = (Wr33F4 *)(D_800E79B8 + a * 0x6D0);
    u8 buf1[16];
    u8 buf2[16];
    u8 *p;

    if (D_800D5E84 != 0) {
        return;
    }
    if (w->f6BA != 0) {
        D_800D5E84 = 1;
        w->f6BA--;
        if (w->f6BA == 3) {
            func_80003684(buf1, D_80038A64[w->f690 >> 8][(w->f690 & 0xFF) - 1], w);
        } else if (w->f6BA == 2) {
            func_80003684(buf2, D_80038A64[w->f690 >> 8][(w->f690 & 0xFF) - 1] + 2, w->f40);
        } else {
            func_8000D210(a, w->f6BA);
        }
        if (w->f6BA != 0) {
            return;
        }
        w->f692 = w->f690;
    } else if (w->f692 != (s16)w->f690 || w->f698 != (w->f696 & 3) || w->f6A8 != w->f6AA ||
               w->f6AC != w->f6AE) {
        w->f692 = -1;
        w->f698 = w->f696 & 3;
        if ((s16)w->f690 >= 0 && D_800E74D8 != -3) {
            p = func_8002B7E0((s16)w->f690, w->f698);
            w->f6AA = p[0x24];
            w->f6AE = p[0x25];
            w->f6A2 = p[0x26];
            w->f6A4 = p[0x27];
            w->f6A6 = p[0x28];
        }
        w->f6C4 = 0x80;
        w->f6A8 = w->f6AA;
        w->f6AC = w->f6AE;
        w->f69C = w->f6A2;
        w->f69E = w->f6A4;
        w->f6A0 = w->f6A6;
        func_8000D238(a, 0x80);
        if ((s16)w->f690 >= 0) {
            func_80012B38(a, -1, 2);
            func_80012364(a, a, -1, 0);
            func_8000CFD4(a, w->f690, w->f6AC, w->f6A8, w->f69C, w->f69E, w->f6A0);
            w->f6BA = 4;
        }
    } else if (w->f69C != w->f6A2 || w->f69E != w->f6A4 || w->f6A0 != w->f6A6) {
        w->f69C = w->f6A2;
        w->f69E = w->f6A4;
        w->f6A0 = w->f6A6;
        func_8000BB40(a, w->f69C, w->f69E, w->f6A0);
    }
    if (w->f6BA == 0) {
        w->f690 = w->f694;
        w->f696 = w->f69A;
    }
}
