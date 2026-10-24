#include "common.h"

typedef struct {
    u16 button;
    s8 stick_x;
    s8 stick_y;
    u8 errno;
} Pad3E78;

typedef struct {
    u16 unk0;
    u16 unk2;
    u16 button;
    u16 pressed;
    u16 released;
    s8 stick_x;
    s8 stick_y;
} Input3E78;

typedef struct {
    u8 data[0x68];
} Pak3E78;

extern s8 D_800484F2;
extern u8 D_800484F0;
extern u8 D_800484F1;
extern u8 D_800484F3;
extern u8 D_800482F0[];
extern u8 D_80048310[];
extern Pad3E78 D_80048320[4];
extern Pad3E78 D_80048338[4];
extern Pak3E78 D_80048350[4];
extern Input3E78 D_8006E178[4];
extern s32 D_8002EEC0;
extern s8 D_80030560;
s32 func_8001C990(void *, void *, s32);
void func_80021190(void *);
void func_80021210(void *);
void func_80022FD0(void *);
void func_80023058(void *);
s32 writeControllerPakBank(void *, s32);
s32 readWriteControllerPakBank(void *, void *, s32);
void func_800042BC(s32);
void func_800043CC(s16);
void func_8000440C(s32);

void func_80003E78(s16 arg0)
{
    u32 i;
    s8 temp;
    Input3E78 *c;
    u16 trig;

    if (D_800484F2 == 1) {
        return;
    }
    func_8001C990(D_800482F0, NULL, 1);
    for (i = 0; i < 4; i++) {
        D_80048338[i] = D_80048320[i];
    }
    func_80023058(D_80048320);
    if (D_800484F0 != D_800484F1) {
        D_800484F0 = D_800484F1;
    }
    if (arg0 == 1 && D_8002EEC0 == 0) {
        func_80021190(D_800482F0);
        func_8001C990(D_800482F0, NULL, 1);
        func_80021210(D_80048310);
    } else {
        if (D_8002EEC0 != 0) {
            func_8000440C(1);
        }
        for (i = 0; i < 4; i++) {
            if ((D_800484F3 >> i) & 1) {
                if (D_800484F4[i] != 0 && D_800484FC[i] >= 0) {
                    if (D_800484FC[i] == 0) {
                        writeControllerPakBank(&D_80048350[i], 1);
                    }
                    if (D_800484FC[i] >= 0) {
                        D_800484FC[i]++;
                    } else {
                        func_800043CC(i);
                    }
                } else if (D_800484FC[i] < 0) {
                    if (D_800484F8[i] == 1) {
                        readWriteControllerPakBank(D_800482F0, &D_80048350[i], i);
                    }
                    if (writeControllerPakBank(&D_80048350[i], 0) != 4) {
                        if (--D_800484FC[i] < -3) {
                            D_800484F8[i] = 0;
                            D_800484FC[i] = 0;
                        }
                    }
                }
            } else if (D_800484FC[i] < 0 && D_800484F8[i] == 1) {
                readWriteControllerPakBank(D_800482F0, &D_80048350[i], i);
                writeControllerPakBank(&D_80048350[i], 0);
                if (--D_800484FC[i] < -3) {
                    D_800484F8[i] = 0;
                    D_800484FC[i] = 0;
                }
            }
        }
        temp = D_80030560;
        if (temp < 4) {
            D_80030560 = temp + 1;
            func_800042BC(temp);
        } else {
            func_80021190(D_800482F0);
            func_8001C990(D_800482F0, NULL, 1);
            func_80021210(D_80048310);
            D_80030560 = 0;
        }
    }
    func_80022FD0(D_800482F0);
    for (i = 0; i < 4; i++) {
        c = &D_8006E178[i];
        if (D_80048320[i].errno != 0 || !((D_800484F0 >> i) & 1)) {
            c->button = 0;
            c->pressed = 0;
            c->released = 0;
            c->stick_x = 0;
            c->stick_y = 0;
        } else {
            trig = D_80048320[i].button ^ D_80048338[i].button;
            c->button = D_80048320[i].button;
            c->pressed = trig & D_80048320[i].button;
            c->released = trig & D_80048338[i].button;
            c->stick_x = D_80048320[i].stick_x;
            c->stick_y = D_80048320[i].stick_y;
        }
    }
}
