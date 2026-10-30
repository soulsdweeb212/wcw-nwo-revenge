/* @header
 * tickPlayerScripts  (originally func_8000DD0C)
 * VRAM 0x8000DD0C | ROM 0xE90C | size 0x134
 * asm: asm/nonmatchings/main/func_8000DD0C.s
 */
#include "common.h"

typedef struct {
    u8 pad[0x24];
    u8 f24;   /* @0x24 */
    u8 f25;   /* @0x25 */
    s8 f26;   /* @0x26 */
    s8 f27;   /* @0x27 */
    s8 f28;   /* @0x28 */
} Nw2DD0CRec;

extern s8 D_800566E8[];      /* per-player script state byte */
extern s16 D_800566E0[];     /* per-player parameter */
extern s16 D_8007DFA8[];     /* per-player current value */
extern Nw2DD0CRec *func_8002B7E0(s16, s16);
extern void func_80002C0C(void);
extern void func_8000C1B8(s32, s32);
extern void func_8000CFD4(s32, s16, u8, u8, s32, s32, s32);

/* Run one step of the per-player scripted effect state machines (4 players).
 * Each player's state byte drives a small command script: 0 clears the value,
 * 1 looks up an entry and starts an effect, 2/3 run the end effect with flag
 * 0/1, and any out-of-range state disables the player. */
void tickPlayerScripts(void)
{
    s32 player = 0;
    s8 *state = D_800566E8;
    s32 playerIndex = 0;
    s16 *param = D_800566E0;
    s16 *value = D_8007DFA8;

    for (; player < 4; player++) {
        Nw2DD0CRec *entry;

        if (*state >= 0) {
            func_80002C0C();
            switch (*state) {
            case 0:
                *value = 0;
                (*state)++;
                return;
            case 1:
                entry = func_8002B7E0(*param, *value);
                func_8000CFD4(playerIndex >> 16, *param, entry->f25, entry->f24, entry->f26, entry->f27, entry->f28);
                (*state)++;
                return;
            case 2:
                func_8000C1B8(playerIndex >> 16, 0);
                (*state)++;
                return;
            case 3:
                func_8000C1B8(playerIndex >> 16, 1);
                (*state)++;
                return;
            default:
                *state = -1;
                return;
            }
        }
        state++;
        playerIndex += 0x10000;
        param++;
        value++;
    }
}
