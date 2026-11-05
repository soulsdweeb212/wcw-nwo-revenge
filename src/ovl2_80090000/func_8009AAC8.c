/* @header
 * func_8009AAC8
 * VRAM 0x8009AAC8 | ROM 0x8DF68 | size 0x824
 * asm: asm/nonmatchings/ovl2_80090000/func_8009AAC8.s
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

extern f32 D_80070C50[][713];
extern u16 D_8007E280;
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
extern s16 D_800FACEA[];

void func_8009AAC8(void) {
    u16 mask;
    u16 n;
    u32 i;
    s32 first;
    f32 x, z; /* reused for the zoom terms and the eye distance */
    f32 minX, minZ, maxX, maxZ;
    f32 sumY;
    f32 cx, cz;
    f32 zoom;
    f32 camY, camZ;
    f32 d;
    f32 ex; /* a separate copy of cx: the ROM keeps it in a GPR (s1) */

    n = 0;
    mask = func_800B8278();
    if (!(D_8007E280 & 0x400)) {
        mask ^= 0x3C0;
        mask >>= 6;
    }
    sumY = maxZ = maxX = minX = minZ = 0.0f;
    first = 1;
    for (i = 0; i < 4; i++) {
        if (D_800FACEA[i] >= 0 && ((mask >> i) & 1)) {
            x = D_800F9AA8[i].x;
            z = D_800F9AA8[i].z;
            if (first == 1) {
                first = 0;
                minX = x;
                minZ = z;
                maxX = minX;
                maxZ = minZ;
            } else {
                if (x < minX) {
                    minX = x;
                }
                if (z < minZ) {
                    minZ = z;
                }
                if (maxX < x) {
                    maxX = x;
                }
                if (maxZ < z) {
                    maxZ = z;
                }
            }
            n++;
            sumY += D_800F9AA8[i].y;
        }
    }
    sumY /= n;
    cx = (maxX + minX) * 0.5;
    cz = -(maxZ + minZ) * 0.5;
    x = func_80003CF0(maxX - minX) * 1.4;
    z = func_80003CF0(maxZ - minZ);
    if (z < x) {
        zoom = x;
    } else {
        zoom = z;
    }
    zoom *= 0.01;
    if (zoom >= 9.0 && cz >= -280.0) {
        sumY = 150.0f;
        cx = 0.0f;
        zoom = 14.0f;
        cz = cx;
    }
    D_800EB3A8 = D_800EB3A8 - (D_800EB3A8 - zoom) * 0.1;
    camY = D_800EB3A8 * 40.0f + 300.0f;
    camZ = cz + 400.0f + D_800EB3A8 * 100.0f;
    ex = cx;
    if ((((mask & 1) && D_80070C50[0][0] == 0.0f && D_800F9AA8[0].z >= 280.0) ||
         ((mask & 2) && D_80070C50[1][0] == 0.0f && D_800F9AA8[1].z >= 280.0) ||
         ((mask & 4) && D_80070C50[2][0] == 0.0f && D_800F9AA8[2].z >= 280.0) ||
         ((mask & 8) && D_80070C50[3][0] == 0.0f && D_800F9AA8[3].z >= 280.0)) &&
        (D_800F9AA8[0].z <= 400.0 || D_800F9AA8[1].z <= 400.0 || D_800F9AA8[2].z <= 400.0 ||
         D_800F9AA8[3].z <= 400.0)) {
        camY += 200.0f;
        camZ -= 200.0f;
        cz += 50.0f;
        cz *= 1.2;
    }
    x = D_800EB3AC - ex;
    z = D_800EB3B4 - camZ;
    if (nw2Sqrtf(x * x + z * z) >= 80.0f) {
        D_800EB3C4 = ex;
        D_800EB3C8 = camY;
        D_800EB3CC = camZ;
        D_800EB3D0 = cx;
        D_800EB3D8 = cz;
    }
    sumY -= D_800EB3A8 * 10.0f;
    if (func_80003CF0(D_800EB3BC - sumY) >= 40.0f) {
        D_800EB3D4 = sumY;
    }
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
    D_800EB37C[0] = D_800EB3AC;
    D_800EB37C[1] = D_800EB3B0;
    D_800EB37C[2] = -D_800EB3B4;
    D_800EB388[0] = D_800EB3B8;
    D_800EB388[1] = D_800EB3BC;
    D_800EB388[2] = -D_800EB3C0;
}
