/* @header
 * n_alAuxBusPull  (originally func_800180A0)
 * VRAM 0x800180A0 | ROM 0x18CA0 | size 0xA0
 * asm: asm/nonmatchings/main/n_alAuxBusPull.s
 */
/* SDK: n_audio, libnaudio/src/n_auxbus.c (same code as the SDK source). */
#include "common.h"

typedef struct {u32 w0,w1;} Cmd180;
typedef struct {u8 pad[0x14];s32 count;u32 pad18;void **children;} Mix180;
typedef struct {u8 pad[0x34];Mix180 *mix;} Audio180;
extern Audio180 *n_syn;
Cmd180 *n_alEnvmixerPull(void *,s32,Cmd180 *);
/* Emits the mixer header command (0x020007C0 / 0x2E0) followed by each child's
 * commands for the given time, returning the advanced cursor. */
Cmd180 *n_alAuxBusPull(s32 time,Cmd180 *out){Mix180 *mix=n_syn->mix;void **start=mix->children;void **child;s32 i;{Cmd180 *q=out++;q->w0=0x020007C0;q->w1=0x2e0;}for(i=0;i<mix->count;i++){out=n_alEnvmixerPull(start[i],time,out);}return out;}
