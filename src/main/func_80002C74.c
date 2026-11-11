/* @header
 * func_80002C74
 * VRAM 0x80002C74 | ROM 0x3874 | size 0x50
 * asm: asm/nonmatchings/main/func_80002C74.s
 */
#include "common.h"

s32 osRecvMesg(s32 *, s32, s32);
s32 osSendMesg(s32 *, s32, s32);
extern s32 D_800467C0;
extern s32 D_800467E0;
#ifndef TARGET_PC /* on PC, port_decls.h declares D_800467FC */
extern s32 D_800467FC;
#endif
extern s32 D_80046800;

/* Initialize two message queues (D_800467C0, D_800467E0), mark the second active,
 * and post a zero message to each. */
void func_80002C74(void) {
    D_800467FC = 0;
    D_80046800 = 1;
#ifdef TARGET_PC
    /* PC: no render thread waits on D_800467C0; the port takes the hand-off (port_present in port.h). */
    port_present(PORT_PRESENT_SYNC);
#else
    osSendMesg(&D_800467C0, 0, 1);
    osRecvMesg(&D_800467E0, 0, 1);
#endif
}
