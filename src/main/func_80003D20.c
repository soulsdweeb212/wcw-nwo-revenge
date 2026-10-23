#include "common.h"

/* func_80003D20: controller subsystem bring-up. Points the four per-seat
 * records at their seat descriptors, initialises and starts the controller
 * read queue paired with D_800482F0, runs the controller-presence scan
 * (initializeControllers) and sends the "detect" message, then clears the
 * per-seat state flags, tears the temporary seats down and returns the scan
 * result. */
typedef struct {
    void *p;
    s32 f4;
    s32 f8;
} Nw2Rec6E178;

extern Nw2Rec6E178 D_8006E178[4];
extern s32 D_80048310[];
extern u8 D_800482F0[];
extern u8 D_80048308[];
extern u8 D_80048350[];
extern s8 D_800484F0;
extern s8 D_800484F2;
extern u8 D_800484F3;
extern s8 D_800484F4[];
extern s8 D_800484F8[];
extern s8 D_800484FC[];

void func_8001C890(void *, void *, s32);
void func_8001CBF0(s32, void *, s32);
s32 initializeControllers(void *, void *, void *);
void func_80021540(s32);
void func_800042BC(s16);
void writeControllerPakBank(void *, s32);
void func_80022FD0(void *);

s32 func_80003D20(void) {
    s32 queue[6];
    s32 msg[2];
    s32 ret;
    u32 i;

    for (i = 0; i < 4; i++) {
        D_8006E178[i].p = &D_80048310[i];
    }
    func_8001C890(queue, msg, 1);
    func_8001CBF0(5, queue, 1);
    ret = initializeControllers(queue, &D_800484F0, D_80048310);
    func_80021540(4);
    func_8001C890(&D_800482F0, &D_80048308, 1);
    func_8001CBF0(5, &D_800482F0, 0);
    D_800484F3 = 0;
    for (i = 0; i < 4; i++) {
        func_800042BC((s16)i);
        if ((D_800484F3 >> i) & 1) {
            writeControllerPakBank(&D_80048350[i * 0x68], 0);
        }
        D_800484FC[i] = 0;
        D_800484F4[i] = 0;
        D_800484F8[i] = 0;
    }
    func_80022FD0(&D_800482F0);
    D_800484F2 = 0;
    return ret;
}
