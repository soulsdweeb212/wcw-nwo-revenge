/* @header
 * osCartRomInit  (originally func_80021AA0)
 * VRAM 0x80021AA0 | ROM 0x226A0 | size 0xD4
 * asm: asm/nonmatchings/main/osCartRomInit.s
 */
/* SDK: libultra 2.0I, ultralib src/io/cartrominit.c (same code as the SDK source). */
#include "common.h"

extern s32 D_8003761C;
extern u8 D_8007E198;
extern u8 D_8007E19C;
extern u8 D_8007E19D;
extern u8 D_8007E19E;
extern u8 D_8007E19F;
extern u8 D_8007E1A0;
extern u8 D_8007E1A1;
extern u32 D_8007E1A4;
extern s32 D_8007E1A8;

void osPiRawReadIo(s32, void *);
void bzero(void *, s32);
s32 __osDisableInt(void);
void __osRestoreInt(s32);

void *osCartRomInit(void)
{
    u32 value = 0;
    s32 tmp;
    s32 old;
    u32 *base = &D_8007E1A4;
    u32 *p;

    if (base[0] != 0xB0000000) {
        D_8007E19C = 0;
        base[0] = 0xB0000000;
        osPiRawReadIo(0, &value);
        D_8007E1A1 = 0;
        D_8007E1A8 = 0;
        D_8007E1A0 = value >> 8;
        D_8007E19D = value;
        D_8007E19E = (value >> 16) & 0xF;
        D_8007E19F = (value >> 20) & 0xF;
        bzero(base + 2, 0x60);
        do { p = base - 3; } while (0);
        tmp = __osDisableInt();
        old = D_8003761C;
        D_8003761C = (s32)p;
        *(s32 *)p = old;
        __osRestoreInt(tmp);
    }
    return &D_8007E198;
}
