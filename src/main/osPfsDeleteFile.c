/* @header
 * osPfsDeleteFile  (originally func_80024180)
 * VRAM 0x80024180 | ROM 0x24D80 | size 0x1AC
 * asm: asm/nonmatchings/main/osPfsDeleteFile.s
 */
/* SDK: libultra 2.0I, ultralib src/io/pfsdeletefile.c (same code as the SDK source). */
#include "common.h"

/* Delete a Controller Pak file: look up its directory entry, reload the bank,
 * then walk and release each inode page in the chain; when the chain is
 * exhausted, zero the directory entry and write it back. Returns 3 (not found
 * in a valid bank), 5 (bad arguments) or the underlying error code. */
typedef struct {s32 flags,queue,channel;u8 padC[0x50];s32 directoryBase;u8 pad60[4];u8 banks,active;} DeletePfs;
s32 osPfsFindFile(void *,u16,u32,u8 *,u8 *,s32 *);
s32 __osPfsSelectBank(void *,s32);
s32 __osContRamRead(s32,s32,u16,void *);
s32 __osContRamWrite(s32,s32,u16,void *,s32);
s32 __osPfsRWInode(void *,void *,s32,u32);
s32 __osPfsReleasePages(void *,void *,u8,u32,void *);
void bzero(void *,s32);
s32 osPfsDeleteFile(DeletePfs *p,u16 company,u32 game,u8 *name,u8 *ext) {
    u16 inode[128];
    u8 dir[32];
    s32 fileIndex;
    Nw2PakInodeUnit next;
    s32 ret;
    u8 bankNo,pageNo;
    u32 inodeBank;
    if((company==0)|(game==0)) return 5;
    ret=osPfsFindFile(p,company,game,name,ext,&fileIndex); if(ret) return ret;
    if(p->active) {ret=__osPfsSelectBank(p,0);if(ret)return ret;}
    ret=__osContRamRead(p->queue,p->channel,p->directoryBase+fileIndex,dir);if(ret)return ret;
    bankNo=dir[6];pageNo=dir[7];inodeBank=bankNo&255;
    if(inodeBank<p->banks) {
        do {
            ret=__osPfsRWInode(p,inode,0,inodeBank);if(ret)return ret;
            ret=__osPfsReleasePages(p,inode,pageNo,inodeBank,&next);if(ret)return ret;
            ret=__osPfsRWInode(p,inode,1,inodeBank);if(ret)return ret;
            if(next.ipage==1)break;
            bankNo=next.inode_t.bank;pageNo=next.inode_t.page;inodeBank=bankNo&255;
        }while(inodeBank<p->banks);
        if(bankNo<p->banks) {
            bzero(dir,32);
            return __osContRamWrite(p->queue,p->channel,p->directoryBase+fileIndex,dir,0);
        }
    }
    return 3;
}
