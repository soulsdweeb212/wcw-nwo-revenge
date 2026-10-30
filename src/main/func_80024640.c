/* @header
 * func_80024640
 * VRAM 0x80024640 | ROM 0x25240 | size 0xF0
 * asm: asm/nonmatchings/main/func_80024640.s
 */
#include "common.h"

extern u8 D_800375E4;
extern u8 D_8007DFD0[];
void func_80024730(s32, s32);
s32 func_80025810(s32, void *);
s32 func_8001C990(void *, void *, s32);
void func_800247C4(s32, void *);

/* Probe the controller pak on channel arg1: set the probe id, issue the
 * identify commands, read back the status, and classify it -- 2 for a rumble
 * pak, 1 for an unrecognised/absent pak, 4 for a pak with bit 2 set, otherwise
 * the raw command result. */
s32 func_80024640(void *arg0, s32 arg1) {
    struct { u16 buttons; u8 status; u8 rest[3]; } status;
    s32 message;
    s32 result;
    D_800375E4 = 0xFA;
    func_80024730(arg1, 0);
    func_80025810(1, D_8007DFD0);
    func_8001C990(arg0, &message, 1);
    result = func_80025810(0, D_8007DFD0);
    func_8001C990(arg0, &message, 1);
    func_800247C4(arg1, &status);
    if ((status.status & 1) && (status.status & 2)) return 2;
    if ((*(u16 *)&status.status & 0x1FF) != 0x100) return 1;
    if (status.status & 4) return 4;
    return result;
}
