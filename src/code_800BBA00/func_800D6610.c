#include "common.h"

extern s32 D_800FABD8;
extern u16 D_800E3F84[];
extern u16 D_800E3F8C[];
extern u8 D_80030560[];
extern u8 D_8007C438[];

typedef struct { f32 x; f32 y; } Nw2Vec2C50;
extern Nw2Vec2C50 D_800E3C50[];

extern void func_800D36E8(f32, f32);

/* Compute the heading from the entity position toward quadrant-table entry arg1. */
void func_800D6610(u8 *arg0, s32 arg1) {
    s32 i = (s16)arg1;

    func_800D36E8(D_800E3C50[i].x - *(f32 *)(arg0 + 0x6C),
                  D_800E3C50[i].y - *(f32 *)(arg0 + 0x74));
}
