#include "common.h"

extern void func_8001446C(u8 *);
extern s32 D_800604FC;
extern u32 D_800604C8;
extern u8 *D_800604D0;

typedef struct {
    u8 cmd;
    s32 data;
} Cmd;

/* Enqueues a type-1 audio message with arg0 as the sound id. */
void func_800142E8(s32 arg0) {
    Cmd c;

    c.data = arg0;
    c.cmd = 1;
    func_8001446C(&c.cmd);
}
