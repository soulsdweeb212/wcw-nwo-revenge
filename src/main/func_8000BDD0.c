#include "common.h"

extern u16 D_8006A2A4[];
extern s16 D_8007DFBC[];
extern s16 D_8007DFB0[];
extern u16 *D_80031998[];
extern s16 **D_80032B44[][1];
extern u16 ***D_800360F0[];
extern s16 *D_800317F0[];
extern s8 D_80031088[];
extern u8 D_800651A0[];
extern u8 D_80073EB0[];
extern u8 D_8007C3D0[][16];
extern u8 D_80070450[];
void func_80004BA8(void *, void *, void *, s16, void *, s32, void *);
void func_80005014(void *, void *, void *, void *);

typedef struct { u8 d[0xDC]; } ObjDC;
typedef struct { u8 d[0x2C]; } Slot2C;

void func_8000BDD0(s16 arg0) {
    u32 i;
    u16 w;
    s32 bank;
    s32 idx;
    u16 *a3;
    s16 *s2;
    Slot2C *s4;
    ObjDC *s3;
    s16 *tbl;
    u16 a2;

    w = D_8006A2A4[arg0];
    bank = (w >> 8) & 0x1F;
    idx = (w & 0x1F) - 1;
    a3 = (u16 *)(idx * 2 + (u32)D_80031998[bank]);
    s2 = ((s16 ***)D_80032B44[bank][0])[idx][D_8007DFB0[arg0]];
    a2 = *D_800360F0[*a3 & 0x7F][D_8007DFBC[arg0]][0];
    s4 = (Slot2C *)(D_80073EB0 + arg0 * 0x3F4);
    tbl = D_800317F0[a2 & 0x7F];
    s3 = (ObjDC *)(D_800651A0 + arg0 * 0x13C4);
    D_80070450[arg0] = a2;
    *(void **)((u8 *)s3 + 4) = &s3[1];
    for (i = 1; i < 0x14; i++) {
        s8 c = D_80031088[i];
        if (c < 0) {
            switch (i) {
            case 4:
                func_80004BA8(&s3[4], &s4[4], D_8007C3D0[arg0], s2[0], s3, 0, &s3[5]);
                break;
            case 5:
                func_80004BA8(&s3[5], &s4[5], D_8007C3D0[arg0], s2[1], s3, 0, &s3[6]);
                break;
            }
        } else {
            func_80004BA8(&s3[i], &s4[i], D_8007C3D0[arg0], tbl[c], s3, 0, &s3[i + 1]);
        }
    }
    *(s32 *)((u8 *)s3 + 0x105C) = 0;
    if (s2[2] != 0) {
        *((u8 *)s3 + 0x1148) = *((u8 *)s3 + 0x464);
        func_80004BA8((u8 *)s3 + 0x1130, &s4[20], D_8007C3D0[arg0], s2[2], &s3[5], 0, NULL);
        *(void **)((u8 *)s3 + 0x450) = (u8 *)s3 + 0x1130;
    } else {
        void *v1 = *(void **)((u8 *)s3 + 0x1144);
        *((u8 *)s3 + 0x1148) = 0x80;
        *(s32 *)((u8 *)s3 + 0x1130) = 0;
        if (v1 != NULL) {
            *(s32 *)((u8 *)v1 + 0x30) = 0;
            *(s16 *)((u8 *)*(void **)((u8 *)s3 + 0x1144) + 0x2C) = 0;
            *(s16 *)((u8 *)*(void **)((u8 *)s3 + 0x1144) + 0x2E) = 0;
            *(s32 *)((u8 *)*(void **)((u8 *)s3 + 0x1144) + 0x34) = 0;
        }
        *(void **)((u8 *)s3 + 0x450) = NULL;
    }
    func_80005014(&s3[2], &s4[2], &s3[1], &s3[3]);
    func_80005014(&s3[4], &s4[4], &s3[3], &s3[5]);
    func_80005014(&s3[7], &s4[7], &s3[6], &s3[1]);
    func_80005014(&s3[14], &s4[14], &s3[13], &s3[1]);
    func_80005014(&s3[11], &s4[11], &s3[9], &s3[12]);
    func_80005014(&s3[16], &s4[16], &s3[17], &s3[19]);
    func_80005014(&s3[1], &s4[1], &s3[7], &s3[14]);
    *(f32 *)(*(u8 **)((u8 *)s3 + 0xA64) + 0x10) -= 5.0f;
    *(f32 *)(*(u8 **)((u8 *)s3 + 0x1068) + 0x10) -= 5.0f;
    *(f32 *)(*(u8 **)((u8 *)s3 + 0x2A8) + 0x14) = *(f32 *)(*(u8 **)((u8 *)s3 + 0x384) + 0x14);
    *(f32 *)(*(u8 **)((u8 *)s3 + 0x618) + 0x24) = -5.0f;
    *(f32 *)(*(u8 **)((u8 *)s3 + 0xC1C) + 0x24) = -5.0f;
    *(f32 *)(*(u8 **)((u8 *)s3 + 0x53C) + 0x24) = -7.0f;
    *(f32 *)(*(u8 **)((u8 *)s3 + 0xB40) + 0x24) = -7.0f;
    *(f32 *)(*(u8 **)((u8 *)s3 + 0x6F4) + 0x24) = 7.0f;
    *(f32 *)(*(u8 **)((u8 *)s3 + 0xCF8) + 0x24) = 7.0f;
}
