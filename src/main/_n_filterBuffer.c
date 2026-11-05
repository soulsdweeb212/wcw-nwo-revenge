/* @header
 * _n_filterBuffer  (originally func_8001A2C0)
 * VRAM 0x8001A2C0 | ROM 0x1AEC0 | size 0x98
 * asm: asm/nonmatchings/main/_n_filterBuffer.s
 */
/* SDK: n_audio, libnaudio/src/n_reverb.c (same code as the SDK source). */
#include "common.h"

u32 osVirtualToPhysical(u32);

/* Build a 4-word command/display-list entry into `out` from the source record
 * `src`: word0 = 0x0B000020, word1 = translated address of src+8,
 * word2 = (src[0x2F] << 16) | (u16 at src+2 | 0x0E000000),
 * word3 = (offset>>8)<<24 | (translated src+0x28 & 0xFFFFFF).
 * Clears src+0x2C and returns a pointer past the emitted entry. */
void *_n_filterBuffer(u8 *src,s32 offset,u32 *out) {
    s32 off24=offset>>8;u32 hiByte,cmd;u32 *p=out;
    p[0]=0x0B000020;
    p[1]=osVirtualToPhysical((u32)(src+8));
    hiByte=src[0x2F]<<16;
    cmd=*(u16*)(src+2)|0x0E000000;
    p[2]=hiByte|cmd;
    {
        u32 *np=p+4;
        p[3]=(off24<<24)|(osVirtualToPhysical(*(u32*)(src+0x28))&0xFFFFFF);
        *(s32*)(src+0x2C)=0;
        return np;
    }
}
