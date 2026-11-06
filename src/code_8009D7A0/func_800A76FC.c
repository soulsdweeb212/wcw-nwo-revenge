/* @header
 * func_800A76FC
 * VRAM 0x800A76FC | ROM 0x9AB9C | size 0xF4
 * asm: asm/nonmatchings/code_8009D7A0/func_800A76FC.s
 */
#include "common.h"

s16 func_800D7B08(s32);
extern s32 D_800E3C90[];
/* Maps a directional input mask (arg1) to a quadrant 0..3 (callers store it in dirIndex). When
 * func_800D7B08 accepts the input (0x900/0x500/0x600/0xA00) the quadrant is rotated by one unless
 * the signed angle D_800E3C90[quadrant] - heading lies in -0x200..0x600. */
s16 func_800A76FC(Wrestler *w,u16 arg1) {
    s16 direction;
    if(func_800D7B08(arg1)!=-1) {
        if(arg1==0x900) direction=0;
        if(arg1==0x500) direction=1;
        if(arg1==0x600) direction=2;
        if(arg1==0xA00) direction=3;
        if((u32)(func_800D3684(D_800E3C90[direction],w->heading)+0x200)>=0x801) direction=(direction+1)&3;
    } else {
        if(arg1==0x800) direction=0;
        if(arg1==0x100) direction=1;
        if(arg1==0x400) direction=2;
        if(arg1==0x200) direction=3;
    }
    return direction;
}
