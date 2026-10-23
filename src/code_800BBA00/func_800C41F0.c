#include "common.h"

void playEntitySound(s8,s32);
void beginPairedEntityActions(void *,s32,void *,s32);

/* Decides whether self can start a counter/paired move against partner and, if
 * so, records the move category in self's u16 +0x3A and fires the matching paired
 * actions.  It rejects a self already linked to partner (+0x355), and when self
 * has flag 0x8000000 it only allows partner states 30/7/28/31 (without partner
 * flags 9), emitting action 0x5C.  Otherwise it maps partner's animation id
 * (+0x386) to a category bit in +0x3A and picks the paired action pair:
 * 0x5A/0x5B (mask 0x7E00), 0x79/0x7A (mask 0x40, and self +0x2C = 0x2010000),
 * 0x5D/0x5E (mask 1) or 0x58/0x59 (default). */
s32 func_800C41F0(u8 *self,u8 *partner) {
#define S(p,o) (*(s16 *)((p)+(o)))
#define H(p,o) (*(u16 *)((p)+(o)))
#define Q(p,o) (*(u64 *)((p)+(o)))
 s32 actionMask;
 if (*(s8 *)(self+0x355)==*(s8 *)partner) return 0;
 if(Q(self,0x20)&0x8000000) {
 if(S(self,0xA)==0x40) return 0;
 switch(S(partner,0xA)) {
 case 30: if(Q(partner,0x20)&9) return 0;
 case 7: case 28: case 31:
 playEntitySound(*(s8 *)self,300);func_800A6C48(self,0x5C);return 1;
 default:return 0;
 }
 }
 H(self,0x3A)=0;
 switch((s16)(S(partner,0xA)-7)) {
 case 23: if(Q(partner,0x20)&9) return 0;
 case 0:case 21:case 24:case 28:
 if(!(Q(partner,0x20)&9) && (u32)(H(partner,0x386)-0x95)<2) H(self,0x3A)|=1;
 switch(S(partner,0x386)) {
 case 5:actionMask=0x80;break;case 6:actionMask=0x100;break;
 case 157:actionMask=2;break;case 159:actionMask=4;break;case 161:actionMask=8;break;case 163:actionMask=16;break;case 165:actionMask=32;break;case 182:actionMask=64;break;
 case 20:actionMask=0x200;break;case 21:actionMask=0x400;break;
 case 41:actionMask=0x2000;break;case 42:actionMask=0x4000;break;
 case 23:actionMask=0x800;break;case 24:actionMask=0x1000;break;
 default:actionMask=0;break;
 }
 H(self,0x3A)|=actionMask;
 playEntitySound(*(s8 *)self,300);
 if(H(self,0x3A)&0x7E00) beginPairedEntityActions(self,0x5A,partner,0x5B);
 else if(H(self,0x3A)&0x40) {beginPairedEntityActions(self,0x79,partner,0x7A);*(s32 *)(self+0x2C)=0x2010000;}
 else if(H(self,0x3A)&1) beginPairedEntityActions(self,0x5D,partner,0x5E);
 else beginPairedEntityActions(self,0x58,partner,0x59);
 return 1;
 }
 return 0;
#undef S
#undef H
#undef Q
}
