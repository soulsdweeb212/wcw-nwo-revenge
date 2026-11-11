/* @header
 * func_8000C1B8
 * VRAM 0x8000C1B8 | ROM 0xCDB8 | size 0x2BC
 * asm: asm/nonmatchings/main/func_8000C1B8.s
 */
#include "common.h"

void loadTextureIntoCacheSlot(void *, s16, s16, s16, s16);
void func_80004F80(void *, s16, s16);
void func_80004FC0(void *);
void func_8000670C(void *, s16, s16);
#ifndef TARGET_PC /* on PC, port.h declares the loader functions */
void lookupResourceDescriptor(void *, u16);
#endif
extern u16 D_8006A2A4[];
extern s8 D_80031088[];
extern u16 *D_80031998[];
extern void ***D_80032B44[];
extern void ***D_800360F0[];
#ifndef TARGET_PC /* on PC, port_decls.h declares D_80070458: four picture pairs */
extern u8 D_80070458[];
#endif
extern s8 D_800706A4[];
extern s16 D_80073E90[];
#ifndef TARGET_PC /* on PC, port_decls.h declares D_80073EB0: four rows of 23 display records */
extern u8 D_80073EB0[];
#endif
extern s16 D_8007DFB0[];
extern s16 D_8007DFBC[];

typedef struct {
    s16 f0;
    s16 f2;
    s16 f4;
    s16 f6;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 fE;
    s16 f10;
    s16 f12;
    s16 f14;
    s16 f16;
} Nw2C1B8Rec;

#ifdef TARGET_PC
/* PC: a display record is Nw2Descr4BA8 (common.h), 0x50 bytes on PC, so a row of D_80073EB0 is stepped by its size. */
typedef Nw2Descr4BA8 Slot2C1B8;
#else
typedef struct { u8 data[0x2C]; } Slot2C1B8;
#endif

void func_8000C1B8(s16 arg0, s16 arg1) {
    s32 buf[4];
    u32 i;
    u16 w;
    s32 idx;
    s32 bank;
    u16 *a3;
    Nw2C1B8Rec *s3;
    s16 (*s4)[2];
    Slot2C1B8 *s5;
    s8 v;

    w = D_8006A2A4[arg0];
    bank = (w >> 8) & 0x1F;
    idx = (w & 0x1F) - 1;
#ifdef TARGET_PC
    /* PC: the same address arithmetic in an integer as wide as a pointer (uptr); a u32 would cut the table's
     * 64-bit address in half. idx can be -1, which steps back 2 bytes on both. */
    a3 = (u16 *)(idx * 2 + (uptr)D_80031998[bank]);
#else
    a3 = (u16 *)(idx * 2 + (u32)D_80031998[bank]);
#endif
    s3 = (Nw2C1B8Rec *)D_80032B44[bank][idx][D_8007DFB0[arg0]];
    s4 = (s16 (*)[2])D_800360F0[*a3 & 0x7F][D_8007DFBC[arg0]][s3->f16];
#ifdef TARGET_PC
    /* PC: player arg0's row of 23 display records, by index; the N64 steps 0x3F4 bytes, 23 records of 0x2C. */
    s5 = D_80073EB0[arg0];
#else
    s5 = (Slot2C1B8 *)(D_80073EB0 + arg0 * 0x3F4);
#endif
    if (arg1 == 0) {
        for (i = 1; i < 0xD; i++) {
            v = D_80031088[i];
            if (v >= 0) {
                loadTextureIntoCacheSlot(&s5[i], s4[v][2], s4[v][1], arg0, i);
            }
        }
        loadTextureIntoCacheSlot(&s5[4], s3->f8, s3->f6, arg0, 4);
        func_80004F80(&s5[5], s3->fC, s3->fA);
        if (s3->f12 != 0) {
            s32 sz;
#ifdef TARGET_PC
            /* PC: player arg0's picture pair, by index; a pair is two pointers (Nw2TexPair, 16 bytes), not 8 bytes. */
            func_8000670C(&D_80070458[arg0], s3->f14, s3->f12);
#else
            func_8000670C(D_80070458 + arg0 * 8, s3->f14, s3->f12);
#endif
            lookupResourceDescriptor(buf, s3->f12);
            sz = buf[2];
            D_800706A4[arg0] = 1;
            D_80073E90[arg0] = sz;
            return;
        }
        D_800706A4[arg0] = 0;
        return;
    }
    for (i = 0xD; i < 0x14; i++) {
        v = D_80031088[i];
        if (v >= 0) {
            loadTextureIntoCacheSlot(&s5[i], s4[v][2], s4[v][1], arg0, i);
            if (i != 0xF && s4[D_80031088[i]][2] < 0x9ED) {
                func_80004FC0(&s5[i]);
            }
        }
    }
    if (s3->f4 != 0) {
        func_80004F80(&s5[20], s3->f10, s3->fE);
    }
}
