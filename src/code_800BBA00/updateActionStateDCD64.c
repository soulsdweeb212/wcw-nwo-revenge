#include "common.h"

/* Action state machine for D_800FAF5C (switch on +0x0C):
 *  0 -> enter clip 0xE0 and fall through;
 *  1 -> clear the global ability mask D_800E3F20[mode]; once the sub-timer
 *       +0x06 reaches +0x370 set flag 0x100, then advance when
 *       func_800DB4FC reports the interaction finished;
 *  2 -> raise flag 0x80000000000, and when +0x06 reaches +0x371 lower it and
 *       push forward; once the timer +0x04 expires, either run the paired
 *       finish (func_800A7D1C 0x23, func_800B68A0, optional addEntityHealthDelta,
 *       then beginEntityActionA8D8C) or just end with action 0x2B. */
typedef struct {
    u8 pad0[4];
    s16 f4;
    s16 f6;
    u8 pad8[4];
    s16 fC;
    u8 padE[0x12];
    u64 flags;
    u8 pad28[0x348];
    u8 f370;
    u8 f371;
    u8 pad372[0x30];
    s8 f3A2;
} Nw2ActionCD64;

extern Nw2ActionCD64 *D_800FAF5C;
extern s8 D_800FADB8;
extern s32 D_800E3F20[];
extern s32 D_800FABD8;
extern s32 D_800F9B00;
void func_800A7C40(void *, s8, s16);
s16 func_800D5438(void *, s32);
void func_800D427C(void *, s32, s32);
void func_800A7F6C(void *, s32);
s8 func_800DB4FC(void *, s32);
void func_800D2B64(void *, f32, s32, s32);
void func_800D4AD0(void *);
void func_800A7D1C(void *, s32);
void func_800B68A0(void *, void *, void *);
s8 func_800D4CC4(void *);
void addEntityHealthDelta(void *, s8);
void beginEntityActionA8D8C(void *);
void func_800A6C48(void *, s32);

void updateActionStateDCD64(void) {
    Nw2ActionCD64 *s;

    switch (D_800FAF5C->fC) {
    case 0:
        func_800A7C40(D_800FAF5C, D_800FADB8, 0xE0);
        func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 0), 3);
        func_800A7F6C(D_800FAF5C, 0);
        D_800FAF5C->fC = D_800FAF5C->fC + 1;
    case 1:
        D_800FABD8 &= ~D_800E3F20[D_800FADB8];
        if (D_800FAF5C->f6 >= D_800FAF5C->f370) {
            D_800FAF5C->flags = (D_800FAF5C->flags & 0xFFFFFFFFFFFFFF7FULL) | 0x100ULL;
        }
        if (func_800DB4FC(D_800FAF5C, D_800F9B00) != 0) {
            D_800FAF5C->fC = D_800FAF5C->fC + 1;
        }
    case 2: {
        u64 flags = D_800FAF5C->flags | 0x80000000000ULL;
        D_800FAF5C->flags = flags;
        if (D_800FAF5C->f6 >= D_800FAF5C->f371) {
            D_800FAF5C->flags = flags & 0xFFFFF7FFFFFFFFFFULL;
            func_800D2B64(D_800FAF5C, 4.0f, 0, 0xFFFFE);
        }
        if (D_800FAF5C->f4 <= 0) {
            func_800D4AD0(D_800FAF5C);
            s = D_800FAF5C;
            if (s->fC == 1) {
                func_800A7D1C(s, 0x23);
                func_800B68A0(D_800FAF5C, D_800FAF5C, D_800FAF5C);
                if (func_800D4CC4(s) != 0) {
                    addEntityHealthDelta(s, s->f3A2);
                }
                beginEntityActionA8D8C(s);
            } else {
                func_800A6C48(s, 0x2B);
            }
        }
        break;
    }
    }
}
