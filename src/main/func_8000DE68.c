#include "common.h"

extern s16 D_80030D38[],D_80030DD4[];
void func_8000327C(s32);
/* Plays sound arg0: ids below 0x4D index D_80030D38, ids 0x4D+ index the 0x34
 * entries of D_80030DD4. Valid (non-negative) ids are played and return 1. */
s32 func_8000DE68(s16 arg0) {
 s16 idx;
 s32 v;
 if(arg0>0) {
 if(arg0<0x4D) v=D_80030D38[arg0];
 else {idx=arg0-0x4D;if(idx>=0x34)return 0;v=D_80030DD4[idx];}
 if(v>=0) {func_8000327C(v);return 1;}
 }
 return 0;
}
extern u32 D_800604C8;extern u8 *D_800604D0; extern s32 *D_800604D8;
s32 func_80015F64(void *,s32,s32,s32,s32);
extern s32 *D_80036F54;
void func_8002023C(void *);void func_8002021C(void *,void *);
s32 *func_80017F18(void); s32 func_80018C24(s32*,s32,s32*);
