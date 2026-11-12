/* @header
 * func_800914F0
 * VRAM 0x800914F0 | ROM 0x3DC60 | size 0x228
 * asm: asm/nonmatchings/code_80090000/func_800914F0.s
 */
#include "common.h"

typedef struct {
    s16 f0;
    s16 f2;
    s16 f4;
    u8 pad6[10];
} Nw2Rec914;

typedef struct {
    s16 f0;
    s16 f2;
    s16 f4;
    s16 f6;
    s16 f8;
    s16 fA;
    u8 fC;
    u8 fD;
    u8 fE;
    u8 fF;
} Nw2Prt914;

#ifdef TARGET_PC
/* PC: arg0 is a 0xDC-byte scene object (func_800936DC's out), which keeps its N64 layout on PC (Nw2SceneObj,
 * common.h), so its vertices (+0xC) are a handle (port.h's PTR_TO_SLOT) and f1B is its vertex count. */
typedef struct {
    u8 pad0[0xC];
    u32 f0C;
    u8 pad10[0xB];
    u8 f1B;
} Nw2Obj914;
_Static_assert(offsetof(Nw2Obj914, f0C) == offsetof(Nw2SceneObj, vtx) &&
                   offsetof(Nw2Obj914, f1B) == offsetof(Nw2SceneObj, vtxCount),
               "Nw2Obj914 must follow Nw2SceneObj");
#else
typedef struct {
    u8 pad0[0xC];
    void *f0C;
    u8 pad10[0xB];
    u8 f1B;
} Nw2Obj914;
#endif

extern s32 D_800DB688;
extern Nw2Prt914 *D_800DB694;
extern void *D_800DBD48;
extern u8 func_800C61D8[];
extern u8 D_800C6418[];

/* Builds the vertex grid for a skinned part. Depending on the mode in
 * D_800DB688 it re-points the part at a canned control-point block and picks a
 * row/column count; then (once, guarded by D_800DBD48) it fills a 240x480 grid
 * of Nw2Prt914 entries by bilinear interpolation between the block's first and
 * last corner, tagging each with a fixed colour (0x49/0x49/0x49/0xFF). */
void func_800914F0(Nw2Obj914 *arg0, Nw2Rec914 *arg1, s32 arg2) {
    Nw2Rec914 *start;
    Nw2Rec914 *endP;
    Nw2Prt914 *out;
    s32 count;
    s32 row, col;
    s32 x0, z0, y0;
    s32 dx, dz, dy;

    start = arg1;
    count = arg2;
    switch (D_800DB688) {
    case 3:
        start = (Nw2Rec914 *)(func_800C61D8 + 0x38);
        count = 0xF;
        arg0->f1B = 4;
        break;
    case 1:
        start = (Nw2Rec914 *)(func_800C61D8 + 0x138);
        count = 0xF;
        arg0->f1B = 4;
        break;
    case 4:
        start = (Nw2Rec914 *)(func_800C61D8 + 0x238);
        count = 3;
        arg0->f1B = 4;
        break;
    case 5:
        count = 4;
        start = (Nw2Rec914 *)(D_800C6418 + 0x38);
        arg0->f1B = 4;
        break;
    }
#ifdef TARGET_PC
    /* PC: the object's vertex field holds a handle (see Nw2Obj914 above). */
    arg0->f0C = PTR_TO_SLOT(start);
#else
    arg0->f0C = start;
#endif
    if (D_800DBD48 == NULL) {
        row = 0;
        y0 = start->f2;
#ifdef TARGET_PC
        /* PC: the address as a pointer-wide integer (port.h's uptr); a u32 would cut it in half. */
        endP = (Nw2Rec914 *)((uptr)(count << 4) + (uptr)start);
#else
        endP = (Nw2Rec914 *)((u32)(count << 4) + (u32)start);
#endif
        x0 = start->f0;
        z0 = start->f4;
        dy = endP->f2 - y0;
        D_800DBD48 = D_800DB694;
        dx = endP->f0 - x0;
        dz = endP->f4 - z0;
        do {
            col = 0;
            do {
                out = D_800DB694;
                out->f0 = x0 + (dx * col) / 480;
                out->f2 = y0 + (dy * row) / 240;
                out->f4 = z0 + (dz * col) / 480;
                out->f6 = 0;
                out->f8 = col << 5;
                out->fA = row << 5;
                out->fC = 0x49;
                D_800DB694->fD = 0x49;
                D_800DB694->fE = 0x49;
                D_800DB694->fF = 0xFF;
                col += 0x50;
                D_800DB694++;
            } while (col < 0x1E1);
            row += 0x14;
        } while (row < 0xF1);
    }
}
