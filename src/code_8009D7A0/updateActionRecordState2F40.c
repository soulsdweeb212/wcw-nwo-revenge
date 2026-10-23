#include "common.h"

/* D_800FABD0 action-record state machine (states 0..4): decides whether the paired
 * hold/reversal action may proceed by comparing the actor's (D_800FAF58) and the
 * opponent's (D_800F9B60) state values against this action's step; sets the hold
 * flags/timers on success and resets the record on failure. */
typedef struct { u8 p0[2]; s16 f2; u16 state; s16 f6; s16 f8; s16 fA; s8 fC; u8 pD[0x1B]; s16 f28; s16 f2A; u8 p2C[2]; u16 linkedState; u8 p30[0x2C]; u32 flags; } Nw2Act2F40;
typedef struct { u8 p0[0xA]; s16 fA; s16 fC; u8 pE[0x12]; u64 f20; } Nw2F58State;
typedef struct { u8 p0[0xA]; s16 fA; } Nw2F9B60State;
extern Nw2Act2F40 *D_800FABD0;
extern Nw2F58State *D_800FAF58;
extern Nw2F9B60State *D_800F9B60;
extern u16 D_800E3CE0[];
s8 func_800D4198(s16);

void updateActionRecordState2F40(void)
{
    s16 s;
    s16 t;
    switch ((s16)D_800FABD0->state) {
    case 0:
        if ((D_800FAF58->f20 & 0x40ULL) == 0) goto reset;
        if (func_800D4198((s16)(D_800FABD0->f28 * 15)) == 0) goto reset;
        {
            u16 n = D_800FABD0->state;
            u16 v = D_800E3CE0[D_800FABD0->f2A] | 4;
            D_800FABD0->state = n + 1;
            D_800FABD0->fA = v;
            D_800FABD0->f6 = v;
        }
        return;
    case 1:
        s = D_800FAF58->fA;
        if (s == 10) goto l3068;
        if (s >= 11) goto l303C;
        if (s == 3) goto l3080;
        if (s == 4) goto l3058;
        goto reset;
    l303C:
        if (s >= 0x8B) goto reset;
        if (s >= 0x89) goto l3080;
        goto reset;
    l3058:
        D_800FABD0->state = 4;
        return;
    l3068:
        D_800FABD0->state++;
        return;
    l3080:
        D_800FABD0->f6 = D_800FABD0->fA;
        return;
    case 2:
        if (D_800FAF58->fA != 10) goto reset;
        D_800FABD0->f6 = 4;
        if (D_800FAF58->fC != 4) return;
        D_800FABD0->state++;
        return;
    case 3:
        if (D_800FAF58->fA != 10) goto reset;
        t = D_800F9B60->fA;
        if (t >= 0x2E) goto l3154;
        if (t < 0x2C) goto l3154;
        if (D_800FABD0->f28 < 0x1F) return;
        if (func_800D4198(200) == 0) return;
        D_800FABD0->f6 = 4;
        D_800FABD0->fC = 0x50;
        return;
    l3154:
        if (func_800D4198(500) != 0) return;
        D_800FABD0->f6 = 4;
        D_800FABD0->f8 = 0x10;
        return;
    case 4:
        if (D_800FAF58->fA == 3) { D_800FABD0->f8 = 0xF00; return; }
        if (D_800FAF58->fA == 4) return;
        goto reset;
    }
    return;
reset:
    D_800FABD0->f2 = 0;
    D_800FABD0->state = 0;
    D_800FABD0->linkedState = (u16)D_800F9B60->fA;
    D_800FABD0->flags &= ~7;
}
