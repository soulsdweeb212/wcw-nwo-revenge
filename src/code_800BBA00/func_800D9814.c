#include "common.h"

extern f64 D_800E6FF0,D_800E6FF8;
s32 func_800D9814(u8 *arg0) {
 s16 dir;
 if(*(u64 *)(arg0+0x20)&0x40) {
 if(*(s16 *)(arg0+0xA)==10) {
 if(*(u64 *)(arg0+0x20)&0x200000000ULL) dir=0; else dir=2;
 if(dir==*(s16 *)(arg0+0x3E)) return 1;
 }
 }
 if(*(u64 *)(arg0+0x20)&0x80) {
 if(*(u64 *)(arg0+0x20)&0x200000000ULL) {
 if(*(f32 *)(arg0+0x6C)>D_800E6FF0 && *(f32 *)(arg0+0x74)>D_800E6FF0) return 1;
 } else {
 if(*(f32 *)(arg0+0x6C)<D_800E6FF8 && *(f32 *)(arg0+0x74)<D_800E6FF8) return 1;
 }
 }
 return 0;
}
