#include "common.h"

void loadTextureIntoCacheSlot(void *, s16, s16, s16, s16);
void func_80004F80(void *, s16, s16);
void func_80004FC0(void *);
void func_8000670C(void *, s16, s16);
void lookupResourceDescriptor(void *, u16);
extern u16 D_8006A2A4[];
extern s8 D_80031088[];
extern u16 *D_80031998[];
extern void ***D_80032B44[];
extern void ***D_800360F0[];
extern u8 D_80070458[];
extern s8 D_800706A4[];
extern s16 D_80073E90[];
extern u8 D_80073EB0[];
extern s16 D_8007DFB0[];
extern s16 D_8007DFBC[];

typedef struct {
    s16 f0;
    s16 f2;
    s16 f4;
    s16 f6;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 fE;
    s16 f10;
    s16 f12;
    s16 f14;
    s16 f16;
} Nw2C1B8Rec;

typedef struct { u8 data[0x2C]; } Slot2C1B8;

void func_8000C1B8(s16 arg0, s16 arg1) {
    s32 buf[4];
    u32 i;
    u16 w;
    s32 idx;
    s32 bank;
    u16 *a3;
    Nw2C1B8Rec *s3;
    s16 (*s4)[2];
    Slot2C1B8 *s5;
    s8 v;

    w = D_8006A2A4[arg0];
    bank = (w >> 8) & 0x1F;
    idx = (w & 0x1F) - 1;
    a3 = (u16 *)(idx * 2 + (u32)D_80031998[bank]);
    s3 = (Nw2C1B8Rec *)D_80032B44[bank][idx][D_8007DFB0[arg0]];
    s4 = (s16 (*)[2])D_800360F0[*a3 & 0x7F][D_8007DFBC[arg0]][s3->f16];
    s5 = (Slot2C1B8 *)(D_80073EB0 + arg0 * 0x3F4);
    if (arg1 == 0) {
        for (i = 1; i < 0xD; i++) {
            v = D_80031088[i];
            if (v >= 0) {
                loadTextureIntoCacheSlot(&s5[i], s4[v][2], s4[v][1], arg0, i);
            }
        }
        loadTextureIntoCacheSlot(&s5[4], s3->f8, s3->f6, arg0, 4);
        func_80004F80(&s5[5], s3->fC, s3->fA);
        if (s3->f12 != 0) {
            s32 sz;
            func_8000670C(D_80070458 + arg0 * 8, s3->f14, s3->f12);
            lookupResourceDescriptor(buf, s3->f12);
            sz = buf[2];
            D_800706A4[arg0] = 1;
            D_80073E90[arg0] = sz;
            return;
        }
        D_800706A4[arg0] = 0;
        return;
    }
    for (i = 0xD; i < 0x14; i++) {
        v = D_80031088[i];
        if (v >= 0) {
            loadTextureIntoCacheSlot(&s5[i], s4[v][2], s4[v][1], arg0, i);
            if (i != 0xF && s4[D_80031088[i]][2] < 0x9ED) {
                func_80004FC0(&s5[i]);
            }
        }
    }
    if (s3->f4 != 0) {
        func_80004F80(&s5[20], s3->f10, s3->fE);
    }
}
