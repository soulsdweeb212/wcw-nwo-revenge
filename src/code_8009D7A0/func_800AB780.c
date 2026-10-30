/* @header
 * func_800AB780
 * VRAM 0x800AB780 | ROM 0x9EC20 | size 0x1EC
 * asm: asm/nonmatchings/code_8009D7A0/func_800AB780.s
 */
#include "common.h"

/* Per-frame attack-range decision (companion to func_800AA9A0). Forces
 * action 0x22 when the opponent flag 0x40000 is set or the current action's
 * frame counter (+0x28) has passed 81 and the range budget allows it. Then,
 * unless blocked, it either triggers a close-range strike (0x21 / 0xD / 0xA
 * depending on distance and opponent flag 0x80000) or routes to one of two
 * scripted action chains (D_800E3574 / D_800E3594) chosen by
 * func_800D4198(action+0x12). */
extern u8 *D_800FABD0, *D_800FAF58;
extern s8 *D_800F9B60;
extern s16 D_800FAF50[];
extern u8 D_800E3574[], D_800E3594[];
s8 func_800D4198(s16);
s8 requestAttachmentAction(void);
s8 func_800AC0B4(void);
s8 func_800AB43C(void);
void func_800AD958(s32);
void func_800ADA38(void *);
void func_800AB780(void) {
    if ((*(u64 *)(D_800FAF58 + 0x20) & 0x40000ULL) || (*(s16 *)(D_800FABD0 + 0x28) >= 81 && func_800D4198(((s16)(D_800FAF50[*D_800F9B60] / 3) + 1) * 40))) {
        func_800AD958(0x22); return;
    }
    if (!requestAttachmentAction()) {
        if (*(f32 *)(D_800FABD0 + 0x3C) > *(f32 *)(D_800FABD0 + 0x58)) { func_800AD958(0x21); return; }
        if (*(u64 *)(D_800FAF58 + 0x20) & 0x80000ULL) {
            if (*(s16 *)(D_800FABD0 + 0x26) < 10 && func_800D4198(500)) { func_800AD958(0xD); return; }
            func_800AD958(0xA); return;
        }
        if (!func_800AC0B4() && !requestAttachmentAction() && !func_800AB43C()) {
            if (func_800D4198(*(s16 *)(D_800FABD0 + 0x12))) func_800ADA38(D_800E3574);
            else func_800ADA38(D_800E3594);
        }
    }
}
