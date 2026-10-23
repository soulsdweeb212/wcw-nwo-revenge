#include "common.h"

extern Nw2ResourceEntryHashed *D_8007FC34;
extern u8 *D_8007FC3C;
s32 releaseHeapBlock(void *);
static __inline__ void checksumA6BC(Nw2ResourceEntryHashed *q) {
 u8 *p=(u8*)q->key;
 q->hash.h.length=0;q->hash.h.sum=0;
 if(!((u32)p&0x40000000)) {
 while(*p) {q->hash.h.sum+=*p++<<(q->hash.h.length&7);q->hash.h.length++;}
 }
}
/* Looks up a cached resource by key+variant+string checksum in the 128-entry
 * table, or claims the first free entry. When found, invalidates a keyed-buffer
 * slot if the key points into the pool, frees the allocation and marks the
 * entry unused. Returns the free result (0 if no entry was found). */
s32 freeCachedResource(u8 *key,s32 arg1) {
 Nw2ResourceEntryHashed probe;
 Nw2ResourceEntryHashed *entry,*found;
 u32 variant=arg1&0xFFFF;
 s32 i;
 u32 value;
 s32 result;
 probe.key=(u32)key;checksumA6BC(&probe);
 entry=D_8007FC34;
 for(i=0;i<128;i++,entry++) {
 if(entry->key==(u32)key && entry->variant==variant && entry->hash.word==probe.hash.word) {found=entry;goto got;}
 }
 i=0;
 entry=D_8007FC34;
 for(;i<128;i++,entry++) {
 if(!entry->key) {entry->hash.h.length=probe.hash.h.length;found=entry;found->hash.h.sum=probe.hash.h.sum;goto got;}
 }
 found=0;
 got:
 if(!found)return 0;
 value=found->key;
 if(value) {
 if(value>=(u32)D_8007FC3C && value<(u32)(D_8007FC3C+0xB40)) {*(u32*)(value+0x40)=0;*(u32*)(value+0x44)=0;*(u8*)value=0;}
 result=releaseHeapBlock(found->allocation);
 found->key=0;
 return result;
 }
 return 0;
}
