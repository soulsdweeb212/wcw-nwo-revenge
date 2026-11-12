/* @header
 * func_80091908
 * VRAM 0x80091908 | ROM 0x3E078 | size 0x340
 * asm: asm/nonmatchings/code_80090000/func_80091908.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: a command is port.h's 16-byte Gfx. D_800DB69C holds the address of a heap block (func_800936DC allocates it),
 * so it is a pointer, as func_800B64EC takes it (its definition takes a u8 *). */
typedef Gfx G919;extern u8 *D_800DB69C;extern u8 *D_800DBD48;extern u8 D_800C6210[];u8 *func_800B64EC(u8 *,s32);void func_80091718(G919**,s32,s32,s32,s32);
#define E919(a,b) {G919*g=dl++;g->w0=(u32)(a);g->w1=(b);}
#else
typedef struct{u32 w0,w1;}G919;extern s32 D_800DB69C;extern u8 *D_800DBD48;extern u8 D_800C6210[];u8 *func_800B64EC(s32,s32);void func_80091718(G919**,s32,s32,s32,s32);
#define E919(a,b) {G919*g=dl++;g->w0=(u32)(a);g->w1=(u32)(b);}
static inline u32 k0phys919(void *p) { return (u32)p - 0x80000000; }
#endif
#ifdef TARGET_PC
/* PC: the vertices' (D_800C6210 and the rows in the block D_800DBD48 holds), palette's and texture's addresses go into
 * the commands as the whole pointers (port.h's DL_ADDR); the N64 writes the vertices' as 32-bit addresses and the
 * others through k0phys919, which subtracts 0x80000000 in 32 bits. */
void func_80091908(G919**out,s32 unused,s32 frame,s32 mode){G919*dl=*out;u8 *palette,*texture;s32 row,col,x,y,tile,n,h,cmd;
    if(mode < 2){y=(mode*4+frame)*2;palette=func_800B64EC(D_800DB69C,y+0x1A);texture=func_800B64EC(D_800DB69C,y+0x1B);
        E919(0xE7000000,0);E919(0xE3001001,0x8000);E919(0x01004008,DL_ADDR(D_800C6210+frame*64));E919(0xFD100000,DL_ADDR(palette));E919(0xE8000000,0);E919(0xF5000100,0x07000000);E919(0xE6000000,0);E919(0xF0000000,0x073FC000);E919(0xE7000000,0);E919(0xFD500000,DL_ADDR(texture+8));E919(0xF5500000,0x07000000);E919(0xE6000000,0);E919(0xF3000000,0x073FF100);E919(0xE7000000,0);E919(0xF5481000,0);E919(0xF2000000,0xFC07C);E919(0x07040602,0x40200);
    }else{h=frame/2;E919(0xE7000000,0);E919(0xE3001001,0);y=h*120;row=0;cmd=0x0100E01C;n=h*6;do{x=(frame%2)*240;tile=(frame%2)*3;col=0;E919(cmd,DL_ADDR(D_800DBD48+n*0x70));do{func_80091718(&dl,x,y,tile,0);col++;tile++;x+=80;}while(col<3);row++;n++;y+=20;}while(row<6);}*out=dl;}
#else
void func_80091908(G919**out,s32 unused,s32 frame,s32 mode){G919*dl=*out;u8 *palette,*texture;s32 row,col,x,y,tile,n,h,cmd;
    if(mode < 2){y=(mode*4+frame)*2;palette=func_800B64EC(D_800DB69C,y+0x1A);texture=func_800B64EC(D_800DB69C,y+0x1B);
        E919(0xE7000000,0);E919(0xE3001001,0x8000);E919(0x01004008,D_800C6210+frame*64);E919(0xFD100000,k0phys919(palette));E919(0xE8000000,0);E919(0xF5000100,0x07000000);E919(0xE6000000,0);E919(0xF0000000,0x073FC000);E919(0xE7000000,0);E919(0xFD500000,k0phys919(texture+8));E919(0xF5500000,0x07000000);E919(0xE6000000,0);E919(0xF3000000,0x073FF100);E919(0xE7000000,0);E919(0xF5481000,0);E919(0xF2000000,0xFC07C);E919(0x07040602,0x40200);
    }else{h=frame/2;E919(0xE7000000,0);E919(0xE3001001,0);y=h*120;row=0;cmd=0x0100E01C;n=h*6;do{x=(frame%2)*240;tile=(frame%2)*3;col=0;E919(cmd,D_800DBD48+n*0x70);do{func_80091718(&dl,x,y,tile,0);col++;tile++;x+=80;}while(col<3);row++;n++;y+=20;}while(row<6);}*out=dl;}
#endif
