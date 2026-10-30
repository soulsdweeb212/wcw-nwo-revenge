/* @header
 * accumulateColorChannels  (originally func_800952CC)
 * VRAM 0x800952CC | ROM 0x41A3C | size 0x128
 * asm: asm/nonmatchings/code_80090000/accumulateColorChannels.s
 */
#include "common.h"

extern s16 D_800E74CC,D_800E74CE,D_800E74D0,D_800E74D2;
/* Accumulates three signed-16 colour channels by (a,b,c), clamping each at 255
 * and tracking their historical maximum in D_800E74D2. A negative first
 * argument clears all four. */
void accumulateColorChannels(s32 a,s32 b,s32 c) {
 s16 *p;
 if(a<0) {
 D_800E74D2=0; D_800E74D0=0; D_800E74CE=0; D_800E74CC=0;
 } else {
 p=&D_800E74CC;
 *p+=a;
 if(*p>=256) *p=255;
 if(D_800E74D2<*p) D_800E74D2=*p;
 D_800E74CE+=b;
 if(D_800E74CE>=256) D_800E74CE=255;
 if(D_800E74D2<D_800E74CE) D_800E74D2=D_800E74CE;
 D_800E74D0+=c;
 if(D_800E74D0>=256) D_800E74D0=255;
 if(D_800E74D2<D_800E74D0) D_800E74D2=D_800E74D0;
 }
}
