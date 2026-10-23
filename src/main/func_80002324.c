#include "common.h"

typedef struct { s32 f0; u8 *f4; } Obj2324;
extern Obj2324 *D_80046860[];
extern s16 D_80047062;
extern u16 D_80047064, D_80047066;
extern u8 D_80048070[];
void func_80002110();
void func_80002324(s16 arg0) {
 s32 pad[2];
 u32 i;
 Obj2324 *obj;
 u8 v;
 D_80047066=0;
 D_80047064=D_80047062;
 i=0;
 if((u16)D_80047062!=0) {
 do {
 obj=D_80046860[i];
 v=obj->f4[0x18];
 D_80048070[i]=v;
 if(v&0x80) D_80048070[i]=0xFF;
 else if(v==6) D_80047064=i;
 else if(obj->f0==1) { if(v!=0) D_80048070[i]=5; }
 i++;
 }while(i<(u32)D_80047062);
 }
 func_80002110(arg0,0,0);
 func_80002110(arg0,0,1);
 func_80002110(arg0,6,0);
 func_80002110(arg0,3,0);
 func_80002110(arg0,5,1);
 func_80002110(arg0,5,0);
}
