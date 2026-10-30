/* @header
 * countControllerPakPageReferences  (originally func_80024018)
 * VRAM 0x80024018 | ROM 0x24C18 | size 0x168
 * asm: asm/nonmatchings/main/func_80024018.s
 */
#include "common.h"

typedef union {struct {u8 bank,page;} inode_t; u16 ipage;} Nw2InodeUnit;
s32 readWriteControllerPakInode(void *,void *,s32,s32);
/* Counts how many inode entries reference `page` across the Controller Pak's
 * banks (up to 2, early-exiting at 2). Reads each bank's inode table once,
 * caching the loaded bank in inode[0x100]; a bank is visited only if it is the
 * page's own bank or its bitmap bit is set. Returns the count, 2 on saturation,
 * or a non-zero/non-3 read error. */
s32 countControllerPakPageReferences(u8 *p,Nw2InodeUnit page,u8 *inode) {
 s32 count=0; u8 bank=0; s32 first,i,result; s32 index; u32 b;
 index=(page.inode_t.page>>2)+((page.inode_t.bank&7)<<5);
 for(bank=0;bank<p[0x64];bank++) {
 b=bank;
 first=1; if(b==0) first=*(s32 *)(p+0x60);
 if(b==page.inode_t.bank || (((inode+index)[0x101]>>(b&7))&1)) {
 if(b!=inode[0x100]) {
 result=readWriteControllerPakInode(p,inode,0,b);
 if((result!=0)&(result!=3)) return result;
 inode[0x100]=bank;
 }
 for(i=first;(count<2)&(i<128);i++) count+=((u16 *)inode)[i]==page.ipage;
 if(count>=2) return 2;
 }
 }
 return count;
}
