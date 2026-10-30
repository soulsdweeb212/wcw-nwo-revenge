/* @header
 * func_80021A50
 * VRAM 0x80021A50 | ROM 0x22650 | size 0x44
 * asm: asm/nonmatchings/main/func_80021A50.s
 */
#include "common.h"

extern void *D_8003761C;
extern u8 D_80065128[];
extern u8 D_8006512C;
extern u8 D_8006512D;
extern u8 D_8006512E;
extern u8 D_8006512F;
extern u8 D_80065130;
extern u8 D_80065131;
extern u8 D_80065134;
extern u32 D_80065138;
extern u8 D_80070A98;

s32 nw2DisableInterrupts(void);
void nw2RestoreInterrupts(s32);
void func_80021F60(u8 *, s32);
void *memset(void *, s32, s32);

/* Registers arg0 as the active PI handle and returns the previous one. */
s32 func_80021A50(void **arg0) {
    s32 t;
    void *old;

    t = nw2DisableInterrupts();
    old = D_8003761C;
    D_8003761C = arg0;
    *arg0 = old;
    nw2RestoreInterrupts(t);
    return 0;
}

typedef struct {
    u8 b0, b1, b2, b3, b4, b5, b6, b7;
} Cmd8;
extern Cmd8 D_8006A260[];
