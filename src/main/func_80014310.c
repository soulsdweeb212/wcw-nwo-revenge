#include "common.h"

extern void func_8001446C(u8 *);
extern s32 D_800604FC;
extern u32 D_800604C8;
extern u8 *D_800604D0;

typedef struct {
    u8 cmd;
    s32 data;
} Cmd;

/* Queue a type-2 audio command and latch the value. */
void func_80014310(s32 arg0) {
    Cmd c;

    c.data = arg0;
    D_800604FC = arg0;
    c.cmd = 2;
    func_8001446C(&c.cmd);
}
