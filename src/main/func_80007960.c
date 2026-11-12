/* @header
 * func_80007960
 * VRAM 0x80007960 | ROM 0x8560 | size 0x78
 * asm: asm/nonmatchings/main/func_80007960.s
 */
#include "common.h"

void func_80007960(u16 *arg0, s32 arg1)
{
    u16 *p = arg0;
    u32 i = 0;
    s32 mode = arg1 & 0xFF;
    s32 c;
    do
    {
        switch (mode)
        {
        case 0:
#ifdef TARGET_PC
            /* PC: the palette stays in the N64's byte order, so its entries are read and written big-endian. */
            c = (((u16) READ_BE16(p)) >> 8) & 0xF8;
#else
            c = (((u16) (*p)) >> 8) & 0xF8;
#endif
            break;
        case 1:
#ifdef TARGET_PC
            c = (((u16) READ_BE16(p)) >> 3) & 0xF8;
#else
            c = (((u16) (*p)) >> 3) & 0xF8;
#endif
            break;
        case 2:
        default:
#ifdef TARGET_PC
            c = (READ_BE16(p) * 4) & 0xF8;
#else
            c = ((*p) * 4) & 0xF8;
#endif
            break;
        }
        if (c & 0xFFFF)
            c += 7;
        c |= 0xFF00;
#ifdef TARGET_PC
        WRITE_BE16(p, c);
#else
        *p = c;
#endif
        i++;
        p++;
    }
    while (i < 0x10);
}
