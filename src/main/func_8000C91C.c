/* @header
 * func_8000C91C
 * VRAM 0x8000C91C | ROM 0xD51C | size 0x3FC
 * asm: asm/nonmatchings/main/func_8000C91C.s
 */
#include "common.h"

extern u16 D_80036746;
extern u16 *D_80031998[];
extern void ***D_80032B44[];
extern s16 D_8003673C[];
extern u16 D_8006A2A4[];
extern s16 D_8007DFB0[];
extern s16 D_8007DFBC[];
extern u16 D_800566E0[];
extern s8 D_800566E8[];
extern u8 D_800706A4[];
extern u8 D_80075468[];
extern s16 D_80075440[][3];
extern s16 D_8007C318[][23];
#ifndef TARGET_PC /* on PC, port_decls.h declares D_8007C438 */
extern s32 D_8007C438[][23];
#endif
#ifndef TARGET_PC /* on PC, port_decls.h declares D_8007C3D0; its label D_8007C3D8 has no PC symbol */
extern s32 D_8007C3D0[][4];
extern s32 D_8007C3D8[][4];
#endif
extern u8 D_800651A0[];
#ifndef TARGET_PC /* on PC, port_decls.h declares D_80073EB0 */
extern u8 D_80073EB0[];
#endif
extern u8 D_800517D0[];
#ifndef TARGET_PC /* on PC, port_decls.h declares D_80050800 */
extern u8 D_80050800[];
#endif

typedef struct {
    u8 d[0xDC];
} ObjC91C;

#ifdef TARGET_PC
/* PC: a slot of D_80073EB0 holds display records, whose PC layout is Nw2Descr4BA8 (common.h, 0x50 bytes). */
typedef Nw2Descr4BA8 SlotC91C;
#else
typedef struct {
    u8 d[0x2C];
} SlotC91C;
#endif

void func_80004B34(void *, void *, s32, f32, f32, f32);
void func_80007A74(void *, s32, s32);
void func_80008B5C(s16);
void func_80008C94(s16);
void func_8000BDD0(s16);
void func_8000C1B8(s16, s16);
void buildObjectChain(void *, void *);

/* Entry n of the list for animation id `id` (bank in bits 8-12, 1-based index in bits 0-4).
 * Written as an inline with an s16 index: the parameter copy changes local allocation so the
 * list pointer gets a3 and the two sign-extended bytes get t1/t0 as in the ROM. */
inline static void *getEntry(u32 id, s16 n)
{
    s32 bank = (id >> 8) & 0x1F;
    s32 idx = (id & 0x1F) - 1;
    return D_80032B44[bank][idx][n];
}

void func_8000C91C(s16 arg0, u16 arg1, s16 arg2, s16 arg3, s32 arg4, s8 arg5, s8 arg6)
{
    u32 i;
    void **list;
    s32 count;
    s32 bank;
    s32 idx;
    u8 *e;
    ObjC91C *a;
    SlotC91C *s;
    s32 lim;
    s16 first;
    s16 second;

    if (D_80036746 != 0)
    {
        u32 j;
        D_80036746 = 0;
        for (i = 0; i < 4; i++)
        {
            ((s16 *) D_8006A2A4)[i] = -1;
            D_8007DFBC[i] = -1;
            D_8007DFB0[i] = -1;
            D_800706A4[i] = 0;
            D_80075468[i] = 0x32;
            ((s16 *) D_800566E0)[i] = -1;
            D_800566E8[i] = -1;
            for (j = 0; j < 23; j++)
            {
                D_8007C438[i][j] = 0;
                D_8007C318[i][j] = 0;
            }
            for (j = 0; j < 3; j++)
            {
                D_80075440[i][j] = 0;
            }
#ifdef TARGET_PC
            /* PC: the arena's two bases by name (Nw2MeshArena in common.h); D_8007C3D8 is arena 0's cmds. */
            D_8007C3D0[i].verts = NULL;
            D_8007C3D0[i].cmds = NULL;
#else
            D_8007C3D0[i][0] = 0;
            D_8007C3D8[i][0] = 0;
#endif
        }
    }
    bank = (arg1 >> 8) & 0x1F;
    idx = (arg1 & 0x1F) - 1;
    lim = D_8003673C[D_80031998[bank][idx] & 0x7F];
    if (arg2 >= lim)
    {
        arg2 = 0;
    }
    list = D_80032B44[bank][idx];
    for (count = 0; list[count] != NULL; count++)
    {
    }
    first = arg5;
    second = arg6;
    if ((s16) count <= arg3)
    {
        arg3 = 0;
    }
    D_8006A2A4[arg0] = arg1;
    D_8007DFBC[arg0] = arg2;
    D_8007DFB0[arg0] = arg3;
    D_800566E0[arg0] = D_8006A2A4[arg0];
    e = getEntry(D_8006A2A4[arg0], D_8007DFB0[arg0]);
#ifdef TARGET_PC
    /* PC: the player's slot of 23 display records (port_decls.h). */
    s = D_80073EB0[arg0];
#else
    s = (SlotC91C *) (D_80073EB0 + arg0 * 0x3F4);
#endif
    a = (ObjC91C *) (D_800651A0 + arg0 * 0x13C4);
    D_80075440[arg0][0] = *(u16 *) (e + 0x16);
    D_80075440[arg0][1] = first;
    D_80075440[arg0][2] = second;
    for (i = 0; i < 23; i++)
    {
        func_80004B34(&a[i], &s[i], 4, 0.0f, 0.0f, 0.0f);
    }
#ifdef TARGET_PC
    /* PC: the player's arena (Nw2MeshArena, 0x20 bytes on PC). */
    func_80007A74(&D_8007C3D0[arg0], 0x2BC, 0x4B0);
#else
    func_80007A74(D_8007C3D0[arg0], 0x2BC, 0x4B0);
#endif
    func_8000BDD0(arg0);
    func_8000C1B8(arg0, 0);
    func_8000C1B8(arg0, 1);
    func_80008B5C(arg0);
    func_80008C94(arg0);
#ifdef TARGET_PC
    /* PC: the player's slot of 23 display records of D_80050800 (port_decls.h); the objects keep their N64 size. */
    buildObjectChain(D_800517D0 + arg0 * 0x13C4, D_80050800[arg0]);
#else
    buildObjectChain(D_800517D0 + arg0 * 0x13C4, D_80050800 + arg0 * 0x3F4);
#endif
}
