/* @header
 * func_8009B2EC
 * VRAM 0x8009B2EC | ROM 0x8E78C | size 0x1488
 * asm: asm/nonmatchings/ovl2_80090000/func_8009B2EC.s
 */
#include "common.h"

typedef struct {
    f32 x, y, z;
    f32 rot;
    s32 f10;
} Pos14;

u16 func_800B8278(void);
f32 func_80003CF0(f32);
f32 nw2Sqrtf(f32);
s16 func_8000CF64(f32, f32);
s8 func_800A90FC(s16);
u16 func_800085E4(s16);
s32 func_8001C580(void);
s32 func_800A9028(s16);
f32 func_80003A3C(f32, f32);
f32 sinf(f32);
f32 cosf(f32);

extern f32 D_80070C50[][713];
extern s16 D_800E2FB0;
extern s16 D_800E2FB2;
extern u16 D_800E2FB4;
extern u16 D_800EB352;
extern f32 D_800EB354;
extern f32 D_800EB37C[3];
extern f32 D_800EB388[3];
extern f32 D_800EB3A8;
extern f32 D_800EB3AC;
extern f32 D_800EB3B0;
extern f32 D_800EB3B4;
extern f32 D_800EB3B8;
extern f32 D_800EB3BC;
extern f32 D_800EB3C0;
extern f32 D_800EB3C4;
extern f32 D_800EB3C8;
extern f32 D_800EB3CC;
extern f32 D_800EB3D0;
extern f32 D_800EB3D4;
extern f32 D_800EB3D8;
extern Pos14 D_800F9AA8[];

static inline f32 normAngle(f32 a) {
    while (a > 6.283185307179586) {
        a -= 6.283185307179586;
    }
    while (a < 0.0f) {
        a += 6.283185307179586;
    }
    return a;
}

