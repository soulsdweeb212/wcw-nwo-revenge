/* @header
 * releaseAllResources1211C  (originally func_8001211C)
 * VRAM 0x8001211C | ROM 0x12D1C | size 0x248
 * asm: asm/nonmatchings/main/releaseAllResources1211C.s
 */
#include "common.h"

/* Releases every cached resource descriptor array and clears its handle:
 * the eleven fixed pools, the six per-entry arrays D_8005B110/D_8005B0F8,
 * the final resource D_8005B218, then the 26 descriptor-record array entries
 * (func_80006E2C) and finally the 4x3 per-player resources D_8005AAA0. */
extern s32 D_8005AAE0, D_8005AB40, D_8005ABA0, D_8005AC2C, D_8005ACB4, D_8005AD3C, D_8005ADC4, D_8005AE4C, D_8005AEA8, D_8005AFE4, D_8005B06C, D_8005B218;
extern u8 D_8005AAE8[], D_8005AB48[], D_8005ABA8[], D_8005AC30[], D_8005ACB8[], D_8005AD40[], D_8005ADC8[], D_8005AE50[], D_8005AEB0[], D_8005AFE8[], D_8005B070[], D_8005B110[][44], D_8005B220[][8];
extern s32 D_8005B0F8[], D_8005AAA0[][4];
void releaseHeapBlock(s32);
void func_80006E2C(void *);
void freeResourceDescriptorArray(void *, s32, s32);

void releaseAllResources1211C(void) {
    u32 i, j;
    freeResourceDescriptorArray(D_8005AAE8, D_8005AAE0, 2); D_8005AAE0 = 0;
    freeResourceDescriptorArray(D_8005AB48, D_8005AB40, 2); D_8005AB40 = 0;
    freeResourceDescriptorArray(D_8005ABA8, D_8005ABA0, 3); D_8005ABA0 = 0;
    freeResourceDescriptorArray(D_8005AC30, D_8005AC2C, 3); D_8005AC2C = 0;
    freeResourceDescriptorArray(D_8005ACB8, D_8005ACB4, 3); D_8005ACB4 = 0;
    freeResourceDescriptorArray(D_8005AD40, D_8005AD3C, 3); D_8005AD3C = 0;
    freeResourceDescriptorArray(D_8005ADC8, D_8005ADC4, 3); D_8005ADC4 = 0;
    freeResourceDescriptorArray(D_8005AE50, D_8005AE4C, 2); D_8005AE4C = 0;
    freeResourceDescriptorArray(D_8005AEB0, D_8005AEA8, 7); D_8005AEA8 = 0;
    freeResourceDescriptorArray(D_8005AFE8, D_8005AFE4, 3); D_8005AFE4 = 0;
    freeResourceDescriptorArray(D_8005B070, D_8005B06C, 3); D_8005B06C = 0;
    for (i = 0; i < 6; i++) {
        freeResourceDescriptorArray(D_8005B110[i], D_8005B0F8[i], 1);
        D_8005B0F8[i] = 0;
    }
    releaseHeapBlock(D_8005B218); D_8005B218 = 0;
    for (i = 0; i < 26; i++)
        func_80006E2C(D_8005B220[i]);
    for (i = 0; i < 4; i++)
        for (j = 0; j < 3; j++) {
            releaseHeapBlock(D_8005AAA0[i][j]);
            D_8005AAA0[i][j] = 0;
        }
}
