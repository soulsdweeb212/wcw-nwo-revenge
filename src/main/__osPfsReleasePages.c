/* @header
 * __osPfsReleasePages  (originally func_8002432C)
 * VRAM 0x8002432C | ROM 0x24F2C | size 0x68
 * asm: asm/nonmatchings/main/func_8002432C.s
 */
#include "common.h"

typedef struct {
    int status;
    void *queue;
    int channel;
    u8 id[32];
    u8 label[32];
    int version;
    int dir_size;
    int inode_table;
    int minode_table;
    int dir_table;
    int inode_start_page;
    u8 banks;
    u8 activebank;
} OSPfs;

typedef union {
    struct { u8 bank; u8 page; } inode_t;
    u16 ipage;
} __OSInodeUnit;

typedef struct {
    __OSInodeUnit inode_page[128];
} __OSInode;

#define PFS_PAGE_NOT_USED 3

/* Release a file's inode page chain: starting from (bank, start_page), mark each
 * page unused and follow it to the next, until a page leaves the bank or falls
 * below inode_start_page. That terminating page is reported through last_page. */
s32 __osPfsReleasePages(OSPfs *pfs, __OSInode *inode, u8 start_page, u8 bank, __OSInodeUnit *last_page) {
    __OSInodeUnit next_page;
    __OSInodeUnit old_page;
    s32 ret = 0;

    next_page.ipage = (bank << 8) + start_page;

    do {
        old_page = next_page;
        next_page = inode->inode_page[next_page.inode_t.page];
        inode->inode_page[old_page.inode_t.page].ipage = PFS_PAGE_NOT_USED;
    } while (next_page.ipage >= pfs->inode_start_page && next_page.inode_t.bank == bank);

    *last_page = next_page;

    return ret;
}
