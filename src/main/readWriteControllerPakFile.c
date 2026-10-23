#include "common.h"

/* libultra PFS file read/write.
 * Reads (flag==0) or writes (flag==1) 'size' bytes at 'offset' in file index
 * 'file' of the Controller Pak pfs into/from 'data'. Validates the file index,
 * size/offset alignment (32 bytes), the pak state and the directory entry,
 * walks the file's inode chain eight pages per inode (next24), reads/writes
 * each 32-byte page through the queue (__osContRamRead) or __osContRamWrite, and
 * marks the directory entry initialized on a successful write. Returns 0 or a
 * PFS_* error code. */
typedef struct { s32 flags, queue, channel; u8 padC[0x44]; s32 dirsize; s32 pad54,pad58; s32 dirbase; s32 first; u8 banks,active; } Pak24;
typedef struct { u32 game; u16 company; Nw2PakInodeUnit start; u8 status; u8 rest[23]; } Dir24;
s32 __osCheckId(void *); s32 func_80025480(void *,s32); s32 __osContRamRead(s32,s32,u16,void *); s32 __osContRamWrite(s32,s32,u16,void *,s32); s32 readWriteControllerPakInode(void *,u16 *,s32,s32);
#define BADPAGE24(n) (((n).inode_t.page == 0) | ((n).inode_t.page >= 128))
#define VALID24(p,n) ((n).ipage >= (p)->first && (n).inode_t.bank < (p)->banks && !BADPAGE24(n))
/* Load the next inode page: read the inode table for the page's bank if it
 * changed, then follow the inode chain entry. Returns 0, or 5/3 on a bad page. */
static __inline__ s32 next24(Pak24 *p,u8 *bank,Nw2PakInodeUnit *page,u16 *inode) { s32 ret; s32 bad; if(page->inode_t.bank != *bank) { *bank=page->inode_t.bank; ret=readWriteControllerPakInode(p,inode,0,page->inode_t.bank); if(ret) return ret; } page->ipage=inode[page->inode_t.page]; if(page->ipage < p->first) goto inv; if(page->inode_t.bank >= p->banks) goto inv; bad = (page->inode_t.page == 0) | (page->inode_t.page >= 128); if(bad){ inv: if(page->ipage==1) return 5; return 3; } return 0; }
s32 readWriteControllerPakFile(Pak24 *p,s32 file,u8 flag,s32 offset,s32 size,u8 *data) {
 Dir24 dir; u16 inode[128]; u8 bank; Nw2PakInodeUnit page;
 s32 ret; s32 block; s32 count; u8 *ptr;
 if (file>=p->dirsize || file<0) return 5;
 if(size<=0) return 5;
 if(size&31) return 5; if(offset<0) return 5; if(offset&31) return 5; if(!(p->flags&1)) return 5;
 if(__osCheckId(p)==2) return 2;
 if(p->active) { ret=func_80025480(p,0); if(ret) return ret; }
 ret=__osContRamRead(p->queue,p->channel,p->dirbase+file,&dir); if(ret) return ret;
 if(!dir.company || !dir.game) return 5;
 if(!VALID24(p,dir.start)) { if(dir.start.ipage==1) return 5; return 3; }
 if(!flag && !(dir.status&2)) return 6;
 bank=255; block=offset/32; page=dir.start;
 while(block>=8) { ret=next24(p,&bank,&page,inode); block-=8; if(ret) return ret; }
 count=size/32; ptr=data;
 while(count>0) {
 if(block==8) { ret=next24(p,&bank,&page,inode); block=0; if(ret) return ret; }
 if(p->active!=page.inode_t.bank) { ret=func_80025480(p,page.inode_t.bank); if(ret) return ret; }
 { u16 addr=page.inode_t.page*8+block; if(!flag) ret=__osContRamRead(p->queue,p->channel,addr,ptr); else ret=__osContRamWrite(p->queue,p->channel,addr,ptr,0); }
 ptr+=32; if(ret) return ret; count--; block++;
 }
 if(flag==1 && !(dir.status&2)) { dir.status|=2; if(p->active) { ret=func_80025480(p,0); if(ret) return ret; } ret=__osContRamWrite(p->queue,p->channel,p->dirbase+file,&dir,0); if(ret) return ret; }
 return 0;
}
