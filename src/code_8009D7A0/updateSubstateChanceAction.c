/* @header
 * updateSubstateChanceAction  (originally func_800B0090)
 * VRAM 0x800B0090 | ROM 0xA3530 | size 0xCC
 * asm: asm/nonmatchings/code_8009D7A0/updateSubstateChanceAction.s
 */
#include "common.h"

f32 func_800B3AD8(void *);
s8 func_800D4198(s16);
typedef struct {
    s16 pad0;
    s16 unk2;
    s16 unk4;
    s16 pad6;
    u16 unk8;
    s16 padA[4];
    s16 unk12;
    s16 unk14;
    s16 pad16[12];
    s16 unk2E;
    char pad30[0x2C];
    s32 unk5C;
} SubState;
typedef struct {
    char pad[0xA];
    s16 unkA;
} Unk9B60;
extern Unk9B60 *D_800F9B60;
extern SubState *D_800FABD0;

void updateSubstateChanceAction(void) {
    switch (D_800FABD0->unk14) {
    default:
        D_800FABD0->unk2 = 0;
        D_800FABD0->unk4 = 0;
        D_800FABD0->unk2E = D_800F9B60->unkA;
        D_800FABD0->unk5C &= ~7;
        break;
    case 4:
    case 8:
    case 14:
        if (func_800D4198(D_800FABD0->unk12 * func_800B3AD8(D_800FABD0))) {
            D_800FABD0->unk8 = 0xC030;
        }
        break;
    }
}
