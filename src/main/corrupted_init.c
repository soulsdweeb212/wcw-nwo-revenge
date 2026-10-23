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

typedef struct {
    __OSInode inode;
    u8 bank;
    u8 map[256];
} __OSInodeCache;

#define ARRLEN(x) ((s32)(sizeof(x) / sizeof((x)[0])))
#define BLOCKSIZE 32
#define PFS_SECTOR_SIZE 4
#define PFS_BANK_LAPPED_BY 8
#define PFS_INODE_DIST_MAP 256
#define PFS_READ 0
#define PFS_ERR_INCONSISTENT 3

s32 readWriteControllerPakInode(void *, __OSInode *, u8, u8);

s32 corrupted_init(OSPfs *pfs, __OSInodeCache *cache) {
    int i;
    int n;
    int offset;
    u8 bank;
    __OSInodeUnit tpage;
    __OSInode tmp_inode;
    s32 ret;

    for (i = 0; i < PFS_INODE_DIST_MAP; i++) {
        cache->map[i] = 0;
    }

    cache->bank = -1;
    for (bank = 0; bank < pfs->banks; bank++) {
        offset = bank > 0 ? 1 : pfs->inode_start_page;

        ret = readWriteControllerPakInode(pfs, &tmp_inode, PFS_READ, bank);

        if (ret != 0 && ret != PFS_ERR_INCONSISTENT) {
            return ret;
        }

        for (i = offset; i < ARRLEN(tmp_inode.inode_page); i++) {
            tpage = tmp_inode.inode_page[i];

            if (tpage.ipage >= pfs->inode_start_page && tpage.inode_t.bank != bank) {
                n = ((tpage.inode_t.page) / PFS_SECTOR_SIZE) +
                    ((tpage.inode_t.bank % PFS_BANK_LAPPED_BY) * BLOCKSIZE);
                cache->map[n] |= 1 << (bank % PFS_BANK_LAPPED_BY);
            }
        }
    }
    return 0;
}
