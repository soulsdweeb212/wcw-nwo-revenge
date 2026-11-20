/* @header
 * decompressLzss  (originally func_800037F4)
 * VRAM 0x800037F4 | ROM 0x43F4 | size 0x124
 * asm: asm/nonmatchings/main/decompressLzss.s
 */
#include "common.h"

/* decompressLzss is the game's decompressor. It's the routine that unpacks the game's compressed files.
 *
 * Why it exists. N64 cartridges were small and expensive, so the developers squeezed many of the game's 7657 resources
 * (textures, models and so on) to save space. 2429 of them are stored compressed in the ROM. Before the game can use
 * one, this function unpacks it.
 *
 * How it works. It uses a common scheme called LZSS, which saves space by pointing back at things it has already
 * written instead of storing them again:
 * 1. The packed data starts with 4 bytes giving the unpacked size.
 * 2. Then comes a flag byte, whose 8 bits describe the next 8 items, one bit each:
 *    - A 1 means "copy the next byte as it is" (a literal).
 *    - A 0 means "go back up to 4096 bytes in what you've already unpacked, and copy 3 to 18 bytes from there". That
 *      reference takes only 2 bytes, which is where the saving comes from.
 * 3. It repeats until it has produced the full size.
 *
 * For example, a texture with a long run of the same colour shrinks to a few "copy from just behind" references
 * instead of hundreds of bytes.
 *
 * In the code: arg0 is the packed data, a big-endian u32 size followed by the compressed stream, and arg1 receives
 * that many bytes. READ_BE32 and uptr come from port.h: on N64 they are the original *(u32 *) read and u32 casts; on
 * PC they read the size big-endian and keep 64-bit addresses whole. */
void decompressLzss(u8 *arg0, u8 *arg1)
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
