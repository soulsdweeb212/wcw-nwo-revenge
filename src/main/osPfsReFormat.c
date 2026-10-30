/* @header
 * osPfsReFormat  (originally func_80024F80)
 * VRAM 0x80024F80 | ROM 0x25B80 | size 0x2FC
 * asm: asm/nonmatchings/main/func_80024F80.s
 */
#include "common.h"

/* Reformat a Controller Pak: clear the directory pages, rewrite the inode tables
 * (inode page 0 holds the checksum, the rest point at free block 3) for every bank,
 * and re-initialise the driver state. Returns 0 or a PFS error code. */
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

#define ARRLEN(x) ((s32)(sizeof(x) / sizeof(x[0])))
#define BLOCKSIZE 32
#define PFS_ONE_PAGE 8
#define DEF_DIR_PAGES 2
#define PFS_INITIALIZED 1
#define FALSE 0

void func_80027744(void);
void func_800277B0(void);
s32 func_80024640(void *, int);
s32 readControllerPakId(void *);
s32 func_80025480(void *, s32);
s32 __osContRamWrite(void *, int, u16, u8 *, s32);
u16 func_80022120(u8 *, s32);

s32 osPfsReFormat(OSPfs *pfs, void *queue, int channel) {
    int j;
    int i;
    __OSInode inode;
    u8 tmp_data[32];
    u8 *ptr;
    s32 ret;

    func_80027744();
    ret = func_80024640(queue, channel);
    if (ret != 0) {
        func_800277B0();
        return ret;
    }
    pfs->status ^= PFS_INITIALIZED;
    pfs->queue = queue;
    pfs->channel = channel;
    func_800277B0();
    ret = readControllerPakId(pfs);
    if (ret != 0) {
        return ret;
    }
    if (pfs->activebank != 0) {
        ret = func_80025480(pfs, 0);
        if (ret != 0) {
            return ret;
        }
    }
    for (j = 0; j < ARRLEN(tmp_data); j++) {
        tmp_data[j] = 0;
    }
    for (j = 0; j < pfs->dir_size; j++) {
        ret = __osContRamWrite(queue, channel, pfs->dir_table + j, tmp_data, FALSE);
        if (ret != 0) {
            return ret;
        }
    }
    for (j = 0; j < pfs->inode_start_page; j++) {
        inode.inode_page[j].ipage = 0;
    }
    for (j = pfs->inode_start_page; j < ARRLEN(inode.inode_page); j++) {
        inode.inode_page[j].ipage = 3;
    }
    inode.inode_page[0].ipage = func_80022120((u8 *)(inode.inode_page + pfs->inode_start_page),
                                              (ARRLEN(inode.inode_page) - pfs->inode_start_page) * sizeof(__OSInodeUnit));
    ptr = (u8 *)&inode;
    for (j = 0; j < PFS_ONE_PAGE; j++) {
        ret = __osContRamWrite(queue, channel, pfs->inode_table + j, ptr + j * BLOCKSIZE, FALSE);
        if (ret != 0) {
            return ret;
        }
        ret = __osContRamWrite(queue, channel, pfs->minode_table + j, ptr + j * BLOCKSIZE, FALSE);
        if (ret != 0) {
            return ret;
        }
    }
    for (i = 1; i < pfs->banks; i++) {
        for (j = 1; j < ARRLEN(inode.inode_page); j++) {
            inode.inode_page[j].ipage = 3;
        }
        inode.inode_page[0].ipage = func_80022120((u8 *)(inode.inode_page + 1),
                                                  (ARRLEN(inode.inode_page) - 1) * sizeof(__OSInodeUnit));
        ptr = (u8 *)&inode;
        for (j = 0; j < PFS_ONE_PAGE; j++) {
            ret = __osContRamWrite(queue, channel, pfs->inode_table + i * PFS_ONE_PAGE + j, ptr + j * BLOCKSIZE, FALSE);
            if (ret != 0) {
                return ret;
            }
            ret = __osContRamWrite(queue, channel, pfs->minode_table + i * PFS_ONE_PAGE + j, ptr + j * BLOCKSIZE, FALSE);
            if (ret != 0) {
                return ret;
            }
        }
    }
    return 0;
}
