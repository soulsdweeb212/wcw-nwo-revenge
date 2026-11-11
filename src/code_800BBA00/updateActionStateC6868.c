/* @header
 * updateActionStateC6868  (originally func_800C6868)
 * VRAM 0x800C6868 | ROM 0xB9D08 | size 0x2B4
 * asm: asm/nonmatchings/code_800BBA00/updateActionStateC6868.s
 */
#include "common.h"

/* D_800FAF5C step machine (cases 0..2): step 0 selects the knockdown animation
 * id + action kind from the flag word and its state; step 1 finds a nearby
 * victim and hands its record to func_800C3A78; step 2 applies
 * the per-animation gravity/knockback rate. Case 1 falls through to 2. */
void func_800D427C(void *, s32, s32);
void func_800A7D1C(void *, s32);
void func_800A7F6C(void *, s32);
s8 func_800C2CDC(void *, s32);
void func_800C3A78(void *, void *, s32);
void func_800D25D0(void *, f32);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D2B64 */
void func_800D2B64(void *, f32, s32, s32);
#endif
void func_800A7188(void *);

void updateActionStateC6868(void)
{
    s16 id;
    s16 anim;
    s32 kind;
    s32 idx;
    f32 scale;
    Wrestler *p;

    switch (D_800FAF5C->step) {
    case 0:
        if (D_800FAF5C->flags & 0x2000000000000ULL) {
            id = 0x100D;
        } else if ((D_800FAF5C->flags & 0x0ULL) == 0) {
            id = 0x1005;
        } else {
            id = 0x100D;
        }
        kind = 0x47;
#ifdef TARGET_PC
        /* PC: the N64 code reads D_800FAF5C through its absolute address 0x800FAF5C, which means nothing on a PC; this
         * reads the same variable by its name. */
        if ((s16)D_800FAF5C->state == 0x23) {
#else
        /* D_800FAF5C read through its absolute address: the ROM reloads the pointer here */
        if ((s16)(*(Wrestler **)0x800FAF5C)->state == 0x23) {
#endif
            id = id + 1;
            kind = 0x48;
        }
        func_800D427C(D_800FAF5C, id, 3);
        switch ((s16)D_800FAF5C->animId) {
        case 0x1005: anim = 0x14; break;
        case 0x1006: anim = 0x15; break;
        case 0x100D: anim = 0x17; break;
        case 0x100E: anim = 0x18; break;
        }
        func_800A7D1C(D_800FAF5C, anim);
        func_800A7F6C(D_800FAF5C, kind);
        D_800FAF5C->step = D_800FAF5C->step + 1;
        break;
    case 1:
        idx = func_800C2CDC(D_800FAF5C, 3);
        if (idx != -1) {
            D_800FAF5C->step = D_800FAF5C->step + 1;
            func_800C3A78(D_800FAF5C, &D_800F9D10[idx], 0x200);
        }
        /* fallthrough */
    case 2:
        scale = 2.0f;
        func_800D25D0(D_800FAF5C, scale);
        p = D_800FAF5C;
        if ((p->flags & 0x0ULL) != 0 || (p->flags & 0x100) != 0) {
            func_800D2B64(p, scale, 0, 0xFFFFE);
        } else {
            switch ((s16)(p->state - 7)) {
            case 15:
                if (p->animFrame > p->anim.hitEnd) {
                    func_800D2B64(p, 2.0f, 0, 0xE);
                }
                break;
            case 0: case 24: case 25: case 26: case 29: case 30: case 31: case 78: case 79:
                if (p->animFrame > p->anim.hitEnd) {
                    func_800D2B64(p, 4.0f, 0, 0xFFFFE);
                } else {
                    func_800D2B64(p, 2.0f, 0, 0xE);
                }
                break;
            case 1: case 23: case 27: case 28: case 32:
                func_800D2B64(D_800FAF5C, 2.0f, 0, 0xE);
                break;
            }
        }
        func_800A7188(D_800FAF5C);
        break;
    }
}
