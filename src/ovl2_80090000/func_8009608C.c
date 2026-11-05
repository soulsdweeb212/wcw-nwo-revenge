/* @header
 * func_8009608C
 * VRAM 0x8009608C | ROM 0x8952C | size 0x184
 * asm: asm/nonmatchings/ovl2_80090000/func_8009608C.s
 */
#include "common.h"

typedef struct {
    u8 data[0x2C];
} Rec2C;

typedef struct {
    s32 flags;
} Node;

typedef struct {
    u8 pad0[0x14];
    Node *node;
    u8 pad18[0xC4];
} ObjDC;

extern s16 D_800E2D8E[];
extern ObjDC D_800E7DF8;
extern ObjDC D_800E7ED8;
extern Rec2C D_800E7F8C[];
extern Rec2C D_800E8014[];
extern s16 D_800E80C4;
extern s16 D_800E80C6;
extern s16 D_800F99B6;
void func_8000DEE4(s16);
void func_800907A0(void *, Rec2C *, s16, s16, f32, f32, f32, f32, u8, u8, u8, u8);
void func_8009786C(s32);

void func_8009608C(s16 arg0) {
    if (D_800F99B6 != 0) {
        return;
    }
    if ((u16)(arg0 - 1) < 3) {
        if (D_800E7DF8.node->flags & 0x80) {
            D_800E80C4 = 0;
        }
        if (D_800E80C4 != arg0) {
            func_8000DEE4(D_800E2D8E[arg0]);
            D_800E80C4 = arg0;
            D_800E80C6 = 0;
            func_800907A0(&D_800E7DF8, &D_800E7F8C[arg0], 0xF0, 0xA, 0.5f, 0.0f, 1.0f, 1.0f, 0xFF, 0xFF, 0xFF, 0xF);
            func_800907A0(&D_800E7ED8, &D_800E8014[D_800E80C4], 0xF0, 0xA, 0.5f, 0.0f, 1.0f, 1.0f, 0xFF, 0, 0, 0);
        }
    }
    func_8009786C(1);
}
