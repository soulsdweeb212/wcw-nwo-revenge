/* @header
 * func_800B242C
 * VRAM 0x800B242C | ROM 0xA58CC | size 0x188
 * asm: asm/nonmatchings/code_8009D7A0/func_800B242C.s
 */
#include "common.h"

extern u8 *D_800FABD0;
extern u16 D_800E3CF0[];
extern f64 D_800E5290;
s32 func_800D3650(void *,void *);
void func_800B242C(void) {
    u8 *p=D_800FABD0; Wrestler *g; s16 state=*(s16*)(p+4); u32 v;
    switch(state) {
    case 0:
        *(s16*)(D_800FABD0+6)=D_800E3CF0[(s16)func_800D3650(&D_800F9B60->jointA[1],&D_800FAF58->jointA[1])]|4;
        (*(s16*)(D_800FABD0+4))++;
        break;
    case 1:
        if (*(s16*)p==4) {
            if (D_800FAF58->state!=3) { *(s16*)(p+4)=state+1; }
            else if (D_800E5290 < (f64)*(f32*)(p+0x48+D_800F9B60->dirIndex*4) || *(s16*)(p+0x22)!=0x11) {
                *(s16*)(p+8)=0xF00; (*(s16*)(p+4))++;
            }
        }
        break;
    case 2:
        if (D_800FAF58->state==3) *(s16*)(p+8)=0xF00;
        else if (D_800FAF58->state!=4) {
            g=D_800F9B60;
            *(s16*)(p+2)=0; *(s16*)(p+4)=0;
            v=(u16)g->state;
            *(u32*)(p+0x5C)&=~7;
            *(u16*)(p+0x2E)=v;
        }
        break;
    }
}
