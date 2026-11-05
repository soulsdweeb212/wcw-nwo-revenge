/* @header
 * osEPiLinkHandle  (originally func_80021A50)
 * VRAM 0x80021A50 | ROM 0x22650 | size 0x44
 * asm: asm/nonmatchings/main/osEPiLinkHandle.s
 */
/* SDK: libultra 2.0I, ultralib src/io/epilinkhandle.c (same code as the SDK source). */
#include "common.h"

extern void *__osPiTable;
extern u8 DriveRomHandle[];
extern u8 D_8006512C;
extern u8 D_8006512D;
extern u8 D_8006512E;
extern u8 D_8006512F;
extern u8 D_80065130;
extern u8 D_80065131;
extern u8 D_80065134;
extern u32 D_80065138;
extern u8 __osMaxControllers;

s32 __osDisableInt(void);
void __osRestoreInt(s32);
void bzero(u8 *, s32);
void *memset(void *, s32, s32);

/* Registers arg0 as the active PI handle and returns the previous one. */
s32 osEPiLinkHandle(void **arg0) {
    s32 t;
    void *old;

    t = __osDisableInt();
    old = __osPiTable;
    __osPiTable = arg0;
    *arg0 = old;
    __osRestoreInt(t);
    return 0;
}

typedef struct {
    u8 b0, b1, b2, b3, b4, b5, b6, b7;
} Cmd8;
extern Cmd8 __osContPifRam[];
