#include "common.h"

typedef struct { u32 flags; u8 pad4[32]; f32 z; } ViewPart;
typedef struct { void *link; u8 pad4[16]; ViewPart *part; u8 pad18[196]; } ViewRecord;
extern ViewRecord D_8005A730[];
extern s32 D_8005B0F8[];
extern Nw2Descr4BA8 D_8005B110[];
extern ViewRecord D_800651A0[][23];
extern s8 D_80070478[][2],D_80070479[][2];
void func_80007874(void *,void *,s32,s32);
/* Change the visible model part of the view record `arg0` to model `arg1`
 * (variant `arg2`). arg1 == 6 (or larger) hides the part (flag 0x80 + null link).
 * Caches the current (model, variant) pair in D_80070478/79. */
void func_80012B38(s16 arg0,s16 arg1,s16 arg2) {
 ViewRecord *p=&D_8005A730[arg0];
 if(arg1!=D_80070478[arg0][0]) {
 p->part->flags&=~0x80;
 if((u16)arg1<6) func_80007874(p,&D_8005B110[arg1],D_8005B0F8[arg1],0);
 else { p->part->flags|=0x80; arg1=-1; }
 if(arg1!=-1) {p->link=&D_800651A0[arg0][arg2];p->part->z=-10.0f;} else p->link=NULL;
 D_80070478[arg0][0]=arg1;
 D_80070479[arg0][0]=arg2;
 }
}
