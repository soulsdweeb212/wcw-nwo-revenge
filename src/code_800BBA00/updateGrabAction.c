/* @header
 * updateGrabAction  (originally func_800C61D8)
 * VRAM 0x800C61D8 | ROM 0xB9678 | size 0x240
 * asm: asm/nonmatchings/code_800BBA00/func_800C61D8.s
 */
#include "common.h"

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
} Nw2ActionC61D8;

extern Nw2ActionC61D8 *D_800FAF5C;
extern u8 D_800F9D10[];
extern s32 D_800E3F20[];
extern s32 D_800FABD8;
extern s8 D_800FADB8;
void func_800D427C(void *, s32, s32);
void func_800A7F6C(void *, s32);
void func_800A7C40(void *, s8, s16);
s16 func_800D5438(void *, s32);
s8 func_800C2CDC(void *, s32);
void func_800C3A78(void *, void *, s32);
void func_800D25D0(void *, f32);
void func_800D2B64(void *, f32, s32, s32);
void func_800A7188(void *);

/* Three-state grab action for D_800FAF5C: state 0 plays animation 0xB4 and
 * arms it; state 1 looks for a nearby target entity and, when one is found,
 * advances and attaches to its 0x3B0-byte record; state 2 re-aims the action,
 * applies a position/scale correction chosen by the animation id (with a
 * 4.0/2.0 scale depending on the height threshold), then updates it. */
void updateGrabAction(void)
{
    s32 id;
    s8 targetIndex;
    f32 scale;
    Nw2ActionC61D8 *p;

    switch (D_800FAF5C->fC) {
    case 0:
        func_800A7C40(D_800FAF5C, D_800FADB8, 0xB4);
        func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 0), 3);
        func_800A7F6C(D_800FAF5C, 0);
        D_800FAF5C->fC = D_800FAF5C->fC + 1;
    case 1:
        id = D_800FADB8;
        D_800FABD8 &= ~D_800E3F20[id];
        targetIndex = func_800C2CDC(D_800FAF5C, 1);
        if (targetIndex != -1) {
            D_800FAF5C->fC = D_800FAF5C->fC + 1;
            func_800C3A78(D_800FAF5C, &D_800F9D10[targetIndex * 0x3B0], 0x100);
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
