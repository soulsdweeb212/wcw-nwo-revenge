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

#define ARRLEN(x) ((s32)(sizeof(x) / sizeof((x)[0])))
#define BLOCKSIZE 32
#define PFS_ONE_PAGE 8
#define PFS_FILE_NAME_LEN 16
#define PFS_FILE_EXT_LEN 4
#define PFS_READ 0
#define PFS_WRITE 1
#define PFS_ERR_INVALID 5
#define PFS_ERR_EXIST 9
#define PFS_DATA_FULL 7
#define PFS_DIR_FULL 8
#define PFS_ERR_INCONSISTENT 3
#define FALSE 0
#define ROUND_UP_DIVIDE(numerator, denominator) (((numerator) + (denominator) - 1) / (denominator))

s32 findControllerPakFile(void *, u16, u32, u8 *, u8 *, s32 *);
s32 getControllerPakFreeBytes(void *, s32 *);
s32 readWriteControllerPakInode(void *, __OSInode *, u8, u8);
s32 __osPfsDeclearPage(void *, __OSInode *, int, int *, u8, int *, int *);
s32 __osContRamWrite(void *, int, u16, void *, int);
void func_80021C40(void *, void *, s32);

/* Allocates a new file on the Controller Pak: validates the company/game codes,
 * rounds the requested byte size up to 8-page (256-byte) blocks, finds a free
 * directory entry and enough free pages by walking the Pak's banks, links the
 * allocated pages into an inode chain (writing each bank's inode table and the
 * previous bank's tail page), builds the __OSDir entry with the game/ext name and
 * writes it to the directory table.  Returns 0 on success or the first error. */
s32 osPfsAllocateFile(OSPfs *pfs, u16 company_code, u32 game_code, u8 *game_name, u8 *ext_name, int file_size_in_bytes,
                  s32 *file_no) {
    int start_page;
    int decleared;
    int last_page;
    int old_last_page = 0;
    s32 ret = 0;
    int file_size_in_pages;
    __OSInode inode;
    __OSInode backup_inode;
    __OSDir dir;
    u8 bank;
    u8 old_bank = 0;
    int firsttime = 0;
    s32 bytes;
    __OSInodeUnit fpage;

    if (company_code == 0 || game_code == 0) {
        return PFS_ERR_INVALID;
    }

    file_size_in_pages = ROUND_UP_DIVIDE(file_size_in_bytes, BLOCKSIZE * PFS_ONE_PAGE);

    if (((ret = findControllerPakFile(pfs, company_code, game_code, game_name, ext_name, file_no)) != 0) &&
        ret != PFS_ERR_INVALID) {
        return ret;
    }

    if (*file_no != -1) {
        return PFS_ERR_EXIST;
    }

    ret = getControllerPakFreeBytes(pfs, &bytes);

    if (file_size_in_bytes > bytes) {
        return PFS_DATA_FULL;
    }

    if (file_size_in_pages == 0) {
        return PFS_ERR_INVALID;
    }

    if (((ret = findControllerPakFile(pfs, 0, 0, NULL, NULL, file_no)) != 0) && ret != PFS_ERR_INVALID) {
        return ret;
    }

    if (*file_no == -1) {
        return PFS_DIR_FULL;
    }

    for (bank = 0; bank < pfs->banks; bank++) {
        ret = readWriteControllerPakInode(pfs, &inode, PFS_READ, bank);
        if (ret != 0) {
            return ret;
        }
        ret = __osPfsDeclearPage(pfs, &inode, file_size_in_pages, &start_page, bank, &decleared, &last_page);
        if (ret != 0) {
            return ret;
        }

        if (start_page != -1) {
            if (firsttime == 0) {
                fpage.inode_t.page = start_page;
                fpage.inode_t.bank = bank;
            } else {
                backup_inode.inode_page[old_last_page].inode_t.bank = bank;
                backup_inode.inode_page[old_last_page].inode_t.page = start_page;
                ret = readWriteControllerPakInode(pfs, &backup_inode, PFS_WRITE, old_bank);
                if (ret != 0) {
                    return ret;
                }
            }

            if (file_size_in_pages > decleared) {
                func_80021C40(&inode, &backup_inode, sizeof(__OSInode));
                old_last_page = last_page;
                old_bank = bank;
                file_size_in_pages -= decleared;
                firsttime++;
            } else {
                file_size_in_pages = 0;
                ret = readWriteControllerPakInode(pfs, &inode, PFS_WRITE, bank);
                if (ret != 0) {
                    return ret;
                }
                break;
            }
        }
    }

    if (file_size_in_pages > 0 || start_page == -1) {
        return PFS_ERR_INCONSISTENT;
    }

    dir.start_page = fpage;
    dir.company_code = company_code;
    dir.game_code = game_code;
    dir.data_sum = 0;

    func_80021C40(game_name, dir.game_name, PFS_FILE_NAME_LEN);
    func_80021C40(ext_name, dir.ext_name, PFS_FILE_EXT_LEN);

    ret = __osContRamWrite(pfs->queue, pfs->channel, pfs->dir_table + *file_no, (u8 *)&dir, FALSE);
    return ret;
}
