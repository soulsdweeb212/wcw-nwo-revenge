/* @header
 * func_800A9D5C
 * VRAM 0x800A9D5C | ROM 0x9D1FC | size 0x534
 * asm: asm/nonmatchings/code_8009D7A0/func_800A9D5C.s
 */
#include "common.h"

typedef struct 
{
    u8 pad0[2];
    s16 f2;
    s16 f4;
    u8 pad6[0xE];
    s16 f14;
    u8 pad16[8];
    s16 s1E;
    s16 f20;
    u8 pad22[0xC];
    s16 s2E;
    u8 pad30[2];
    u16 f32;
    u8 pad34[8];
    f32 f3C;
    u8 pad40[0x1C];
    u32 f5C;
} Nw2B9D5C;
extern Nw2B9D5C *D_800FABD0;
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D3B24 */
s8 func_800D3B24(void *, void *, f32, s32);
#endif
s32 func_800D4148(void);
void func_800ADFB8(void);
void func_800AA290(void);
void func_800AA9A0(void);
void func_800AABA0(void);
void func_800AABF8(void);
void selectActionVariant(void);
void func_800A9D5C(void)
{
    if (D_800FAF58->flags & 1)
    {
        switch (D_800FAF58->state)
        {
        case 0x11:
        case 0x12:
        case 0x13:
        case 0x28:
        case 0x3B:
        case 0x3D:
        case 0x3F:
        case 0x4A:
        case 0x4C:
        case 0x4E:
        case 0x50:
        case 0x52:
        case 0x54:
        case 0x57:
            if ((!(D_800FABD0->f5C & 8)) && (D_800FABD0->f20 != D_800FAF58->state))
            {
                D_800FABD0->f20 = D_800FAF58->state;
                {
                    u16 t = D_800FABD0->f32 - 1;
                    D_800FABD0->f32 = t;
                    if (((s16) t) < 0)
                    {
                        D_800FABD0->f5C |= 8;
                        D_800FABD0->f32 = ((s16) func_800D4148()) % 8;
                    }
                }
            }
            break;
        default:
            D_800FABD0->f20 = D_800FAF58->state;
            break;
        }

        if (D_800FABD0->f5C & 0x10)
        {
            if (!func_800D3B24(&D_800FAF58->jointA[1], &D_800F9B60->jointA[1], 300.0f, 0))
            {
                u64 gm = D_800F9B60->flags & 0x1C0ULL;
                if (!(D_800FAF58->flags & gm))
                {
                    D_800FABD0->f5C &= ~0x18;
                    return;
                }
            }
        }
        else
        {
            if (D_800FABD0->f5C & 8)
            {
                s16 k;
                s8 c = D_800FAF58->id;
                k = (c & 1) ^ 1;
                if ((D_800F9D10[k].opponentId == c) && func_800D3B24(&D_800FAF58->jointA[1], &D_800F9D10[k].jointA[1], 120.0f, 0))
                {
                    D_800FAF58->opponentId = k;
                    D_800FABD0->f5C |= 0x10;
                    return;
                }
                k |= 2;
                if ((D_800F9D10[k].opponentId == D_800FAF58->id) && func_800D3B24(&D_800FAF58->jointA[1], &D_800F9D10[k].jointA[1], 120.0f, 0))
                {
                    D_800FAF58->opponentId = k;
                    D_800FABD0->f5C |= 0x10;
                    return;
                }
            }
            func_800ADFB8();
            return;
        }
    }
    if (D_800FAF58->flags & 2)
    {
        if (!(D_800FAF58->flags & 0x20))
        {
            s16 i;
            for (i = 0; i < 4; i++)
            {
                u64 f;
                if (i == D_800FAF58->id)
                {
                    continue;
                }
                if (D_800F9D10[i].characterId == (-1))
                {
                    continue;
                }
                f = D_800F9D10[i].flags;
                if (!(f & 2))
                {
                    continue;
                }
                if (f & 0x20)
                {
                    break;
                }
            }

            if (i == 4)
            {
                func_800ADFB8();
                return;
            }
        }
        if (D_800FAF58->opponentId == D_800FAF58->partnerId)
        {
            if (D_800FAF58->flags & 0x20)
            {
                D_800FAF58->opponentId = D_800FAF58->partnerId ^ 1;
            }
            else
            {
                D_800FAF58->opponentId = D_800FAF58->id ^ 1;
            }
        }
    }
    if (D_800FABD0->f14 == 1)
    {
        if (D_800FABD0->f5C & 0x1110000)
        {
            func_800AA290();
        }
        if (D_800FABD0->f5C & 0x20000)
        {
            func_800AA290();
        }
        if (D_800FABD0->f5C & 0x40000)
        {
            func_800AA9A0();
        }
        if (D_800FABD0->f5C & 0x200000)
        {
            func_800AABA0();
        }
        if (D_800FABD0->f5C & 0x80000)
        {
            func_800AABF8();
        }
        if (D_800FABD0->f5C & 0x400000)
        {
            selectActionVariant();
        }
        if (D_800FABD0->f5C & 0x800000)
        {
            selectActionVariant();
        }
    }
}
