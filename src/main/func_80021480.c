#include "common.h"

extern u8 D_80070A98;
extern s32 D_8006A298;
extern s32 D_8006A29C;

typedef struct {
    u8 b0, b1, b2, b3, b4, b5, b6, b7;
} Cmd8;
extern Cmd8 D_8006A260[];

/* Reset the 8-byte command buffer at D_8006A260: clear the 15 s32 status words ending at
 * D_8006A298, set D_8006A29C to 1, fill the D_80070A98 entries with the request packet
 * {0xFF, 1, 3, arg0, 0xFF, 0xFF, 0xFF, 0xFF} and store the 0xFE terminator byte. */
void func_80021480(s32 arg0) {
    s32 i;
    s32 *p;
    u8 *flag;
    Cmd8 *q;
    Cmd8 tmp;

    for (i = 0xE, p = &D_8006A298; i >= 0; i--) {
        *p = 0;
        p--;
    }
    flag = (u8 *)&D_8006A29C;
    q = (Cmd8 *)(flag - 0x3C);
    *(s32 *)flag = 1;
    tmp.b0 = 0xFF;
    tmp.b1 = 1;
    tmp.b2 = 3;
    tmp.b3 = arg0;
    tmp.b4 = 0xFF;
    tmp.b5 = 0xFF;
    tmp.b6 = 0xFF;
    tmp.b7 = 0xFF;
    for (i = 0; i < D_80070A98; i++) {
        *q++ = tmp;
    }
    *(u8 *)q = 0xFE;
}
