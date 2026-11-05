/* @header
 * __osPfsRequestData  (originally func_8002184C)
 * VRAM 0x8002184C | ROM 0x2244C | size 0xA4
 * asm: asm/nonmatchings/main/__osPfsRequestData.s
 */
/* SDK: libultra 2.0I, ultralib src/io/pfsisplug.c (same code as the SDK source). */
#include "common.h"

typedef struct { u8 b0,b1,b2,b3,b4,b5,b6,b7; } Cmd8;
extern u8 __osMaxControllers; extern u8 __osContLastCmd; extern Cmd8 __osPfsPifRam[]; extern s32 D_8007E00C;
static inline void pack(u8 cmd) {
    u8 *ptr;
    Cmd8 req;
    s32 i;
    ptr = (u8 *)__osPfsPifRam;
    D_8007E00C = 1;
    req.b0 = 0xFF; req.b1 = 1; req.b2 = 3; req.b3 = cmd;
    req.b4 = 0xFF; req.b5 = 0xFF; req.b6 = 0xFF; req.b7 = 0xFF;
    for (i = 0; i < __osMaxControllers; i++) {
        *(Cmd8 *)ptr = req;
        ptr += sizeof(Cmd8);
    }
    *ptr = 0xFE;
}
void __osPfsRequestData(u8 arg0) {
    __osContLastCmd = arg0;
    pack(arg0);
}
