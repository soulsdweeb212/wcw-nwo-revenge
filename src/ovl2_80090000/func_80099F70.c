/* @header
 * func_80099F70
 * VRAM 0x80099F70 | ROM 0x8D410 | size 0x404
 * asm: asm/nonmatchings/ovl2_80090000/func_80099F70.s
 */
#include "common.h"

typedef struct { u8 pad[0xC]; } View;
typedef struct {
    f32 x, y, z;
    f32 rot;
    s32 f10;
} Pos14;
typedef struct {
    u8 pad0[0x24];
    u8 f24;
    u8 f25;
    s8 f26;
    s8 f27;
    s8 f28;
} CharInfo;

void func_80001260(s32);
void func_80002BA0(void *, void *);
void func_80008810(void);
void func_8009A714(f32, f32, f32, f32, f32, f32);
void func_80005304(void *, f32, f32, f32, f32, f32, f32);
void func_800056F4(void *, f32, f32, f32);
void initSideSlotTransforms(void);
void func_8000E920(s32, s32);
void initializeMatchResources(void);
void updateRingCornerFlags(void);
CharInfo *func_8002B7E0(s16, s16);
void func_8000C91C(s16, s16, s32, s32, s32, s32, s32);
void func_8009A69C(void *, Pos14 *);
void func_80001DC4(void *);
void func_8000CD18(s16, f32, f32);
void func_8000DB90(s16, s32);
void initializeTransformNode(void *, s32, f32, f32, f32);
void buildColorOverlayDisplayList(void *, s32, s32, s32, s32);
void func_8000E644(void);
void func_800922C0(u8);
void func_800982AC(void);

extern u8 D_800651A0[];
extern u8 D_800706A0[];
extern s16 D_8007DFA8[];
extern s32 D_8007E8C0[];
extern u8 D_8007FC10;
extern View D_800EB360[];
extern s16 D_800EB378;
extern u8 D_800EB379;
extern s16 D_800EB37A;
extern u8 D_800EB37B;
extern f32 D_800EB37C[3]; /* camera eye */
extern f32 D_800EB388[3]; /* camera target */
extern f32 D_800EB394[];
extern f32 D_800EB3A4;
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
extern s16 D_800F99BA;
/* D_800F99C0 is s32 in common.h */
extern Pos14 D_800F9AA8[];
extern s16 D_800FACEA[];

void func_80099F70(void) {
    u32 i;
    s16 id;
    CharInfo *c;

    func_80001260(0x1E0);
    func_80002BA0(&D_800EB360[0], &D_800EB360[1]);
    func_80008810();
    D_800EB378 = 0;
    for (i = 0; i < 4; i++) {
        if (D_800FACEA[i] >= 0) {
            D_800EB378++;
        }
    }
    func_8009A714(0.0f, 400.0f, 500.0f, 0.0f, 150.0f, 0.0f);
    func_80005304(&D_800EB360[0], D_800EB37C[0], D_800EB37C[1], D_800EB37C[2], D_800EB388[0],
                  D_800EB388[1], D_800EB388[2]);
    func_80005304(&D_800EB360[1], D_800EB37C[0], D_800EB37C[1], D_800EB37C[2], D_800EB388[0],
                  D_800EB388[1], D_800EB388[2]);
    func_800056F4(D_800EB394, 0.0f, 400.0f, 0.0f);
    D_800EB3A4 = 0.0f;
    D_800F99BA = 0;
    D_800EB3AC = 0.0f;
    D_800EB3B0 = 400.0f;
    D_800EB3B4 = 400.0f;
    D_800EB3B8 = 0.0f;
    D_800EB3BC = 0.0f;
    D_800EB3C0 = 0.0f;
    D_800EB3C4 = 0.0f;
    D_800EB3C8 = 400.0f;
    D_800EB3CC = 400.0f;
    D_800EB3D0 = 0.0f;
    D_800EB3D4 = 0.0f;
    D_800EB3D8 = 0.0f;
    D_800EB3A8 = 16.0f;
    initSideSlotTransforms();
    func_8000E920(D_800EB378, D_8007FC10);
    initializeMatchResources();
    updateRingCornerFlags();
    for (i = 0; i < 4; i++) {
        id = D_800FACEA[i];
        if (D_800FACEA[i] <= 0) {
            id = 1;
            D_8007DFA8[i] = 0;
        } else {
            D_8007DFA8[i] = D_8007E8C0[0x1C + i];
            if (D_8007DFA8[i] < 0) {
                D_8007DFA8[i] = 0;
            }
        }
        D_800F9AA8[i].x = 0.0f;
        D_800F9AA8[i].y = 0.0f;
        D_800F9AA8[i].z = 0.0f;
        D_800F9AA8[i].rot = 0.0f;
        D_800F9AA8[i].f10 = 0;
        c = func_8002B7E0(id, D_8007DFA8[i]);
        func_8000C91C(i, id, c->f25, c->f24, c->f26, c->f27, c->f28);
        func_8009A69C(D_800651A0 + i * 0x13C4, &D_800F9AA8[i]);
        func_80001DC4(D_800651A0 + i * 0x13C4);
        func_8000CD18(i, 90.0f, 0.0f);
        D_800706A0[i] = 0;
        if (D_800FACEA[i] < 0) {
            func_8000DB90(i, 0);
        }
    }
    D_800EB37A = 0xFF;
    initializeTransformNode(&D_800F99C0, 5, 0.0f, 0.0f, 0.0f);
    buildColorOverlayDisplayList(&D_800F99C0, 0xFF, 0xFF, 0xFF, D_800EB37B);
    func_80001DC4(&D_800F99C0);
    func_8000E644();
    func_800922C0(D_800EB379);
    func_800982AC();
}
