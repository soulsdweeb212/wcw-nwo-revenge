/* @header
 * func_8009C774
 * VRAM 0x8009C774 | ROM 0x8FC14 | size 0x102C
 * asm: asm/nonmatchings/ovl2_80090000/func_8009C774.s
 */
#include "common.h"

/* func_8009C774: overlay 2 camera for special (focused) camera modes, arg0 = D_800F99BA, ids = wrestler order */

typedef struct {
    f32 x, y, z;
    f32 rot;
    s32 f10;
} Pos14;

f32 nw2Sqrtf(f32);
f32 func_80003A3C(f32, f32);
f32 func_80003CF0(f32);
s16 func_8000CF64(f32, f32);
s32 func_8001C580(void);
s8 func_800D633C(void);
f32 sinf(f32);
f32 cosf(f32);

extern f32 D_80070C50[][713];
extern f32 D_80070CB8[][713];
extern s16 D_800E2F38[];
extern s16 D_800E2F5C[];
extern f32 D_800E2FB8[];
extern f32 D_800E2FC8[];
extern u8 D_800E2FD8[];
extern s16 D_800E2FDC;
extern s16 D_800E2FDE;
extern s16 D_800E2FE0;
extern u16 D_800E2FE2;
extern f32 D_800EB358;
extern f32 D_800EB37C[3];
extern f32 D_800EB388[3];
extern f32 D_800EB3A0;
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
extern s16 D_800F99B6;
extern Pos14 D_800F9AA8[];

