#include "common.h"

s16 func_800D7B08(s32);
extern s32 D_800E3C90[];
/* Maps a directional input mask (arg1) to a quadrant 0..3. When the input is a
 * stick direction the base quadrant is rotated by one when the entity's heading
 * (arg0+0x58) differs from the quadrant's reference angle by more than 0x400. */
s16 func_800A76FC(void *arg0,u16 arg1) {
 s16 direction;
 if(func_800D7B08(arg1)!=-1) {
 if(arg1==0x900) direction=0;
 if(arg1==0x500) direction=1;
 if(arg1==0x600) direction=2;
 if(arg1==0xA00) direction=3;
 if((u32)(func_800D3684(D_800E3C90[direction],*(s32 *)((u8 *)arg0+0x58))+0x200)>=0x801) direction=(direction+1)&3;
 } else {
 if(arg1==0x800) direction=0;
 if(arg1==0x100) direction=1;
 if(arg1==0x400) direction=2;
 if(arg1==0x200) direction=3;
 }
 return direction;
}
