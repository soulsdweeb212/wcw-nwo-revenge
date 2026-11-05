/* @header
 * osContSetCh  (originally func_80021540)
 * VRAM 0x80021540 | ROM 0x22140 | size 0x60
 * asm: asm/nonmatchings/main/osContSetCh.s
 */
/* SDK: libultra 2.0I, ultralib src/io/contsetch.c (same code as the SDK source). */
#include "common.h"

extern u8 D_80070A98;
extern u8 D_8007BD30;
extern s32 D_8006A298;
extern s32 D_8006A29C;

typedef struct {
    u8 b0, b1, b2, b3, b4, b5, b6, b7;
} Cmd8;
extern Cmd8 D_8006A260[];

extern void __osSiGetAccess(void);
extern void __osSiRelAccess(void);
extern s32 __osPfsGetStatus(s32, s32);
extern s32 __osGetId(void *);
extern s32 osPfsChecker(void *);

/* Sets the active controller count (clamped to 4) and re-arms the Pak status. */
s32 osContSetCh(s32 arg0) {
    __osSiGetAccess();
    if ((u8)arg0 >= 5) {
        D_80070A98 = 4;
    } else {
        D_80070A98 = (u8)arg0;
    }
    D_8007BD30 = 0xFE;
    __osSiRelAccess();
    return 0;
}
