/* @header
 * pickPresentControllerEntity  (originally func_800BC7D8)
 * VRAM 0x800BC7D8 | ROM 0xAFC78 | size 0x230
 * asm: asm/nonmatchings/code_800BBA00/func_800BC7D8.s
 */
#include "common.h"

extern u32 D_8007E848;
extern u16 D_8007E280;
extern u16 D_800E3984[];
extern u16 D_800E398C[];
extern u8 D_800F9D30[];

/* Picks a "present" controller/entity index (0..3) from the D_8007E848 bitmask
 * using the two mask tables. Returns -1 if none present, or the first present
 * entity (or the second list's first entry when the first is flagged 4). When
 * D_8007E280 bit 0x200 is set, also raises the partner entity's 0x4000 flag. */
s8 pickPresentControllerEntity(void) {
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
        if (*(u64 *)(D_800F9D30 + buf[0] * 0x3B0) & 4) {
            s32 o;
            cand = buf[8];
            o = cand * 0x3B0;
            if ((*(u64 *)(D_800F9D30 + o) & 4) == 0) {
                t0 = (u8)cand;
            }
        }
        if (D_8007E280 & 0x200) {
            s32 s;
            s = (buf[0] ^ 1) * 0x3B0;
            *(u64 *)(D_800F9D30 + s) |= 0x4000;
        }
        return (s8)t0;
        }
      }
    }
    return -1;
}
