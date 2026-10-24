#include "common.h"

typedef struct EntE920 {
    struct EntE920 *a0;
    struct EntE920 *a4;
    struct EntE920 *a8;
    u8 padC[0x10];
    f32 mtx[4][4];
    u8 pad5C[0x80];
} EntE920;
typedef struct {
    u8 pad[0x2C];
} PartE920;

extern EntE920 D_80057030[];
extern PartE920 D_800583F8[];
extern u8 D_800587F0[];
extern u8 D_80058900[];
extern u8 D_80058988[];
extern u8 D_80036C68[];
extern u8 D_80036C8C[];
extern u8 D_80036CFC[];
extern u8 D_80036D04[];
extern void *D_80036C74[];
extern void *D_80036C94[];
extern s16 D_80036C50[];
extern u16 D_80036C58[];
extern s16 D_80036C60[];
extern s32 D_800587EC;
extern s32 D_800588F8;
extern s32 D_80058984;
extern s16 D_80059D80;
extern s16 D_80059D82;
extern f64 D_8003B220;
extern f64 D_8003B228;

s32 func_80007020(void *, void *, void *, s32);
void func_80007818(void *, void *, s32, s32);
void func_80001544(void *);
void func_80001DC4(void *);
void func_80004B34(void *, void *, s32, f32, f32, f32);
void func_80004BA8(void *, void *, s32, s32, s32, s32, void *);
void func_80004F80(void *, s16, s16);
void func_80007E14(void *, f32);
void func_8000EF90(void);
void nw2Mat4Mul(void *, void *, void *);
void func_80021C40(void *, void *, s32);

void func_8000E920(void *unused, s16 arg1)
{
    f32 mtx[4][4];
    u32 i;
    u32 j;
    s32 n;
    f64 fv;
    EntE920 *ents = D_80057030;
    PartE920 *parts = D_800583F8;

    D_80059D82 = arg1;
    if (arg1 >= 6) {
        D_80059D82 = 0;
    }
    if (D_80036C74[D_80059D82] != NULL) {
        D_800587EC = func_80007020(D_800587F0, D_80036C68, D_80036C74[D_80059D82], 6);
    }
    D_800588F8 = func_80007020(D_80058900, D_80036C8C, D_80036C94[D_80059D82], 3);
    D_80058984 = func_80007020(D_80058988, D_80036CFC, D_80036D04, 3);
    func_80004B34(&ents[0], &parts[0], 6, 0.0f, 0.0f, 0.0f);
    if (D_80036C74[D_80059D82] != NULL) {
        func_80007818(&ents[0], D_800587F0, D_800587EC, 0);
        func_80001544(&ents[0]);
    }
    ents[0].a8 = &ents[1];
    n = 1;
    for (i = 0; i < 4; i++) {
        fv = (s32)i;
        if ((s32)i < 0) {
            fv += D_8003B220;
        }
        func_80007E14(mtx, fv * D_8003B228);
        for (j = 0; j < 3; j++) {
            func_80004B34(&ents[n], &parts[n], 3, 0.0f, 0.0f, 0.0f);
            func_80004BA8(&ents[n], &parts[n], 0, D_80036C50[j], 0, 0, &ents[n + 1]);
            if (D_80036C58[j] != 0) {
                func_80004F80(&parts[n], D_80036C58[j], D_80036C60[j]);
            }
            nw2Mat4Mul(mtx, ents[n].mtx, ents[n].mtx);
            n++;
        }
        func_80004B34(&ents[n], &parts[n], 0, 0.0f, 0.0f, 0.0f);
        func_80007818(&ents[n], D_80058900, D_800588F8, 0);
        func_80001544(&ents[n]);
        ents[n].a0 = NULL;
        ents[n].a8 = &ents[n + 2];
        ents[n].a4 = &ents[n + 1];
        func_80021C40(mtx, ents[n].mtx, 0x40);
        n++;
        if (i != 0) {
            func_80004B34(&ents[n], &parts[n], 5, 0.0f, 0.0f, 0.0f);
            func_80007818(&ents[n], D_80058988, D_80058984, 0);
            func_80001544(&ents[n]);
            ents[n].a0 = &ents[n - 1];
            ents[n].a8 = NULL;
            ents[n].a4 = NULL;
            n++;
        }
    }
    D_80059D80 = (s8)n + 1;
    func_80001DC4(ents);
    func_8000EF90();
}
