/* @header
 * func_80002BC0
 * VRAM 0x80002BC0 | ROM 0x37C0 | size 0x4C
 * asm: asm/nonmatchings/main/func_80002BC0.s
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

/* Set the queue's mode from arg0, clear the active flag, and post a zero message to
 * both message queues (D_800467C0, D_800467E0). */
#ifdef TARGET_PC
/* PC: arg0 is the record of the view to draw (func_8009A374 passes &D_800EB360[D_800E2FA8]), which this function
 * keeps in D_800467FC; func_80002CC4 reads it back as a pointer. The N64 definition takes it as an s32, which on PC
 * would cut the address in half, so the PC definition takes a pointer and port_decls.h declares D_800467FC as one. */
void func_80002BC0(void *arg0) {
#else
void func_80002BC0(s32 arg0) {
#endif
    D_800467FC = arg0;
    D_80046800 = 0;
    osSendMesg(&D_800467C0, 0, 1);
    osRecvMesg(&D_800467E0, 0, 1);
}
