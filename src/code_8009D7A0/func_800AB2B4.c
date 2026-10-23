#include "common.h"

extern u8 D_8007E228[],D_8007EF30[];
extern u8 *D_800FAF58,*D_800FABD0;
typedef union { u64 value; struct {u32 hi,lo;} words;} FlagPairAB;
s32 func_800AB2B4(void) {
 s32 off; FlagPairAB f; u8 *p;
 if (!(*(u16*)(D_8007E228+0x58)&0x200)) return 0;
 if (*(u16*)(D_8007EF30+0x170)&0x40) return 0;
 p=D_800FAF58; f.value=*(u64*)(p+0x20);
 if (f.value&0x80ULL) {
 if (!(f.value&0x200ULL)) {
 off=*(s8*)(p+0x353)*0x3B0;
 f.words.hi=*(u32*)(D_800F9D30+off); f.words.lo=*(u32*)(D_800F9D34+off);
 if (!(f.value&0x200ULL) && (f.value&0x80ULL)) goto success;
 }
 p=D_800FAF58; f.value=*(u64*)(p+0x20);
 }
 if ((f.value&0x40ULL) && (f.value&0x200ULL)) {
 off=*(s8*)(p+0x353)*0x3B0;
 f.words.hi=*(u32*)(D_800F9D30+off); f.words.lo=*(u32*)(D_800F9D34+off);
 if (!(f.value&0x200ULL) && !(f.value&0x40ULL)) {
 success:
 *(s16*)(D_800FABD0+8)=1;
 return 1;
 }
 }
 return 0;
}
