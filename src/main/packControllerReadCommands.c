#include "common.h"

typedef struct { u8 b0, b1, b2, b3; u16 b4; s8 b6, b7; } ReadCmd;
extern ReadCmd D_8006A260[];

/* Clear the 15 controller read slots (backwards from slot 14), mark the set
 * valid, fill each active slot with the default 0xFF/1/4/1 command, then write
 * the 0xFE terminator after the last slot. */
void packControllerReadCommands(void) {
    s32 i;
    s32 *p;
    ReadCmd *q;
    ReadCmd def;
    q = D_8006A260;
    for (i = 0xE, p = (s32 *)((u8 *)q + 0x38); i >= 0; i--) { *p = 0; p--; }
    D_8006A29C = 1;
    def.b0 = 0xFF; def.b1 = 1; def.b2 = 4; def.b3 = 1;
    def.b4 = 0xFFFF; def.b6 = -1; def.b7 = -1;
    for (i = 0; i < D_80070A98; i++) { *q++ = def; }
    *(u8 *)q = 0xFE;
}
