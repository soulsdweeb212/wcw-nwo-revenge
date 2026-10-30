/* @header
 * func_80093DAC
 * VRAM 0x80093DAC | ROM 0x4051C | size 0x2A8
 * asm: asm/nonmatchings/code_80090000/func_80093DAC.s
 */
#include "common.h"

extern u8 func_800DB4FC[],func_800DBB80[],handleEntityState38To3F[],applyEntityMovementC8D84[],updateEntityAttackState[],sceneNodeCallback5AD0[],sceneNodeCallback5C50[];
extern f32 D_800E7508,D_800E7510,D_800E74F8,D_800E74FC,D_800E7500,D_800E750C,D_800E7504;extern s32 D_800E74C4,D_800E8210,D_800E79BC,D_800E9F70,D_800E74E8;extern s16 D_800E74D2,D_800E74D0,D_800E74CE,D_800E74CC;
void initializeTransformNode(void*,s32,f32,f32,f32);void func_800015AC(void*,s32);void func_80001544(void*);void buildScaledRotationTranslationMatrix(void*,f32,f32,f32,f32,f32,f32,f32);void *allocateHeap(u32);void func_80021C40(void*,void*,s32);
#define W(b,n) (*(s32*)((b)+(n)))
u8 *func_80093DAC(u8 *a,u8 *b){f32 mat[20];u8 *p,*next,*record;void *alloc;s32 i,rword;f32 zero=0.0f;initializeTransformNode(b,6,zero,zero,zero);W(b,4)=(s32)a;initializeTransformNode(a,6,zero,zero,zero);W(a,0)=(s32)b;
{ s32 t = (s32)a + 0xDC; W(a,4)=t; W(func_800DB4FC,0x178)=t; p=(u8*)t; }
W(func_800DBB80,0x1CC)=0;buildScaledRotationTranslationMatrix(mat,zero,zero,zero,1.0f,zero,zero,zero);W(func_800DB4FC,0x19C)=(s32)allocateHeap(0x2000);W(func_800DB4FC,0x194)=(s32)allocateHeap(0x1800);alloc=allocateHeap(0x6000);i=0;record=applyEntityMovementC8D84+0x100+W(func_800DB4FC,0x18C)*52;rword=W(record,12);W(handleEntityState38To3F,0x3C)=(s32)alloc;W(updateEntityAttackState,0x80)=0;W(func_800DB4FC,0x184)=(s32)record;W(func_800DB4FC,0x188)=rword;
for(i=0;i<72;i++){initializeTransformNode(p,6,zero,zero,zero);W(p,12)=(s32)sceneNodeCallback5AD0;W(p,16)=(s32)sceneNodeCallback5C50;func_800015AC(p,1);func_80001544(p);next=p+0xDC;W(p,0)=(s32)a;W(p,8)=(s32)next;p[24]|=0x80;func_80021C40(mat,p+28,64);p=next;}
D_800E7508=zero;D_800E7510=zero;W(handleEntityState38To3F,0x34)=0;D_800E74C4=0;D_800E8210=-1;D_800E79BC=255;D_800E74D2=0;D_800E74D0=0;D_800E74CE=0;D_800E74CC=0;D_800E9F70=-1;W(func_800DB4FC,0x18C)=-1;D_800E74E8=0;W(func_800DB4FC,0x1A4)=0;W(func_800DB4FC,0x1A0)=0;D_800E74F8=-868.0f;D_800E74FC=-565.0f;D_800E7500=3081.0f;D_800E750C=-34.0f;D_800E7504=1.0f;return p;}
