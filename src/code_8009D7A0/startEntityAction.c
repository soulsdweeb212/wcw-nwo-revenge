/* @header
 * startEntityAction  (originally func_800A9924)
 * VRAM 0x800A9924 | ROM 0x9CDC4 | size 0x438
 * asm: asm/nonmatchings/code_8009D7A0/func_800A9924.s
 */
#include "common.h"

/* Begin an action for the current entity. Resolves the entity (D_800FAF58),
 * its target (D_800F9B60), the entity it faces (D_800FAF80) and the facing
 * deal (D_800FADDC) from D_800F9D10 records, fills the action context
 * (D_800FABD0) with relative vectors/angles, picks the action id from the
 * relative-facing case table, and dispatches through D_800E3660. */
extern s8 D_800FADB8;
extern s8 D_800FABE4;
extern u8 D_800F9D10[];
extern u8 D_800F9B88[];
extern s8 D_800FA063[];
extern u8 *D_800FAF58;
extern u8 *D_800F9B60;
extern u8 *D_800FAF80;
extern u8 *D_800FADDC;
extern f32 D_800E3C50[];
extern f32 D_800E3C54[];
extern f64 D_800E4BF0;
extern void (*D_800E3660[])(void);

typedef struct {
  u8 pad0[2];
  s16 f2;
  u8 pad4[2];
  s16 f6;
  s16 f8;
  u8 padA[2];
  u8 fC;
  u8 padD[7];
  u16 f14;
  u8 pad16[6];
  s16 f1C;
  s16 f1E;
  u8 pad20[2];
  s16 f22;
  u8 pad24[6];
  s16 f2A;
  s16 f2C;
  u8 pad2E[2];
  u16 f30;
  u8 pad32[6];
  f32 f38[4];
  f32 f48[4];
  f32 f58;
} Nw2Act;

extern Nw2Act *D_800FABD0;

s32 func_800AD7B0(void *, void *);
void func_800AD958(s32);
void func_800AD9E8(s32);
s32 func_800ADAE4(void *);
s32 func_800ADB44(void);
f32 func_800D3890(void *, void *, void *);
f32 func_800D3EEC(void *, void *, s32);
s8 func_800D4198(s16);
s32 getXZDirectionQuadrant(f32 *);

void startEntityAction(void)
{
    s16 i;
    s16 k;
    f32 vec[4];
    Nw2Act *act;

    D_800FAF58 = D_800F9D10 + D_800FADB8 * 0x3B0;
    D_800F9B60 = D_800F9D10 + D_800FABE4 * 0x3B0;
    D_800FAF80 = D_800F9D10 + *(s8 *)(D_800FAF58 + 0x355) * 0x3B0;
    D_800FADDC = D_800F9D10 + D_800FA063[*(s8 *)(D_800FAF58 + 0x355) * 0x3B0] * 0x3B0;
    act = (Nw2Act *)(D_800F9B88 + D_800FADB8 * 0x60);
    D_800FABD0 = act;
    act->fC = 0;
    act->f6 = 0;
    act->f8 = 0;
    D_800FABD0->f14 = func_800AD7B0(D_800FAF58, D_800FAF58);
    D_800FABD0->f22 = func_800AD7B0(D_800F9B60, D_800FAF58);
    func_800ADB44();
    func_800D3890(D_800FAF58 + 0x6C, D_800F9B60 + 0x6C, D_800FABD0->f38);
    i = 0;
loop:
    k = i;
    vec[0] = D_800E3C50[k * 2];
    vec[2] = D_800E3C54[k * 2];
    D_800FABD0->f48[k] = func_800D3890(D_800FAF58 + 0x6C, vec, NULL);
    i++;
    if (i < 4) goto loop;
    D_800FABD0->f58 = (f32)((f64)func_800D3EEC(D_800F9B60 + 0x4C, D_800FAF58 + 0x6C, *(s32 *)(D_800F9B60 + 0x58)) + D_800E4BF0);
    D_800FABD0->f1C = func_800ADAE4(D_800FAF58);
    D_800FABD0->f2A = func_800ADAE4(D_800F9B60);
    D_800FABD0->f1E = getXZDirectionQuadrant((f32 *)(D_800FAF58 + 0x6C));
    D_800FABD0->f2C = getXZDirectionQuadrant((f32 *)(D_800F9B60 + 0x6C));
    *(u64 *)(D_800FAF58 + 0x20) &= ~0x10000000ULL;
    switch ((s16)(D_800FABD0->f14 - 3)) {
    case 0: func_800AD958(0x10); break;
    case 2: func_800AD958(0x11); break;
    case 1: case 5: case 11: func_800AD9E8(0x12); break;
    case 6: case 9: case 19: func_800AD9E8(0x25); break;
    case 17: func_800AD9E8(0x32); break;
    case 18: func_800AD9E8(0x33); break;
    case 12: func_800AD9E8(0x26); break;
    case 13: func_800AD9E8(0xE); break;
    case 16: func_800AD9E8(0x8); break;
    }
    if (*(s16 *)(D_800F9B60 + 0xA) == 0x29) {
        if (func_800D4198(0x12C)) func_800AD9E8(0x22);
        else func_800AD9E8(0x27);
    }
    if ((*(u64 *)(D_800FAF58 + 0x20) & 0x200ULL) && (*(u64 *)(D_800FAF58 + 0x20) & 0x80ULL)) {
        D_800FABD0->f30 += 1;
        if ((s16)D_800FABD0->f30 >= 0x97) {
            D_800FABD0->f30 = 0;
            func_800AD958(0);
        }
    } else {
        D_800FABD0->f30 = 0;
    }
    ((void (*)(void))D_800E3660[D_800FABD0->f2])();
}
