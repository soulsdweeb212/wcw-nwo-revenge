/* @header
 * copyPartCoordinateFields  (originally func_800D49A0)
 * VRAM 0x800D49A0 | ROM 0xC7E40 | size 0x130
 * asm: asm/nonmatchings/code_800BBA00/func_800D49A0.s
 */
#include "common.h"

extern f32 D_80070C94, D_80070C98, D_80070C9C, D_80070CAC, D_80070CB4;
extern f32 D_800F9D6C, D_800F9D70, D_800F9D74, D_800F9EDC, D_800F9EE0, D_800F9EE4;
#define AT(n,o) (*(volatile f32 *)((u8 *)&n+(o)))
/* Copies the X/Y/Z coordinate fields (and two more) of parts 1..19 for all four
 * entities from the 0xB24/0x7C-strided source arrays into the 0x3B0/0x10-strided
 * destination arrays. */
void copyPartCoordinateFields(void) {
 s16 i,j;
 s32 dst,src;
 for(i=0;i<4;i++) {
  for(j=1;j<20;j++) {
   dst=j*0x10+i*0x3B0;
   src=j*0x7C+i*0xB24;
   AT(D_800F9D6C,dst)=AT(D_80070C94,src);
   AT(D_800F9D74,dst)=AT(D_80070C9C,src);
   AT(D_800F9D70,dst)=AT(D_80070C98,src);
   AT(D_800F9EDC,dst)=AT(D_80070CAC,src);
   AT(D_800F9EE4,dst)=AT(D_80070CB4,src);
   AT(D_800F9EE0,dst)=AT(D_80070CAC,src+4);
  }
 }
}
