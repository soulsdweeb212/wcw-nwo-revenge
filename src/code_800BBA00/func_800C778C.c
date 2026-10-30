/* @header
 * func_800C778C
 * VRAM 0x800C778C | ROM 0xBAC2C | size 0xE4
 * asm: asm/nonmatchings/code_800BBA00/func_800C778C.s
 */
#include "common.h"

/* Selects an attachment/action id from arg0's +0x30 flag word: bit 0x1000
 * selects the 0x104A/0x104C/0x104E group, otherwise 0x104B/0x104D apply and
 * bit 0x10000000 uses the attachment record's signed byte +0x1E to pick
 * 0x107B..0x1080 (falling back to 0x1049). arg1 is the caller's default. */
s16 func_800C778C(u8 *arg0, s32 arg1) {
    u32 flags=*(u32 *)(arg0+0x30);
    if(flags & 0x1000) {
        if(flags & 0x10000000) arg1=0x104A;
        if(flags & 0x20000000) arg1=0x104C;
        if(flags & 0x40000000) arg1=0x104E;
    } else {
        if(flags & 0x20000000) arg1=0x104B;
        if(flags & 0x40000000) arg1=0x104D;
        if(flags & 0x10000000) {
            s8 index=(*(u8 **)(arg0+0x364))[0x1E]-1;
            switch(index) {
            case 0: arg1=0x107B; break;
            case 1: arg1=0x107C; break;
            case 2: arg1=0x107D; break;
            case 3: arg1=0x107E; break;
            case 4: arg1=0x107F; break;
            case 5: arg1=0x1080; break;
            default: arg1=0x1049; break;
            }
        }
    }
    return arg1;
}
