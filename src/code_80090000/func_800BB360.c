/* @header
 * func_800BB360
 * VRAM 0x800BB360 | ROM 0x67AD0 | size 0x7C
 * asm: asm/nonmatchings/code_80090000/func_800BB360.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: D_800DCFC4 holds the address of the controllers' message queue that func_8000424C returns (its definition
 * returns an s32 *), which an s32 would cut in half. osPfsInitPak (libultra's, which the port replaces with a
 * stand-in) and osMotorInit (port.h's port_osMotorInit) take the queue as a pointer, as func_800B947C declares them. */
extern s32 *D_800DCFC4;
extern s32 D_800DCFBC;
extern u8 D_800DCF50[];
s32 *func_8000424C(void);
void func_80004290(void);
s32 osPfsInitPak(void *queue, void *pfs, s32 channel);
s32 osMotorInit(void *queue, void *pfs, s32 channel);
#else
extern s32 D_800DCFC4, D_800DCFBC;
extern u8 D_800DCF50[];
s32 func_8000424C(void);
void func_80004290(void);
s32 osPfsInitPak(s32, void *, s32);
s32 osMotorInit(s32, void *, s32);
#endif

s32 func_800BB360(void) {
    u8 buf[0x68];
#ifdef TARGET_PC
    /* PC: the queue's address, as a pointer. */
    s32 *x = func_8000424C();
#else
    s32 x = func_8000424C();
#endif
    D_800DCFC4 = x;
    D_800DCFBC = osPfsInitPak(x, D_800DCF50, 0);
    if (D_800DCFBC == 0xA) {
        if (osMotorInit(D_800DCFC4, buf, 0) == 0) {
            D_800DCFBC = 0x40;
        }
    }
    func_80004290();
    return D_800DCFBC;
}
