/* @header
 * func_8002184C
 * VRAM 0x8002184C | ROM 0x2244C | size 0xA4
 * asm: asm/nonmatchings/main/func_8002184C.s
 */
#include "common.h"

typedef struct { u8 b0,b1,b2,b3,b4,b5,b6,b7; } Cmd8;
extern u8 D_80070A98; extern u8 D_8007BD30; extern Cmd8 D_8007DFD0[]; extern s32 D_8007E00C;
static inline void pack(u8 cmd) {
    u8 *ptr;
    Cmd8 req;
    s32 i;
    ptr = (u8 *)D_8007DFD0;
    D_8007E00C = 1;
    req.b0 = 0xFF; req.b1 = 1; req.b2 = 3; req.b3 = cmd;
    req.b4 = 0xFF; req.b5 = 0xFF; req.b6 = 0xFF; req.b7 = 0xFF;
    for (i = 0; i < D_80070A98; i++) {
        *(Cmd8 *)ptr = req;
        ptr += sizeof(Cmd8);
    }
    *ptr = 0xFE;
}
void func_8002184C(u8 arg0) {
    D_8007BD30 = arg0;
    pack(arg0);
}
