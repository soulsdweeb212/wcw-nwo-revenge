/* @header
 * readWriteControllerPakInode  (originally func_8002286C)
 * VRAM 0x8002286C | ROM 0x2346C | size 0x338
 * asm: asm/nonmatchings/main/readWriteControllerPakInode.s
 */
#include "common.h"

typedef struct {u8 pad0[4];void *queue;s32 channel;u8 padC[0x48];s32 inode,mirror;u8 pad5C[4];s32 first;u8 banks,active;} Pak228;
extern s32 D_800375E0;extern u8 D_800375E4,D_8007DDB8[];
void func_80021C40(void*,void*,s32);s32 __osContRamRead(void*,s32,u16,void*);s32 __osContRamWrite(void*,s32,u16,void*,s32);s32 func_80025480(void*,u8);
static __inline__ s32 inodeSum(s32 start,u8 *base) {u32 sum;s32 j;u8 *ptr;s32 length;sum=0;ptr=(u8 *)(start*2+(u32)base);j=0;length=(128-start)*2;for(;j<length;j++)sum+=*ptr++;return sum;}

/* Reads or writes one 256-byte Controller Pak inode block for a bank, keeping a
 * cached copy at D_8007DDB8.  A read (rw&255 == 0) whose bank/channel match the
 * cache (D_800375E4 / D_800375E0) is served from cache.  A write first unlocks
 * the Pak (func_80025480) if needed, checksums the block (inodeSum) into inode[1],
 * and writes all eight 32-byte sectors to both the inode and mirror pages via
 * __osContRamWrite (write) or __osContRamRead (read).  On a read whose checksum
 * fails it re-reads from the mirror and, if that also fails, returns error 3; on
 * success it updates the cache and returns 0. */
s32 readWriteControllerPakInode(Pak228 *pak,u8 *inode,s32 rw,u8 bank) {
 s32 i,status,first;u8 *block;
 if(!(rw&255) && (bank&255)==D_800375E4 && pak->channel==D_800375E0) {func_80021C40(D_8007DDB8,inode,256);return 0;}
 if(pak->active) {status=func_80025480(pak,0);if(status)return status;}
 first=1;if(!(bank&255))first=pak->first;
 if((rw&255)==1) {inode[1]=inodeSum(first,inode);}
 i=0;
 do {
 block=inode+(i<<5);
 if((rw&255)==1) {
 __osContRamWrite(pak->queue,pak->channel,(pak->inode+(bank&255)*8+i)&65535,block,0);
 status=__osContRamWrite(pak->queue,pak->channel,(pak->mirror+(bank&255)*8+i)&65535,block,0);
 }else status=__osContRamRead(pak->queue,pak->channel,(pak->inode+(bank&255)*8+i)&65535,block);
 i++;
 if(status)return status;
 }while(i<8);
 if(!(rw&255)) {
 if((inodeSum(first,inode)&255)!=inode[1]) {
 s32 offset;
 i=0;offset=(bank&255)*8;block=inode;
 for(;i<8;i++,block+=32)__osContRamRead(pak->queue,pak->channel,(pak->mirror+offset+i)&65535,block);
 {s32 n=(128-first)*2;u32 sum=0;u8 *ptr=(u8 *)(first*2+(u32)inode);s32 j=0;for(;j<n;j++)sum+=*ptr++;if((sum&255)!=inode[1])return 3;}
 i=0;offset=(bank&255)*8;block=inode;
 for(;i<8;i++,block+=32)__osContRamWrite(pak->queue,pak->channel,(pak->inode+offset+i)&65535,block,0);
 }
 }
 D_800375E4=bank;func_80021C40(inode,D_8007DDB8,256);D_800375E0=pak->channel;return 0;
}
