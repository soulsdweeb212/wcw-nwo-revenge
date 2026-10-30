/* @header
 * resolveEntityMoveHeading  (originally func_800B4690)
 * VRAM 0x800B4690 | ROM 0xA7B30 | size 0x4AC
 * asm: asm/nonmatchings/code_8009D7A0/resolveEntityMoveHeading.s
 */
#include "common.h"

/* Resolve an entity's move/action heading from the input word.
 * Picks a direction index (dirIndex) from the input and the entity's status
 * flags, validates the resulting target against the ring boundary
 * (getRingBoundaryPointAlongHeading) and the movement check (func_800D2ACC),
 * writes the chosen heading to *out, and returns 1 if the move is allowed or
 * 0 if it is blocked. moveFlags collects the resolution bits. */
typedef struct {
    u8 pad0[0x20];
    u64 flags;          /* +0x20 entity status bits */
    u16 moveFlags;      /* +0x28 resolution/result bits */
    u8 pad2A[0x12];
    s16 facing;         /* +0x3C */
    s16 dirIndex;       /* +0x3E */
    u8 pad40[0x2C];
    f32 pos[3];         /* +0x6C world position */
    u8 pad78[0x2C4];
    f32 vec[4];         /* +0x33C */
} ObjB4690;
extern s32 D_800E3C90[],D_800E3CA0[],D_800E3CB0[],D_800F9B14;
s16 func_800D7B08(u16); s16 func_800D7A2C(u16);
s16 findBoundaryQuadrant(void*,void*,s32); s8 func_800B4B3C(void*);
void func_800E212C(void*); s16 func_800D65D0(void*,u16);
void getRingBoundaryPointAlongHeading(void*,s32,void*);
s32 func_800D6610(void*,s16); f32 func_800D63F0(void*,s32,s32);
void func_800D37C0(s32,f32,void*); s8 func_800D26A0(void*,void*,s32);
u32 func_800D2ACC(void*,s32,void*);
s32 resolveEntityMoveHeading(ObjB4690 *obj,u16 input,s32 *out) {
 f32 point[4]; s16 idx; s16 result; u32 hit;
 obj->moveFlags=0; obj->flags&=~0x8001000000ULL;
 if(input&0xF00){
 if(((*(volatile u64*)&obj->flags)&0x40) && ((obj->dirIndex=func_800D7B08(input))!=-1)){if(obj->dirIndex==findBoundaryQuadrant(obj,0,2))return 0;obj->moveFlags|=9;}
 else obj->moveFlags|=3;
 }else obj->moveFlags=4;
 if(obj->moveFlags&2){
 if((obj->flags&0x100) && (result=func_800D7B08(input))!=-1){obj->moveFlags|=0x10;*out=D_800E3CB0[result];}
 else {
 if(obj->flags&0x140){obj->dirIndex=func_800D7A2C(input);*out=D_800E3C90[obj->dirIndex];if(func_800B4B3C(obj)){obj->moveFlags|=0x4000;func_800E212C(obj);}}
 if(obj->flags&0x80){result=func_800D65D0(obj,input);if(!result)return 0;idx=(u16)obj->facing;if(result==1){obj->flags|=0x8000000000ULL;idx--;}else idx++;obj->dirIndex=idx&3;*out=D_800E3C90[obj->dirIndex];}
 }
 }
 if(obj->moveFlags&4){
 if(obj->flags&0x40){s32 *heading=&D_800F9B14;getRingBoundaryPointAlongHeading(obj->pos,*heading,point);obj->dirIndex=findBoundaryQuadrant(obj,point,0);if(obj->dirIndex==-1){obj->dirIndex=getXZDirectionQuadrant(point);*out=*heading;obj->moveFlags|=2;}else obj->moveFlags|=8;}
 if(obj->flags&0x80){idx=obj->facing;if(func_800D3684(D_800E3CA0[idx],D_800F9B14)<0){obj->flags|=0x8000000000ULL;idx--;}else idx++;obj->dirIndex=idx&3;*out=D_800E3C90[obj->dirIndex];obj->moveFlags|=2;}
 if(obj->flags&0x100)*out=D_800F9B14;
 }
 if(obj->moveFlags&8)*out=func_800D6610(obj,obj->dirIndex);
 func_800D37C0(*out,func_800D63F0(obj,0,2),obj->vec);
 if(func_800D26A0(obj,obj->vec,-1)!=-1)return 0;
 hit=func_800D2ACC(obj,2,obj->vec);
 if(hit && (obj->moveFlags&6)){
 if(obj->flags&0x80)return 0;
 if((obj->flags&0x100) && (hit>>16))return 0;
 }
 return 1;
}
