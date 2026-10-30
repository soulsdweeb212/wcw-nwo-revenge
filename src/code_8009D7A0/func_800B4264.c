/* @header
 * func_800B4264
 * VRAM 0x800B4264 | ROM 0xA7704 | size 0x254
 * asm: asm/nonmatchings/code_8009D7A0/func_800B4264.s
 */
#include "common.h"

extern void *D_800FABD0,*D_800F9B60,*D_800FAF58;
#define H(p,o) (*(s16 *)((u8 *)(p)+(o)))
#define U(p,o) (*(u16 *)((u8 *)(p)+(o)))
#define W(p,o) (*(u32 *)((u8 *)(p)+(o)))

static inline void setCmd4264(s16 cmd) {
    void *p = D_800FABD0;
    void *g = D_800F9B60;
    u16 st;
    H(p, 2) = cmd;
    H(p, 4) = 0;
    st = U(g, 0xA);
    U(p, 0x2E) = st;
    W(p, 0x5C) &= ~7;
}

void func_800B4264(void) {
    void *p = D_800FABD0;
    s16 state = H(p, 4);

    switch (state) {
    case 0:
        switch (H(p, 2)) {
        case 0x39:
        case 0x3B:
            if (!(*(u64 *)((u8 *)D_800F9B60 + 0x20) & 0x200000ULL)) {
                setCmd4264(0xD);
            } else {
                H(D_800FABD0, 6) = 2;
                goto inc;
            }
            break;
        case 0x3A:
        case 0x3C:
            if (!(*(u64 *)((u8 *)D_800F9B60 + 0x20) & 0x200000ULL)) {
                H(D_800FABD0, 6) = 2;
                goto inc;
            } else {
                setCmd4264(0xD);
            }
            break;
        default:
        inc:
            H(D_800FABD0, 4)++;
            break;
        }
        break;
    case 1:
        if (H(D_800FAF58, 0xA) == 0x30) {
            H(p, 4) = state + 1;
        } else {
            goto reset;
        }
        break;
    case 2:
        switch (H(D_800FAF58, 0xA)) {
        case 0x30:
        case 0x2B:
            U(D_800FABD0, 6) = 0x8000;
            break;
        case 0x3A:
        case 0x3C:
            H(D_800FABD0, 4)++;
            break;
        default:
            setCmd4264(0);
            break;
        }
        break;
    case 3:
        switch (H(D_800FAF58, 0xA)) {
        case 0x3A:
        case 0x3C:
            break;
        default:
        reset:;
            {
                void *g = D_800F9B60;
                u16 st;
                H(p, 2) = 0;
                H(p, 4) = 0;
                st = U(g, 0xA);
                W(p, 0x5C) &= ~7;
                U(p, 0x2E) = st;
            }
            break;
        }
        break;
    }
}
