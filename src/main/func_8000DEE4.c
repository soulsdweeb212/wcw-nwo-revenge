/* @header
 * func_8000DEE4
 * VRAM 0x8000DEE4 | ROM 0xEAE4 | size 0x94
 * asm: asm/nonmatchings/main/func_8000DEE4.s
 */
#include "common.h"

extern u16 D_8006A2A4[];
extern u8 D_80031060[];
extern s16 D_80030DD4[];

#ifdef TARGET_PC
/* PC: the menus' sound ids 0x401..0x42B are 16-bit values in the table at 0x80030EA2, after the effect bytes of
 * D_80030E53. The N64 reaches it as D_800306A0 indexed by the id itself; on PC it is read by its own label, so that
 * tools/port_data.py converts it as s16 (docs/port.md, "Byte order on PC"). */
extern s16 D_80030EA2[];
#else
extern u16 D_800306A0[];
#endif
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800032A4 */
s32 func_800032A4(s32, s32, s32, s32, s32);
#endif
void MusHandleSetReverb(s32, s32);

/* Plays sound arg0 (remapped through D_800306A0 for ids 0x401..0x42B) if it is
 * in range, and returns the voice handle. */
s32 func_8000DEE4(s32 arg0) {
    s32 ret;
    s32 t;
    s16 x;

    ret = 0;
    t = arg0;
    if ((u16)(arg0 - 0x401) < 0x2B) {
#ifdef TARGET_PC
        x = D_80030EA2[(s16)arg0 - 0x401];
#else
        x = D_800306A0[(s16)arg0];
#endif
    } else {
        x = t;
    }
    if (x >= 0) {
        if (x < 0x97) {
            ret = func_800032A4(x, 0x80, 0x80, 0, -1);
            MusHandleSetReverb(ret, 0);
        }
    }
    return ret;
}
