#include "common.h"

/* Read and validate a Controller Pak's ID block: read block 1, check the
 * checksum pair (sum/inverse) at id[14]/id[15], repair the block if needed,
 * then copy the serial and fill in the Pak225 geometry; finally read the label. */
typedef struct {u32 f0;void *queue;s32 channel;u8 id[32];u8 label[32];s32 banks; s32 inodeSize; s32 dirSize; s32 inodeStart; s32 minodeStart; s32 dataStart; volatile u8 bankCount;u8 activeBank;} Pak225;
s32 func_80025480(void *,s32);s32 __osContRamRead(void *,s32,s32,void *);s32 func_80022484(void *,void *);s32 func_80022198(void *,void *,void *);void func_80021C40(void *,void *,s32);
static __inline__ void checksum225(u16 *sum,u16 *inverse,u16 *it,u16 *end) {u16 v;*inverse=0;*sum=0;do {v=*it++;*sum+=v;*inverse+=~v;}while(it<end);}
s32 readControllerPakId(Pak225 *p) {
 u16 id[16];u16 repaired[16];u16 sum,inverse;u16 *idBlock;s32 ret;u8 bankCountTmp;
 if(p->activeBank) {ret=func_80025480(p,0);if(ret)return ret;}
 ret=__osContRamRead(p->queue,p->channel,1,id);if(ret)return ret;
 checksum225(&sum,&inverse,id,id+14);idBlock=id;
 if(id[14]!=sum || id[15]!=inverse) {
 ret=func_80022484(p,idBlock);
 if(ret==10) {ret=func_80022198(p,idBlock,repaired);if(ret)return ret;idBlock=repaired;}
 else if(ret)return ret;
 }
 if(!(idBlock[12]&1)) {
 ret=func_80022198(p,idBlock,repaired);if(ret)return ret;idBlock=repaired;
 if(!(repaired[12]&1))return 11;
 }
 func_80021C40(idBlock,p->id,32);
 p->banks=((u8 *)idBlock)[27];bankCountTmp=((u8 *)idBlock)[26];p->inodeSize=16;p->dirSize=8;p->bankCount=bankCountTmp;p->dataStart=bankCountTmp*2+3;
 p->inodeStart=(p->bankCount+1)*8;p->minodeStart=p->inodeStart+p->bankCount*8;
 ret=__osContRamRead(p->queue,p->channel,7,p->label);if(ret)return ret;return 0;
}
