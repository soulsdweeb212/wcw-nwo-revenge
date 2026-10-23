#include "common.h"

typedef struct {
    u8 pad[0xC];
    s32 fC;
    s32 f10;
    s32 f14;
} Nw2P25A60;

s32 func_8001C990(void *, void *, s32);
s32 func_8001CAC0(void *, s32, s32);
void __osViSwapContext(void);
u32 func_80026AF0(void);
void handleTimerInterrupt(void);
void *func_800275E0(void);

extern u16 D_80063890;
extern u32 D_80065120;
extern u32 D_80070480;
extern u64 D_80070B20;

/* VI manager message loop: consumes messages from queue arg0->fC, swapping the
 * VI context every D_80063890 retraces (case 0xD) and handling timer
 * interrupts (case 0xE). Accumulates per-frame timing in D_80070B20. */
void func_80025A60(Nw2P25A60 *arg0) {
    u16 *msg;
    Nw2P25A60 *obj;
    Nw2P25A60 *p;
    u32 t;
    s32 flag;

    msg = NULL;
    D_80063890 = ((u16 *)func_800275E0())[1];
    if (D_80063890 == 0) {
        D_80063890 = 1;
    }
    flag = 0;
    obj = arg0;
    for (;;) {
        func_8001C990(obj->fC, &msg, 1);
        switch (*msg) {
        case 0xD:
            __osViSwapContext();
            if (--D_80063890 == 0) {
                p = func_800275E0();
                if (p->f10 != 0) {
                    func_8001CAC0(p->f10, p->f14, 0);
                }
                D_80063890 = ((u16 *)p)[1];
            }
            D_80070480++;
            if (flag) {
                flag = 0;
                t = func_80026AF0();
                D_80070B20 = t;
            }
            t = D_80065120;
            D_80065120 = func_80026AF0();
            t = D_80065120 - t;
            D_80070B20 += t;
            break;
        case 0xE:
            handleTimerInterrupt();
            break;
        }
    }
}
