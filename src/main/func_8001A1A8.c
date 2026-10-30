/* @header
 * func_8001A1A8
 * VRAM 0x8001A1A8 | ROM 0x1ADA8 | size 0x118
 * asm: asm/nonmatchings/main/func_8001A1A8.s
 */
#include "common.h"

typedef struct {
    u32 pad[5];
    u32 start;      /* @0x14: DRAM address of the buffer start */
    u32 pad18;
    s32 length;     /* @0x1C: buffer length in samples (bytes = length * 2) */
} AudioBuffer;

typedef struct {
    u32 w0, w1;
} AudioCommand;

u32 func_8001CE80(u32);

/* Append the audio-save command(s) (opcode 0x06000000) that write a fixed count
 * from addr out of buf, starting at segment. If the range wraps past the buffer
 * end, emit two 0x06000000 commands split at the buffer end; otherwise emit one
 * 0x06170000 command. Returns the advanced command pointer. */
AudioCommand *func_8001A1A8(AudioBuffer *buf, u32 addr, s32 segment, AudioCommand *cmdOut) {
    s32 first;
    s32 second;
    u32 end;
    u32 limit;
    AudioCommand *cmd, *cmd2;
    end = buf->start + buf->length * 2;
    cmd = cmdOut;
    if (addr < buf->start) addr += buf->length * 2;
    limit = addr + 0x170;
    if (end < limit) {
        cmdOut++;
        first = ((s32)(end - addr) >> 1) * 2;
        cmd->w0 = 0x06000000 | (((u32)first & 0xFFF) << 12) | ((u32)segment & 0xFFF);
        second = (s32)(limit - end) >> 1;
        cmd->w1 = func_8001CE80(addr);
        cmd2 = cmdOut++;
        cmd2->w0 = 0x06000000 | (((u32)(second * 2) & 0xFFF) << 12) | ((u32)(segment + first) & 0xFFF);
        addr = buf->start;
        cmd2->w1 = func_8001CE80(addr);
    } else {
        cmdOut++;
        cmd->w0 = (segment & 0xFFF) | 0x06170000;
        cmd->w1 = func_8001CE80(addr);
    }
    return cmdOut;
}
