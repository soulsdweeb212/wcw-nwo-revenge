/* @header
 * func_800BBA00
 * VRAM 0x800BBA00 | ROM 0xAEEA0 | size 0x5D8
 * asm: asm/nonmatchings/code_800BBA00/func_800BBA00.s
 */
#include "common.h"

extern u8 D_8006A2A0[];
extern u8 D_800EB466;
extern u8 D_800FABE4;
extern s8 D_800FADB8;
void func_800BBFD8(void);
void func_800D43DC(void);
void func_800D54A0(void);
void updateFieldRecordMotion(void);
void updatePlayerEntryStates(void);
void func_800A712C(void *, void *, s32 *, f32 *);
void func_800A7240(void *, s32, s32, u64);
#ifdef TARGET_PC
/* func_800D49A0 is the old name of copyPartCoordinateFields. The N64 link gets that name's address from build.json's
 * symbol list, and the N64 compiler accepts a call without a declaration; the PC link finds a function only under the
 * name it is defined with, and C99 needs a declaration. */
void copyPartCoordinateFields(void);
#endif
void func_800BBA00(void)
{
    s16 i;
    s16 k;
    s16 seq;
    s32 angle[2];
    s32 o;
    u32 tq;
    for (i = 0; i < 4; i++)
    {
        o = i;
        if (D_800F9D10[o].flags & WR_FLAG_PAIR_LEADER)
        {
            tq = (u32)o & 1;
            if (tq >> 1)
            {
                D_800FADB8 = 0;
            }
            if (D_800F9D10[o].attached[0] != (-1))
            {
                for (k = 0; k < 4; k++)
                {
                    ;
                }
            }
        }
    }

#ifdef TARGET_PC
    /* PC: func_800D49A0 by the name it is defined with, as the note above the function says. */
    copyPartCoordinateFields();
#else
    func_800D49A0();
#endif
    seq = (s8) D_800EB466;
    D_800F9D10[0].flags &= ~WR_FLAG_UPDATED;
    D_800F9D10[1].flags &= ~WR_FLAG_UPDATED;
    D_800F9D10[2].flags &= ~WR_FLAG_UPDATED;
    D_800F9D10[3].flags &= ~WR_FLAG_UPDATED;
    do
    {
        if ((D_800F9D10[seq].flags & WR_FLAG_PAIR_LEADER) && (!(D_800F9D10[seq].flags & WR_FLAG_UPDATED)))
        {
            D_800FADB8 = seq;
            D_800FABE4 = D_800F9D10[seq].opponentId;
            func_800BBFD8();
            for (i = 0; i < 2; i++)
            {
                s8 link = D_800F9D10[seq].attached[i];
                if (!(D_800F9D10[link].flags & WR_FLAG_UPDATED))
                {
                    D_800FADB8 = link;
                    D_800FABE4 = D_800F9D10[D_800F9D10[seq].attached[i]].opponentId;
                    if (link != (-1))
                    {
                        func_800BBFD8();
                    }
                }
            }
        }
        seq = (seq + 1) & 3;
    }
    while (seq != ((s8) D_800EB466));
    seq = (s8) D_800EB466;
    do
    {
        if (!(D_800F9D10[seq].flags & WR_FLAG_UPDATED))
        {
            D_800FADB8 = seq;
            D_800FABE4 = D_800F9D10[seq].opponentId;
            func_800BBFD8();
        }
        seq = (seq + 1) & 3;
    }
    while (seq != ((s8) D_800EB466));
    seq = (s8) D_800EB466;
    do
    {
        if (D_800F9D10[seq].flags & WR_FLAG_RERUN)
        {
            D_800FADB8 = seq;
            D_800FABE4 = D_800F9D10[seq].opponentId;
            func_800BBFD8();
        }
        seq = (seq + 1) & 3;
    }
    while (seq != (*((s8 *) (&D_800EB466))));
    seq = 0;
    for (; seq < 4; seq++)
    {
        if (D_800F9D10[seq].flags & WR_FLAG_AUTO_FACE)
        {
            s8 v = D_800F9D10[seq].opponentId;
            func_800A712C(&D_800F9D10[seq], &D_800F9D10[v], angle, NULL);
            do
            {
            }
            while (0);
            func_800A7240(&D_800F9D10[seq], angle[0], 0x155, 0ULL);
        }
    }

    D_800EB466 = (D_800EB466 + 1) & 3;
    i = 0;
    updateFieldRecordMotion();
    updatePlayerEntryStates();
    for (; i < 4; i++)
    {
        if (D_800F9D10[i].flags & 4)
        {
            D_8006A2A0[i] = 0;
        }
        else
        {
            D_8006A2A0[i] = 1;
        }
    }

    func_800D43DC();
    func_800D54A0();
}
