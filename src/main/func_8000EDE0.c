/* @header
 * func_8000EDE0
 * VRAM 0x8000EDE0 | ROM 0xF9E0 | size 0xF8
 * asm: asm/nonmatchings/main/func_8000EDE0.s
 */
#include "common.h"

extern s16 D_80059D80,D_80059D82;
extern void *D_80036C74[];
typedef struct {u8 data[0xDC];} EDE0Obj;
typedef struct {u8 data[0x2C];} EDE0Res;
extern EDE0Obj D_80057030[];
extern EDE0Res D_800583F8[];
extern u8 D_800587F0[], D_80058900[], D_80058988[];
extern s32 D_800587EC,D_800588F8,D_80058984;
void func_8000520C(void *,void *);
void freeResourceDescriptorArray(void *,s32,s16);
void func_8000F408(void);
/* Tears down the arena: releases each object's paired resource, frees the
 * descriptor arrays (conditionally the first, always the other two) and runs
 * the final cleanup. */
void func_8000EDE0(void) {
 u32 i;
 for(i=0;i<D_80059D80;i++) func_8000520C(&D_80057030[i],&D_800583F8[i]);
 if(D_80036C74[D_80059D82]) {freeResourceDescriptorArray(D_800587F0,D_800587EC,6);D_800587EC=0;}
 freeResourceDescriptorArray(D_80058900,D_800588F8,3);D_800588F8=0;
 freeResourceDescriptorArray(D_80058988,D_80058984,3);D_80058984=0;
 func_8000F408();
}
