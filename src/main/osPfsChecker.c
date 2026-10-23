#include "common.h"

/* libultra Controller Pak (PFS) consistency checker.
 * Reads every directory entry, walks each file's inode chain validating pages
 * (CHECK_IPAGE) and reference counts, zeroes corrupt directory entries (and
 * writes them back), then rewrites each bank's inode table keeping only the
 * reachable inodes. Sets PFS_CORRUPTED in pfs->status if anything was repaired;
 * returns 0 on success or the first PFS_* error encountered. */
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
    u32 game_code;
    u16 company_code;
    __OSInodeUnit start_page;
    u8 status;
    s8 reserved;
    u16 data_sum;
    u8 ext_name[4];
    u8 game_name[16];
} __OSDir;

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
#define PFS_ONE_PAGE 8
#define PFS_INODE_DIST_MAP 256
#define PFS_EOF 1
#define PFS_READ 0
#define PFS_WRITE 1
#define PFS_INITIALIZED 0x1
#define PFS_CORRUPTED 0x2
#define PFS_ERR_NEW_PACK 2
#define PFS_ERR_INCONSISTENT 3
#define PFS_ERR_INVALID 5
#define DIR_STATUS_EMPTY 0
#define FALSE 0

#define CHECK_IPAGE(p) \
    (((p).ipage >= pfs->inode_start_page) && ((p).inode_t.bank < pfs->banks) && \
     ((p).inode_t.page >= 0x01) && ((p).inode_t.page < 0x80))

s32 __osCheckId(void *);
s32 readControllerPakId(void *);
s32 corrupted_init(void *, __OSInodeCache *);
s32 countControllerPakPageReferences(void *, __OSInodeUnit, __OSInodeCache *);
s32 readWriteControllerPakInode(void *, __OSInode *, u8, u8);
s32 __osContRamRead(void *, int, u16, void *);
s32 __osContRamWrite(void *, int, u16, void *, int);
s32 func_80025480(void *, s32);
void func_80021F60(void *, s32);

s32 osPfsChecker(OSPfs *pfs) {
    int j;
    s32 ret;
    __OSInodeUnit next_page;
    __OSInode checked_inode;
    __OSInode tmp_inode;
    __OSDir tmp_dir;
    __OSInodeUnit file_next_node[16];
    __OSInodeCache cache;
    int fixed = 0;
    u8 bank;
    u8 oldbank = 254;
    s32 cc;
    s32 cl;
    int offset;

    ret = __osCheckId(pfs);

    if (ret == PFS_ERR_NEW_PACK) {
        ret = readControllerPakId(pfs);
    }

    if (ret != 0) {
        return ret;
    }

    ret = corrupted_init(pfs, &cache);
    if (ret != 0) {
        return ret;
    }

    for (j = 0; j < pfs->dir_size; j++) {
        ret = __osContRamRead(pfs->queue, pfs->channel, pfs->dir_table + j, (u8 *)&tmp_dir);
        if (ret != 0) {
            return ret;
        }

        if (tmp_dir.company_code != 0 || tmp_dir.game_code != 0) {
            if (tmp_dir.company_code == 0 || tmp_dir.game_code == 0) {
                cc = -1;
            } else {
                next_page = tmp_dir.start_page;
                cl = cc = 0;
                bank = 255;

                while (CHECK_IPAGE(next_page)) {
                    if (bank != next_page.inode_t.bank) {
                        bank = next_page.inode_t.bank;

                        if (oldbank != bank) {
                            ret = readWriteControllerPakInode(pfs, &tmp_inode, PFS_READ, bank);
                            oldbank = bank;
                        }

                        if (ret != 0 && ret != PFS_ERR_INCONSISTENT) {
                            return ret;
                        }
                    }

                    if ((cc = countControllerPakPageReferences(pfs, next_page, &cache) - cl) != 0) {
                        break;
                    }

                    cl = 1;
                    next_page = tmp_inode.inode_page[next_page.inode_t.page];
                }
            }

            if (cc != 0 || next_page.ipage != PFS_EOF) {
                func_80021F60(&tmp_dir, sizeof(__OSDir));

                if (pfs->activebank != 0) {
                    ret = func_80025480(pfs, 0);
                    if (ret != 0) {
                        return ret;
                    }
                }
                ret = __osContRamWrite(pfs->queue, pfs->channel, pfs->dir_table + j, (u8 *)&tmp_dir, FALSE);
                if (ret != 0) {
                    return ret;
                }
                fixed++;
            }
        }
    }
    for (j = 0; j < pfs->dir_size; j++) {
        ret = __osContRamRead(pfs->queue, pfs->channel, pfs->dir_table + j, (u8 *)&tmp_dir);
        if (ret != 0) {
            return ret;
        }

        if (tmp_dir.company_code != 0 && tmp_dir.game_code != 0 &&
            tmp_dir.start_page.ipage >= (u16)pfs->inode_start_page) {
            file_next_node[j].ipage = tmp_dir.start_page.ipage;
        } else {
            file_next_node[j].ipage = 0;
        }
    }

    for (bank = 0; bank < pfs->banks; bank++) {
        ret = readWriteControllerPakInode(pfs, &tmp_inode, PFS_READ, bank);

        if (ret != 0 && ret != PFS_ERR_INCONSISTENT) {
            return ret;
        }

        offset = (bank > 0) ? 1 : pfs->inode_start_page;

        for (j = 0; j < offset; j++) {
            checked_inode.inode_page[j].ipage = tmp_inode.inode_page[j].ipage;
        }

        for (; j < 128; j++) {
            checked_inode.inode_page[j].ipage = PFS_ERR_INCONSISTENT;
        }

        for (j = 0; j < pfs->dir_size; j++) {
            while (file_next_node[j].inode_t.bank == bank && file_next_node[j].ipage >= (u16)pfs->inode_start_page) {
                u8 pp = file_next_node[j].inode_t.page;
                file_next_node[j] = checked_inode.inode_page[pp] = tmp_inode.inode_page[pp];
            }
        }
        ret = readWriteControllerPakInode(pfs, &checked_inode, PFS_WRITE, bank);
        if (ret != 0) {
            return ret;
        }
    }

    if (fixed) {
        pfs->status |= PFS_CORRUPTED;
    } else {
        pfs->status &= ~PFS_CORRUPTED;
    }

    return 0;
}
