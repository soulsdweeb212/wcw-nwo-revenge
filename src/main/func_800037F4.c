/* @header
 * func_800037F4
 * VRAM 0x800037F4 | ROM 0x43F4 | size 0x124
 * asm: asm/nonmatchings/main/func_800037F4.s
 */
#include "common.h"

/* LZSS decompressor for compressed resources (4 KiB window, matches of 3 to 18 bytes): arg0 is the packed data, a
 * big-endian u32 size followed by the compressed stream, and arg1 receives that many bytes. READ_BE32 and uptr come
 * from port.h: on N64 they are the original *(u32 *) read and u32 casts; on PC they read the size big-endian and keep
 * 64-bit addresses whole. */
void func_800037F4(u8 *arg0, u8 *arg1)
{
    u8 tmp[8];
    u32 size;
    u16 flags;
    u32 b0;
    u32 b1;
    s32 off;
    s32 pos;
    u32 i;
    u8 *out;
    u8 *p;
    u8 *q;
    u8 *src;
    size = READ_BE32(arg0);
    src = arg0 + 4;
    pos = 0x1000;
    if (size < 0x1000)
    {
        pos = size;
    }
    if (pos != 0)
    {
        q = arg1;
        p = (u8 *) (((uptr) pos) + ((uptr) arg1));
        do
        {
            *q = 0;
            q++;
        }
        while (q < p);
    }
    flags = 0;
    pos = 0;
    if (size != 0)
    {
        out = arg1;
        do
        {
            flags >>= 1;
            if (!(flags & 0x100))
            {
                flags = (*(src++)) | 0xFF00;
            }
            if (flags & 1)
            {
                *out = *(src++);
                out++;
                pos++;
            }
            else
            {
                b0 = *(src++);
                b1 = *(src++);
                b0 |= (b1 & 0xF0) << 4;
                b1 = (b1 & 0xF) + 2;
                off = (b0 + 0x12) & 0xFFF;
                off -= pos & 0xFFF;
                if (off >= 0)
                {
                    off = off - 0x1000;
                }
                i = 0;
                p = (u8 *) (((uptr) pos) + ((uptr) arg1));
                do
                {
                    if ((pos + off) >= 0)
                    {
                        *p = arg1[pos + off];
                    }
                    else
                    {
                        *p = 0;
                    }
                    p++;
                    out++;
                    i++;
                    pos++;
                }
                while (i <= b1);
            }
        }
        while (((u32) pos) < size);
    }
}
