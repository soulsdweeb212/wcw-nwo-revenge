/* @header
 * readRomSynchronousChunks  (originally func_8000061C)
 * VRAM 0x8000061C | ROM 0x121C | size 0xE4
 * asm: asm/nonmatchings/main/readRomSynchronousChunks.s
 */
#include "common.h"

void func_8001C5B0(s32, s32); void func_8001C890(void *, void *, s32); s32 func_8001C990(void *, void *, s32); s32 func_800219B0(s32, void *, s32);
extern s32 D_8003DD98; extern u8 D_8003DDA0[], D_8003DDA4[];

/* Synchronously read arg2 bytes from ROM at arg0 into arg1, in chunks of at most
 * 512 bytes, queueing each chunk through the DMA command block and waiting for
 * the queue to drain, with cache maintenance around the transfer. */
void readRomSynchronousChunks(s32 arg0, s32 arg1, s32 arg2) {
    s32 queue[6];
    s32 message;
    s32 received;
    func_8001C890(queue, &message, 1);
    func_8001C5B0(arg1, arg2);
    {
        s32 source = arg0;
        s32 dest = arg1;
        s32 left = arg2;
        while (left > 0) {
            s32 size = left;
            if (size > 512) size = 512;
            *(void **)D_8003DDA4 = queue;
            D_8003DDA4[-2] = 0;
            *(s32 *)(D_8003DDA4 + 8) = source;
            *(s32 *)(D_8003DDA4 + 4) = dest;
            *(s32 *)(D_8003DDA4 + 12) = size;
            while (func_800219B0(D_8003DD98, D_8003DDA0, 0)) {
            }
            func_8001C990(queue, &received, 1);
            source += size;
            left -= size;
            dest += size;
        }
    }
}
