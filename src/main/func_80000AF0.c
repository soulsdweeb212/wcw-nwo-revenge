/* @header
 * func_80000AF0
 * VRAM 0x80000AF0 | ROM 0x16F0 | size 0x238
 * asm: asm/nonmatchings/main/func_80000AF0.s
 */
#include "common.h"

extern u8 D_80044570[];
extern u8 D_80037650[];
extern u8 D_800420C0[];
extern u8 D_800440C0[];
extern s32 D_80044574;
extern s32 D_80044578;
extern void *D_80044580;
void func_80000E0C(void);
void rspTaskThread(void);
void renderTaskThread(void);
s32 func_8001C890(void *, void *, s32);
s32 func_8001C8C0(void *, s32, void *, void *, void *, s32);
s32 func_8001CBF0(s32, void *, s32);
void startThread(void *);
void func_80020E70(void *, s32, s32);
void func_80020ED0(void *);
void func_80021130(s32);
void createViManager(s32);

typedef struct {
    s16 state;
    u8 pad2[0x1E];
    s16 f20;
    u8 pad22[0x1E];
    u8 mq[0x18];
    u8 msgs[0x58];
    u8 thread[0x1B0];
    s32 f260;
    u8 pad264[0x18];
    s32 f27C;
} Mgr;

void func_80000AF0(Mgr *arg0, void *arg1, s32 arg2, u8 arg3, u8 arg4) {
    u8 *base;
    u8 *s4;
    u8 *s5;
    u8 *s6;

    D_80044580 = arg0;
    arg0->state = 1;
    arg0->f260 = 0;
    arg0->f27C = 0;
    arg0->f20 = 4;
    base = D_80044570;
    *(s32 *)base = 0;
    D_80044574 = 0;
    D_80044578 = 0;
    func_8001C890(arg0->mq, arg0->msgs, 8);
    func_8001C890(base - 0x478, base - 0x460, 8);
    s4 = base - 0x4B0;
    func_8001C890(s4, base - 0x498, 8);
    s6 = base - 0x440;
    func_8001C890(s6, base - 0x428, 8);
    s5 = base - 0x408;
    func_8001C890(s5, base - 0x3F0, 8);
    func_8001C890(base - 0x398, base - 0x380, 8);
    func_8001C890(base - 0x3D0, base - 0x3B8, 8);
    createViManager(0xFE);
    func_80020ED0(((arg3 & 0xFF) * 0x50) + D_80037650);
    func_80021130(1);
    func_80020E70(arg0->mq, 0x29A, arg4);
    func_8001CBF0(0xE, arg0->mq, 0x29D);
    func_8001CBF0(4, s6, 0x29B);
    func_8001CBF0(9, s5, 0x29C);
    func_8001C8C0(arg0->thread, 4, func_80000E0C, arg0, arg1, 0x78);
    startThread(arg0->thread);
    func_8001C8C0(base - 0x360, 0x12, rspTaskThread, s4, D_800420C0, 0x6E);
    startThread(base - 0x360);
    func_8001C8C0(base - 0x1B0, 0x11, renderTaskThread, s4, D_800440C0, 0x64);
    startThread(base - 0x1B0);
}
