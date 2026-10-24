#include "common.h"

extern u8 D_8007EF30[];
s8 func_800B71F8(void*,void*,s32);s16 func_800BF2FC(void*);void func_800A6D80(void*,s32);
#define FL(p) (*(u64*)((p)+0x20))
s32 func_800C472C(u8 *a,u8 *b,s16 mode){s32 flags,tmp;u8 n;s8 r;*(u16*)(b+0x44)=*(u16*)(a+0x38E);*(s16*)(b+0x46)=(s8)a[0x3A4];flags=0;b[0x35]=0;if(!(FL(b)&0x400000000ULL)&&*(s8*)(a+0x393))flags=(func_800B71F8(a,b,4)!=0)*2;
if((*(u16*)(D_8007EF30+0x170)&1)&&*(s8*)(a+0x394)&&!(FL(b)&0x80080ULL)){if(func_800BF2FC(b)<25){r=func_800B71F8(a,0,5);tmp=flags|1;if(r){flags=tmp;if(*(s8*)(a+0x355)==*(s8*)b)flags=tmp|0x20;if(FL(a)&0x80000ULL)flags|=0x40;if(!(FL(a)&0x200ULL))flags|=0x80;}}}
if(flags&3){switch(mode){case 0:if(*(s16*)(b+0xA)==20)flags|=4;break;case 1:flags|=8;break;case 2:n=b[0x36F];b[0x42]=n;if((s8)n>=7){flags|=8;if(n&1)FL(b)&=~0x200000ULL;else FL(b)|=0x200000ULL;}break;}b[0x35]|=flags;if(flags&2)func_800A6D80(b,0x2A);else func_800A6D80(b,0x29);tmp=1;return tmp;}return 0;}
