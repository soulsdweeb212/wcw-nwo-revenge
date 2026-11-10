/* @header
 * updateEntityGrabActionState  (originally func_800C6418)
 * VRAM 0x800C6418 | ROM 0xB98B8 | size 0x450
 * asm: asm/nonmatchings/code_800BBA00/updateEntityGrabActionState.s
 */
#include "common.h"

/* Grab/hold step machine (steps 0..2). Picks the grab animation from the
 * wrestler's state and status bits, finds a target (func_800C2CDC) and sets
 * its heldById/opponentId to self, then keeps the wrestler aligned to the held
 * target (func_800D2B64 chosen from animFrame/anim.hitEnd). */
extern s32 D_800E3F20[];
extern s32 D_800FABD8;
extern s8 D_800FADB8;
void func_800D427C(void*,s32,s32);
void func_800A7C40(void*,s8,s16);
void func_800A7F6C(void*,s32);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D5438 */
s16 func_800D5438(void*,s32);
#endif
s8 func_800C2CDC(void*,s32);
void func_800A837C(void*);
void func_800A7188(void*);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D2B64 */
s32 func_800D2B64(void*,f32,u16,s32);
#endif
void func_800A7D1C(void*,s32);
void func_800C5FBC(void*);
s8 func_800D26A0(void*,void*,s32);
void func_800D2600(void*,s32,f32);

void updateEntityGrabActionState(void) {
    s8 slot;
    s32 animId;
    s32 auxAnim;
    Wrestler *ent;

    switch (D_800FAF5C->step) {
    case 0:
        if (D_800FAF5C->state == 0x24) {
            if (D_800FAF5C->flags & 0x2000000000000ULL) { animId = 0x1011; auxAnim = 0x19; }
            else { animId = 0x1009; auxAnim = 0x16; }
            func_800D427C(D_800FAF5C, animId, 3);
            func_800A7D1C(D_800FAF5C, auxAnim);
            func_800A7F6C(D_800FAF5C, 0x49);
        } else {
            func_800A7C40(D_800FAF5C, D_800FADB8, 0xAF);
            func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 0), 3);
            func_800C5FBC(D_800FAF5C);
            func_800A7C40(D_800FAF5C, D_800FADB8, 0xB0);
            func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 0), 3);
            func_800C5FBC(D_800FAF5C);
            if (D_800FAF5C->state == 0x56) auxAnim = 0xB1;
            else if (D_800F9B00->flags & 0x200000) auxAnim = 0xB0;
            else auxAnim = 0xAF;
            func_800A7C40(D_800FAF5C, D_800FADB8, auxAnim);
            func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 0), 3);
            func_800A7F6C(D_800FAF5C, 0);
        }
        D_800FAF5C->step++;
        break;
    case 1:
        D_800FABD8 &= ~D_800E3F20[D_800FADB8];
        if (D_800FAF5C->state == 0x24) animId = 4; else animId = 2;
        slot = func_800C2CDC(D_800FAF5C, animId);
        if (slot != -1) {
            func_800A837C(D_800FAF5C);
            D_800F9D10[slot].heldById = D_800FADB8;
            D_800F9D10[slot].opponentId = D_800FADB8;
            func_800A6C48(&D_800F9D10[slot], 0x57);
            D_800FAF5C->comboHits = 0;
            D_800FAF5C->step++;
        }
    case 2:
        slot = func_800D26A0(D_800FAF5C, 0, -1);
        if (slot != -1) {
            if ((D_800F9D10[slot].flags & 0x400000) == 0)
                func_800D2600(D_800FAF5C, -1, 2.0f);
        }
        ent = D_800FAF5C;
        if (ent->flags & 0x100) {
            func_800D2B64(ent, 2.f, 0, 0xFFFFE);
        } else {
            switch ((s16)(ent->state - 7)) {
            case 15:
                if (ent->animFrame > ent->anim.hitEnd) func_800D2B64(ent, 2.f, 0, 0xE);
                break;
            case 0: case 24: case 25: case 26: case 29: case 30: case 31: case 78: case 79:
                if (ent->animFrame > ent->anim.hitEnd) func_800D2B64(ent, 4.f, 0, 0xFFFFE);
                else func_800D2B64(ent, 2.f, 0, 0xE);
                break;
            case 1: case 23: case 27: case 28: case 32:
                func_800D2B64(D_800FAF5C, 2.f, 0, 0xE);
                break;
            }
        }
        func_800A7188(D_800FAF5C);
        break;
    }
}
