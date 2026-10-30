/* @header
 * func_800A3BFC
 * VRAM 0x800A3BFC | ROM 0x9709C | size 0x178
 * asm: asm/nonmatchings/code_8009D7A0/func_800A3BFC.s
 */
#include "common.h"

typedef struct {s32 f0; s16 f4; u8 pad6[26]; u64 flags; u8 pad28[0x329]; s8 f351; u8 pad352[16]; s8 f362;} Obj3B;
extern void *D_800EB40C;
extern u8 D_800FABE4,D_800FADB8;
void func_800D2BEC(void*,void*,void*,f32,u16,s32);
s16 func_800D5438(void*,s32);
void func_800D427C(void*,s16,s32);
void func_800A6BE0(void*,s32);
void func_800D4AD0(void*);
void beginEntityActionA8D8C(void*);
void func_800C472C(void*,void*,s32);
#define A ((Obj3B*)D_800EB408)
#define B ((Obj3B*)D_800EB40C)
void func_800A3BFC(void){
Obj3B *p = A;
s32 k;
do { } while (0);
k = 0xffffe;
func_800D2BEC(p,B,0,4.0f,0,k);
if(B->flags&0x800000ULL){
func_800D427C(A,func_800D5438(A,0),1);
func_800A6BE0(A,0x51);func_800A6BE0(B,0x52);
A->flags|=0x40000000ULL;
B->flags&=~0x40000000ULL;
A->f362=D_800FABE4;B->f362=-1;B->f351=D_800FADB8;
}
if(A->f4<=0){func_800D4AD0(A);beginEntityActionA8D8C(A);func_800C472C(B,A,2);}
}
