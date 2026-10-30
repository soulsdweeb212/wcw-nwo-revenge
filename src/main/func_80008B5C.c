/* @header
 * func_80008B5C
 * VRAM 0x80008B5C | ROM 0x975C | size 0x138
 * asm: asm/nonmatchings/main/func_80008B5C.s
 */
#include "common.h"

void func_800080A0(void *,void *,void *,void *);
typedef struct { u8 b[220]; } PartInput;
typedef struct { u8 b[124]; } PartOutput;
extern PartInput D_800651A0[][23];
extern PartOutput D_80070C40[][23];
extern f32 D_80070C88[][23][31],D_80070C74[][23][31],D_80070C90[][23][31];
extern f32 D_80070CA0[][23][31],D_80070CA4[][23][31],D_80070CA8[][23][31];
void func_80008B5C(s16 arg0) {
 u32 i=1; u8 *p; void *q; f32 x,y,z;
 do {
 if(i!=20) {
 q=&D_800651A0[arg0][i];
 p=D_80070C40[arg0][i].b;
 func_800080A0(q,p+0x48,p+0x30,p+0x3C);
 x=D_80070C88[arg0][i][0];
 y=D_80070C74[arg0][i][0];
 z=D_80070C90[arg0][i][0];
 D_80070CA0[arg0][i][0]=x;
 D_80070CA4[arg0][i][0]=y;
 D_80070CA8[arg0][i][0]=z;
 }
 i++;
 }while(i<23);
}
