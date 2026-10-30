/* @header
 * func_800D05E4
 * VRAM 0x800D05E4 | ROM 0xC3A84 | size 0x11C
 * asm: asm/nonmatchings/code_800BBA00/func_800D05E4.s
 */
#include "common.h"

typedef struct {s8 id;u8 p1[0x2B];s32 f2C;u8 p30[0x37C];s32 f3AC;} Nw2D05E4Entity;
typedef struct {s8 id;u8 p1[0x1F];u64 flags;s32 f28,f2C;} Nw2D05E4Obj;
s32 func_800A8D14(void*,void*);void func_800A7C40(void*,s8,s16);void func_800A7F6C(void*,s32);
s32 func_800D05E4(Nw2D05E4Entity *arg0,Nw2D05E4Obj *arg1,s16 arg2){
 u64 flags=arg1->flags;s32 f;
 if(!(flags&0x02000000))goto ret0;
 if(!(arg0->f3AC&1))goto ret0;
 f=arg0->f2C;
 if(f&0x400){if(f&0x40){if(f&2){arg2=0x45;arg1->f2C=2;}else arg2=0x44;goto finish;}
shared:arg1->flags=flags|0x01000000;func_800A7C40(arg1,arg0->id,(s16)func_800A8D14(arg0,arg1));goto ret0;}
 if(f&0x80)goto shared;if(f&0x100)arg2=0x7F;if(f&0x200)arg2=0x83;
finish:func_800A7C40(arg1,arg1->id,arg2);func_800A7F6C(arg1,0);return 1;
ret0:return 0;
}
