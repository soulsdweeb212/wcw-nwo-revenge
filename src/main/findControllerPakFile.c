#include "common.h"

typedef struct { s32 flags,queue,channel; u8 padC[0x44]; s32 directorySize; u8 pad54[8]; s32 directoryBase; } FindPfs;
typedef struct { u32 game; u16 company; u8 pad6[6]; u8 extension[4]; u8 name[16]; } FindDirectory;
s32 __osCheckId(void*);
s32 __osContRamRead(s32,s32,u16,void*);

/* libultra osPfsFindFile: scan the Controller Pak directory for the entry whose
 * company/game code (and, if given, name/extension) match `company`/`game`/`name`/
 * `extension`. On success stores the entry index in *fileNo; returns 0 on a hit,
 * 5 if the pak is absent or the file was not found, otherwise an I/O error code. */
s32 findControllerPakFile(FindPfs *pfs,u16 company,u32 game,u8 *name,u8 *extension,s32 *fileNo) {
 FindDirectory dirEntry;
 s32 index,k,mismatch,result;
 if(!(pfs->flags&1)) return 5;
 result=__osCheckId(pfs);
 if(result) return result;
 for(index=0;index<pfs->directorySize;index++) {
  result=__osContRamRead(pfs->queue,pfs->channel,pfs->directoryBase+index,&dirEntry);
  if(result) return result;
  if(dirEntry.company==company && dirEntry.game==game) {
   mismatch=0;
   if(name) { for(k=0;k<16;k++) {if(dirEntry.name[k]!=name[k]) {mismatch=1;break;}} }
   if((extension!=NULL)&(mismatch==0)) {for(k=0;k<4;k++) {if(dirEntry.extension[k]!=extension[k]) {mismatch=1;break;}}}
   if(!mismatch) {*fileNo=index;return result;}
  }
 }
 *fileNo=-1;
 return 5;
}
