/* @header
 * func_80094424
 * VRAM 0x80094424 | ROM 0x878C4 | size 0x3E0
 * asm: asm/nonmatchings/ovl2_80090000/func_80094424.s
 */
#include "common.h"

typedef struct {
    s32 flags;
} Node;

typedef struct {
    u8 pad0[0x10];
    s32 f10;
    Node *node;
    u8 pad18[0xC4];
} ObjDC;

typedef struct {
    u8 data[0x2C];
} Rec2C;

typedef struct {
    u8 data[8];
} Tex8;

extern ObjDC D_800E77C0;
extern void *D_800E789C[];
extern Tex8 D_800E78A8[];
extern ObjDC D_800E7950[];
extern Tex8 D_800E7DA0[];
extern Rec2C D_800E7FB8[];
extern Rec2C D_800E8040[];
extern Rec2C D_800E8438[][10];
extern Rec2C D_800E87A8[][10];
extern Rec2C D_800E8CE8[];
extern Rec2C D_800E8D40[];
extern Rec2C D_800E8F60[];
extern Rec2C D_800E9098[];
extern Rec2C D_800E9398[];
extern Rec2C D_800E93F0[];
extern Rec2C D_800E97C0[];
extern Rec2C D_800E9818[];
extern Tex8 D_800E9BE8[];
extern Rec2C D_800E9C88[];
extern Tex8 D_800EA0E0[];
extern Tex8 D_800EA100[];
extern Tex8 D_800EA110[];
extern Rec2C D_800EA1B0[];
extern Tex8 D_800EA5D8;
extern Tex8 D_800EA5E0;
extern Rec2C D_800EA5E8[];
extern Rec2C D_800EA698[];
extern Tex8 D_800EA748[];
extern Rec2C D_800EAAC8[];
extern Rec2C D_800EAC58;
extern Rec2C D_800EAFF8[];
void func_80006D14(void *);
void func_80006E2C(void *);
void releaseHeapBlock(void *);
void releaseObjectHeapBlocks(void *);

void func_80094424(void) {
    u32 i;
    u32 j;

    for (i = 0; i < 5; i++) {
        func_80006D14(&D_800E7950[i]);
    }
    for (i = 0; i < 11; i++) {
        func_80006E2C(&D_800E7DA0[i]);
    }
    D_800E77C0.f10 = 0;
    func_80006D14(&D_800E77C0);
    for (i = 0; i < 3; i++) {
        releaseHeapBlock(D_800E789C[i]);
    }
    for (i = 0; i < 19; i++) {
        func_80006E2C(&D_800E78A8[i]);
    }
    for (i = 0; i < 3; i++) {
        releaseObjectHeapBlocks(&D_800E7FB8[i]);
        releaseObjectHeapBlocks(&D_800E8040[i]);
    }
    for (j = 0; j < 2; j++) {
        for (i = 0; i < 10; i++) {
            releaseObjectHeapBlocks(&D_800E8438[j][i]);
            releaseObjectHeapBlocks(&D_800E87A8[j][i]);
        }
    }
    for (i = 0; i < 2; i++) {
        releaseObjectHeapBlocks(&D_800E8CE8[i]);
        releaseObjectHeapBlocks(&D_800E8D40[i]);
    }
    for (i = 0; i < 7; i++) {
        releaseObjectHeapBlocks(&D_800E8F60[i]);
        releaseObjectHeapBlocks(&D_800E9098[i]);
    }
    for (i = 0; i < 2; i++) {
        releaseObjectHeapBlocks(&D_800E9398[i]);
        releaseObjectHeapBlocks(&D_800E93F0[i]);
    }
    for (i = 0; i < 2; i++) {
        releaseObjectHeapBlocks(&D_800E97C0[i]);
        releaseObjectHeapBlocks(&D_800E9818[i]);
    }
    for (i = 0; i < 20; i++) {
        func_80006E2C(&D_800E9BE8[i]);
    }
    for (i = 0; i < 4; i++) {
        releaseObjectHeapBlocks(&D_800E9C88[i]);
    }
    for (i = 0; i < 4; i++) {
        func_80006E2C(&D_800EA0E0[i]);
    }
    for (i = 0; i < 2; i++) {
        func_80006E2C(&D_800EA100[i]);
    }
    for (i = 0; i < 20; i++) {
        func_80006E2C(&D_800EA110[i]);
    }
    func_80006E2C(&D_800EA5D8);
    func_80006E2C(&D_800EA5E0);
    for (i = 0; i < 2; i++) {
        func_80006E2C(&D_800EA748[i]);
    }
    for (i = 0; i < 4; i++) {
        releaseObjectHeapBlocks(&D_800EA1B0[i]);
        releaseObjectHeapBlocks(&D_800EAFF8[i]);
        releaseObjectHeapBlocks(&D_800EA5E8[i]);
        releaseObjectHeapBlocks(&D_800EA698[i]);
        releaseObjectHeapBlocks(&D_800EAAC8[i]);
        releaseObjectHeapBlocks(&D_800EAC58);
    }
}
