/* @header
 * updateFieldRecordMotion  (originally func_800E1B9C)
 * VRAM 0x800E1B9C | ROM 0xD503C | size 0x26C
 * asm: asm/nonmatchings/code_800DE9C0/updateFieldRecordMotion.s
 */
#include "common.h"

/* Animates the four field records D_800F98xx (one per lane/record index).
 * For each active record (D_800F98E3[i][0] != 0):
 *  - when bit 1 is set, fall under gravity: subtract D_800E7768 from the
 *    height D_800F98E8[i][0] and, if it drops below the record's floor
 *    (0, or 90 when bit 8 is set), deactivate it and clear its linked ids;
 *  - when bits 2/4 are set, advance the motion: integrate the per-record
 *    velocity (func_800D37C0 into move), accumulate X/Z into D_800F98E4/
 *    D_800F98EC, advance the speed D_800F9900 by its acceleration
 *    D_800F9904, advance the vertical speed D_800F9908 by D_800F990C, and
 *    clamp both speeds back to 1.0 when they fall to/below D_800E7760. */
extern f64 D_800E7760, D_800E7768;
extern u8 D_800F98E0[][48], D_800F98E1[][48], D_800F98E2[][48], D_800F98E3[][48];
extern f32 D_800F98E4[][12], D_800F98E8[][12], D_800F98EC[][12], D_800F9900[][12], D_800F9904[][12], D_800F9908[][12], D_800F990C[][12];
extern s32 D_800F98FC[][12];
void func_800D37C0(s32, f32, f32 *);

void updateFieldRecordMotion(void) {
    f32 move[3];
    f64 threshold = D_800E7760;
    f32 one = 1.0f;
    s16 i = 0;
    s32 minusOne = -1;
    f32 minHeight, height, speed;
    for (i = 0; i < 4; i++) {
        if (!D_800F98E3[i][0])
            continue;
        if (D_800F98E3[i][0] & 1) {
            height = D_800F98E8[i][0] - D_800E7768;
            D_800F98E8[i][0] = height;
            minHeight = 0.0f;
            if (D_800F98E3[i][0] & 8)
                minHeight = 90.0f;
            if (height < minHeight) {
                D_800F98E0[i][0] = minusOne;
                D_800F98E1[i][0] = minusOne;
                D_800F98E2[i][0] = minusOne;
                D_800F98E3[i][0] = 0;
            }
        }
        if (D_800F98E3[i][0] & 6) {
            func_800D37C0(D_800F98FC[i][0], D_800F9900[i][0], move);
            D_800F98E4[i][0] += move[0];
            D_800F98EC[i][0] += move[2];
            speed = D_800F9900[i][0] + D_800F9904[i][0];
            D_800F9900[i][0] = speed;
            D_800F98E8[i][0] += D_800F9908[i][0];
            if (speed <= threshold)
                D_800F9900[i][0] = one;
            D_800F9908[i][0] += D_800F990C[i][0];
            if (D_800F9908[i][0] <= threshold)
                D_800F9908[i][0] = one;
        }
    }
}
