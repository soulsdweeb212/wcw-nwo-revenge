/* @header
 * func_80024850
 * VRAM 0x80024850 | ROM 0x25450 | size 0x1E8
 * asm: asm/nonmatchings/main/func_80024850.s
 */
#include "common.h"

/* Controller Pak init: reset the channel, read and checksum the ID block,
 * repair it if the CRC is bad, then fill in the Pak248 geometry (bank counts
 * and inode/dir/data start offsets) and read the label. */
typedef struct {u32 f0;void *queue;s32 channel;u8 id[32];u8 label[32];s32 banks; s32 inodeSize; s32 dirSize; s32 inodeStart; s32 minodeStart; s32 dataStart; volatile u8 bankCount;u8 activeBank;} Pak248;

s32 func_80025480(void *,s32);
s32 __osContRamRead(void *,s32,s32,void *);
s32 func_80022484(void *,void *);
s32 func_80022198(void *,void *,void *);
void func_80021C40(void *,void *,s32);
void func_80027744(void);
void func_800277B0(void);
s32 func_80024640(void *,s32);
void func_80022154(u16 *,u16 *,u16 *);
s32 osPfsChecker(void *);

s32 func_80024850(void *queue, Pak248 *p, s32 channel) {
    u16 id[16];
    u16 repaired[16];
    u16 sum, inverse;
    u16 *cur;
    s32 ret;
    u8 banks;

    func_80027744();
    ret = func_80024640(queue, channel);
    func_800277B0();
    if (ret) return ret;

    p->queue = queue;
    p->channel = channel;
    p->f0 = 0;
    ret = func_80025480(p, 0);
    if (ret) return ret;

    ret = __osContRamRead(p->queue, p->channel, 1, id);
    if (ret) return ret;

    func_80022154(id, &sum, &inverse);
    cur = id;
    if (id[14] != sum || id[15] != inverse) {
        ret = func_80022484(p, cur);
        if (ret) {
            p->f0 |= 4;
            return ret;
        }
    }
    if (!(cur[12] & 1)) {
        ret = func_80022198(p, cur, repaired);
        if (ret) {
            if (ret == 10) {
                p->f0 |= 4;
            }
            return ret;
        }
        cur = repaired;
        if (!(repaired[12] & 1)) return 11;
    }
    func_80021C40(cur, p->id, 32);
    p->banks = ((u8 *)cur)[27];
    banks = ((u8 *)cur)[26];
    p->inodeSize = 16;
    p->dirSize = 8;
    p->bankCount = banks;
    p->dataStart = banks * 2 + 3;
    p->inodeStart = (p->bankCount + 1) * 8;
    p->minodeStart = p->inodeStart + p->bankCount * 8;
    ret = __osContRamRead(p->queue, p->channel, 7, p->label);
    if (ret) return ret;
    ret = osPfsChecker(p);
    p->f0 |= 1;
    return ret;
}
