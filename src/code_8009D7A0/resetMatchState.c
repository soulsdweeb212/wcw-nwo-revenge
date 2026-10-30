/* @header
 * resetMatchState  (originally func_800B7A30)
 * VRAM 0x800B7A30 | ROM 0xAAED0 | size 0x194
 * asm: asm/nonmatchings/code_8009D7A0/resetMatchState.s
 */
#include "common.h"

extern u8 D_8007E228[];
extern u8 D_80064AD8[];
extern u8 D_8007BD64[];
extern u8 D_800FA0E0[], D_800FA490[], D_800FA840[];
extern s16 D_800FAF8C;
extern s8 D_800FADCF, D_800FADCE, D_800EB465;
extern s16 D_800FACEA, D_800FACEC, D_800FACEE, D_800FACF0;
extern s16 D_800FAF96, D_800FAF98, D_800FAF9A, D_800FAF9C;
void func_800D4088(s32);
void func_80003684(void *, s32, void *);
void func_800B7BC4(void);
void func_800BFCF0(void);
/* Resets the match to its initial state: clears the action/animation counters,
 * snapshots the saved match settings from D_8007E228 into the D_800FACxx and
 * D_800FAF9x fields, loads five packed animation records into stack buffers,
 * clears the four 0x3B0-entity flag words, and (when D_8007E228+0x58 bit 0x100
 * is set) re-runs the fighter setup. */
void resetMatchState(void) {
 u8 b0[16], b1[16], b2[16], b3[16], b4[16];
 func_800D4088(0xA);
 D_800FAF8C=0;
 D_800FADCF=0;
 D_800FADCE=0;
 D_800EB465=0;
 D_800FACEA=*(s32*)(D_8007E228+0x688);
 D_800FACEC=*(s32*)(D_8007E228+0x68C);
 D_800FACEE=*(s32*)(D_8007E228+0x690);
 D_800FACF0=*(s32*)(D_8007E228+0x694);
 func_80003684(b0,0x126,D_8007BD64+0x14);
 func_80003684(b1,0x127,D_80064AD8+8);
 func_80003684(b2,0x128,D_80064AD8+8+0x190);
 func_80003684(b3,0x129,D_80064AD8+8+0x320);
 func_80003684(b4,0x12A,D_80064AD8+8+0x4B0);
 func_800B7BC4();
 *(u64*)D_800F9D30=0;
 *(u64*)D_800FA0E0=0;
 *(u64*)D_800FA490=0;
 *(u64*)D_800FA840=0;
 if (*(u16*)(D_8007E228+0x58)&0x100) {
  func_800BFCF0();
  func_800B7BC4();
 }
 D_800FAF96=*(s32*)(D_8007E228+0x698);
 D_800FAF98=*(s32*)(D_8007E228+0x69C);
 D_800FAF9A=*(s32*)(D_8007E228+0x6A0);
 D_800FAF9C=*(s32*)(D_8007E228+0x6A4);
}
