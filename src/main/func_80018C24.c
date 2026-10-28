#include "common.h"

void func_800194B8(void *, s32);

/* Handle a command `cmd` (3, 4 or 9) on a controller/input state block:
 * 3 stores `value` as the current and previous target (writing through the
 *   pointer held at +0x80 when one is present);
 * 4 re-initialises the state (flags at +0x78/+0x84/+0x5A/+0x4C/+0x50/+0x48)
 *   then forwards the command to func_800194B8;
 * 9 sets the +0x84 flag;
 * anything else is just forwarded. Returns 0. */
s32 func_80018C24(u8 *state, s32 cmd, s32 value) {
    switch (cmd) {
    case 3:
        if (*(s32 *)(state + 0x80) != 0) {
            *(s32 *)*(s32 *)(state + 0x80) = value;
        } else {
            *(s32 *)(state + 0x7C) = value;
        }
        *(s32 *)(state + 0x80) = value;
        break;
    case 4:
        cmd = 4;
        *(s32 *)(state + 0x78) = 1;
        *(s32 *)(state + 0x84) = 0;
        *(s16 *)(state + 0x5A) = 1;
        *(s32 *)(state + 0x4C) = 0;
        *(s32 *)(state + 0x50) = 1;
        *(s32 *)(state + 0x48) = 0;
        func_800194B8(state, cmd);
        break;
    case 9:
        *(s32 *)(state + 0x84) = 1;
        break;
    default:
        func_800194B8(state, cmd);
        break;
    }
    return 0;
}

typedef struct {
    u8 b0, b1, b2, b3, b4, b5, b6, b7;
} Cmd8;

extern Cmd8 D_8006A260[];
extern u8 D_80070A98;
