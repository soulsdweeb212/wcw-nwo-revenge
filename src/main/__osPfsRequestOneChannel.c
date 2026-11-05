/* @header
 * __osPfsRequestOneChannel  (originally func_80024730)
 * VRAM 0x80024730 | ROM 0x25330 | size 0x94
 * asm: asm/nonmatchings/main/__osPfsRequestOneChannel.s
 */
/* SDK: libultra 2.0I, ultralib src/io/pfsgetstatus.c (same code as the SDK source). */
#include "common.h"

typedef struct {
    u8 b[6];
} Nw2Six;

extern s32 D_8007E00C[];

/* Builds the command buffer for controller channel arg1: fills arg0 entries with
 * the read request record and a 0xFE terminator. */
void __osPfsRequestOneChannel(s32 arg0, u8 arg1) {
    s32 *base;
    u8 *p;
    u8 buf[16];
    s32 i;

    base = D_8007E00C;
    p = (u8 *)base - 0x3C;
    i = 0;
    __osContLastCmd = 0xFE;
    base[0] = 1;
    buf[0] = 1;
    buf[1] = 3;
    buf[2] = arg1;
    buf[3] = 0xFF;
    buf[4] = 0xFF;
    buf[5] = 0xFF;
    if (arg0 > 0) {
        do {
            *p = 0;
            i++;
            p++;
        } while (i < arg0);
    }
    *(Nw2Six *)p = *(Nw2Six *)buf;
    p[6] = 0xFE;
}

extern u8 __osPfsPifRam[];

extern Nw2IdSubTable lookupSubTables[];
