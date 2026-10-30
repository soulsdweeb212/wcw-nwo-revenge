/* @header
 * func_800004B8
 * VRAM 0x800004B8 | ROM 0x10B8 | size 0xC8
 * asm: asm/nonmatchings/main/func_800004B8.s
 */
#include "common.h"

extern s32 D_80000300;
extern u8 D_8003DC80[];
extern u8 D_8003DD80[];
extern s32 D_8003DD98;
extern s32 D_8003DDC4;
extern u8 D_8003DE30[];
extern u8 D_800400C0[];
void createPiManager(s32, void *, void *, s32);
s32 initControllerPakDescriptor(void);
void func_80000AF0(void *, void *, s32, s32, s32);
void func_800130A0(s32);
void func_8001CC50(s32, s32);
void func_8001C580(void);

/* Main startup: create the PI manager, initialize the Controller Pak descriptor (storing
 * it in D_8003DD98), bring the game up via func_80000AF0 (region mode 2 when D_80000300
 * is 1, else 0x1E), run func_800130A0(arg0), start the scheduler and then spin forever in
 * func_8001C580. */
void func_800004B8(s32 arg0) {
    createPiManager(0x96, D_8003DD80, D_8003DC80, 0x40);
    D_8003DD98 = initControllerPakDescriptor();
    D_8003DDC4 = 0;
    if (D_80000300 == 1) {
        func_80000AF0(D_8003DE30, D_800400C0, 0x78, 2, 1);
    } else {
        func_80000AF0(D_8003DE30, D_800400C0, 0x78, 0x1E, 1);
    }
    func_800130A0(arg0);
    func_8001CC50(0, 0);
    for (;;) {
        func_8001C580();
    }
}
