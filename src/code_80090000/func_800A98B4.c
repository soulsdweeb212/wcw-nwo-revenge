/* @header
 * func_800A98B4
 * VRAM 0x800A98B4 | ROM 0x56024 | size 0x2DC
 * asm: asm/nonmatchings/code_80090000/func_800A98B4.s
 */
#include "common.h"

extern u8 D_8007EF30[];
#define F16(o) (*(u16 *)(D_8007EF30 + (o)))
#define S16(o) (*(s16 *)(D_8007EF30 + (o)))
#define F32(o) (*(s32 *)(D_8007EF30 + (o)))
extern struct { u8 pad[0x620]; s32 f; } D_8007E228;
extern s8 D_800CC8F5[][12];
extern s32 D_80038A8C, D_80038A98, D_80038AA8;
extern s16 D_80038A90, D_80038A92, D_800E7CB8, D_800E9F7C;
extern s32 D_800E6B88, D_800E6B90, D_800E74C8, D_800E74E0, D_800E7530, D_800E798C, D_800E79CC, D_800E7C90;
extern s32 D_800E9F70, D_800E9F8C, D_800E9F90, D_800EA0B4, D_800EA318;
extern u8 lookupSubTables[];
void func_8000DEE4(s32);
void func_800A9108(void);
void func_800AD840(void);
void func_800AEF28(s32);
void func_800B2588(void);
void func_800B50CC(void);
void func_800B511C(s32);
void func_800B807C(s32, s32);
void func_800BA058(void);
void func_800BA59C(s32);
void func_800BABF4(void);
void func_800BC32C(void);

void func_800A98B4(void) {
    s32 i, j;
    u8 *q;

    D_80038A8C = 0;
    D_800EA318 = -1;
    if ((u16)D_80038A92 < 2) {
        D_800E798C = 0;
        D_800E9F90 = 0;
        D_800E9F8C = 0;
        D_800E74E0 = 0;
        D_800E7C90 = 0;
        if (D_80038A92 == 0) {
            D_80038A90 = 0;
        } else {
            D_80038A90 = 1;
            func_800AD840();
            D_800E74C8 = 0xFF;
        }
        F16(0xE) = 0;
        *(void **)(D_8007EF30 + 0x2C) = lookupSubTables;
        F16(0x12) = 0;
        F16(0x10) = 0;
        F32(0x20) = 0;
        F32(0x1C) = 0;
        F16(0x18) = 8;
        F16(8) = 0;
        F16(0x28) = 0;
        F16(0x26) = 0;
        F16(0x24) = 0;
        for (j = 0; j < 8; j++) {
            i = j * 16;
            q = D_8007EF30 + 8 + i;
            *(s16 *)(q + 0x46) = -1;
            S16(0x4C + i) = -1;
            D_8007EF30[0x52 + i] = 5;
        }
        func_800BA058();
        func_800BA59C(0);
        func_800A9108();
        D_80038AA8 = 0;
        for (i = 0x27; i >= 0; i--) {
            F16(0xC90 + i * 2) = 0;
        }
        if (D_80038A98 != 0) {
            func_800AEF28(0);
        }
        F16(0xC) = 8;
        D_8007E228.f = 0;
    } else if (D_80038A92 == 0x15) {
        func_800BC32C();
    } else {
        func_800BABF4();
        D_800E798C = 0;
        D_800E9F90 = 0;
        D_800E9F8C = 0;
        D_800E74E0 = 0;
        D_800E7C90 = 0;
        D_800E74C8 = 0xFF;
        if (D_8007E228.f == 0) {
            D_80038A90 = 1;
            func_800AD840();
            D_800E74C8 = 0xFF;
        } else {
            func_8000DEE4(0x411);
            D_80038A90 = 0xF;
            func_800B2588();
        }
    }
    D_800E9F7C = 1;
    D_800E79CC = 0;
    F32(0xD00) = 0;
    D_800E7CB8 = 0;
    D_800E6B88 = 0;
    D_800E6B90 = 0;
    D_800EA0B4 = -1;
    D_800E7530 = -1;
    if (D_80038A98 != 0) {
        func_800B807C(0, 0);
        D_800E9F70 = D_8007EF30[4];
        func_800B50CC();
        func_800B511C(D_800CC8F5[D_80038A90][0]);
    }
}
