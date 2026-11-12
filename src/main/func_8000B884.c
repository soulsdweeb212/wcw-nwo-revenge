/* @header
 * func_8000B884
 * VRAM 0x8000B884 | ROM 0xC484 | size 0x2BC
 * asm: asm/nonmatchings/main/func_8000B884.s
 */
#include "common.h"

extern u16 D_8007C318[][23];
extern void *D_8007C438[][23];
extern s16 D_80075440[][3];
extern u16 D_800485F0[];
extern u16 D_80030860[];
extern u16 D_800307A0;
extern s8 D_80030868[];
extern s16 D_8003086C[];
#ifndef TARGET_PC /* on PC, port.h declares the loader functions */
void func_80003684(void *, u16, void *);
#endif
#ifndef TARGET_PC /* on PC, port_decls.h declares convertRgba16ToGrayscale, which takes the u16 colours */
void convertRgba16ToGrayscale(void *, u16);
#endif
void func_8000B884(u16 *out, s16 entity, s16 slot)
{
    u8 meta[16];
    u8 meta2[16];
    u32 channel;
    u32 i;
    u16 *src;
    u16 mask;
    s16 level;
    u32 index;
    s32 t;
    u32 half = 0;
    func_80003684(meta, 0xA51, D_800485F0);
    if (D_8007C318[entity][slot] >= 17)
    {
        for (channel = 1; channel < 3; channel++)
        {
            for (i = 0; i < 16; i++)
            {
                src = D_8007C438[entity][slot];
                mask = D_80030860[channel];
#ifdef TARGET_PC
                /* PC: palettes stay in the N64's byte order (docs/port.md, "Byte order on PC"), so the entries this function tests
                 * and shifts are read big-endian (READ_BE16); the entries it copies (out[i] = ...) are copied as they are. */
                if (!((READ_BE16(&src[16 + i]) & 0xFFFF) & (~mask)))
#else
                if (!((src[16 + i] & 0xFFFF) & (~mask)))
#endif
                {
#ifdef TARGET_PC
                    if ((READ_BE16(&src[16 + i]) & 0xFFFF) >= 2)
#else
                    if ((src[16 + i] & 0xFFFF) >= 2)
#endif
                    {
                        level = D_80075440[entity][channel];
                        if (level < 15)
                        {
#ifdef TARGET_PC
                            t = ((s32) (READ_BE16(&src[16 + i]) & mask)) >> D_80030868[channel];
#else
                            t = ((s32) (src[16 + i] & mask)) >> D_80030868[channel];
#endif
                            half = (u32)t >> 1;
                            t = 15 - half;
                            half = D_800485F0[(level * 16) + t];
                            out[i] = half;
                        }
                        else
                        {
                            out[i] = src[i];
                        }
                    }
                }
            }

        }

    }
    {
        s16 lv = D_8003086C[slot];
        if (lv)
        {
            u16 *s2;
            u16 px;
            u16 mk;
            u32 bt;
            func_80003684(meta2, lv, D_800485F0);
            for (i = 0; i < 16; i++)
            {
                s2 = D_8007C438[entity][slot];
#ifdef TARGET_PC
                px = READ_BE16(&((volatile u16 *) s2)[i]);
#else
                px = ((volatile u16 *) s2)[i];
#endif
                mk = *((volatile u16 *) (&D_80030860[0]));
                bt = px & 0xFFFF;
                if (!(bt & (~mk)))
                {
                    if (bt >= 2)
                    {
                        t = ((s32) (px & mk)) >> D_80030868[0];
                        out[i] = D_800485F0[(D_80075440[entity][0] * 16) + ((u32)t >> 1)];
                    }
                }
            }

        }
    }
    if (D_800307A0 == 1)
    {
        convertRgba16ToGrayscale(out, 16);
    }
}
