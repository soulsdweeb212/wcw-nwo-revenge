/* @header
 * pickPostMatchFocusSlot  (originally func_800BC7D8)
 * VRAM 0x800BC7D8 | ROM 0xAFC78 | size 0x230
 * asm: asm/nonmatchings/code_800BBA00/pickPostMatchFocusSlot.s
 */
#include "common.h"

extern u32 D_8007E848;
extern u16 D_8007E280;
extern u16 D_800E3984[];
extern u16 D_800E398C[];

/* After the match (match phase 3): picks the slot (0..3) to show from the result bits D_8007E848
 * (1/2/4/8 the winners, D_800E3984; 0x10..0x80 the losers, D_800E398C; set by func_800B9730). Returns -1 if none, or the first winner
 * (or the first loser when the winner is CPU-controlled and that loser is human). When
 * D_8007E280 bit 0x200 is set, also raises the winner flag 0x4000 on the winner's tag partner (slot ^ 1). */
s8 pickPostMatchFocusSlot(void) {
    s8 buf[12];
    s16 n1, n2;
    s16 i;
    s8 cand;
    u8 t0;

    buf[0] = -1;
    buf[1] = -1;
    n1 = 0;
    for (i = 0; i < 4; i++) {
        if (D_8007E848 & D_800E3984[i]) {
            buf[n1] = i;
            n1++;
        }
    }
    buf[8] = -1;
    buf[9] = -1;
    buf[10] = -1;
    n2 = 0;
    for (i = 0; i < 4; i++) {
        if (D_8007E848 & D_800E398C[i]) {
            buf[8 + n2] = i;
            n2++;
        }
    }
    if (n1 == 0) return -1;
    if (n1 != 0) {
        if (n1 >= 0) {
            if (n1 < 3) {
                t0 = (u8)buf[0];
                if (D_800F9D10[buf[0]].flags & WR_FLAG_CPU) {
                    cand = buf[8];
                    if ((D_800F9D10[cand].flags & WR_FLAG_CPU) == 0) {
                        t0 = (u8)cand;
                    }
                }
                if (D_8007E280 & 0x200) {
                    D_800F9D10[buf[0] ^ 1].flags |= 0x4000;
                }
                return (s8)t0;
            }
        }
    }
    return -1;
}
