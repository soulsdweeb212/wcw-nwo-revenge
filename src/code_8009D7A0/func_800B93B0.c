#include "common.h"

/* Per-frame crowd/timer pair advance: decay the two D_800FAF84/D_800F9B58
 * counters, clamp them and pick which one to play on the audio/sfx tick, then
 * (once the pair has run out and an intro intro is over) roll a random check
 * to trigger the next event flag. Returns 1 when the state machine should
 * restart (func_800B8484), else 0. */
typedef struct { s16 a,b,c; } Obj3;
typedef struct { s16 a,b; } Obj2;
extern Obj3 D_800FAF84;
extern Obj2 D_800F9B58;
extern u16 D_800FADD0;
extern s8 D_8007E228[], D_800E399C[];
extern s8 D_8007E2BA;
void func_800DA850(void *,s16);
void func_800DA8B4(void *,s16,s16);
void func_80095CB0(s16,s16);
s32 func_800B8484(s32);
s8 func_800D4198(s16);
s8 func_800B93B0(void) {
func_800DA850(&D_800FAF84,30);
func_800DA850(&D_800F9B58,30);
if (D_8007E2BA == 0) {
if (D_800FAF84.a == 1000) func_800DA8B4(&D_800FAF84,1000,0);
if (D_800F9B58.a == 60) func_800DA8B4(&D_800F9B58,0,0);
func_80095CB0(D_800F9B58.b,D_800F9B58.a);
} else {
func_80095CB0(D_800FAF84.b,D_800FAF84.a);
if (D_800FAF84.a == D_800E399C[D_8007E2BA]) return (s8)func_800B8484(0x4000);
}
if (D_800FAF84.b != 0) return 0;
if (D_800FAF84.c != 0) return 0;
if (D_800FAF84.a < 10) return 0;
if (*(u16 *)(D_8007E228+0x58)&0x1000) {
if (!(D_800FADD0&0x100)) {
if(func_800D4198(250)) D_800FADD0 |= 0x30;
D_800FADD0 |= 0x100;
}
} else if(func_800D4198(500)) D_800FADD0 |= 0x30;
return 0;
}
