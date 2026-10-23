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
/* Reinitialize the shared collision state and cache the current track id. */
void func_800B9148(void) {
    func_8009678C();
    func_800DA8B4(D_800EB468, 0, 0);
    D_800FACE8 = D_800E3978[D_8007E8C0[0x66C]];
}
/* Reset the four 6-byte D_800FAF60 entries. */
void func_800B8D04(void) {
    s16 i;
    D_800EB46E = 0;
    D_800EB46F = -1;
    func_80096018();
    for (i = 0; i < 4; i++) {
        func_800DA8B4(D_800FAF60[i], 0, 0);
    }
}
/* Initialize the four entries to -1 and set the marker D_800EB472. */
void func_800B8C94(void) {
    s8 entries[4];
    s16 i;
    for (i = 0; i < 4; i++) entries[i] = -1;
    func_800B9730(entries, entries, 0x100800, 1);
    D_800EB472 = 1;
}
/* Report whether entity arg0 is close enough to trigger a reaction. */
s32 func_800B83CC(s16 arg0) {
    s32 offset = arg0 * 0x3B0;
    s32 condition;
    s32 result;
    if (*(s16 *)(D_800F9D1A + offset) == 0x3D) {
        condition = D_800FA05C[offset + D_800FA0A6[D_800FA063[offset] * 0x3B0]] < 10;
    } else {
        condition = func_800BF2FC(D_800F9D10 + offset) < 25;
    }
    result = 1;
    if (condition == 0) result = 0;
    return result;
}
