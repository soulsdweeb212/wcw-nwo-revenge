#include "common.h"

/* Action state machine for D_800FAF5C (switch on +0x0C):
 *  0 -> enter the action clip selected by D_800FAF8E[mode]: 0x98 when bits
 *       0xF00 are set, else 0x97; then fall through;
 *  1 -> clear the global ability mask bit D_800E3F20[mode] and search for a
 *       nearby target with func_800C2CDC(.., 0x15); if one is found enter the
 *       paired state and start the action via func_800C3A78(.., 0x4000), then
 *       fall through;
 *  2 -> move the entity and choose the lunge distance: a plain push when the
 *       range flags are set, otherwise a per-action distance table keyed on
 *       the action id (+0x0A). */
typedef struct {
    u8 pad0[6];
    s16 f6;
    u8 pad8[2];
    u16 fA;
    s16 fC;
    u8 padE[0x12];
    u64 flags;
    u8 pad28[0x349];
    u8 f371;
} Nw2ActionNode;

extern Nw2ActionNode *D_800FAF5C;
extern u8 D_800F9D10[];
extern s32 D_800E3F20[];
extern s32 D_800FABD8;
extern s8 D_800FADB8;
extern u16 D_800FAF8E[];
void func_800D427C(void *, s32, s32);
void func_800A7D1C(void *, s32);
void func_800A7F6C(void *, s32);
void func_800A7C40(void *, s8, s16);
s16 func_800D5438(void *, s32);
s8 func_800C2CDC(void *, s32);
void func_800C3A78(void *, void *, s32);
void func_800D25D0(void *, f32);
void func_800D2B64(void *, f32, s32, s32);
void func_800A7188(void *);

void updateActionStateC707C(void)
{
    s32 id;
    s32 anim;
    s32 idx;
    f32 scale;
    Nw2ActionNode *p;

    switch (D_800FAF5C->fC) {
    case 0:
        {
            s8 k = D_800FADB8;
            s32 a2;
            if (D_800FAF8E[k] & 0xF00) {
                a2 = 0x98;
            } else {
                a2 = 0x97;
            }
            func_800A7C40(D_800FAF5C, k, a2);
            func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 0), 3);
            func_800A7F6C(D_800FAF5C, 0);
            D_800FAF5C->fC = D_800FAF5C->fC + 1;
        }
    case 1:
        {
            s8 k = D_800FADB8;
            s8 r;
            D_800FABD8 &= ~D_800E3F20[k];
            r = func_800C2CDC(D_800FAF5C, 0x15);
            if (r != -1) {
                D_800FAF5C->fC = D_800FAF5C->fC + 1;
                func_800C3A78(D_800FAF5C, &D_800F9D10[r * 0x3B0], 0x4000);
            }
        }
    case 2:
        scale = 2.0f;
        func_800D25D0(D_800FAF5C, scale);
        p = D_800FAF5C;
        if ((p->flags & 0x0ULL) != 0 || (p->flags & 0x100) != 0) {
            func_800D2B64(p, scale, 0, 0xFFFFE);
        } else {
            switch ((s16)(p->fA - 7)) {
            case 15:
                if (p->f6 > p->f371) {
                    func_800D2B64(p, 2.0f, 0, 0xE);
                }
                break;
            case 0: case 24: case 25: case 26: case 29: case 30: case 31: case 78: case 79:
                if (p->f6 > p->f371) {
                    func_800D2B64(p, 4.0f, 0, 0xFFFFE);
                } else {
                    func_800D2B64(p, 2.0f, 0, 0xE);
                }
                break;
            case 1: case 23: case 27: case 28: case 32:
                func_800D2B64(D_800FAF5C, 2.0f, 0, 0xE);
                break;
            }
        }
        func_800A7188(D_800FAF5C);
        break;
    }
}
