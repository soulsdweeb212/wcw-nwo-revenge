/* @header
 * updateActionCounterState  (originally func_800AF52C)
 * VRAM 0x800AF52C | ROM 0xA29CC | size 0x144
 * asm: asm/nonmatchings/code_8009D7A0/updateActionCounterState.s
 */
#include "common.h"

extern u8 *D_800FABD0;
extern u8 D_8007EF30[],D_8007E8C0[];
extern s8 D_800FACE8;
/* Two-state action counter handler on D_800FABD0 (state at +4). State 0 sets
 * the action's count word (0xC000 when +0x26 is below 10 and the AI wrestler
 * has SPECIAL, else 0x8000) and advances. State 1, when the AI wrestler is in
 * state 0x3A/0x3C on the floor and all the global gates allow it, sets +8 to
 * 0x10; otherwise the action is reset (state 0, opponent's state copied). */
void updateActionCounterState(void){
    switch(*(s16 *)(D_800FABD0+4)) {
    case 0:
        if(*(s16 *)(D_800FABD0+0x26)<10 && (D_800FAF58->flags&WR_FLAG_SPECIAL)) *(u16 *)(D_800FABD0+6)=0xc000;
        else *(u16 *)(D_800FABD0+6)=0x8000;
        (*(s16 *)(D_800FABD0+4))++;break;
    case 1:
        switch(D_800FAF58->state){
        case 0x3a: case 0x3c:
            if((D_800FAF58->flags&WR_FLAG_ON_FLOOR) && !(*(u16 *)(D_8007EF30+0x170)&0x100) && *(s8 *)(D_8007E8C0+0x66c) && D_800FACE8<3) *(s16 *)(D_800FABD0+8)=0x10;
            break;
        default:{
            Wrestler *g=D_800F9B60;
            *(s16 *)(D_800FABD0+2)=0;*(s16 *)(D_800FABD0+4)=0;
            *(u16 *)(D_800FABD0+0x2e)=(u16)g->state;
            *(u32 *)(D_800FABD0+0x5c)&=~7;
        }break;
        }break;
    }
}
