/* @header
 * n_alSynSetFXMix  (originally func_800177D0)
 * VRAM 0x800177D0 | ROM 0x183D0 | size 0x84
 * asm: asm/nonmatchings/main/n_alSynSetFXMix.s
 */
/* SDK: n_audio, libnaudio/src/n_synsetfxmix.c (same code as the SDK source). */
#include "common.h"

extern s16 D_80030D38[],D_80030DD4[];
void func_8000327C(s32);
extern u32 D_800604C8;extern u8 *D_800604D0; extern s32 *D_800604D8;
s32 __MusIntStartEffect(void *,s32,s32,s32,s32);
extern s32 *D_80036F54;
void alUnlink(void *);void alLink(void *,void *);
s32 *__n_allocParam(void); s32 n_alEnvmixerParam(s32*,s32,s32*);
/* Sends command 16 (with payload arg1&255) to the node referenced by arg0[2]. */
void n_alSynSetFXMix(s32 *arg0,s32 arg1) {
    s32 *p;
    if(arg0[2]!=0) {
        p=__n_allocParam();
        if(p!=0) {
            p[1]=D_80036F54[7]+*(s32*)((u8*)arg0[2]+0x88);
            *(s16*)((u8*)p+8)=16;
            p[3]=arg1&255;p[0]=0;
            n_alEnvmixerParam((s32*)arg0[2],3,p);
        }
    }
}
