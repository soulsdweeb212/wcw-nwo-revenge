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
void func_80008CE8(s8, s16, s16, void *, s32, s32);
void func_800D43DC(void)
{
    s16 i;
    s32 base;
    s32 mask;
    s32 r;
    Wrestler *ent;
    u16 old;
    for (i = 0; i < 4; i++)
    {
        if (D_800F9D10[i].characterId != (-1))
        {
            base = (s32) (&D_800EB688[i]);
            r = updateEntityTargetLookAngles(i, (void *) base);
            do { } while (0);
            mask = base & (-((r << 24) != 0));
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
