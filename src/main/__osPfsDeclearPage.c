/* @header
 * __osPfsDeclearPage  (originally func_8002393C)
 * VRAM 0x8002393C | ROM 0x2453C | size 0x118
 * asm: asm/nonmatchings/main/__osPfsDeclearPage.s
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

#define ARRLEN(x) ((s32)(sizeof(x) / sizeof((x)[0])))

/* Claims a run of free (ipage==3) inode pages for a file of
 * file_size_in_pages pages, chaining them through the inode's bank/page fields
 * and terminating the chain (ipage 1). Sets *first_page, *decleared and
 * *last_page (the last page when the run hit the end of the table, else 0). */
s32 __osPfsDeclearPage(OSPfs *pfs, __OSInode *inode, int file_size_in_pages, int *first_page, u8 bank, int *decleared,
                  int *last_page) {
    int j;
    int spage;
    int old_page;
    s32 ret = 0;
    int offset = bank > 0 ? 1 : pfs->inode_start_page;

    for (j = offset; j < ARRLEN(inode->inode_page); j++) {
        if (inode->inode_page[j].ipage == 3) {
            break;
        }
    }

    if (j == ARRLEN(inode->inode_page)) {
        *first_page = -1;
        return ret;
    }

    spage = j;
    *decleared = 1;
    old_page = j;
    j++;

    while (file_size_in_pages > *decleared && j < ARRLEN(inode->inode_page)) {
        if (inode->inode_page[j].ipage == 3) {
            inode->inode_page[old_page].inode_t.bank = bank;
            inode->inode_page[old_page].inode_t.page = j;
            old_page = j;
            (*decleared)++;
        }
        j++;
    }

    *first_page = spage;

    if (j == ARRLEN(inode->inode_page) && file_size_in_pages > *decleared) {
        *last_page = old_page;
    } else {
        inode->inode_page[old_page].ipage = 1;
        *last_page = 0;
    }

    return ret;
}
