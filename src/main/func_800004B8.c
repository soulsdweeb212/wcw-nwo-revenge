/* @header
 * func_800004B8
 * VRAM 0x800004B8 | ROM 0x10B8 | size 0xC8
 * asm: asm/nonmatchings/main/func_800004B8.s
 */
#include "common.h"

extern s32 osTvType;
extern u8 D_8003DC80[];
extern u8 D_8003DD80[];
extern s32 D_8003DD98;
extern s32 D_8003DDC4;
extern u8 D_8003DE30[];
extern u8 D_800400C0[];
void osCreatePiManager(s32, void *, void *, s32);
s32 osCartRomInit(void);
void osCreateScheduler(void *, void *, s32, s32, s32);
void func_800130A0(s32);
void osSetThreadPri(s32, s32);
void guRandom(void);

/* Main startup: create the PI manager, initialize the Controller Pak descriptor (storing
 * it in D_8003DD98), bring the game up via osCreateScheduler (region mode 2 when osTvType
 * is 1, else 0x1E), run func_800130A0(arg0), start the scheduler and then spin forever in
 * guRandom. */
void func_800004B8(s32 arg0) {
    osCreatePiManager(0x96, D_8003DD80, D_8003DC80, 0x40);
    D_8003DD98 = osCartRomInit();
    D_8003DDC4 = 0;
    if (osTvType == 1) {
        osCreateScheduler(D_8003DE30, D_800400C0, 0x78, 2, 1);
    } else {
        osCreateScheduler(D_8003DE30, D_800400C0, 0x78, 0x1E, 1);
    }
    func_800130A0(arg0);
    osSetThreadPri(0, 0);
    for (;;) {
        guRandom();
    }
}
