#include "common.h"

typedef struct {
    s8 pad10;
    s8 n;      /* 11 */
    s8 e12;
    s8 e13;
    f32 x, y, z;        /* 14 18 1C */
    s32 rx, ry, rz, rw; /* 20 24 28 2C */
    f32 v30[3];         /* 30 */
    f32 pts[4][3];      /* 3C */
} Ent;
typedef struct { s8 a, b; } Pair;

extern Ent D_8007E010[];
extern u8 D_8005A3C0[];
extern u8 D_8005A730[];
extern u8 D_800651B8[];
extern u8 D_80066054[];
extern Pair D_80070478[];
extern s8 D_80036D30[];
extern s8 D_80036D38[];
extern f64 D_8003B310;

void multiplyMatrix4x4(void *, void *, void *);
void func_80001DC4(void *);
void func_800056CC(f32 *, f32 *, f32 *);
void func_80007E04(void *, f32, f32, f32);
void func_80007E14(void *, f32);
void func_80011764(s16);
void func_8001A490(void *, f32, f32, f32, f32);
void func_8001B3EC(void *, f32, f32, f32, f32 *, f32 *, f32 *);

void func_80012CD0(void) {
    f32 rot[4][4];
    f32 mtx[4][4];
    f32 px, py, pz;
    u32 i;
    u32 n;
    u8 *obj;
    u8 *m;
    f64 scale = D_8003B310;
    f32 zero = 0.0f;

    for (i = 0; i < 4; i++) {
        if (D_8007E010[i].e13 != -1) {
            obj = D_8005A3C0 + i * 0xDC;
            if (D_8007E010[i].e13 < 11) {
                buildEulerRotationMatrixDegrees(mtx, D_8007E010[i].rx * scale, D_8007E010[i].ry * scale, D_8007E010[i].rz * scale);
                m = obj + 0x1C;
                func_80007E14(rot, D_8007E010[i].rw * scale);
                multiplyMatrix4x4(mtx, rot, m);
            } else {
                func_80011764(i);
                func_800056CC(&px, &py, &pz);
                m = obj + 0x1C;
                func_8001A490(m, 0.0f, D_8007E010[i].x - px, D_8007E010[i].y - py, -(pz - D_8007E010[i].z));
            }
            func_80007E04(m, D_8007E010[i].x, D_8007E010[i].y, D_8007E010[i].z);
            func_80001DC4(obj);
            func_8001B3EC(obj + 0x5C, zero, zero, zero, &D_8007E010[i].v30[0], &D_8007E010[i].v30[1], &D_8007E010[i].v30[2]);
            if (D_8007E010[i].e13 != -1) {
                for (n = 0; n < D_8007E010[i].n; n++) {
                    func_8001B3EC(obj + 0x5C, D_80036D30[D_8007E010[i].n + n], 0.0f, D_80036D38[D_8007E010[i].n + n],
                                  &D_8007E010[i].pts[n][0], &D_8007E010[i].pts[n][1], &D_8007E010[i].pts[n][2]);
                }
            }
            obj[0x18] = D_80066054[D_8007E010[i].e12 * 0x13C4];
        }
        if (D_80070478[i].a != -1) {
            obj = D_8005A730 + i * 0xDC;
            obj[0x18] = D_800651B8[i * 0x13C4 + D_80070478[i].b * 0xDC];
            func_80001DC4(obj);
        }
    }
}
