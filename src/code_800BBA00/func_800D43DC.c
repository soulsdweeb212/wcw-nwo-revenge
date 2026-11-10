/* @header
 * func_800D43DC
 * VRAM 0x800D43DC | ROM 0xC787C | size 0x228
 * asm: asm/nonmatchings/code_800BBA00/func_800D43DC.s
 */
#include "common.h"

typedef struct 
{
    u8 b[12];
} Look43DC;
typedef struct 
{
    s8 b0;
    s8 b1;
    s8 b2;
    s8 b3;
} Col43DC;
extern Look43DC D_800EB688[];
extern Col43DC D_800EB6B8[];
s32 updateEntityTargetLookAngles(s8, void *);
void func_800D427C(void *, s16, s32);
#ifdef TARGET_PC
/* PC: the types of func_80008CE8's definition. Its fifth parameter is a pointer (f32 *vec), which the N64 declaration
 * passes as an s32. */
void func_80008CE8(s16, s16, s16, f32 *, f32 *, u8);
#else
void func_80008CE8(s8, s16, s16, void *, s32, s32);
#endif
void func_800D43DC(void)
{
    s16 i;
#ifdef TARGET_PC
    /* PC: base and mask hold an address, which an s32 would cut in half. mask is base when the look angles changed and
     * NULL otherwise; the N64 code gets it with an AND on 32-bit integers. */
    u8 *base;
    f32 *mask;
#else
    s32 base;
    s32 mask;
#endif
    s32 r;
    Wrestler *ent;
    u16 old;
    for (i = 0; i < 4; i++)
    {
        if (D_800F9D10[i].characterId != (-1))
        {
#ifdef TARGET_PC
            /* PC: base and mask as pointers, as above; mask is base or NULL without the 32-bit AND. */
            base = (u8 *) (&D_800EB688[i]);
            r = updateEntityTargetLookAngles(i, (void *) base);
            mask = ((r << 24) != 0) ? (f32 *) base : NULL;
#else
            base = (s32) (&D_800EB688[i]);
            r = updateEntityTargetLookAngles(i, (void *) base);
            do { } while (0);
            mask = base & (-((r << 24) != 0));
#endif
            if (D_800F9D10[i].animFramesLeft <= 0)
            {
                if (D_800F9D10[i].anim.loop == 0)
                {
                    func_80008CE8(D_800F9D10[i].id, D_800F9D10[i].animId, D_800F9D10[i].animFrame, &D_800F9D10[i].x, mask, (&D_800EB6B8[i])->b3);
                    continue;
                }
                ent = &D_800F9D10[i];
                old = D_800F9D10[i].animId;
                ent->animId = -1;
                func_800D427C(ent, old, 0);
            }
            func_80008CE8(D_800F9D10[i].id, D_800F9D10[i].animId, D_800F9D10[i].animFrame, &D_800F9D10[i].x, mask, (&D_800EB6B8[i])->b3);
            if (D_800F9D10[i].animFramesLeft > 0)
            {
                D_800F9D10[i].animFrame++;
                D_800F9D10[i].animFramesLeft--;
            }
        }
    }

}
