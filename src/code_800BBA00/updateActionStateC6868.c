#include "common.h"

/* D_800FAF5C action state machine (cases 0..2): state 0 selects the knockdown
 * animation id + action kind from the flag word and D_800F9D10 state; state 1 finds
 * a nearby victim and hands its 0x3B0-stride record to func_800C3A78; state 2 applies
 * the per-animation gravity/knockback rate. Case 1 falls through to 2. */
typedef struct {
    u8 pad0[6];
    s16 f6;
    s16 f8;
    u16 fA;
    s16 state;
    u8 padE[0x12];
    u64 flags;
    u8 pad28[0x349];
    u8 f371;
} Nw2ActionC6868;

extern Nw2ActionC6868 *D_800FAF5C;
extern u8 D_800F9D10[];
void func_800D427C(void *, s32, s32);
void func_800A7D1C(void *, s32);
void func_800A7F6C(void *, s32);
s8 func_800C2CDC(void *, s32);
void func_800C3A78(void *, void *, s32);
void func_800D25D0(void *, f32);
void func_800D2B64(void *, f32, s32, s32);
void func_800A7188(void *);

void updateActionStateC6868(void)
{
    s16 id;
    s16 anim;
    s32 kind;
    s32 idx;
    f32 scale;
    Nw2ActionC6868 *p;

    switch (D_800FAF5C->state) {
    case 0:
        if (D_800FAF5C->flags & 0x2000000000000ULL) {
            id = 0x100D;
        } else if ((D_800FAF5C->flags & 0x0ULL) == 0) {
            id = 0x1005;
        } else {
            id = 0x100D;
        }
        kind = 0x47;
        if ((s16)(*(Nw2ActionC6868 **)0x800FAF5C)->fA == 0x23) {
            id = id + 1;
            kind = 0x48;
        }
        func_800D427C(D_800FAF5C, id, 3);
        switch ((s16)D_800FAF5C->f8) {
        case 0x1005: anim = 0x14; break;
        case 0x1006: anim = 0x15; break;
        case 0x100D: anim = 0x17; break;
        case 0x100E: anim = 0x18; break;
        }
        func_800A7D1C(D_800FAF5C, anim);
        func_800A7F6C(D_800FAF5C, kind);
        D_800FAF5C->state = D_800FAF5C->state + 1;
        break;
    case 1:
        idx = func_800C2CDC(D_800FAF5C, 3);
        if (idx != -1) {
            D_800FAF5C->state = D_800FAF5C->state + 1;
            func_800C3A78(D_800FAF5C, &D_800F9D10[idx * 0x3B0], 0x200);
        }
        /* fallthrough */
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
