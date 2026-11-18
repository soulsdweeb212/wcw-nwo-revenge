/* @header
 * syncFieldSlotsToRender  (originally func_800E1E08)
 * VRAM 0x800E1E08 | ROM 0xD52A8 | size 0x114
 * asm: asm/nonmatchings/code_800DE9C0/syncFieldSlotsToRender.s
 */
#include "common.h"

typedef struct { s8 value; u8 pad[47]; } ByteColumn;   /* one s8 per player */
typedef struct { u8 value; u8 pad[91]; } Tbl7E010;      /* one u8 per player */
extern ByteColumn D_800F98E0[], D_800F98E1[], D_800F98E2[], D_800F98E3[];
extern Tbl7E010 D_8007E010[];
extern u8 D_800F98E4[];
void func_80012364(s16, s8, s8, void *);

/* For each of the four field slots at D_800F98E0 (not players): if the slot's type is 11 or 12
 * and its D_8007E010 flag is set, clear the slot; then pass the slot's id, type and position
 * (its 0x30-byte buffer) to func_80012364 for drawing. */
void syncFieldSlotsToRender(void) {
    s16 player = 0;
    do {
        if ((u32)((u8)D_800F98E1[player].value - 11) < 2) {
            if (D_8007E010[player].value == 1) {
                D_800F98E0[player].value = -1;
                D_800F98E1[player].value = -1;
                D_800F98E2[player].value = -1;
                D_800F98E3[player].value = 0;
            }
        }
        func_80012364(player, D_800F98E2[player].value, D_800F98E1[player].value, D_800F98E4 + player * 0x30);
        player++;
    } while (player < 4);
}
