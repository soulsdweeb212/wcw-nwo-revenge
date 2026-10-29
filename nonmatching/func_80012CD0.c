#include "common.h"

typedef struct {
    s8 f10;
    s8 n;
    s8 src;
    s8 mode;
    f32 x, y, z;
    s32 rx, ry, rz, rw;
    f32 v30[3];
    f32 pts[4][3];
} Ent;
typedef struct {
    u8 pad0[0x18];
    u8 b18;
    u8 pad19[3];
    f32 m1C[16];
    u8 m5C[0xDC - 0x5C];
} Render4;
typedef struct { s8 a, b; } Pair;

extern Ent D_8007E010[];
extern Render4 D_8005A3C0[];
extern Render4 D_8005A730[];
extern Pair D_80070478[];
extern s8 D_80036D30[];
extern s8 D_80036D38[];
extern u8 D_80066054[];
extern u8 D_800651B8[];

void func_80007E04(f32 *, f32, f32, f32);
void func_80007E14(f32 *, f32);
void func_80001DC4(void *);
void func_800056CC(f32 *, f32 *, f32 *);
void func_80011764(s16);
void func_8001A490(void *, f32, f32, f32, f32);
void func_8001B3EC(void *, f32, f32, f32, f32 *, f32 *, f32 *);
void multiplyMatrix4x4(f32 [4][4], f32 [4][4], f32 *);

/* Per-slot (4 players) transform update: builds each slot's render matrix from
 * the D_8007E010 record (Euler rotation + translation, or a look-at when mode
 * >= 11), refreshes its pivot points and picks the source byte, then updates the
 * second render object from the D_80070478 table. */
void func_80012CD0(void) {
    f32 rot[4][4];
    f32 mtx[4][4];
    f32 px, py, pz;
    f32 dx, dy, dz;
    Render4 *r;
    f32 *m;
    u32 i;
    u32 j;

    for (i = 0; i < 4; i++) {
        if (D_8007E010[i].mode != -1) {
            r = &D_8005A3C0[i];
            if (D_8007E010[i].mode < 11) {
                m = r->m1C;
                buildEulerRotationMatrixDegrees(mtx, (f32)(D_8007E010[i].rx * 0.087890625),
                                                (f32)(D_8007E010[i].ry * 0.087890625),
                                                (f32)(D_8007E010[i].rz * 0.087890625));
                func_80007E14(&rot[0][0], (f32)(D_8007E010[i].rw * 0.087890625));
                multiplyMatrix4x4(mtx, rot, m);
            } else {
                func_80011764(i);
                func_800056CC(&px, &py, &pz);
                m = r->m1C;
                func_8001A490(m, 0.0f, D_8007E010[i].x - px, D_8007E010[i].y - py, D_8007E010[i].z - pz);
            }
            func_80007E04(m, D_8007E010[i].x, D_8007E010[i].y, D_8007E010[i].z);
            func_80001DC4(r);
            func_8001B3EC(r->m5C, 0.0f, 0.0f, 0.0f, &D_8007E010[i].v30[0],
                          &D_8007E010[i].v30[1], &D_8007E010[i].v30[2]);
            if (D_8007E010[i].mode != -1) {
                for (j = 0; j < D_8007E010[i].n; j++) {
                    func_8001B3EC(r->m5C, D_80036D30[D_8007E010[i].n + j], 0.0f,
                                  D_80036D38[D_8007E010[i].n + j], &D_8007E010[i].pts[j][0],
                                  &D_8007E010[i].pts[j][1], &D_8007E010[i].pts[j][2]);
                }
            }
            r->b18 = D_80066054[D_8007E010[i].src * 0x13C4];
        }
        if (D_80070478[i].a != -1) {
            r = &D_8005A730[i];
            r->b18 = D_800651B8[i * 0x13C4 + D_80070478[i].b * 0xDC];
            func_80001DC4(r);
        }
    }
}
