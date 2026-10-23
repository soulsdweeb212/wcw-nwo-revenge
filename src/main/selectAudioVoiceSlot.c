#include "common.h"

typedef struct {s32 f0,active;u8 pad8[0x5C];s32 priority;u8 pad68[0x2C];void *owner;u8 pad98[4];s32 sample;u8 padA0[0x26];u16 kind;u8 padC8[0x90];} Voice15;
typedef struct {s32 f0;s32 *samples;} Owner15;
extern u32 D_800604C8;
extern Voice15 *D_800604D0;
/* Picks a voice slot for `owner` playing owner->samples[index], in order of
 * preference: first idle voice; else the lowest-priority sounding voice; else a
 * free (kind==0) voice owned by someone else; else the owner's own voice already
 * playing that sample; finally wraps to index % voiceCount. */
s32 selectAudioVoiceSlot(Owner15 *owner,s32 index) {
 u32 i;
 Voice15 *p;
 s32 best,bestPriority;
 p=D_800604D0;
 for(i=0;i<D_800604C8;i++,p++) if(!p->active) return i;
 p=D_800604D0;
 bestPriority=0x7FFFFFFF;best=-1;
 for(i=0;i<D_800604C8;i++,p++) {
  if(p->kind && p->priority<=bestPriority) {bestPriority=p->priority;best=i;}
 }
 if(best!=-1)return best;
 p=D_800604D0;
 for(i=0;i<D_800604C8;i++) if(!p->kind && p->owner!=owner) return i;
 p=D_800604D0;
 for(i=0;i<D_800604C8;i++,p++) if(p->owner==owner && owner->samples[index]==p->sample)return i;
 return index%(s32)D_800604C8;
}
