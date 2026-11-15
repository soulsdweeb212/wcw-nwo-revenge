/* @header
 * func_80092960
 * VRAM 0x80092960 | ROM 0x3F0D0 | size 0x1C0
 * asm: asm/nonmatchings/code_80090000/func_80092960.s
 */
#include "common.h"

/* Emit a 3-digit decimal number as Gfx: set up the font tile block, then for
 * each digit slot load the glyph tile and write the cube/quad command; a zero
 * digit additionally tints the counter. arg1 is the packed counter value. */
#ifdef TARGET_PC
/* PC: a command is port.h's 16-byte Gfx (common.h's Nw2GfxCommand is the N64's 8 bytes), and every address goes into
 * its command as the whole pointer (port.h's DL_ADDR). The N64 code reaches the list D_800C5D90 as
 * func_800C5D48 + 0x48 (a label that splat named as a function; on PC the lists are copies made of 16-byte commands,
 * where that sum lands in the middle of one), and the word D_800DBD54 as D_800DBB80 + 0x1D4: the PC names both, as
 * func_80092B20 does. arg2 is record 8 of D_800C6508 (common.h's Nw2PicShape). */
s32 loadResourceTexture4b(Gfx **, Nw2PicShape *, s32);
void accumulateColorChannels(s32, s32, s32);
extern u8 D_800C5D90[];
extern s32 D_800DBD54;
void func_80092960(Gfx **arg0, s32 arg1, Nw2PicShape *arg2)
{
    Gfx *cmd;
    s32 digitIdx;
    s32 i;
    cmd = *arg0;
    {
        Gfx *g = cmd++;
        g->w0 = 0xDE000000;
        g->w1 = DL_ADDR(D_800C5D90);
    }
    {
        Gfx *g = cmd++;
        g->w0 = (0x01000000 | ((arg2->count & 255) << 12)) | ((arg2->count & 127) * 2);
        g->w1 = DL_ADDR(arg2->vtx);
    }
    i = 0;
    do
    {
        if (arg1 >= 0)
        {
            digitIdx = arg1 % 22;
            if (digitIdx >= 8)
            {
                digitIdx += 14;
            }
            if (loadResourceTexture4b(&cmd, arg2, digitIdx))
            {
                Gfx *g = cmd++;
                g->w0 = (((((i * 8) & 255) << 16) | ((((i * 8) + 2) & 255) << 8)) | (((i * 8) + 6) & 255)) | 0x07000000;
                g->w1 = ((((i * 8) & 255) << 16) | ((((i * 8) + 6) & 255) << 8)) | (((i * 8) + 4) & 255);
            }
            if (digitIdx == 0)
            {
                accumulateColorChannels(0x1F, 0x1F, 0x1F);
                if (i == 0)
                {
                    D_800DBD54 = 0x421;
                }
            }
        }
        i++;
        arg1 -= 7;
    }
    while (i < 3);
    *arg0 = cmd;
}
#else
s32 loadResourceTexture4b(void *, void *, s32);
void accumulateColorChannels(s32, s32, s32);
extern u8 func_800C5D48[];
extern u8 D_800DBB80[];
typedef struct 
{
    s32 f0;
    u32 f4;
    u16 f8;
} Desc929;
void func_80092960(Nw2GfxCommand **arg0, s32 arg1, Desc929 *arg2)
{
    Nw2GfxCommand *cmd;
    s32 digitIdx;
    s32 i;
    cmd = *arg0;
    {
        Nw2GfxCommand *g = cmd++;
        g->w0 = 0xDE000000;
        g->w1 = (u32) (func_800C5D48 + 0x48);
    }
    {
        Nw2GfxCommand *g = cmd++;
        g->w0 = (0x01000000 | ((arg2->f8 & 255) << 12)) | ((arg2->f8 & 127) * 2);
        g->w1 = arg2->f4;
    }
    i = 0;
    do
    {
        if (arg1 >= 0)
        {
            if (arg2)
            {
                digitIdx = arg1 % 22;
            }
            else
            {
                digitIdx = arg1 % 22;
            }
            if (digitIdx >= 8)
            {
                digitIdx += 14;
            }
            if (loadResourceTexture4b(&cmd, arg2, digitIdx))
            {
                Nw2GfxCommand *g = cmd++;
                g->w0 = (((((i * 8) & 255) << 16) | ((((i * 8) + 2) & 255) << 8)) | (((i * 8) + 6) & 255)) | 0x07000000;
                g->w1 = ((((i * 8) & 255) << 16) | ((((i * 8) + 6) & 255) << 8)) | (((i * 8) + 4) & 255);
            }
            if (digitIdx == 0)
            {
                accumulateColorChannels(0x1F, 0x1F, 0x1F);
                if (i == 0)
                {
                    *((s32 *) (D_800DBB80 + 0x1D4)) = 0x421;
                }
            }
        }
        i++;
        arg1 -= 7;
    }
    while (i < 3);
    *arg0 = cmd;
}
#endif
