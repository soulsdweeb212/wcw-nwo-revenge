/* @header
 * osDriveRomInit  (originally func_80021B80)
 * VRAM 0x80021B80 | ROM 0x22780 | size 0xBC
 * asm: asm/nonmatchings/main/osDriveRomInit.s
 */
/* SDK: libultra 2.0I, ultralib src/io/driverominit.c (same code as the SDK source). */
#include "common.h"

extern void *D_8003761C;
extern u8 D_80065128[];
extern u8 D_8006512C;
extern u8 D_8006512D;
extern u8 D_8006512E;
extern u8 D_8006512F;
extern u8 D_80065130;
extern u8 D_80065131;
extern u8 D_80065134;
extern u32 D_80065138;

s32 __osDisableInt(void);
void __osRestoreInt(s32);
void bzero(u8 *, s32);

/* One-time initialization of the controller descriptor whose signature word sits at
 * D_80065134 (guard value 0xA6000000): when uninitialized, set the state byte to 1 and the
 * signature, the header bytes 0x40/7/7/2/0, zero the count word, clear the 0x60-byte body
 * via bzero, then under an interrupt guard push the descriptor node (at
 * D_80065128) onto the head of the D_8003761C list. Returns the descriptor base. */
void *osDriveRomInit(void)
{
    u8 *p = &D_80065134;
    u8 *node;
    s32 t;
    void *old;

    if (*(u32 *)p != 0xA6000000) {
        D_8006512C = 1;
        *(u32 *)p = 0xA6000000;
        D_8006512D = 0x40;
        D_80065130 = 7;
        D_8006512E = 7;
        D_8006512F = 2;
        D_80065131 = 0;
        D_80065138 = 0;
        bzero(p + 8, 0x60);
        do { node = p - 0xC; } while (0);
        t = __osDisableInt();
        old = D_8003761C;
        D_8003761C = node;
        *(void **)(p - 0xC) = old;
        __osRestoreInt(t);
    }
    return D_80065128;
}
