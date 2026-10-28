#include "common.h"

extern void func_8009678C(void);
extern void func_80096018(void);
extern void func_800DA8B4(void *, s32, s32);
extern void func_800B9730(void *, void *, s32, s32);
extern s16 func_800BF2FC(void *);
extern s8 D_8007E8C0[];
extern u8 D_800E3978[], D_800EB468[], D_800FACE8;
extern s8 D_800EB46E, D_800EB46F;
extern u8 D_800FAF60[][6];
extern s16 D_800EB472;
extern u8 D_800F9D10[], D_800F9D1A[];
extern s8 D_800FA05C[], D_800FA063[], D_800FA0A6[];
/* Resets all four entities to the -1 id with the 0x100800 mode flags. */
void func_800B8C94(void) {
    s8 entries[4];
    s16 i;
    for (i = 0; i < 4; i++) entries[i] = -1;
    func_800B9730(entries, entries, 0x100800, 1);
    D_800EB472 = 1;
}
