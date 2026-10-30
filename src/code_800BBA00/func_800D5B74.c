/* @header
 * func_800D5B74
 * VRAM 0x800D5B74 | ROM 0xC9014 | size 0x1A8
 * asm: asm/nonmatchings/code_800BBA00/func_800D5B74.s
 */
#include "common.h"

/* Arm a stage/transition: store the two indices, reset the timer branch to 3,
 * set the transition flags for the requested mode (0x8000/0x1000/0x2000) and
 * compute the target camera angle, wrapping the stored value into [0,600). */
extern u8 D_8007E228[];
extern s8 D_800F97D0,D_800F97D1;
extern u16 D_800F97D2,D_800F97DC;
extern s16 D_800F97D4,D_800F97D6,D_800F97D8,D_800F97E0;
extern u16 D_800F9D14[][0x1D8];
extern u32 D_800FABD8;
void func_800D5B74(s8 idxA,s8 idxB,u32 mode) {
 u32 flagBits=D_800FABD8;
 s16 *wrap;
 D_800F97D4=9999;
 D_800F97D0=idxA; D_800F97D1=idxB; D_800F97E0=3;
 D_800FABD8=flagBits|0x100;
 switch(mode) {
 case 0x8000:
 D_800FABD8=flagBits|0x300;
 D_800F97D6=-105; D_800F97D8=D_800F97D2-90; break;
 case 0x1000:
 D_800FABD8=flagBits|0x500;
 D_800F97D6=-105; D_800F97D8=D_800F97D2+D_800F9D14[idxA][0]+3; break;
 case 0x2000:
 D_800FABD8=flagBits|0x900;
 if(*(u16 *)(D_8007E228+0x58)&0x200) {
 D_800F97D6=-180; D_800F97D8=D_800F97D2+D_800F9D14[idxA][0]+3;
 } else { D_800F97D6=-135; D_800F97D8=D_800F97D2-60; }
 break;
 }
 wrap=&D_800F97D8;
 if(*wrap>=600) *wrap-=600;
 if(*wrap<0) *wrap+=600;
 D_800F97DC=*wrap;
}
