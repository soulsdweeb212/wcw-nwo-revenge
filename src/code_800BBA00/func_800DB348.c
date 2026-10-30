/* @header
 * func_800DB348
 * VRAM 0x800DB348 | ROM 0xCE7E8 | size 0x1B4
 * asm: asm/nonmatchings/code_800BBA00/func_800DB348.s
 */
#include "common.h"

/* Per-frame paired-move outer hook: while the entity's timer/frame is inside
 * its active window, resolve the movement direction (func_800D3890 /
 * func_800D37C0), translate it and step a shared counter; then clear the
 * sub-action bit and, once past the window, clear the paired flags and run the
 * follow-up. */
typedef struct Nw2EntDB348 {
    u8 f0;
    u8 pad1[5];
    s16 f6;
    u8 pad8[2];
    s16 fA;
    u8 padC[0x14];
    u64 flags;
    u8 pad28[0xC];
    u8 f34;
    u8 pad35[0x1B];
    f32 f50;
    u8 pad54[8];
    u8 f5C[0x2E0];
    f32 f33C;
    f32 f340;
    f32 f344;
    u8 pad348[0x29];
    u8 f371;
    u8 pad372[8];
    u8 f37A;
    u8 f37B;
    u8 pad37C[0x1B];
    s8 f397;
} Nw2EntDB348;

typedef struct {
    u8 pad[0xA];
    s16 fA;
    s16 fC;
} Nw2OtherDB348;

typedef struct {
    f32 x, y, z;
    s32 angle;
} Nw2DirRes;

extern u8 D_800F9890[];
extern s16 D_800F9888[];

void func_800D3890(void *, void *, void *);
void func_800D37C0(s32, f32, void *);
void translateEntityXZ(void *, void *);
s32 func_800D2B64(void *, f32, u16, s32);

void func_800DB348(Nw2EntDB348 *e, Nw2OtherDB348 *o) {
    Nw2DirRes dir;
    s32 id;
    u8 flagBits;
    s8 idx;

    e->flags |= 0x80000000000ULL;
    id = e->f0;
    if (e->f6 < e->f37A || e->f37B < e->f6)
        goto skip;
    idx = e->f397;
    func_800D3890(e->f5C + idx * 0x10, D_800F9890 + (s8)id * 0x10, &dir);
    func_800D37C0(dir.angle, dir.y / (f32)D_800F9888[(s8)id], &e->f33C);
    translateEntityXZ(e, &e->f33C);
    if (e->fA == 0x6C) {
        e->f50 += e->f340;
    } else if (e->fA == 0x6F) {
        e->f50 += e->f340;
    }
    ((u16 *)D_800F9888)[(s8)id]--;
skip:
    flagBits = e->f34;
    if ((flagBits & 2) && (o->fA != 0x2C || o->fC != 3))
        e->f34 = flagBits & ~0x10;
    if (e->f6 < e->f371)
        return;
    e->flags &= ~0x80000000080ULL;
    func_800D2B64(e, 4.0f, 0, 0xFFFFE);
}
