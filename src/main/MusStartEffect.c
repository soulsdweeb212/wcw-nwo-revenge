/* @header
 * MusStartEffect  (originally func_80013994)
 * VRAM 0x80013994 | ROM 0x14594 | size 0xB4
 * asm: asm/nonmatchings/main/MusStartEffect.s
 */
/* SDK: libmus, libmus/src/player.c (+playerinc/player_api.inc.c) (SDK code with changes, see docs/sdk_functions.md). */
#include "common.h"

extern s16 D_80030D38[],D_80030DD4[];
void func_8000327C(s32);
extern u32 max_channels;extern u8 *mus_channels; extern s32 *D_800604D8;
s32 __MusIntStartEffect(void *,s32,s32,s32,s32);
/* Allocates a voice for channel arg0 (threshold D_800604D8[arg0]): first free
 * voice, else the least-recently-used one below the threshold; returns 0 when
 * none qualifies. */
s32 MusStartEffect(s32 arg0) {
    u8 *p=mus_channels,*best;
    s32 threshold=D_800604D8[arg0];
    s32 min=threshold+1;
    u32 i;
    for(i=0;i<max_channels;i++,p+=0x158) {
        if(*(s32*)(p+4)==0) return __MusIntStartEffect(p,arg0,128,128,threshold);
        if(*(u16*)(p+0xC6)!=0 && *(s32*)(p+0x64)<min) {min=*(s32*)(p+0x64);best=p;}
    }
    if(min<threshold) return __MusIntStartEffect(best,arg0,128,128,threshold);
    return 0;
}
extern s32 *n_syn;
void alUnlink(void *);void alLink(void *,void *);
s32 *__n_allocParam(void); s32 n_alEnvmixerParam(s32*,s32,s32*);
