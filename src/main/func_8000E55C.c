#include "common.h"

void func_8000337C(void *);
void func_800033C0(s16);
s16 func_800033F8(void);
void func_80003684(void *, s32, void *);
extern s16 D_80030D0C[];
extern s16 D_80036748;
extern u8 D_800487F0[];
/* Plays the indexed sound arg0 (0..21, forced to 0 when arg2 is clear) at a
 * duration of at least 2. Does nothing if it is already the current index;
 * otherwise, if the sound system is idle it loads the descriptor for
 * D_80030D0C[index] into the ring buffer and plays it, else it aborts the
 * current sound and sets the duration. */
void func_8000E55C(s32 arg0,s16 arg1,s8 arg2) {
 u8 buffer[24]; s16 index; s32 id; u16 sound; s16 duration=arg1;
 if((u16)arg0<22U) {
 if(!arg2) arg0=0;
 index=arg0;
 if(arg1<2) duration=2;
 if(index!=D_80036748) {
 if(func_800033F8()==0) {
 id=D_80030D0C[index];
 D_80036748=index;
 sound=id;
 if(id>0) {
 func_80003684(buffer,sound,D_800487F0);
 func_8000337C(D_800487F0);
 }
 } else {
 D_80036748=0;
 func_800033C0(duration);
 }
 }
 }
}
