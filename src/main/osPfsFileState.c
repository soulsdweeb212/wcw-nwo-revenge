#include "common.h"

/* Reads a Controller Pak file's directory entry and walks its inode chain to
 * count used pages, filling in the caller's OSPfsState (file size, game/company
 * codes and names). Returns 0 on success, PFS_EOF/PFS_ERR_* codes otherwise. */
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

typedef struct {
    u32 file_size;
    u32 game_code;
    u16 company_code;
    char ext_name[4];
    char game_name[16];
} OSPfsState;

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

#define PFS_ERR_INVALID 5
#define PFS_ERR_INCONSISTENT 3
#define PFS_EOF 1
#define PFS_INITIALIZED 0x1
#define PFS_READ 0
#define PFS_ONE_PAGE 8
#define BLOCKSIZE 32

s32 __osCheckId(void *);
s32 func_80025480(void *, u8);
s32 __osContRamRead(void *, int, u16, void *);
s32 readWriteControllerPakInode(void *, __OSInode *, u8, u8);
void func_80021C40(void *, void *, s32);

s32 osPfsFileState(OSPfs *pfs, s32 file_no, OSPfsState *state) {
    s32 ret;
    int pages;
    __OSInode inode;
    __OSDir dir;
    __OSInodeUnit next_page;
    u8 bank;

    if (file_no >= pfs->dir_size || file_no < 0) {
        return PFS_ERR_INVALID;
    }
    if ((pfs->status & PFS_INITIALIZED) == 0) {
        return PFS_ERR_INVALID;
    }
    ret = __osCheckId(pfs);
    if (ret != 0) {
        return ret;
    }
    if (pfs->activebank != 0) {
        ret = func_80025480(pfs, 0);
        if (ret != 0) {
            return ret;
        }
    }
    ret = __osContRamRead(pfs->queue, pfs->channel, pfs->dir_table + file_no, (u8 *)&dir);
    if (ret != 0) {
        return ret;
    }
    if (dir.company_code == 0 || dir.game_code == 0) {
        return PFS_ERR_INVALID;
    }
    pages = 0;
    next_page = dir.start_page;
    bank = 0xFF;
    while (1) {
        if (next_page.ipage < pfs->inode_start_page) {
            break;
        } else if (next_page.inode_t.bank != bank) {
            bank = next_page.inode_t.bank;
            ret = readWriteControllerPakInode(pfs, &inode, PFS_READ, bank);
            if (ret != 0) {
                return ret;
            }
        }
        pages++;
        next_page = inode.inode_page[next_page.inode_t.page];
    }
    if (next_page.ipage != PFS_EOF) {
        return PFS_ERR_INCONSISTENT;
    }
    state->file_size = pages * (PFS_ONE_PAGE * BLOCKSIZE);
    state->company_code = dir.company_code;
    state->game_code = dir.game_code;
    func_80021C40(dir.game_name, state->game_name, 16);
    func_80021C40(dir.ext_name, state->ext_name, 4);
    return 0;
}
