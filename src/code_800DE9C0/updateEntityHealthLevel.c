/* @header
 * updateEntityHealthLevel  (originally func_800E13F8)
 * VRAM 0x800E13F8 | ROM 0xD4898 | size 0x168
 * asm: asm/nonmatchings/code_800DE9C0/updateEntityHealthLevel.s
 */
#include "common.h"

extern u16 D_800FAF50[];
extern s16 D_800F98D8[];
s32 func_800BF2FC(Wrestler *);
static inline u16 getCount(Wrestler *w) { if (w->state==0x42) return 0; return D_800FAF50[w->id]; }
static inline s16 getValue(Wrestler *w) { if (w->state==0x42) return 255; return func_800BF2FC(w); }
/* Computes the wrestler's health/status level code, stores it into D_800F98D8[w->id] and returns it. A wrestler
 * with WR_FLAG_SPECIAL uses the 0xF3E code (0xF3D without flag bit 0x200000; 2 less when profile+0x38 has bit
 * 0x800000). Otherwise the level is 1..2 from D_800FAF50[id] (the last hit's size, docs/wrestler.md; >= 15,
 * >= 22), else 0..2 from health (func_800BF2FC, which gives health here as SPECIAL is clear; >= 128 -> 0,
 * >= 64 -> 1, else 2), then offset by 0xF2D and +6 with flag bit 0x200000. In state 0x42 the D_800FAF50 value
 * counts as 0 and health as 255. */
s16 updateEntityHealthLevel(Wrestler *w) {
    s16 result, base;
    s16 value;
    u16 count;
    if (w->flags & WR_FLAG_SPECIAL) {
        result = 0xF3E;
        if (!(w->flags & 0x200000ULL)) result=0xF3D;
        if (*(u64 *)(w->profile+0x38) & 0x800000ULL) result-=2;
    } else {
        count=getCount(w);
        if ((s16)count>=15) {
            result=1;
            if ((s16)count>=22) result=2;
        } else {
            value=getValue(w);
            if (value>=128) result=0;
            else { result=2; if(value>=64) result=1; }
        }
        base=result+0xF2D;
        result=base;
        if (w->flags&0x200000ULL) result=base+6;
    }
    D_800F98D8[w->id]=result;
    return result;
}
