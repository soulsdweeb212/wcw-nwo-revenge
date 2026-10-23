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

/* Append the audio-load command(s) (opcode 0x04000000) needed to play count
 * samples starting at addr out of buf, starting at segment. If the requested
 * range wraps past the end of the buffer, emit two commands and split the
 * range at the buffer end; otherwise emit a single command. Returns the
 * advanced command pointer. */
AudioCommand *func_8001A080(AudioBuffer *buf, u32 addr, s32 segment, s32 count, AudioCommand *cmdOut) {
    AudioCommand *cmd = cmdOut, *cmd2;
    s32 span1, span2;
    u32 end, limit;
    end = buf->start + buf->length * 2;
    if (addr < buf->start) addr += buf->length * 2;
    limit = addr + count * 2;
    if (end < limit) {
        cmdOut++;
        span1 = ((s32)(end - addr) >> 1) * 2;
        cmd->w0 = 0x04000000 | (((u32)span1 & 0xFFF) << 12) | ((u32)segment & 0xFFF);
        span2 = (s32)(limit - end) >> 1;
        cmd->w1 = func_8001CE80(addr);
        cmd2 = cmdOut++;
        cmd2->w0 = 0x04000000 | (((u32)(span2 * 2) & 0xFFF) << 12) | ((u32)(segment + span1) & 0xFFF);
        addr = buf->start;
        cmd2->w1 = func_8001CE80(addr);
    } else {
        cmdOut++;
        cmd->w0 = 0x04000000 | (((u32)(count * 2) & 0xFFF) << 12) | ((u32)segment & 0xFFF);
        cmd->w1 = func_8001CE80(addr);
    }
    return cmdOut;
}