void func_8009C774(s16 arg0, u16 *ids) {
    s16 kind;   /* s16: HImode pseudo (no PROMOTE_MODE on MIPS), so every later use of p sign-extends */
    s16 p;      /* focused wrestler, (arg0 >> 8) - 1 */
    f32 x, y, z; /* camera target */
    f32 dist;
    f32 height;
    f32 ang;
    /* one angle temporary per block: a single shared variable changes every block's FP registers */
    f32 r, t0, t1, t2, t3, t4, df;
    f32 d;
    f32 ex, ez; /* camera eye x/z */

    kind = arg0 & 0x3F;
    p = (arg0 >> 8) - 1;
    if (p >= 0 && p < 4) {
        x = D_800F9AA8[p].x;
        y = D_800F9AA8[p].y;
        z = -D_800F9AA8[p].z;
    } else {
        z = x = y = 0.0f;
    }
    if (D_800F99B6 == 0 && kind < 0x20) {
        dist = nw2Sqrtf((D_800F9AA8[ids[0]].x - D_800F9AA8[ids[1]].x) * (D_800F9AA8[ids[0]].x - D_800F9AA8[ids[1]].x) +
                        (D_800F9AA8[ids[0]].z - D_800F9AA8[ids[1]].z) * (D_800F9AA8[ids[0]].z - D_800F9AA8[ids[1]].z));
        if (dist > 200.0f) {
            dist = 200.0f;
        }
        dist *= 0.005;
        x = x * (1.0 - dist) + (D_800F9AA8[ids[0]].x + D_800F9AA8[ids[1]].x) * (dist * 0.5);
        y = y * (1.0 - dist) + (D_800F9AA8[ids[0]].y + D_800F9AA8[ids[1]].y) * (dist * 0.5);
        z = z * (1.0 - dist) + -(D_800F9AA8[ids[0]].z + D_800F9AA8[ids[1]].z) * (dist * 0.5);
    }
    r = func_80003A3C(D_800EB3AC - D_800EB3B8, D_800EB3B4 - D_800EB3C0);
    while (r > 6.283185307179586) {
        r -= 6.283185307179586;
    }
    while (r < 0.0f) {
        r += 6.283185307179586;
    }
    ang = r;
    if (D_800E2FDC != kind || (arg0 & 0x40)) {
        D_800E2FDC = kind;
        D_800E2FDE = kind;
        if (kind == 0x1A || kind == 0x1E) {
            D_800E2FDE = func_8001C580() % 6 + 0x14;
        }
        if (D_800E2FDE == 0x14 || D_800E2FDE == 0x17) {
            if (func_8001C580() % 5 == 0) {
                D_800E2FDE = 0x1A;
            }
        }
        if (D_800E2FDE != 0x1F && D_800E2FDE != 0x20) {
            t0 = D_80070CB8[p][0]; /* read first: expands the D_80070CB8 index before the D_800E2FD8 load (sched order) */
            t0 = (D_800E2FD8[D_800E2FE2] * 90 - t0) * 0.017453292519943295;
            while (t0 > 6.283185307179586) {
                t0 -= 6.283185307179586;
            }
            while (t0 < 0.0f) {
                t0 += 6.283185307179586;
            }
            D_800EB358 = t0;
            D_800E2FE2 = (D_800E2FE2 + 1) & 3;
            if (D_800F99B6 == 0 && !func_800D633C()) {
                D_800EB3A0 = D_800E2FC8[func_8001C580() % 3];
            }
        } else {
            D_800EB358 = ang;
            if (func_80003CF0(D_800F9AA8[ids[0]].y - D_800F9AA8[ids[1]].y) > 100.0f &&
                func_8000CF64(D_800F9AA8[p].x, D_800F9AA8[p].z)) {
                D_800E2FE0 = 1;
            } else {
                D_800E2FE0 = 0;
            }
        }
    }
    dist = D_800E2F38[D_800E2FDE];
    height = D_800E2F5C[D_800E2FDE];
    switch (D_800E2FDE) {
    case 0x16:
    case 0x19:
        if (func_80003CF0(height - y) < 50.0) {
            height += 50.0;
        }
        break;
    case 0x1F:
        if (D_800E2FE0 != 0) {
            dist -= 200.0f;
            y += 50.0f;
            height = 100.0f;
        }
    case 0x20:
        t1 = D_800EB358 + 0.017453292519943295;
        y += 20.0f;
        while (t1 > 6.283185307179586) {
            t1 -= 6.283185307179586;
        }
        while (t1 < 0.0f) {
            t1 += 6.283185307179586;
        }
        D_800EB358 = t1;
        break;
    case 0x22:
        t2 = (-D_80070CB8[p][0] + 30.0) * 0.017453292519943295;
        y += 40.0f;
        while (t2 > 6.283185307179586) {
            t2 -= 6.283185307179586;
        }
        while (t2 < 0.0f) {
            t2 += 6.283185307179586;
        }
        D_800EB358 = t2;
        break;
    case 0x21:
        t3 = -D_80070CB8[p][0] * 0.017453292519943295;
        y += 20.0f;
        while (t3 > 6.283185307179586) {
            t3 -= 6.283185307179586;
        }
        while (t3 < 0.0f) {
            t3 += 6.283185307179586;
        }
        D_800EB358 = t3;
        break;
    case 0x23:
        t4 = -D_80070CB8[p][0] * 0.017453292519943295;
        while (t4 > 6.283185307179586) {
            t4 -= 6.283185307179586;
        }
        while (t4 < 0.0f) {
            t4 += 6.283185307179586;
        }
        D_800EB358 = t4;
        break;
    case 0x24:
        D_800EB358 = 0.0f;
        y = 200.0f;
        z = -1250.0f;
        x = 0.0f;
        break;
    }
    if (!(arg0 & 0x80)) {
        df = D_800EB358 - ang;
        if (df > 3.141592653589793) {
            df -= 6.283185307179586;
        } else if (df < -3.141592653589793) {
            df += 6.283185307179586;
        }
        ang += df * 0.5;
    } else {
        ang = D_800EB358;
    }
    if (kind < 0x20) {
        if (!func_8000CF64(D_800F9AA8[ids[0]].x, D_800F9AA8[ids[0]].z) ||
            !func_8000CF64(D_800F9AA8[ids[1]].x, D_800F9AA8[ids[1]].z)) {
            if (height < 120.0) {
                height += 250.0;
            }
        }
        if ((D_80070C50[ids[0]][0] == 0.0f && D_800F9AA8[ids[0]].z >= 280.0) ||
            (D_80070C50[ids[1]][0] == 0.0f && D_800F9AA8[ids[1]].z >= 280.0)) {
            ang = D_800E2FB8[D_800E2FE2];
        }
    } else {
        if (D_80070C50[p][0] == 0.0f && D_800F9AA8[p].z >= 280.0) {
            ang = 0.0f;
        }
    }
    ex = x + dist * sinf(ang);
    ez = z + dist * cosf(ang);
    D_800EB3C4 = ex;
    D_800EB3C8 = height;
    D_800EB3CC = ez;
    D_800EB3D0 = x;
    D_800EB3D4 = y;
    D_800EB3D8 = z;
    if (!(arg0 & 0x80)) {
        d = (D_800EB3AC - D_800EB3C4) * 0.1;
        if (func_80003CF0(d) >= 0.1) {
            D_800EB3AC = D_800EB3AC - d;
        } else {
            D_800EB3AC = D_800EB3C4;
        }
        d = (D_800EB3B0 - D_800EB3C8) * 0.1;
        if (func_80003CF0(d) >= 0.1) {
            D_800EB3B0 = D_800EB3B0 - d;
        } else {
            D_800EB3B0 = D_800EB3C8;
        }
        d = (D_800EB3B4 - D_800EB3CC) * 0.1;
        if (func_80003CF0(d) >= 0.1) {
            D_800EB3B4 = D_800EB3B4 - d;
        } else {
            D_800EB3B4 = D_800EB3CC;
        }
        d = (D_800EB3B8 - D_800EB3D0) * 0.1;
        if (func_80003CF0(d) >= 0.1) {
            D_800EB3B8 = D_800EB3B8 - d;
        } else {
            D_800EB3B8 = D_800EB3D0;
        }
        d = (D_800EB3BC - D_800EB3D4) * 0.1;
        if (func_80003CF0(d) >= 0.1) {
            D_800EB3BC = D_800EB3BC - d;
        } else {
            D_800EB3BC = D_800EB3D4;
        }
        d = (D_800EB3C0 - D_800EB3D8) * 0.1;
        if (func_80003CF0(d) >= 0.1) {
            D_800EB3C0 = D_800EB3C0 - d;
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
