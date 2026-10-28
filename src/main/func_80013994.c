#include "common.h"

extern s16 D_80030D38[],D_80030DD4[];
void func_8000327C(s32);
extern u32 D_800604C8;extern u8 *D_800604D0; extern s32 *D_800604D8;
s32 func_80015F64(void *,s32,s32,s32,s32);
/* Allocates a voice for channel arg0 (threshold D_800604D8[arg0]): first free
 * voice, else the least-recently-used one below the threshold; returns 0 when
 * none qualifies. */
s32 func_80013994(s32 arg0) {
 u8 *p=D_800604D0,*best;
 s32 threshold=D_800604D8[arg0];
 s32 min=threshold+1;
 u32 i;
 for(i=0;i<D_800604C8;i++,p+=0x158) {
 if(*(s32*)(p+4)==0) return func_80015F64(p,arg0,128,128,threshold);
 if(*(u16*)(p+0xC6)!=0 && *(s32*)(p+0x64)<min) {min=*(s32*)(p+0x64);best=p;}
 }
 if(min<threshold) return func_80015F64(best,arg0,128,128,threshold);
 return 0;
}
extern s32 *D_80036F54;
void func_8002023C(void *);void func_8002021C(void *,void *);
s32 *func_80017F18(void); s32 func_80018C24(s32*,s32,s32*);
