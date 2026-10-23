#include "common.h"

extern void func_8001446C(u8 *);
extern s32 D_800604FC;
extern u32 D_800604C8;
extern u8 *D_800604D0;

typedef struct {
    u8 cmd;
    s32 data;
} Cmd;

/* Queue a type-0 audio command. */
void func_800142C4(s32 arg0) {
    Cmd c;

    c.data = arg0;
    c.cmd = 0;
    func_8001446C(&c.cmd);
}

/* Queue a type-1 audio command. */
void func_800142E8(s32 arg0) {
    Cmd c;

    c.data = arg0;
    c.cmd = 1;
    func_8001446C(&c.cmd);
}

/* Queue a type-2 audio command and latch the value. */
void func_80014310(s32 arg0) {
    Cmd c;

    c.data = arg0;
    D_800604FC = arg0;
    c.cmd = 2;
    func_8001446C(&c.cmd);
}

/* Return the s32 at +0x98 of the first voice record whose key (+0x60) matches arg0. */
s32 func_80014268(s32 arg0) {
    u32 n;
    u8 *p;

    if (arg0 == 0) {
        return 0;
    }
    n = D_800604C8;
    p = D_800604D0;
    if (n != 0) {
        u32 count;
        u32 i;

        count = n;
        i = 0;
        do {
            if (*(s32 *)(p + 0x60) == arg0) {
                return *(s32 *)(p + 0x98);
            }
            i++;
            p += 0x158;
        } while (i < count);
    }
    return 0;
}
