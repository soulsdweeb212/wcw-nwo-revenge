#include "common.h"

typedef struct {u32 w[4];} Nw2Vec4U;
extern u8 D_800F9D10[];
extern f32 D_800FADE0[][23],D_800FADE4[][23],D_800FADF4[][23];
extern u32 D_800EB4D8[][4],D_800EB4DC[][4],D_800EB4E0[][4],D_800EB4E4[][4];
s8 func_800D3B24(void*,void*,f32,s32);
void func_800C357C(void*,s16,s8*);
void func_800E2230(void*,void*);
#define FLAGS(P) (*(u64*)((P)+0x20))
#define OK ((FLAGS(arg0)&0x40 && FLAGS(T)&0xC0)||(FLAGS(arg0)&0x80 && FLAGS(T)&0x1C0)||(FLAGS(arg0)&0x100 && FLAGS(T)&0x100))
#define COPY(A,B) *(Nw2Vec4U*)vec1=*(Nw2Vec4U*)(arg0+(A)); *(Nw2Vec4U*)vec2=*(Nw2Vec4U*)(arg0+(B)); break
s32 func_800C2CDC(u8 *arg0,s16 arg1){
s8 list[8];u32 vec1[4];u32 vec2[4];s16 i,j,link;u8 *T;f32 r;
if(*(s16*)(arg0+6)<arg0[0x370])goto done;
if(arg0[0x371]<*(s16*)(arg0+6))goto done;
func_800C357C(arg0,arg1,list);
i=0;
while(list[i]!=-1){
T=D_800F9D10+list[i]*0x3B0;
switch(arg1){
case 1:case 5:case 6:case 7:case 8:case 9:case 10:case 11:case 12:case 13:case 14:case 15:case 16:case 17:case 18:case 19:case 21:
if(OK){if(func_800D3B24(arg0+0x6C,T+0x6C,180.0f,0)){
for(j=0;j<3;j++){
link=(s8)*(u8*)(arg0+j+0x397);
switch(link){
case 1:case 2:case 3:case 4:case 5:case 8:case 9:case 10:case 15:case 17:case 18:COPY(0x5C+link*16,0x5C+link*16);
case 14:COPY(0x2AC,0x29C);
case 7:COPY(0x23C,0x22C);
case 13:COPY(0x29C,0x2BC);
case 6:COPY(0x22C,0x24C);
case 19:COPY(0x2FC,0x2CC);
case 12:COPY(0x28C,0x27C);
case 16:COPY(0x2CC,0x2DC);
case 11:COPY(0x27C,0x25C);
}
r=D_800FADE0[*(s8*)arg0][link]+D_800FADE4[*(s8*)T][0];
if(func_800D3B24(vec1,T+0x6C,r,0))return *(s8*)T;
if(func_800D3B24(vec2,T+0x6C,r,0))return *(s8*)T;
r=D_800FADE0[*(s8*)arg0][link]+D_800FADF4[*(s8*)T][0];
if(func_800D3B24(vec1,T+0xAC,r,0))return *(s8*)T;
if(func_800D3B24(vec2,T+0xAC,r,0))return *(s8*)T;
}}}break;
case 3:
if(OK){if(func_800D3B24(arg0+0x6C,T+0x6C,180.0f,0)){
func_800E2230(arg0,vec1);
r=*(f32*)((u8*)vec1+4)+D_800FADE4[*(s8*)T][0];
if(func_800D3B24(vec1,T+0x6C,r,0))return *(s8*)T;
r=*(f32*)((u8*)vec1+4)+D_800FADF4[*(s8*)T][0];
if(func_800D3B24(vec1,T+0xAC,r,0))return *(s8*)T;
}}break;
case 4:case 20:return *(s8*)T;
case 2:
if(*(s8*)T==*(s8*)(arg0+0x353)){
if((FLAGS(arg0)&FLAGS(T))&0x140)return *(s8*)T;
}
break;
}
i++;
}
done:*(Nw2Vec4U*)D_800EB4D8[*(s8*)arg0]=*(Nw2Vec4U*)(arg0+0x5C+*(s8*)(arg0+0x397)*16);return -1;
}
#undef FLAGS
#undef OK
#undef COPY
