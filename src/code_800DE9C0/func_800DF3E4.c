#include "common.h"

/* Grab/throw attempt: when asked (flags & 0x10), either play the hurt reaction
 * on self, or start a paired grab action (0x32/0x33) with the opponent if it
 * is grabbable and close enough, or a secondary grab (0x34/0x35); otherwise
 * fall back to a generic strike. Returns 1 if an action was chosen. */
extern f64 D_800E76A0, D_800E76A8;
f32 func_800D3EEC(void *,void *,s32);
void func_800E212C(void *);
void beginPairedEntityActions(void *,s32,void *,s32);
s32 func_800DF3E4(u8 *self,u8 *other,s32 flags,f32 distance) {
 if(flags & 0x10) {
  if(*(u64 *)(self+0x20)&0x80ULL) { func_800A6C48(self,9); return 1; }
  if((*(u64 *)(other+0x20)&0x400000ULL) && (f64)distance < (f64)func_800D3EEC(other+0x4C,self+0x6C,*(s32 *)(other+0x58))+D_800E76A0 && !(*(u64 *)(other+0x20)&0x1000000000ULL) && (*(u64 *)(self+0x20)&*(u64 *)(other+0x20)&0x140ULL)) {
   func_800E212C(self); beginPairedEntityActions(self,0x32,other,0x33); return 1;
  }
  if((other[0x37]&1) && (*(u64 *)(self+0x20)&*(u64 *)(other+0x20)&0x40ULL) && (f64)distance < D_800E76A8) {
   func_800E212C(self); beginPairedEntityActions(self,0x34,other,0x35); return 1;
  }
  func_800E212C(self); func_800A6C48(self,0x40); return 1;
 }
 return 0;
}
