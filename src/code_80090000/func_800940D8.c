#include "common.h"

extern s32 D_800E8210;
extern s32 D_800E74C4;
extern f32 D_800E7504;
extern s32 D_800DBD40;
extern u8 func_800DB4FC[];

typedef struct {
    void *ent;
    void *node;
    u8 pad8[4];
    u16 kind;
    u16 off;
    s16 phase;
    u8 padx[6];
} Nw2Rec940D8;
extern Nw2Rec940D8 D_800DB8C0[];

void func_800B82B8(void *, void *, void *, void *, void *, void *);
void func_8001B3EC(void *, f32, f32, f32, f32 *, f32 *, f32 *);
void buildScaledRotationTranslationMatrix(void *, f32, f32, f32, f32, f32, f32, f32);
f32 sinf(f32);
f32 cosf(f32);

extern const double D_800D5FB0, D_800D5FB8, D_800D5FC0, D_800D5FC8, D_800D5FD0, D_800D5FD8, D_800D5FE0, D_800D5FE8, D_800D5FF0, D_800D5FF8, D_800D6000;
#define K_B0 D_800D5FB0
#define K_B8 D_800D5FB8
#define K_C0 D_800D5FC0
#define K_C8 D_800D5FC8
#define K_D0 D_800D5FD0
#define K_D8 D_800D5FD8
#define K_E0 D_800D5FE0
#define K_E8 D_800D5FE8
#define K_F0 D_800D5FF0
#define K_F8 D_800D5FF8
#define K_00 D_800D6000

void func_800940D8(void) {
    f32 fs0, fs1, fs5;
    s32 buf[6];
    f32 vec[3];
    f32 fp;
    s32 i;
    u16 *s0;
    s32 lo;
    u16 s1;
    s32 s2;
    Nw2Rec940D8 *p;
    void *node;
    void *ent;
    s32 m;
    register s32 ang;
    f32 sv;

    p = D_800DB8C0;
    func_800B82B8(&buf[0], &buf[1], &buf[2], &buf[3], &buf[4], &buf[5]);
    if (D_800E8210 >= 0) {
        s0 = *(u16 **)(*(u8 **)(func_800DB4FC + 0x184) + D_800E8210 * 4 + 0x1C);
    }
    for (i = 0; i < D_800DBD40; i++, p++) {
        ent = p->ent;
        node = p->node;
        s2 = p->phase;
        if (*(u16 *)((u8 *)ent + 6) & 0x8000) {
            continue;
        }
        if (p->off != 0) {
            continue;
        }
        switch (p->kind) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            s1 = 0;
            if (0 <= D_800E8210) {
                s1 = s0[i];
            }
            break;
        default:
            s1 = *(u16 *)((u8 *)ent + 6);
            break;
        }
        fs0 = D_800E7504;
        fs1 = 0.0f;
        fs5 = fs1;
        fp = fs1;
        func_8001B3EC((u8 *)node + 0x5C, fs1, fs1, fs1, &vec[0], &vec[1], &vec[2]);
        lo = s1 & 0xFF;
        if (0 > D_800E74C4) {
            fs0 = fs0 * K_B0;
        } else {
            switch (s1 & 0xFF00) {
            case 0x1000:
                ang = (((s2 + (s1 & 0xF0)) << 2) & 0x3FF) * 0x168;
                sv = sinf(ang * K_B8);
                fs1 = (s1 & 0xF) * K_C8 + sv * K_D0;
                break;
            case 0x100:
                ang = ((s2 << 4) & 0x3FF) * 0x168;
                sv = sinf(ang * K_B8);
                fs0 = fs0 * (sv * K_D8 + K_C0);
                break;
            case 0x200:
                m = s2 + lo;
                if (m & 0x2E) {
                    fs0 = fs0 * K_B0;
                } else {
                    fs0 = fs0 * K_E0;
                }
                break;
            case 0x300:
                m = s2 + lo;
                if (m & 0x3E) {
                    fs0 = fs0 * K_B0;
                } else {
                    fs0 = fs0 * K_E8;
                }
                break;
            case 0x400:
                m = ((s2 & 0x7F) * 0x5A0) * K_F0;
                if (s1 & 0x80) {
                    m = -m;
                }
                fs1 = m;
                sv = cosf(m * K_F8);
                fs0 = fs0 * (sv * K_00 + K_C0);
                break;
            case 0x500: {
                s32 d = 1 << (s1 & 0xF);
                register ang = (((s2 * 2) / d) & 0x3FF) * 0x168;
                sv = sinf(ang * K_B8);
                m = (f32)(d * 180) * sv;
                if (s1 & 0x80) {
                    m = -m;
                }
                fs1 = m;
                sv = cosf(m * K_F8);
                fs0 = fs0 * (sv * K_00 + K_C0);
                break;
            }
            case 0x600:
                if (s1 & 0x10) {
                    m = s2 + (s1 & 7) * 8;
                    if (!(m & 0x38)) break;
                } else {
                    m = s2 + (s1 & 0xF) * 8;
                    if (!(m & 0x78)) goto store;
                    if (!((m + 8) & 0x78)) break;
                }
                fs0 = fs0 * K_B0;
                break;
            case 0x800:
                fs0 = fs0 * K_B0;
                break;
            }
        }
    store:
        buildScaledRotationTranslationMatrix((u8 *)node + 0x5C, fp, fs5, fs1, fs0, vec[0], vec[1], vec[2]);
    }
}
