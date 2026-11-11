/* @header
 * func_800AB2B4
 * VRAM 0x800AB2B4 | ROM 0x9E754 | size 0x188
 * asm: asm/nonmatchings/code_8009D7A0/func_800AB2B4.s
 */
#include "common.h"

extern u8 D_8007E228[],D_8007EF30[];
extern u8 *D_800FABD0;
typedef union { u64 value; struct {u32 hi,lo;} words;} FlagPairAB;
s32 func_800AB2B4(void) {
    s32 off; FlagPairAB f; Wrestler *p;
    if (!(*(u16*)(D_8007E228+0x58)&0x200)) return 0;
    if (*(u16*)(D_8007EF30+0x170)&0x40) return 0;
    p=D_800FAF58; f.value=p->flags;
    if (f.value&WR_FLAG_ON_APRON) {
        if (!(f.value&WR_FLAG_LEGAL)) {
#ifdef TARGET_PC
            /* PC: a wrestler record is sizeof(Wrestler) bytes (0x3B8), not the N64's 0x3B0, so the byte offset of slot n is n * sizeof(Wrestler). */
            off=p->opponentId*(s32)sizeof(Wrestler);
#else
            off=p->opponentId*0x3B0;
#endif
            f.words.hi=((WrFlagWords *)((u8 *)&D_800F9D10[0].flags+off))->hi; f.words.lo=((WrFlagWords *)((u8 *)&D_800F9D10[0].flags+off))->lo;
            if (!(f.value&WR_FLAG_LEGAL) && (f.value&WR_FLAG_ON_APRON)) goto success;
        }
        p=D_800FAF58; f.value=p->flags;
    }
    if ((f.value&WR_FLAG_IN_RING) && (f.value&WR_FLAG_LEGAL)) {
#ifdef TARGET_PC
        off=p->opponentId*(s32)sizeof(Wrestler);
#else
        off=p->opponentId*0x3B0;
#endif
        f.words.hi=((WrFlagWords *)((u8 *)&D_800F9D10[0].flags+off))->hi; f.words.lo=((WrFlagWords *)((u8 *)&D_800F9D10[0].flags+off))->lo;
        if (!(f.value&WR_FLAG_LEGAL) && !(f.value&WR_FLAG_IN_RING)) {
success:
            *(s16*)(D_800FABD0+8)=1;
            return 1;
        }
    }
    return 0;
}
