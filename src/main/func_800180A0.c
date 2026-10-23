#include "common.h"

typedef struct {u32 w0,w1;} Cmd180;
typedef struct {u8 pad[0x14];s32 count;u32 pad18;void **children;} Mix180;
typedef struct {u8 pad[0x34];Mix180 *mix;} Audio180;
extern Audio180 *D_80036F54;
Cmd180 *func_80018660(void *,s32,Cmd180 *);
/* Emits the mixer header command (0x020007C0 / 0x2E0) followed by each child's
 * commands for the given time, returning the advanced cursor. */
Cmd180 *func_800180A0(s32 time,Cmd180 *out){Mix180 *mix=D_80036F54->mix;void **start=mix->children;void **child;s32 i;{Cmd180 *q=out++;q->w0=0x020007C0;q->w1=0x2e0;}for(i=0;i<mix->count;i++){out=func_80018660(start[i],time,out);}return out;}
