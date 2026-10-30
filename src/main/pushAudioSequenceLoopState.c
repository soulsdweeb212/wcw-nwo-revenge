/* @header
 * pushAudioSequenceLoopState  (originally func_800165FC)
 * VRAM 0x800165FC | ROM 0x171FC | size 0xB4
 * asm: asm/nonmatchings/main/pushAudioSequenceLoopState.s
 */
#include "common.h"

typedef struct {u8 p0[0x48];u8 *f48,*f4C;u8 p50[0x40];f32 f90;u8 p94[0x2e];u16 fC2,fC4;u8 pC6[0x16];u8 fDC;u8 pDD[0x1e];u8 fFB;u8 pFC[4];u8 *p100[4],*p110[4],*p120[4];u16 p130[4],p138[4];u8 p140[4],p144[4],p148[4];} V165FC;

/* Push the current sequence state onto the loop stack at depth v->fFB: save the
 * loop byte, the stream pointer, the two sample pointers, the note and the two
 * counters, then advance the depth. Returns the advanced stream pointer. */
u8 *pushAudioSequenceLoopState(V165FC *v,u8 *p){s32 depth=v->fFB;v->p140[depth]=*p++;v->p100[depth]=p;v->p110[depth]=v->f4C;v->p120[depth]=v->f48;v->p144[depth]=v->fDC;v->p148[depth]=(u8)v->f90;v->p130[depth]=v->fC2;v->p138[depth]=v->fC4;v->fFB++;return p;}
