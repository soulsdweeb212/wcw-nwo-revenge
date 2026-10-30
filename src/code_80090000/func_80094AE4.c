/* @header
 * func_80094AE4
 * VRAM 0x80094AE4 | ROM 0x41254 | size 0x7E8
 * asm: asm/nonmatchings/code_80090000/func_80094AE4.s
 */
#include "common.h"

typedef struct { u32 w0, w1; } Gw4AE4;

typedef struct {
    u16 id;
    u16 count;
    u16 flags;
    u16 f6;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 fE;
} Sub4AE4;

typedef struct {
    void *f0;
    u8 pad4[0x18];
    f32 f1C[16];
    u8 pad5C[0x80];
} Out4AE4;

typedef struct {
    u8 pad0[0x18];
    u8 f18;
    u8 pad19[0x147];
    s16 f160, f162, f164, f166, f168, f16A, f16C, f16E, f170, f172;
    s32 f174;
} Ptc4AE4;

typedef struct { s16 a[3]; s16 count; } Cnt4AE4;

extern s32 D_800C9094;
extern Out4AE4 *D_800DB674;
extern Out4AE4 *D_800DB678;
extern Out4AE4 *D_800DB67C;
extern Sub4AE4 *D_800DB684;
extern s32 D_800DB688;
extern void *D_800DB69C;
extern void *D_800DB6A0;
extern Gw4AE4 *D_800DB8AC;
extern Gw4AE4 *D_800DB8B0;
extern s32 D_800DBD40;
extern Ptc4AE4 D_800D6D50[];
extern Out4AE4 D_800DB3E0[];
extern const f64 D_800D6010, D_800D6018, D_800D6020, D_800D6028, D_800D6030, D_800D6038, D_800D6040, D_800D6048;
extern Cnt4AE4 D_800E74CC;
extern s32 D_800E74E8;
extern f32 D_800E74F8, D_800E74FC, D_800E7500, D_800E7504;
typedef struct { f32 x, y, z, w; } Vec4AE4;
extern Vec4AE4 D_800E7508;
extern s32 D_800E79BC;
extern s32 D_800E7BEC;
extern s32 D_800E7CD8;
extern s32 D_800E9F70;
extern u8 sceneNodeCallback5C50[];
extern u8 D_800C9C70[];

void buildScaledRotationTranslationMatrix(void *, f32, f32, f32, f32, f32, f32, f32);
f32 sinf(f32);
void func_80090384(s32, s32, s32);
void func_800936DC(s32);
void func_800945E0(s32);
void func_800948BC(s32);
void func_8009F800(Gw4AE4 **, s32, Cnt4AE4 *);
void releaseHeapBlock(void *);

static __inline__ void spawnParticle4AE4(s32 x, s32 z, s32 life, s32 a, s32 c, s32 b, s32 flags) {
    s32 i;
    Ptc4AE4 *p;

    for (i = 0, p = D_800D6D50; i < 0x30; i++, p++) {
        if (p->f160 < 0) {
            break;
        }
    }
    if (i == 0x30) {
        return;
    }
    p->f170 = -0xE10;
    p->f160 = 0;
    p->f166 = life;
    p->f162 = a;
    p->f16C = x;
    p->f16E = z;
    p->f172 = flags;
    p->f168 = 0x320;
    p->f16A = b;
    p->f164 = c;
    p->f174 = 0;
}

