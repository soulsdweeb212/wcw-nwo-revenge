#include "common.h"

typedef struct { u8 pad[0x44]; s32 heading; } Nw2ActionFABD0;
extern s32 D_800E3C90[];
extern f32 D_800E3C50[][2];
extern f32 D_800E3C54[][2];
extern Nw2ActionFABD0 *D_800FABD0;
extern void *D_800FAF58;
s32 func_800D3550(s32);
s32 func_800D3684(s32, s32);
void func_800D3890(void *, void *, void *);
s16 func_800AEBF0(void) {
    f32 pos[3];
    Nw2DirectionResult res;
    s16 i;
    s32 angle;
    for (i = 0; i < 4; i++) {
        angle = func_800D3550(func_800D3684(D_800E3C90[i], D_800FABD0->heading));
        if (angle < 0xAA) return i * 2;
    }
    for (i = 0; i < 4; i++) {
        pos[0] = D_800E3C50[i][0];
        pos[2] = D_800E3C54[i][0];
        func_800D3890((u8 *)D_800FAF58 + 0x6C, pos, &res);
        angle = func_800D3550(func_800D3684(res.angle, D_800FABD0->heading));
        if (angle < 0xAA) return i * 2 + 1;
    }
    return -1;
}
