/* @header
 * packFieldRecords  (originally func_800E1F1C)
 * VRAM 0x800E1F1C | ROM 0xD53BC | size 0x174
 * asm: asm/nonmatchings/code_800DE9C0/func_800E1F1C.s
 */
#include "common.h"

/*
 * Pack four field records from the parallel float/int tables D_800F98Ex into
 * compact entries: position components (x,y,z) and four extra channels
 * (a..d) are scaled by D_800E7770 / D_800E7778 and truncated to integers.
 */
extern const f64 D_800E7770, D_800E7778;
extern u8 D_800F98E1[][48], D_800F98E2[][48];
extern f32 D_800F98E4[][12], D_800F98E8[][12], D_800F98EC[][12];
extern s32 D_800F98F0[][12], D_800F98F4[][12], D_800F98F8[][12], D_800F98FC[][12];
typedef struct { u8 id, mode; s16 x, y, z; s8 a, b, c, d; } PackedFieldRecord;
void packFieldRecords(PackedFieldRecord *out) {
 s16 i;
 for (i = 0; i < 4; i++, out++) {
  out->id = D_800F98E2[i][0];
  out->mode = D_800F98E1[i][0];
  out->x = (s32)(D_800F98E4[i][0] * D_800E7770);
  out->y = (s32)(D_800F98E8[i][0] * D_800E7770);
  out->z = (s32)(D_800F98EC[i][0] * D_800E7770);
  out->a = (s32)(D_800F98F0[i][0] * D_800E7778);
  out->b = (s32)(D_800F98F4[i][0] * D_800E7778);
  out->c = (s32)(D_800F98F8[i][0] * D_800E7778);
  out->d = (s32)(D_800F98FC[i][0] * D_800E7778);
 }
}