void func_80094AE4(Out4AE4 *arg0, Out4AE4 *arg1, s32 arg2) {
    s32 k;
    s32 i;
    f32 unused[20];
    Out4AE4 *out = D_800DB674;
    Sub4AE4 *sub;
    Ptc4AE4 *p;
    Out4AE4 *o;
    s32 j;
    s32 rot;
    f32 sr;
    f32 *pv;
    void *dl;
    Gw4AE4 *g;
    u32 tq;

    D_800DB8AC = (Gw4AE4 *)((u8 *)D_800DB8B0 + D_800C9094 * 0x3000);
    switch (D_800DB688) {
    case 6:
        k = 0;
        for (sub = D_800DB684; sub->count != 0; sub++, out++) {
            if (sub->flags & 0x4000) {
                if (D_800E7CD8 & 1) {
                    rot = (arg2 * 40) % 360;
                } else {
                    rot = 0;
                }
                buildScaledRotationTranslationMatrix(out->f1C, sub->fE ? (f32)-rot : (f32)rot, sub->fE, 0.0f, 1.0f, sub->f8, sub->fA, sub->fC);
                if ((D_800E7CD8 & 2) && !((arg2 + k) & 0xF)) {
                    spawnParticle4AE4(sub->f8, sub->fC, 0x19, 0x30, 0x55, 0x30, ((-(sub->fE != 0)) & 0xC01) | 0x401);
                }
                do { k++; } while (0);
            }
        }
        buildScaledRotationTranslationMatrix(D_800DB678->f1C, 0.0f, D_800E7508.w, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
        break;
    case 7:
    case 8:
        sr = sinf((((arg2 * 6) & 0x3FF) * 360) * D_800D6010) * D_800D6018 + D_800D6020;
        buildScaledRotationTranslationMatrix(D_800DB67C->f1C, 0.0f, 0.0f, 0.0f, sr, 0.0f, 0.0f, 0.0f);
        buildScaledRotationTranslationMatrix(D_800DB678->f1C, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, sr * D_800D6028 - D_800D6028, 0.0f);
        break;
    }

    if (D_800E9F70 != D_800DB688) {
        if (D_800E9F70 < 0 || D_800E74E8 != 0) {
            D_800E7504 = 0.0f;
            if (D_800DB688 >= 0) {
                D_800DB688 = -2;
            }
        }
        if (D_800DB688 < 0) {
            if (D_800DB688 == -1) {
                p = D_800D6D50;
                for (j = 0; j < 0x30; j++, p++) {
                    p->f18 |= 0x80;
                    p->f160 = -1;
                    p->f174 = 0;
                    p->f162 = 0;
                    p->f166 = 0;
                }
                if (D_800DB69C != 0) {
                    releaseHeapBlock(D_800DB69C);
                    D_800DB69C = 0;
                }
                if (D_800DB6A0 != 0) {
                    releaseHeapBlock(D_800DB6A0);
                    D_800DB6A0 = 0;
                }
                D_800DBD40 = 0;
                D_800DB688 = D_800E9F70;
                if (D_800E9F70 >= 0) {
                    func_800936DC(D_800E9F70);
                    for (i = 0; i < 300; i++) {
                        func_800948BC(i);
                        func_80090384(0, 0, 1);
                    }
                    if (D_800E74E8 < 0) {
                        D_800E7504 = 1.0f;
                    } else if (D_800E74E8 > 0) {
                        D_800E7504 = D_800E74E8 * D_800D6030;
                    }
                }
            } else {
                pv = &D_800E7504;
                *pv -= D_800D6038;
                if (*pv < 0.0f) {
                    *pv = 0.0f;
                    D_800DB688 = -1;
                }
            }
        } else {
            D_800E7BEC = 0;
            D_800DB688 = -2;
        }
    } else if (D_800E9F70 >= 0 && D_800E74E8 == 0) {
        pv = &D_800E7504;
        *pv += D_800D6040;
        if (*pv > D_800D6048) {
            *pv = 1.0f;
        }
    }

    if (D_800DB688 >= 0) {
        func_800945E0(D_800E79BC);
    }
    if (D_800E9F70 >= 0) {
        buildScaledRotationTranslationMatrix(arg1->f1C, 1.0f, 0.0f, 0.0f, 0.3f, 0.0f, 0.0f, 0.0f);
        buildScaledRotationTranslationMatrix(arg0->f1C, D_800E7508.x, D_800E7508.y, D_800E7508.z, D_800E7504, D_800E74F8, D_800E74FC, D_800E7500);
        func_800948BC(arg2);
    }
    tq = (u32)arg0 & 1;
    if (tq >> 1) {
        func_800948BC(0);
    }
    func_80090384(D_800C9094, D_800E79BC / 2 + 0x80, 0);
    dl = sceneNodeCallback5C50;
    if (D_800DB688 == -1) {
        dl = D_800C9C70;
    }
    for (k = 0; k < 3; k++) {
        o = &D_800DB3E0[k];
        if (k == 1 && D_800E74CC.count != 0) {
            o->f0 = D_800DB8AC;
            func_8009F800(&D_800DB8AC, D_800E74CC.count * 2 / 3, &D_800E74CC);
            g = D_800DB8AC++;
            g->w0 = 0xDE000000;
            g->w1 = (u32)dl;
            g = D_800DB8AC++;
            g->w0 = 0xDF000000;
            g->w1 = 0;
        } else {
            o->f0 = dl;
        }
    }
    D_800C9094 ^= 1;
}
