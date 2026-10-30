/* @header
 * freeResourceDescriptorArray  (originally func_800072E8)
 * VRAM 0x800072E8 | ROM 0x7EE8 | size 0x1BC
 * asm: asm/nonmatchings/main/func_800072E8.s
 */
#include "common.h"

/* Free an array of resource descriptors: for each 0x2C-byte entry release the
 * cached resource at +0x18 and any live sub-resources at +0xC/+0x10/+0x14
 * (skipping shared ones when the +0x28 ref flag is set) and +0x18/+0x1C, then
 * free the descriptor block itself. */
typedef struct Cache72 {struct Cache72 *next; void *data; u16 key, refs;} Cache72;
extern Cache72 *nw2ResourceCacheHead;
void releaseHeapBlock(void *);
#define F72(p,t,o) (*(t *)((u8 *)(p)+(o)))
static __inline__ void release72(void *data) {
Cache72 *node=nw2ResourceCacheHead,*prev=0;
while(node) {
if(node->data==data) break;
prev=node; node=node->next;
}
if(node && --node->refs==0) {
if(!prev) nw2ResourceCacheHead=node->next; else prev->next=node->next;
releaseHeapBlock(node->data);releaseHeapBlock(node);
}
}
void freeResourceDescriptorArray(void *base, void *allocation, s16 count) {
 void *desc,*entry,*res;
 if(count) {
 s32 countCopy=count;
 desc=base;
 loop:
 if(F72(desc,void*,0x18)) {
 release72(F72(desc,void*,0x18));
 F72(desc,void*,0x18)=0;
 }
 entry=desc;
 if(F72(entry,u8,0)) {
 res=F72(entry,void*,0xC); F72(entry,u8,0)=0;
 if(res) {if(!F72(entry,s32,0x28)) releaseHeapBlock(res); F72(entry,void*,0xC)=0;}
 res=F72(entry,void*,0x10);
 if(res) {if(!F72(entry,s32,0x28)) releaseHeapBlock(res); F72(entry,void*,0x10)=0;}
 res=F72(entry,void*,0x14);
 if(res) {if(!F72(entry,s32,0x28)) releaseHeapBlock(res); F72(entry,void*,0x14)=0;}
 res=F72(entry,void*,0x18);
 if(res) {releaseHeapBlock(res); F72(entry,void*,0x18)=0;}
 res=F72(entry,void*,0x1C);
 if(res) {releaseHeapBlock(res); F72(entry,void*,0x1C)=0;}
 }
 desc=(u8*)desc+0x2C;
 if((u32)desc<(u32)(countCopy*0x2C+(u32)base)) goto loop;
 }
 releaseHeapBlock(allocation);
}
