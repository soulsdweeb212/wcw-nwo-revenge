/* @header
 * updateEntityGrabActionState  (originally func_800C6418)
 * VRAM 0x800C6418 | ROM 0xB98B8 | size 0x450
 * asm: asm/nonmatchings/code_800BBA00/func_800C6418.s
 */
#include "common.h"

/* Entity grab/hold action state machine (states 0..2). Picks the grab
 * animation from the entity's action type (fA) and status bits, finds a free
 * slot (func_800C2CDC) and marks it for the grabbed partner, then keeps the
 * entity aligned to the held target (func_800D2B64 chosen from f6/f371). */
typedef struct {s8 f0;u8 pad1[5];s16 f6;u8 pad8[2];s16 fA;s16 fC;u8 padE[0x12];u64 flags;u8 pad28[0x1B];u8 f43;u8 pad44[0x32D];u8 f371;} EntC6418;
extern EntC6418 *D_800FAF5C;
extern EntC6418 *D_800F9B00;
extern s32 D_800E3F20[];
extern s32 D_800FABD8;
extern s8 D_800FADB8;
extern u8 D_800FA061[];
extern u8 D_800FA063[];
extern u8 D_800F9D10[];
extern u8 D_800F9D30[];
extern u8 D_800F9D34[];
void func_800D427C(void*,s32,s32);
void func_800A7C40(void*,s8,s16);
void func_800A7F6C(void*,s32);
s16 func_800D5438(void*,s32);
s8 func_800C2CDC(void*,s32);
void func_800A837C(void*);
void func_800A7188(void*);
s32 func_800D2B64(void*,f32,u16,s32);
void func_800A7D1C(void*,s32);
void func_800C5FBC(void*);
s8 func_800D26A0(void*,void*,s32);
void func_800D2600(void*,s32,f32);
void func_800A6C48(void*,s32);

void updateEntityGrabActionState(void) {
    s8 slot;
    s32 animId;
    s32 auxAnim;
    EntC6418 *ent;

    switch (D_800FAF5C->fC) {
    case 0:
        if (D_800FAF5C->fA == 0x24) {
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
            if (D_800FAF5C->fA == 0x56) auxAnim = 0xB1;
            else if (D_800F9B00->flags & 0x200000) auxAnim = 0xB0;
            else auxAnim = 0xAF;
            func_800A7C40(D_800FAF5C, D_800FADB8, auxAnim);
            func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 0), 3);
            func_800A7F6C(D_800FAF5C, 0);
        }
        D_800FAF5C->fC++;
        break;
    case 1:
        D_800FABD8 &= ~D_800E3F20[D_800FADB8];
        if (D_800FAF5C->fA == 0x24) animId = 4; else animId = 2;
        slot = func_800C2CDC(D_800FAF5C, animId);
        if (slot != -1) {
            func_800A837C(D_800FAF5C);
            D_800FA061[slot * 0x3B0] = (u8)D_800FADB8;
            D_800FA063[slot * 0x3B0] = (u8)D_800FADB8;
            func_800A6C48(&D_800F9D10[slot * 0x3B0], 0x57);
            D_800FAF5C->f43 = 0;
            D_800FAF5C->fC++;
        }
    case 2:
        slot = func_800D26A0(D_800FAF5C, 0, -1);
        if (slot != -1) {
            if ((*(u64*)(D_800F9D30 + slot * 0x3B0) & 0x400000) == 0)
                func_800D2600(D_800FAF5C, -1, 2.0f);
        }
        ent = D_800FAF5C;
        if (ent->flags & 0x100) {
            func_800D2B64(ent, 2.f, 0, 0xFFFFE);
        } else {
            switch ((s16)(ent->fA - 7)) {
            case 15:
                if (ent->f6 > ent->f371) func_800D2B64(ent, 2.f, 0, 0xE);
                break;
            case 0: case 24: case 25: case 26: case 29: case 30: case 31: case 78: case 79:
                if (ent->f6 > ent->f371) func_800D2B64(ent, 4.f, 0, 0xFFFFE);
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
