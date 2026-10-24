#include "common.h"

typedef struct{u32 w0,w1;}G922;extern s32 D_800DB69C;extern u8 *D_800DBD48;extern u8 D_800C6450[];u8 *func_800B64EC(s32,s32);void func_80091718(G922**,s32,s32,s32,s32);
#define E922(a,b) {G922*g=dl++;g->w0=(u32)(a);g->w1=(u32)(b);}
static inline u32 k0phys(void *p) { return (u32)p - 0x80000000; }
void func_80092230(G922**out,s32 unused,s32 frame,s32 mode){G922*dl=*out;u8 *palette,*texture;s32 row,col,x,y,tile,base,n;
if(mode == 0){palette=func_800B64EC(D_800DB69C,14);texture=func_800B64EC(D_800DB69C,15);
E922(0xE7000000,0);E922(0xE3001001,0x8000);E922(0x01004008,D_800C6450);E922(0xFD100000,k0phys(palette));E922(0xE8000000,0);E922(0xF5000100,0x07000000);E922(0xE6000000,0);E922(0xF0000000,0x0703C000);E922(0xE7000000,0);E922(0xFD500000,k0phys(texture+8));E922(0xF5500000,0x07000000);E922(0xE6000000,0);E922(0xF3000000,0x071FF200);E922(0xE7000000,0);E922(0xF5400800,0);E922(0xF2000000,0xFC07C);E922(0x07040602,0x40200);
}else{E922(0xE7000000,0);E922(0xE3001001,0);base=((frame/2)*0x1C200+(frame%2)*0x1E0)>>1;row=0;y=0;n=0;do{col=0;x=0;tile=0;E922(0x0100E01C,D_800DBD48+n*0x70);do{func_80091718(&dl,x,y,tile,base);col++;tile++;x+=80;}while(col<3);row++;n++;y+=20;}while(row<6);{G922 pad;}}*out=dl;}
