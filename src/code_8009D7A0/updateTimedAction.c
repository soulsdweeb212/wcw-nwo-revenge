/* @header
 * updateTimedAction  (originally func_800A6108)
 * VRAM 0x800A6108 | ROM 0x995A8 | size 0x13C
 * asm: asm/nonmatchings/code_8009D7A0/updateTimedAction.s
 */
#include "common.h"

typedef struct {
    s32 f0;
    s16 timer;    /* @0x4 */
    s16 f6;
    s16 animId;   /* @0x8: model/animation id (0xF5A/0xF5B here) */
    s16 padA;
    s16 state;    /* @0xC: 0 = start, 1 = running */
    s16 fE;
    u8 pad16[6];
    s16 counter;  /* @0x16: ticks elapsed in the current action */
    u8 pad18[0x40];
    s32 heading;  /* @0x58: value being stepped */
    u8 pad5C[0x2EC];
    s32 step;     /* @0x348: per-tick delta */
} Nw2ObjA6108;

extern void *D_800EB408;
extern s32 D_800F9B0C;
s32 func_800D2B64(void *, f32, u16, s32);
s32 func_800D3684(s32, s32);
s32 func_800D35B0(s32, s32);
s32 func_800D4D44(void *, s32, s32);
void func_800D427C(void *, s32, s32);
void func_800A6C48(void *, s32);

#define OBJ ((Nw2ObjA6108 *)D_800EB408)

/* Tick a timed action: on entry (state 0) set the per-tick step to 1/20 of the
 * remaining distance and fall into state 1, which steps the value toward its
 * target. After 0x15 ticks it issues the follow-up command (0x2D for model
 * 0xF5A, otherwise 1). */
void updateTimedAction(void)
{
    func_800D2B64(D_800EB408, 1.0f, 0, 2);

    switch (OBJ->state) {
    case 0:
        OBJ->counter = 0;
        OBJ->step = func_800D3684(OBJ->step, OBJ->heading) / 20;
        OBJ->state++;
    case 1:
        OBJ->heading = func_800D35B0(OBJ->heading, OBJ->step);
        if (OBJ->animId == 0xF5B && OBJ->timer <= 0) {
            func_800D427C(D_800EB408, (s16)func_800D4D44(D_800EB408, 1, D_800F9B0C), 2);
        }
        if (++OBJ->counter >= 0x15) {
            if (OBJ->animId == 0xF5A)
                func_800A6C48(D_800EB408, 0x2D);
            else
                func_800A6C48(D_800EB408, 1);
        }
        break;
    }
}
