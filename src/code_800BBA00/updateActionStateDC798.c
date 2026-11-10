/* @header
 * updateActionStateDC798  (originally func_800DC798)
 * VRAM 0x800DC798 | ROM 0xCFC38 | size 0x3BC
 * asm: asm/nonmatchings/code_800BBA00/updateActionStateDC798.s
 */
#include "common.h"

/* Per-frame step of the action state machine of self (D_800FAF5C):
 * switch on step: 0 = pick/enter the action (fixed 0xEF8 when the profile's
 * flag 0x40000 is set, else a table lookup; 0xEF9 otherwise), 1 = action
 * setup (play select animation and transition), 2 = run the action
 * (collision/timer driven, may advance step), 3 = teardown, 4/5 = idle.
 * Uses animFramesLeft, animFrame, flags, profile, the anim.hitStart/hitEnd
 * frame window and move.spiritOnFinish. */
#ifdef TARGET_PC
/* PC: D_800F9B0C is a float (the distance to the opponent), and func_800D4D44's third parameter is a float (on PC,
 * port_decls.h declares it with its definition's types). The N64 code reads the float's bits as an s32 and passes
 * them in an integer register, where the N64 callee finds them. On PC an s32 would be converted by value into another
 * float, so the PC reads the variable as the float it is. */
extern f32 D_800F9B0C;
#else
extern s32 D_800F9B0C;
#endif
extern s32 D_800FABD8;
extern s8 D_800FADB8;
extern s32 D_800E3F20[];
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D4D44 */
s32 func_800D4D44(void *, s32, s32);
#endif
void func_800D427C(void *, s16, s32);
void func_800D7E80(void *, s32);
s8 func_800D8D74(void *, s32);
void func_800A7C40(void *, s8, s16);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D5438 */
s16 func_800D5438(void *, s32);
#endif
void func_800A7F6C(void *, s32);
void func_800A7D1C(void *, s32);
void func_800B68A0(void *, void *, void *);
void func_800D4AD0(void *);
s8 func_800D4CC4(void *);
void addEntityHealthDelta(void *, s32);
void beginEntityActionA8D8C(void *);
s8 func_800DB4FC(void *, void *);
void func_800C38FC(s8 *, u64, s32);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D2B64 */
void func_800D2B64(void *, f32, u32, s32);
#endif
void updateActionStateDC798(void)
{
    /* address of the global state pointer, used to reload it after a call */
#ifdef TARGET_PC
    /* PC: objSlot points at the pointer D_800FAF5C, which is 8 bytes; a u32 * would read half of it. It is set here
     * because case 1 can be reached without passing case 0's assignment. The N64 compiler folded the constant
     * &D_800FAF5C into both paths (case 1 loads D_800FAF5C itself), so case 1 sees the same value there. */
    Wrestler **objSlot = &D_800FAF5C;
#else
    u32 *objSlot;
#endif
    switch (D_800FAF5C->step)
    {
    case 0:
#ifndef TARGET_PC /* on PC, objSlot is set where it is declared */
        objSlot = &(*((u32 *) (&D_800FAF5C)));
#endif
        {
            s32 act;
            if ((*((u64 *) (D_800FAF5C->profile + 0x38))) & 0x40000ULL)
            {
                act = 0xEF8;
            }
            else
            {
                act = func_800D4D44(D_800FAF5C, 0, D_800F9B0C);
            }
            func_800D427C(D_800FAF5C, act, 2);
            func_800D7E80(D_800FAF5C, 0);
            D_800FAF5C->step++;
    case 1:
            if (func_800D8D74((Wrestler *) (*objSlot), 0))
            {
                if ((*((u64 *) (D_800FAF5C->profile + 0x38))) & 0x40000ULL)
                {
                    D_800FAF5C->step++;
                }
                else
                {
                    func_800D427C(D_800FAF5C, 0xEF9, 2);
                    D_800FAF5C->step = 5;
                }
            }
            break;
        }

    case 2:
        {
            if (D_800FAF5C->animFramesLeft > 0)
            {
                break;
            }
            func_800A7C40(D_800FAF5C, D_800FADB8, 0xDD);
            func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 0), 1);
            func_800A7F6C(D_800FAF5C, 0);
            D_800FAF5C->step++;
            break;
        }

    case 3:
        {
            D_800FABD8 &= ~D_800E3F20[D_800FADB8];
            if (D_800FAF5C->animFrame >= D_800FAF5C->anim.hitStart)
            {
                D_800FAF5C->flags = (D_800FAF5C->flags & (~WR_FLAG_IN_RING)) | WR_FLAG_ON_FLOOR;
            }
            if (func_800DB4FC(D_800FAF5C, D_800F9B00))
            {
                D_800FAF5C->step++;
            }
    case 4:
            D_800FAF5C->flags |= 0x80000000000ULL;
            func_800C38FC((s8 *) D_800FAF5C, 0x1000000000ULL, 0x800000);
            if (D_800FAF5C->animFrame >= D_800FAF5C->anim.hitEnd)
            {
                D_800FAF5C->flags &= ~0x80000000000ULL;
                func_800D2B64(D_800FAF5C, 4.0f, 0, 0xFFFFE);
            }
            if (D_800FAF5C->animFramesLeft <= 0)
            {
                Wrestler *o;
                func_800D4AD0(D_800FAF5C);
                o = D_800FAF5C;
                if (o->step == 3)
                {
                    func_800A7D1C(o, 0x23);
                    func_800B68A0(D_800FAF5C, D_800FAF5C, D_800FAF5C);
                    if (func_800D4CC4(o))
                    {
                        addEntityHealthDelta(o, o->move.spiritOnFinish);
                    }
                    beginEntityActionA8D8C(o);
                    break;
                }
                func_800A6C48(D_800FAF5C, 0x2B);
            }
            break;
        }

    case 5:
        {
            if (D_800FAF5C->animFramesLeft > 0)
            {
                break;
            }
            func_800A7D1C(D_800FAF5C, 0xE);
            func_800B68A0(D_800FAF5C, D_800FAF5C, D_800FAF5C);
            func_800D4AD0(D_800FAF5C);
            func_800A6C48(D_800FAF5C, 0x2B);
            break;
        }


    }

}
