#include "common.h"

/* Action state machine for D_800FAF5C (switch on +0x0C):
 *  0 -> pick the entry clip by the +0x20 weapon flag 0x0100000000000000
 *       (0xAC when the flag is clear, else 4) and play it, then fall through;
 *  1 -> clear the global ability mask bit D_800E3F20[+mode] and search for a
 *       nearby target with func_800C2CDC; if one is found enter the paired
 *       state and start the action via func_800C3A78, then fall through;
 *  2 -> move the entity and choose how far it lunges: a plain push when the
 *       range flags are set, otherwise a per-action distance table keyed on
 *       the action id (+0x0A). */
typedef struct {
    s8 f0;
    u8 pad1[5];
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
void func_800C5FBC(void *);
void func_800D25D0(void *, f32);
void func_800D2B64(void *, f32, s32, s32);
void func_800A7188(void *);

void updateActionStateC5D48(void)
{
    s8 targetIdx;
    s32 clip;
    f32 scale;
    Nw2ActionNode *p;

    switch (D_800FAF5C->fC) {
    case 0:
        if (D_800FAF5C->flags & 0x0100000000000000ULL) {
            clip = 4;
        } else if ((D_800FAF5C->flags & 0x0ULL) == 0) {
            clip = 0xAC;
        } else {
            clip = 4;
        }
        func_800A7C40(D_800FAF5C, D_800FAF5C->f0, clip);
        func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 0), 3);
        func_800A7F6C(D_800FAF5C, 0);
        D_800FAF5C->fC = D_800FAF5C->fC + 1;
    case 1:
        D_800FABD8 &= ~D_800E3F20[D_800FADB8];
        func_800C5FBC(D_800FAF5C);
        targetIdx = func_800C2CDC(D_800FAF5C, 1);
        if (targetIdx != -1) {
            D_800FAF5C->fC = D_800FAF5C->fC + 1;
            func_800C3A78(D_800FAF5C, &D_800F9D10[targetIdx * 0x3B0], 4);
        }
    case 2:
        scale = 2.0f;
        func_800D25D0(D_800FAF5C, scale);
        p = D_800FAF5C;
        if ((p->flags & 0x0ULL) != 0 || (p->flags & 0x100) != 0) {
            func_800D2B64(p, scale, 0, 0xFFFFE);
        } else {
            switch ((s16)(p->fA - 7)) {
            case 0:
            case 15:
                if (p->f6 > p->f371) {
                    func_800D2B64(p, 2.0f, 0, 0xE);
                }
                break;
            case 24:
            case 25:
            case 26:
            case 29:
            case 30:
            case 31:
            case 78:
            case 79:
                if (p->f6 > p->f371) {
                    func_800D2B64(p, 4.0f, 0, 0xFFFFE);
                } else {
                    func_800D2B64(p, 2.0f, 0, 0xE);
                }
                break;
            case 1:
            case 23:
            case 27:
            case 28:
            case 32:
                func_800D2B64(D_800FAF5C, 2.0f, 0, 0xE);
                break;
            }
        }
        func_800A7188(D_800FAF5C);
        break;
    }
}
