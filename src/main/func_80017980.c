/* @header
 * func_80017980
 * VRAM 0x80017980 | ROM 0x18580 | size 0xA8
 * asm: asm/nonmatchings/main/func_80017980.s
 */
#include "common.h"

extern s32 *D_80036F54;
s32 *func_80017F18(void);
s32 func_80018C24(s32 *, s32, s32 *);
s32 func_80018044(s32, s32);

/* If the node has a stream (arg0[2]), allocate a packet, set command 0xB with the
 * parameter arg1, schedule it at the current time plus the node's duration
 * offset (+0x88) and enqueue it into the stream. */
void func_80017980(s32 *arg0, s16 arg1, s32 arg2) {
    s32 *p;
    if (arg0[2] != 0) {
        p = func_80017F18();
        if (p != 0) {
            s32 g = D_80036F54[7];
            s32 off = *(s32 *)((u8 *)arg0[2] + 0x88);
            *(s16 *)((u8 *)p + 8) = 0xB;
            p[3] = arg1;
            p[1] = g + off;
            p[4] = func_80018044(arg2, p[1]);
            p[0] = 0;
            func_80018C24((s32 *)arg0[2], 3, p);
        }
    }
}
