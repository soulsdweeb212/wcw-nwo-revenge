/* @header
 * func_800A553C
 * VRAM 0x800A553C | ROM 0x989DC | size 0x1F0
 * asm: asm/nonmatchings/code_8009D7A0/func_800A553C.s
 */
#include "common.h"

/* Three-stage item/weapon action driver on self record D_800EB408:
 * 0) spawn via func_800CE124 and arm a sub-mode from the flag word,
 * 1) wait for func_800CE2C8 to signal completion,
 * 2) run the 4-frame hit window and clear the action when the timer expires. */
typedef struct {
    s32 f0;
    s16 f4, f6;
    s32 f8;
    s16 state, fE;
    u8 pad10[0x1C];
    u32 flags;
} Nw2F408c;

typedef struct {
    u8 pad[0x391];
    s8 f391;
} Nw2E418;

s32 func_800D2BEC(void *, s32, void *, f32, u16, s32);
void func_800CE124(void *, s32, void *);
s32 func_800CE2C8(void *, s32, void *, void *, void *);
void func_800A7F6C(void *, s32);
void func_800A837C(void *);
s16 func_800D5438(void *, s16);
void func_800D427C(void *, s16, s32);
void func_800D4AD0(void *);
void func_800A6C48(void *, s32);
void addEntityHealthDelta(void *, s32);
extern s32 D_800EB40C;
extern void *D_800EB418;
extern u8 D_800F9B18[];
extern s8 D_800FABE4;
extern s8 D_800FADB8;

#define P ((Nw2F408c *)D_800EB408)
#define E418 ((Nw2E418 *)D_800EB418)

void func_800A553C(void) {
    s16 state;
    s16 mode;
    u32 flags;

    state = P->state;
    switch (state) {
    case 0:
        func_800CE124(D_800EB408, D_800EB40C, D_800F9B18 + D_800FADB8 * 16);
        flags = P->flags;
        if (flags & 0x1800) {
            mode = (flags >> 14) & 1;
        }
        if (flags & 0x2000) {
            mode = (flags >> 6) & 1;
        }
        func_800D427C(D_800EB408, func_800D5438(D_800EB418, mode), 2);
        func_800A7F6C(D_800EB408, 0x41);
        func_800A837C(D_800EB408);
        P->state++;
    case 1:
        if ((s8)func_800CE2C8(D_800EB408, D_800EB40C, D_800EB418,
                D_800F9B18 + D_800FADB8 * 16, D_800F9B18 + D_800FABE4 * 16)) {
            P->state++;
        }
        break;
    case 2:
        func_800D2BEC(D_800EB408, D_800EB40C, D_800EB418, 4.0f, 0, 0xFFFFE);
        if (P->f4 == 1) {
            addEntityHealthDelta(D_800EB408, E418->f391);
        }
        if (P->f4 <= 0) {
            func_800D4AD0(D_800EB408);
            func_800A6C48(D_800EB408, 0x2B);
        }
        break;
    }
}
