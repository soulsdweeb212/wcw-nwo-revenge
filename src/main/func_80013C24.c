#include "common.h"

typedef struct { s32 f0,active; u8 p8[0xBE]; u16 kind; u8 pC8[0x90]; } VoiceC24;
extern u32 D_800604C8; extern VoiceC24 *D_800604D0;
/* Counts active voices: bit0 counts sounding voices (kind != 0), bit1 counts
 * free/idle ones (kind == 0). */
s32 func_80013C24(s32 flags) {
 u32 i=0;VoiceC24 *p=D_800604D0;s32 n=0;
 while(i<D_800604C8){
   if(p->active){
     if(p->kind){ if(flags&1) goto count; goto skip; }
     else { if(flags&2){ count: n++; } goto skip; }
   } else { goto skip; }
   skip: i++;
   p++;
 }
 return n;
}
