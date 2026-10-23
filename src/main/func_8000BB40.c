#include "common.h"

extern u8 ***D_80032B44[];
extern u16 D_8006A2A4[];
extern s16 D_8007DFB0[];
extern u16 D_80075440[][3];
extern s16 D_80075442[][3], D_80075444[][3];
extern void *D_8007C438[][23];
extern s32 D_80073ECC[][23][11];
void func_8000B884(s32, s16, s16);
/* Set the entity's active animation slot: store the caller-supplied pair of
 * halfwords (arg2/arg3) plus the u16 attribute value looked up from the
 * animation tables (D_80032B44 group/index -> D_8007DFB0 record +0x16), then
 * rebuild the display list of every populated body part via func_8000B884. */
void func_8000BB40(s16 arg0, s32 arg1, s8 arg2, s8 arg3) {
    s16 first = arg2;
    u32 part;
    u16 animId;
    s16 second;
    s32 group, index;
    u16 attrValue;
    animId = D_8006A2A4[arg0];
    second = arg3;
    part = 0;
    group = (animId >> 8) & 31;
    index = (animId & 31) - 1;
    attrValue = *(u16 *)((*(u8 ***)((u8 *)D_80032B44[group] + index * 4))[D_8007DFB0[arg0]] + 0x16);
    D_80075442[arg0][0] = first;
    D_80075444[arg0][0] = second;
    D_80075440[arg0][0] = attrValue;
    do {
        if (D_8007C438[arg0][part] != 0) func_8000B884(D_80073ECC[arg0][part][0], arg0, (s16)part);
        part++;
    } while (part < 23);
}
