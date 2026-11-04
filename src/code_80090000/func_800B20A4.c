/* @header
 * func_800B20A4
 * VRAM 0x800B20A4 | ROM 0x5E814 | size 0x4E4
 * asm: asm/nonmatchings/code_80090000/func_800B20A4.s
 */
#include "common.h"


typedef struct { s32 x; s32 y; s32 page; s32 len; } Kb;
extern Kb D_800E7BF0;
extern s32 D_800E7BFC;
extern u16 D_800EA0C0[];
extern s16 D_800E9824;
extern s32 D_800EA318;
extern u8 D_8007E8C0[];
extern u8 D_800CD838;
s32 func_800B1F98(s32);
void func_800B1E88(void);
void func_8002A820(u8 *, s32);

static inline s32 maxlen(void) {
    if (D_800E7BF0.page == 0) {
        return 0x18;
    }
    if (D_800E7BF0.page == 1) {
        return 0xA;
    }
    return 0x14;
}

static inline s32 canAdvance(void) {
    s32 m = maxlen();
    s32 n = D_800E7BF0.len;
    if (n >= m - 1) {
        return 0;
    }
    return -(D_8007E8C0[0x80 + n] != 0);
}

s32 func_800B20A4(void) {
    s32 r = 0x12;
    u16 b = D_800EA0C0[2];
    u16 b2;

    if (b & 0x800) {
        if (--D_800E7BF0.y < 0) {
            D_800E7BF0.y = 6;
        }
        D_800EA318 = 0x409;
    } else if (b & 0x400) {
        if (++D_800E7BF0.y >= 7) {
            D_800E7BF0.y = 0;
        }
        D_800EA318 = 0x409;
    } else if (b & 0x200) {
        if (D_800E7BF0.y == 6) {
            D_800E7BF0.x = (D_800E7BF0.x < 9) ? 9 : 0;
        } else if (--D_800E7BF0.x < 0) {
            D_800E7BF0.x = 0xE;
        }
        D_800EA318 = 0x409;
    } else if (b & 0x100) {
        if (D_800E7BF0.y == 6) {
            D_800E7BF0.x = (D_800E7BF0.x < 9) ? 9 : 0;
        } else if (++D_800E7BF0.x >= 0xF) {
            D_800E7BF0.x = 0;
        }
        D_800EA318 = 0x409;
    } else {
        b2 = D_800EA0C0[1];
        if (b2 & 0x1000) {
            if (D_800E7BF0.x < 9 && D_800E7BF0.y == 6) {
                r = func_800B1F98(0x12);
            } else {
                D_800E7BF0.x = 8;
                D_800E7BF0.y = 6;
                D_800EA318 = 0x409;
            }
        } else if (D_800E7BF0.y == 6) {
            if (D_800E7BF0.x >= 9) {
                D_800E9824 = 1;
                if (b2 & 0x8000) {
                    r = 0x200;
                } else if (b2 & 0x4000) {
                    r = 0x200;
                }
            } else {
                D_800E9824 = 2;
                if (b2 & 0x8000) {
                    r = func_800B1F98(0x12);
                } else if (b2 & 0x4000) {
                    r = 0x200;
                }
            }
        } else {
            D_800E9824 = 0;
            if (b2 & 0x8000) {
                func_800B1E88();
                D_800EA318 = 0x408;
            } else if (b2 & 0x4002) {
                u8 *p = D_8007E8C0 + 0x80;
                if (p[0]) {
                    s32 k;
                    u8 *q;
                    func_8002A820(p, 8);
                    k = D_800E7BF0.len;
                    q = &p[k];
                    if (*q == 0) {
                        D_800E7BF0.len = k - 1;
                        p[D_800E7BF0.len] = 0;
                    } else {
                        do {
                            q[0] = q[1];
                            q++;
                        } while (*q);
                    }
                }
                if (D_800EA0C0[1] & 2) {
                    if (D_800E7BF0.len != 0) {
                        D_800E7BF0.len--;
                    }
                }
                D_800EA318 = 0x403;
            } else if (b2 & 9) {
                s32 m = maxlen();
                u8 *p = D_8007E8C0 + 0x80;
                s32 j;
                func_8002A820(p, 8);
                for (j = m - 1; D_800E7BFC < j; j--) {
                    p[j] = p[j - 1];
                }
                p[j] = D_800CD838;
                D_800EA318 = 0x408;
                if (D_800EA0C0[1] & 1) {
                    if (canAdvance()) {
                        D_800E7BF0.len++;
                    }
                }
            } else if (b2 & 0x10) {
                if (canAdvance()) {
                    D_800EA318 = 0x403;
                    D_800E7BF0.len++;
                }
            } else if (D_800EA0C0[1] & 0x20) {
                if (D_800E7BF0.len != 0) {
                    D_800E7BF0.len--;
                    D_800EA318 = 0x403;
                }
            } else if (D_800EA0C0[1] & 4) {
                D_800E7BF0.x = 0;
                D_800E7BF0.y = 6;
                D_800EA318 = 0x409;
            }
        }
    }
    return r;
}
