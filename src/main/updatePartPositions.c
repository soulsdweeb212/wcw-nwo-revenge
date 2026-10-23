#include "common.h"

extern u8 D_800651A0[];
extern u8 D_80070C94[];
extern u8 D_80070C98[];
extern u8 D_80070C9C[];
void func_8000D424(void *, f32, s32, s32);

/* Refreshes the 19 part transforms of entity arg0 from the per-part source
 * tables (skipping entities flagged 0x80 at +0xF4), then copies the last three
 * parts' values down to the fixed slots. */
void updatePartPositions(s16 arg0) {
    u8 *rec;
    s32 off;
    u8 *dst;
    u32 i;

    rec = D_800651A0 + arg0 * 0x13C4;
    i = 1;
    if (!(rec[0xF4] & 0x80)) {
        off = arg0 * 0xB24 + 0x7C;
        dst = rec + 0xDC;
        do {
            func_8000D424(dst, -*(f32 *)(D_80070C94 + off),
                          *(s32 *)(D_80070C98 + off),
                          *(s32 *)(D_80070C9C + off));
            off += 0x7C;
            dst += 0xDC;
            i++;
        } while (i < 0x14);
        rec[0x1148] = rec[0x464];
        rec[0x1224] = rec[0x6F8];
        rec[0x1300] = rec[0xCFC];
    }
}
