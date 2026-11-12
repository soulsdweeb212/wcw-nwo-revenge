/* @header
 * func_800B1F98
 * VRAM 0x800B1F98 | ROM 0x5E708 | size 0x10C
 * asm: asm/nonmatchings/code_80090000/func_800B1F98.s
 */
#include "common.h"



extern u8 D_8007E8C0[], D_8007E978[], D_8007E99A[];
extern u8 D_800CD838;
extern s32 D_800E7BF0, D_800E7BF4, D_800E7BF8, D_800E7BFC, D_800E79AC, D_800EA318;
void func_8002A820(void *, s32);
void bcopy(void *, void *, s32);

static inline s32 slen(u8 *str) {
    s32 n = 0;
    if (*str != 0) {
        u8 *s = str;
        do {
            s++;
            n++;
        } while (*s != 0);
    }
    return n;
}

s32 func_800B1F98(s32 a) {
    u8 *t = D_8007E8C0 + 0x80;
    u8 *s;
    s32 n;
    s32 bad;
    s32 x;
    n = slen(t);
    bad = 0;
    if (n != 0) {
        do {
#ifdef TARGET_PC
            /* PC: the address as a pointer-wide integer (port.h's uptr); an s32 would cut it in half. */
            s = (u8 *)(n + (uptr)t);
#else
            s = (u8 *)(n + (s32)t);
#endif
            if (s[-1] != D_800CD838) {
                goto fail;
            }
            n--;
            s[-1] = 0;
        } while (n != 0);
    }
    goto done;
fail:
    /* placeholder: the do-while(0) only gives this set loop weight in flow, so bad outranks t in
       global-alloc (a3 vs t0); the real source is unknown */
    do {
        bad = -1;
    } while (0);
done:
    x = 0x403;
    if (bad != 0) {
        D_800E79AC = 1;
        if (D_800E7BF8 == 0) {
            /* D_8007E978/D_8007E99A = D_8007E8C0+0xB8/+0xDA under their own names: with the
               same symbol, CSE keeps the address across the call in s0 */
            func_8002A820(D_8007E978, 8);
            bcopy(D_8007E8C0 + 0x80, D_8007E8C0 + 0xB8, 0x19);
        } else {
            func_8002A820(D_8007E99A, 8);
            bcopy(D_8007E8C0 + 0x80, D_8007E8C0 + 0xDA, 0xB);
        }
        a = 0x200;
        x = 0x42A;
    } else {
        D_800E7BF0 = 0;
        D_800E7BF4 = 0;
        D_800E7BFC = 0;
    }
    D_800EA318 = x;
    return a;
}
