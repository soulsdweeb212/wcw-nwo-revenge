/* @header
 * func_80092B20
 * VRAM 0x80092B20 | ROM 0x3F290 | size 0x2C0
 * asm: asm/nonmatchings/code_80090000/func_80092B20.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: a spot of the scene's list (common.h's Nw2EncSpot), which the PC converts as 16-bit values, so the N64's byte at
 * +7 is the low byte of the u16 f6 (F7 below). */
typedef struct {
    u8 pad0[6];
    u16 f6;
    s16 f8;
    u8 padA[2];
    s16 fC;
} Sub92B20;
_Static_assert(offsetof(Sub92B20, f6) == offsetof(Nw2EncSpot, f6) && offsetof(Sub92B20, f8) == offsetof(Nw2EncSpot, x) &&
                   offsetof(Sub92B20, fC) == offsetof(Nw2EncSpot, z),
               "Sub92B20 must follow Nw2EncSpot");
#else
typedef struct {
    u8 pad0[7];
    u8 f7;
    s16 f8;
    u8 padA[2];
    s16 fC;
} Sub92B20;
#endif

#ifdef TARGET_PC
/* PC: an encounter record of D_800DB8C0 (func_80092DE0's S2DE0): its part, its scene object and its record of
 * D_800C6508 are pointers, 8 bytes each on PC, so the fields after them move. */
typedef struct {
    Sub92B20 *f0;
    void *f4;
    void *f8;
    u16 fC;
    u8 padE[2];
    s16 f10;
} S92B20;
#else
typedef struct {
    Sub92B20 *f0;
    u8 pad4[8];
    u16 fC;
    u8 padE[2];
    s16 f10;
} S92B20;
#endif

extern s32 D_800E74C4;
extern u8 D_800C5D90[];
#ifdef TARGET_PC
/* PC: the picture shapes D_800C6508 (common.h's Nw2PicShape). The N64 reads records 6, 7 and 8 by labels inside the
 * table: D_800C6568 is record 6, D_800C656C, D_800C6570 and D_800C6574 its vertices, count and fC, D_800C657C the
 * vertices of record 7, D_800C6588 record 8. On PC the records are 0x18 bytes, so the PC indexes the table. */
extern Nw2PicShape D_800C6508[];
#else
extern u8 D_800C6568[];
extern u8 D_800C6588[];
extern s32 D_800C656C[];
extern u16 D_800C6570[];
extern u8 D_800C6574[];
extern s32 D_800C657C[];
#endif
extern s32 D_800DBD54;

void func_800927B0(void **, s32, void *);
void func_80092960(void **, s32, void *);
void func_80092554(void **, s32, s16, s16);
s32 loadResourceTexture4b(void **, void *, s32);
void accumulateColorChannels(s32, s32, s32);

#ifdef TARGET_PC
/* PC: a command is port.h's 16-byte Gfx, as the functions this one calls write them (common.h's Nw2GfxCommand is the
 * N64's 8 bytes), and the vertices' addresses go into the commands as whole pointers (port.h's DL_ADDR). */
#define EMIT(a, b) { Gfx *q = p; p = q + 1; q->w0 = (a); q->w1 = (b); }
#else
#define EMIT(a, b) { Nw2GfxCommand *q = p; p = q + 1; q->w0 = (a); q->w1 = (b); }
#endif

void func_80092B20(void **out, S92B20 *s) {
    void *p;
    s32 mode;
    s32 k;
    s32 idx;

    p = *out;
    mode = D_800E74C4;
    k = s->f10;
    if (mode == 7) {
        switch (s->fC) {
        case 7:
        case 9:
            mode = 4;
            break;
        case 8:
            mode = 2;
            break;
        case 6:
            mode = 6;
            break;
        }
    }
    switch (mode) {
    case 1:
#ifdef TARGET_PC
        func_800927B0(&p, k, &D_800C6508[8]);
#else
        func_800927B0(&p, k, D_800C6588);
#endif
        break;
    case 2:
#ifdef TARGET_PC
        func_80092960(&p, k, &D_800C6508[8]);
#else
        func_80092960(&p, k, D_800C6588);
#endif
        break;
    case 4:
        if (s->f10 >= 0x30) {
            s->f10 = 0;
        }
        goto case3;
    case 6:
        if (s->f10 >= 0x1C) {
            s->f10 = 0;
        }
    case 5:
        idx = s->f10;
#ifdef TARGET_PC
        if (idx >= 0 && idx < D_800C6508[6].fC) {
#else
        if (idx >= 0 && idx < D_800C6574[0]) {
#endif
#ifdef TARGET_PC
            /* PC: the display list's address as the whole pointer (port.h's DL_ADDR). */
            EMIT(0xDE000000, DL_ADDR(D_800C5D90));
#else
            EMIT(0xDE000000, (u32)D_800C5D90);
#endif
            EMIT(0xFB000000, 0xFF0000FF);
            EMIT(0xFA000000, 0xFFFF00FF);
#ifdef TARGET_PC
            { u32 hi = (D_800C6508[6].count & 0xFF) << 12; u32 lo = ((D_800C6508[6].count & 0x7F) << 1) | 0x01000000; EMIT(hi | lo, DL_ADDR(D_800C6508[6].vtx)); }
            if (loadResourceTexture4b(&p, &D_800C6508[6], idx)) {
#else
            { u32 hi = (D_800C6570[0] & 0xFF) << 12; u32 lo = ((D_800C6570[0] & 0x7F) << 1) | 0x01000000; EMIT(hi | lo, D_800C656C[0]); }
            if (loadResourceTexture4b(&p, D_800C6568, idx)) {
#endif
                EMIT(0x07000206, 0x604);
            }
            if (idx < 0x14 && (idx & 1)) {
                accumulateColorChannels(0xF, 0, 0);
            }
            if (idx == 0) {
                D_800DBD54 = 0x421;
            }
        }
        break;
    case 8:
        if (s->f10 >= 0x30) {
#ifdef TARGET_PC
            func_80092960(&p, s->f10 - 0x30, &D_800C6508[8]);
#else
            func_80092960(&p, s->f10 - 0x30, D_800C6588);
#endif
            break;
        }
    case 3:
case3:
#ifdef TARGET_PC
        EMIT(0xDE000000, DL_ADDR(D_800C5D90)); /* PC: as above */
#else
        EMIT(0xDE000000, (u32)D_800C5D90);
#endif
#ifdef TARGET_PC
        EMIT(0x01014028, DL_ADDR(D_800C6508[7].vtx));
#else
        EMIT(0x01014028, D_800C657C[0]);
#endif
        func_80092554(&p, s->f10, s->f0->f8, s->f0->fC);
        break;
    default:
#ifdef TARGET_PC
        s->f10 = ~(u8)s->f0->f6;
#else
        s->f10 = ~s->f0->f7;
#endif
        break;
    }
    *out = p;
}
