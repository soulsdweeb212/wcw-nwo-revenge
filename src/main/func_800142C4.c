/* @header
 * func_800142C4
 * VRAM 0x800142C4 | ROM 0x14EC4 | size 0x24
 * asm: asm/nonmatchings/main/func_800142C4.s
 */
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
