/* @header
 * func_800BA770
 * VRAM 0x800BA770 | ROM 0xADC10 | size 0x4C0
 * asm: asm/nonmatchings/code_8009D7A0/func_800BA770.s
 */
#include "common.h"

extern u8 D_800FADB9[];
extern u16 D_800FADD2[];
extern u16 D_800F9B80[];
extern u16 D_800F9B68[];
extern u16 D_800FADC6[];
extern u16 D_800F9B78[];
extern u8 D_8007E228[];
extern u8 D_80070494[];
extern u8 D_8007EF30[];
void func_800BF548(void *, s16);
void updateEntityStunTimer(void *, s32, s32);
void func_800C2B20(s8);
void func_800A97A0(s32);
void func_800D9234(s32);
void func_800BF254(s32);
void func_800D43B4(void *, s32, s32);
void func_800BA770(s8 arg0, s16 arg1, s32 arg2)
{
    s32 a1off;
    s32 key;
    Wrestler *ent;
    s8 idx;
    u8 *p;
    s32 off;
    key = arg2 << 16;
    idx = arg0;
    D_800F9D10[idx].id = arg0;
    D_800F9D10[idx].spirit = 0x32;
    D_800F9D10[idx].characterId = arg1;
    D_800F9D10[idx].comboHits = 0;
    D_800F9D10[idx].escapeTimer = 0;
    D_800F9D10[idx].heldById = 0;
    D_800F9D10[idx].secondAttackerId = 0;
    D_800F9D10[idx].attached[0] = -1;
    D_800F9D10[idx].attached[1] = -1;
    D_800F9D10[idx].steppedOverId = -1;
    D_800F9D10[idx].frameStatus = 0;
    D_800F9D10[idx].y = 90.0f;
    do
    {
    }
    while (0);
    if (key == 0)
    {
        s32 v1 = idx * 8;
        D_800F9D10[idx].state = 0;
        D_800F9D10[idx].step = 0;
        D_800F9D10[idx].healthMax = D_8007E228[v1 + 0x60];
        D_800F9D10[idx].health = D_8007E228[v1 + 0x60];
        D_800F9D10[idx].bodyPart[0] = D_8007E228[v1 + 0x61];
        D_800F9D10[idx].bodyPart[1] = D_8007E228[v1 + 0x64];
        D_800F9D10[idx].bodyPart[2] = D_8007E228[v1 + 0x62];
        D_800F9D10[idx].bodyPart[3] = D_8007E228[v1 + 0x63];
        D_800F9D10[idx].bodyPart[4] = D_8007E228[v1 + 0x65];
        D_800FADB9[idx] = D_8007E228[v1 + 0x67];
    }
    else
    {
        D_800F9D10[idx].healthMax = 0xFF;
        D_800F9D10[idx].health = 0xFF;
        D_800F9D10[idx].bodyPart[0] = 0x32;
        D_800F9D10[idx].bodyPart[1] = 0x32;
        D_800F9D10[idx].bodyPart[2] = 0x32;
        D_800F9D10[idx].bodyPart[3] = 0x32;
        D_800F9D10[idx].bodyPart[4] = 0x32;
        D_800FADB9[idx] = 0;
        do
        {
            D_800F9D10[idx].flags &= 0x200000204ULL;
        }
        while (0);
    }
    idx = arg0;
    ent = &D_800F9D10[idx];
    D_800F9D10[idx].profile = (D_80070494 + 0x10C) + (idx << 6);
    D_800FADD2[idx] = 0;
    D_800F9B80[idx] = 0;
    D_800F9B68[idx] = 0;
    D_800FADC6[idx] = 0;
    D_800F9B78[idx] = 0x1E;
    func_800BF548(ent, 0);
    updateEntityStunTimer(ent, 0, 0);
    func_800C2B20(idx);
    func_800A97A0(idx);
    func_800D9234(idx);
    func_800BF254(idx);
    func_800D43B4(ent, 0xE39, 0);
    p = D_800F9D10[idx].profile;
    if ((*((u64 *) (p + 0x38))) & 0x20000000000ULL)
    {
        D_800F9D10[idx].flags |= 1ULL;
    }
    p = D_800F9D10[(s8) arg0].profile;
    if ((*((u64 *) (p + 0x38))) & 2ULL)
    {
        D_800F9D10[(s8) arg0].flags |= 8ULL;
    }
    arg1 = 0;
    a1off = ((s8) arg0) * 0x2B8;
    off = a1off;
    do
    {
        s32 o = (arg1 * 8) + off;
        *((u32 *) ((D_8007EF30 + 0x1B0) + o)) = 0;
        *((u32 *) ((D_8007EF30 + 0x1B4) + o)) = 0;
        arg1 += 1;
    }
    while (arg1 < 0x57);
}