void func_8009B2EC(s16 arg0, u16 *ids) {
    f32 x, y, z;
    f32 d;
    f32 df;
    f32 t;
    f32 s;
    f32 cx, cy, cz;
    f32 ex, ey, ez;
    f32 a;
    s16 flag;
    u16 m;
    u16 bits;
    u32 i;
    s16 k;

    x = func_80003CF0(D_800F9AA8[ids[0]].x - D_800F9AA8[ids[1]].x);
    y = func_80003CF0(D_800F9AA8[ids[0]].y - D_800F9AA8[ids[1]].y);
    z = func_80003CF0(D_800F9AA8[ids[0]].z - D_800F9AA8[ids[1]].z);
    d = z;
    if (z < x * 1.1) {
        /* do-while(0): its loop notes double flow's ref weight for x, so x outranks cz in global-alloc */
        do {
            d = x;
        } while (0);
    }
    cx = (D_800F9AA8[ids[0]].x + D_800F9AA8[ids[1]].x) * 0.5;
    cy = (D_800F9AA8[ids[0]].y + D_800F9AA8[ids[1]].y) * 0.5;
    cz = -(D_800F9AA8[ids[0]].z + D_800F9AA8[ids[1]].z) * 0.5;
    d *= 0.02;
    if (d < 5.0) {
        if (y < 150.0) {
            t = 2.0f;
        } else {
            t = 4.0f;
        }
    } else if (cz >= -280.0) {
        if (d < 13.0) {
            t = 8.0f;
        } else {
            cx = 0.0f;
            if (d < 20.0) {
                cy = 150.0f;
                t = 17.0f;
            } else {
                cy = 300.0f;
                t = 22.0f;
            }
            cz = cx;
        }
    } else {
        t = d * 0.8;
    }
    if (!(arg0 & 0x80)) {
        D_800EB3A8 = D_800EB3A8 - (D_800EB3A8 - t) * 0.1;
    } else {
        D_800EB3A8 = t;
    }
    d = nw2Sqrtf(x * x + z * z);
    flag = (func_8000CF64(D_800F9AA8[ids[0]].x, D_800F9AA8[ids[0]].z) == 0) |
           (func_8000CF64(D_800F9AA8[ids[1]].x, D_800F9AA8[ids[1]].z) == 0);
    if (arg0 != 0) {
        if (D_800E2FB4 == 0 || D_800E2FB2 != (arg0 & 0x3F)) {
            D_800EB352 = 0;
            D_800E2FB2 = arg0 & 0x3F;
            D_800E2FB4 = 1;
        } else {
            D_800EB352++;
        }
    } else {
        m = func_800B8278();
        bits = 0;
        for (i = 0; i < 2; i++) {
            if ((m >> func_800A90FC(ids[i])) & 1) {
                bits |= func_800085E4(ids[i]);
            }
        }
        if (bits != 0) {
            if (D_800E2FB4 == 0) {
                D_800E2FB4 = 1;
                if (bits >= 9) {
                    D_800E2FB2 = 0;
                    if (bits == 9) {
                        D_800E2FB2 = func_8001C580() % 4 + 15;
                    }
                } else {
                    do {
                        k = func_8001C580() % 5 + 7;
                        D_800E2FB2 = k;
                    } while (k == D_800E2FB0);
                    D_800E2FB0 = k;
                    if (bits == 8) {
                        if ((func_800A9028(ids[0]) | func_800A9028(ids[1])) & 0x10) {
                            if (D_800E2FB2 == 10) {
                                D_800E2FB2 = 13;
                            }
                            if (func_800A9028(ids[0]) & 0x10) {
                                D_800EB354 = func_80003A3C(D_800F9AA8[ids[0]].x - D_800F9AA8[ids[1]].x, -z);
                            } else {
                                D_800EB354 = func_80003A3C(D_800F9AA8[ids[1]].x - D_800F9AA8[ids[0]].x, -z);
                            }
                        } else {
                            D_800E2FB4 = 0;
                            D_800E2FB2 = 0;
                        }
                    } else if (d > 180.0) {
                        D_800E2FB2 = 0;
                    }
                }
                D_800EB352 = 0;
            } else {
                D_800EB352++;
            }
        } else {
            D_800E2FB4 = 0;
            D_800E2FB2 = 0;
        }
    }
    switch (D_800E2FB2) {
        case 1:
            ex = cx - 380.0f;
            ey = 300.0f;
            ez = cz + 380.0f;
            break;
        case 2:
            ex = cx - 600.0f;
            ey = 500.0f;
            ez = cz + 600.0f;
            break;
        case 3:
            ex = cx - 700.0f;
            ey = 800.0f;
            ez = cz + 700.0f;
            break;
        case 4:
            ex = cx - 100.0f;
            ey = 400.0f;
            ez = cz + 300.0f;
            if (!flag) {
                ey = 130.0f;
            }
            break;
        case 5:
            cx = D_800EB3B8 = 0.0f;
            cy = D_800EB3BC = 200.0f;
            cz = D_800EB3C0 = 0.0f;
            ex = D_800EB3AC = -500.0f;
            ey = D_800EB3B0 = 500.0f;
            ez = D_800EB3B4 = -500.0f;
            break;
        case 6:
            ex = 250.0f;
            ey = 350.0f;
            ez = ex;
            break;
        case 7:
            ex = cx + 100.0f;
            ey = cy + 300.0f;
            ez = cz + 200.0f;
            break;
        case 8:
            ex = cx + 400.0f;
            ey = 300.0f;
            ez = cz;
            if (!flag) {
                ey = 200.0f;
            }
            break;
        case 9:
            ex = cx - 400.0f;
            ey = 300.0f;
            ez = cz + 100.0f;
            if (!flag) {
                ey = 150.0f;
            }
            break;
        case 10:
            ex = cx;
            ey = 400.0f;
            ez = cz + 300.0f;
            if (!flag) {
                ey = 130.0f;
            }
            break;
        case 11:
            ex = cx;
            ez = cz + 100.0f;
            if (!flag) {
                ey = 700.0f - cy;
            } else {
                ey = 400.0f;
            }
            break;
        case 12:
            ex = cx + 10.0f;
            ez = cz + 100.0f;
            if (!flag) {
                ey = 180.0f - cy;
                if (ey < 60.0f) {
                    ez = cz + 300.0f - cy;
                } else {
                    ey = 400.0f;
                }
                if (D_800EB352 > 40) {
                    D_800E2FB2 = func_8001C580() % 5 + 7;
                }
            } else {
                ey = 400.0f;
            }
            break;
        case 13:
            ex = cx + sinf(D_800EB354) * 300.0f;
            ez = cz - cosf(D_800EB354) * 300.0f;
            ey = 400.0f;
            if (!flag) {
                ey = 130.0f;
            }
            break;
        case 14:
            cz = 30.0f - D_800F9AA8[1].z;
            cy = D_800F9AA8[1].y;
            ey = 50.0f - cy;
            cx = D_800F9AA8[1].x;
            ex = cx;
            ez = cz + 20.0f;
            break;
        case 15:
            if (cy >= 230.0f) {
                ex = cx + 200.0f;
                ey = 120.0f;
                ez = cz + 200.0f;
            } else {
                ex = cx;
                ey = 400.0f;
                ez = cz + 400.0f;
            }
            break;
        case 16:
            ex = cx;
            ey = cy + 400.0f;
            ez = cz + 200.0f;
            break;
        case 17:
            ey = 150.0f;
            if (cz >= 0.0f) {
                ex = 0.0f;
                ez = 430.0f;
            } else {
                if (cx >= 0.0f) {
                    ex = 430.0f;
                } else {
                    ex = -430.0f;
                }
                ez = 0.0f;
            }
            break;
        case 18:
            if (cy >= 230.0f) {
                if (cx >= 0.0f) {
                    ex = 430.0f;
                } else {
                    ex = -430.0f;
                }
                ey = 600.0f;
                if (cz >= 0.0f) {
                    ez = 430.0f;
                } else {
                    ez = -430.0f;
                }
            } else {
                if (cx >= 0.0f) {
                    ex = 480.0f;
                } else {
                    ex = -480.0f;
                }
                ey = 120.0f;
                ez = cz + 150.0f;
            }
            break;
        default:
            if (func_8000CF64(cx, cz) == 0) {
                cx *= 0.9;
                cz *= 0.9;
            }
            ey = D_800EB3A8 * 40.0f + 300.0f;
            ez = cz + 350.0f + D_800EB3A8 * 80.0f;
            ex = cx;
            if (((D_80070C50[ids[0]][0] == 0.0f && D_800F9AA8[ids[0]].z >= 280.0) ||
                 (D_80070C50[ids[1]][0] == 0.0f && D_800F9AA8[ids[1]].z >= 280.0)) &&
                (D_800F9AA8[ids[0]].z <= 400.0 || D_800F9AA8[ids[1]].z <= 400.0)) {
                ey += 200.0f;
                ez -= 200.0f;
                cz += 50.0f;
                cz *= 1.3;
            }
            break;
    }
    a = normAngle(func_80003A3C(D_800EB3AC - D_800EB3B8, D_800EB3B4 - D_800EB3C0));
    x = normAngle(func_80003A3C(ex - cx, ez - cz));
    df = a - x;
    if (df > 3.141592653589793) {
        df -= 6.283185307179586;
    } else if (df < -3.141592653589793) {
        df += 6.283185307179586;
    }
    if (func_80003CF0(df) > 1.5707963267948966) {
        x += df * 0.5;
        d = nw2Sqrtf((ex - cx) * (ex - cx) + (ez - cz) * (ez - cz));
        ex = cx + d * sinf(x);
        ez = cz + d * cosf(x);
    } else if (a != 0.0 && D_800E2FB2 == 0) {
        D_800E2FB2 = 19;
    }
    x = D_800EB3AC - ex;
    z = D_800EB3B4 - ez;
    if (D_800E2FB2 >= 4 || nw2Sqrtf(x * x + z * z) >= 80.0f) {
        D_800EB3C4 = ex;
        D_800EB3C8 = ey;
        D_800EB3CC = ez;
        D_800EB3D0 = cx;
        D_800EB3D4 = cy;
        D_800EB3D8 = cz;
    }
    if (!(arg0 & 0x80)) {
        s = (D_800EB3AC - D_800EB3C4) * 0.1;
        if (func_80003CF0(s) >= 0.1) {
            D_800EB3AC = D_800EB3AC - s;
        } else {
            D_800EB3AC = D_800EB3C4;
        }
        s = (D_800EB3B0 - D_800EB3C8) * 0.1;
        if (func_80003CF0(s) >= 0.1) {
            D_800EB3B0 = D_800EB3B0 - s;
        } else {
            D_800EB3B0 = D_800EB3C8;
        }
        s = (D_800EB3B4 - D_800EB3CC) * 0.1;
        if (func_80003CF0(s) >= 0.1) {
            D_800EB3B4 = D_800EB3B4 - s;
        } else {
            D_800EB3B4 = D_800EB3CC;
        }
        s = (D_800EB3B8 - D_800EB3D0) * 0.1;
        if (func_80003CF0(s) >= 0.1) {
            D_800EB3B8 = D_800EB3B8 - s;
        } else {
            D_800EB3B8 = D_800EB3D0;
        }
        s = (D_800EB3BC - D_800EB3D4) * 0.1;
        if (func_80003CF0(s) >= 0.1) {
            D_800EB3BC = D_800EB3BC - s;
        } else {
            D_800EB3BC = D_800EB3D4;
        }
        s = (D_800EB3C0 - D_800EB3D8) * 0.1;
        if (func_80003CF0(s) >= 0.1) {
            D_800EB3C0 = D_800EB3C0 - s;
        } else {
            D_800EB3C0 = D_800EB3D8;
        }
    } else {
        D_800EB3AC = D_800EB3C4;
        D_800EB3B0 = D_800EB3C8;
        D_800EB3B4 = D_800EB3CC;
        D_800EB3B8 = D_800EB3D0;
        D_800EB3BC = D_800EB3D4;
        D_800EB3C0 = D_800EB3D8;
    }
    D_800EB37C[0] = D_800EB3AC;
    D_800EB37C[1] = D_800EB3B0;
    D_800EB37C[2] = -D_800EB3B4;
    D_800EB388[0] = D_800EB3B8;
    D_800EB388[1] = D_800EB3BC;
    D_800EB388[2] = -D_800EB3C0;
}
