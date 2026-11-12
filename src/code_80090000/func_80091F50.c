/* @header
 * func_80091F50
 * VRAM 0x80091F50 | ROM 0x3E6C0 | size 0x2E0
 * asm: asm/nonmatchings/code_80090000/func_80091F50.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: a command is port.h's 16-byte Gfx. D_800DB69C holds the address of a heap block (func_800936DC allocates it),
 * so it is a pointer, as func_800B64EC takes it (its definition takes a u8 *). */
typedef Gfx G91F;extern u8 *D_800DB69C;extern u8 *D_800DBD48;extern u8 D_800C6410[];u8 *func_800B64EC(u8 *,s32);void func_80091718(G91F**,s32,s32,s32,s32);
#define E91F(a,b) {G91F*g=dl++;g->w0=(u32)(a);g->w1=(b);}
#else
typedef struct{u32 w0,w1;}G91F;extern s32 D_800DB69C;extern u8 *D_800DBD48;extern u8 D_800C6410[];u8 *func_800B64EC(s32,s32);void func_80091718(G91F**,s32,s32,s32,s32);
#define E91F(a,b) {G91F*g=dl++;g->w0=(u32)(a);g->w1=(u32)(b);}
static inline u32 k0phys91F(void *p) { return (u32)p - 0x80000000; }
#endif
void func_80091F50(G91F**out,s32 unused,s32 frame,s32 mode){G91F*dl=*out;u8 *palette,*texture;s32 row,col,x,y,tile,n;
    if(mode == 0){palette=func_800B64EC(D_800DB69C,14);texture=func_800B64EC(D_800DB69C,15);
#ifdef TARGET_PC
        /* PC: the vertices', palette's and texture's addresses as the whole pointers (port.h's DL_ADDR); the N64 writes
         * D_800C6410 as a 32-bit address and the others through k0phys91F, which subtracts 0x80000000 in 32 bits. */
        E91F(0xE7000000,0);E91F(0xE3001001,0x8000);E91F(0x01004008,DL_ADDR(D_800C6410));E91F(0xFD100000,DL_ADDR(palette));E91F(0xE8000000,0);E91F(0xF5000100,0x07000000);E91F(0xE6000000,0);E91F(0xF0000000,0x073FC000);E91F(0xE7000000,0);E91F(0xFD500000,DL_ADDR(texture+8));E91F(0xF5500000,0x07000000);E91F(0xE6000000,0);E91F(0xF3000000,0x073FF100);E91F(0xE7000000,0);E91F(0xF5481000,0);E91F(0xF2000000,0xFC07C);E91F(0x07040602,0x40200);
    /* PC: the row's vertices (in the block D_800DBD48 holds) as the whole pointer (port.h's DL_ADDR). */
    }else{E91F(0xE7000000,0);E91F(0xE3001001,0);row=0;y=0;n=0;do{col=0;x=0;tile=0;E91F(0x0100E01C,DL_ADDR(D_800DBD48+n*0x70));do{func_80091718(&dl,x,y,tile,0);col++;tile++;x+=80;}while(col<6);row++;n++;y+=20;}while(row<12);}*out=dl;}
#else
        E91F(0xE7000000,0);E91F(0xE3001001,0x8000);E91F(0x01004008,D_800C6410);E91F(0xFD100000,k0phys91F(palette));E91F(0xE8000000,0);E91F(0xF5000100,0x07000000);E91F(0xE6000000,0);E91F(0xF0000000,0x073FC000);E91F(0xE7000000,0);E91F(0xFD500000,k0phys91F(texture+8));E91F(0xF5500000,0x07000000);E91F(0xE6000000,0);E91F(0xF3000000,0x073FF100);E91F(0xE7000000,0);E91F(0xF5481000,0);E91F(0xF2000000,0xFC07C);E91F(0x07040602,0x40200);
    }else{E91F(0xE7000000,0);E91F(0xE3001001,0);row=0;y=0;n=0;do{col=0;x=0;tile=0;E91F(0x0100E01C,D_800DBD48+n*0x70);do{func_80091718(&dl,x,y,tile,0);col++;tile++;x+=80;}while(col<6);row++;n++;y+=20;}while(row<12);}*out=dl;}
#endif
