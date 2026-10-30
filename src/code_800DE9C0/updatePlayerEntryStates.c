/* @header
 * updatePlayerEntryStates  (originally func_800E1E08)
 * VRAM 0x800E1E08 | ROM 0xD52A8 | size 0x114
 * asm: asm/nonmatchings/code_800DE9C0/updatePlayerEntryStates.s
 */
#include "common.h"

typedef struct { s8 value; u8 pad[47]; } ByteColumn;   /* one s8 per player */
typedef struct { u8 value; u8 pad[91]; } Tbl7E010;      /* one u8 per player */
extern ByteColumn D_800F98E0[], D_800F98E1[], D_800F98E2[], D_800F98E3[];
extern Tbl7E010 D_8007E010[];
extern u8 D_800F98E4[];
void func_80012364(s16, s8, s8, void *);

/* For each of the four players: if the entry is in state 11 or 12 and the
 * player's flag is set, reset the four per-player state bytes; then forward the
 * player's state bytes to func_80012364 along with its 0x30-byte buffer. */
void updatePlayerEntryStates(void) {
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
