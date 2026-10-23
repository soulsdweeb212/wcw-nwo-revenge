#include "common.h"

extern u8 *D_800FABD0;
extern u8 *D_800F9B60;
extern u8 *D_800FAF58;

/* Two-step action state machine driven by the s16 at D_800FABD0+4:
 * step 0 stores the byte 0x50 at D_800FABD0+0xC and advances the step; step 1 finishes the
 * action (reset +2/+4, copy D_800F9B60's u16 +0xA into +0x2E and clear the low three bits
 * of the u32 flags at +0x5C) whenever the recorded +0x2E differs from D_800F9B60's current
 * u16 +0xA, or D_800FAF58's s16 state (+0xA) is not 0x17. */
void func_800B18E0(void) {
    switch (*(s16 *)(D_800FABD0 + 4)) {
    case 0:
        *(u8 *)(D_800FABD0 + 0xC) = 0x50;
        (*(s16 *)(D_800FABD0 + 4))++;
        break;
    case 1:
        if (*(s16 *)(D_800FABD0 + 0x2E) != *(s16 *)(D_800F9B60 + 0xA)) {
            u8 *g = D_800F9B60;
            *(s16 *)(D_800FABD0 + 2) = 0;
            *(s16 *)(D_800FABD0 + 4) = 0;
            *(u16 *)(D_800FABD0 + 0x2E) = *(u16 *)(g + 0xA);
            *(u32 *)(D_800FABD0 + 0x5C) &= ~7;
        }
        if (*(s16 *)(D_800FAF58 + 0xA) != 0x17) {
            u8 *g = D_800F9B60;
            *(s16 *)(D_800FABD0 + 2) = 0;
            *(s16 *)(D_800FABD0 + 4) = 0;
            *(u16 *)(D_800FABD0 + 0x2E) = *(u16 *)(g + 0xA);
            *(u32 *)(D_800FABD0 + 0x5C) &= ~7;
        }
        break;
    }
}
