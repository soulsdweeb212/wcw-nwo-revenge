/* @header
 * func_800DACE4
 * VRAM 0x800DACE4 | ROM 0xCE184 | size 0x664
 * asm: asm/nonmatchings/code_800BBA00/func_800DACE4.s
 */
#include "common.h"

typedef struct {
    f32 x, y, z;
    s32 angle;
    s32 extra;
} Nw2Dir5;

extern s16 D_800F9888[];
extern u8 D_800F9890[];
extern u8 D_800F9898[];
extern s32 D_800E3C90[];
extern s32 D_800E3CA0[];
extern s32 D_800E3CB0[];
extern s32 D_800E3CC0[];
extern f32 D_800E3FC0[][2];
extern f32 D_800E3FC4[][2];
extern f32 D_800E3FE0[][2];
extern f32 D_800E3FE4[][2];

void func_800D3890(void *, void *, void *);
s32 func_800D3684(s32, s32);
s32 func_800D3550(s32);
f32 func_800D3564(f32);
s32 func_800D35B0(s32, s32);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D37C0 */
void func_800D37C0(void *, f32, void *);
#endif

/* Aims a dive / jump of self at other. Sets D_800F9888[id] to the length of the anim's active window
 * (anim.activeEnd - anim.activeStart + 1, at least 1) and clears unk034. By state it sets the zone bits and a
 * minimum distance: 0x6B/0x6D/0x6E in ring, 0; 0x6C/0x6F apron|floor (leaving the ring), 0, and moveDelta[1] =
 * -90 / window so the body drops 90; 0x67 floor, 50; 0x68 floor, 90; 0x69 in ring, 100; 0x65/0x66/0x6A 50.
 * func_800D3890 gives the XZ direction (dir.y = distance, dir.angle = heading) from self's pelvis (jointA[1]) to
 * other's jointA[move.targetJoint]; a switch on moveId - 0xD1 then adjusts the heading and distance with the tables
 * indexed by ringSide / dirIndex, and for some moves sets unk034 |= 2. The distance is capped at
 * move.range * 2 * 0.1 * profile[0x1B] (unk034 |= 1 when capped) and raised to the minimum. The landing point
 * (pelvis + direction * distance, XZ) goes to D_800F9890/D_800F9898[id]; returns the heading. */
s32 func_800DACE4(Wrestler *self, Wrestler *other) {
    s32 id;
    s8 sid;
    Nw2DirectionResult dir;
    f32 vec[4];
    Nw2Dir5 dir2;
    f32 floor;
    f32 cap;
    s16 v;
    s32 d;
    s32 r;

    id = self->id;
    sid = id;
    self->unk034 = 0;
    D_800F9888[id] = v = self->anim.activeEnd - self->anim.activeStart + 1;
    if (v <= 0) {
        D_800F9888[id] = 1;
    }

    switch ((s16)(self->state - 0x65)) {
    case 6:
    case 8:
    case 9:
        self->flags = (self->flags & ~WR_FLAG_ON_APRON) | WR_FLAG_IN_RING;
        floor = 0.0f;
        break;
    case 7:
    case 10:
        self->flags = (self->flags & ~WR_FLAG_IN_RING) | WR_FLAG_ON_APRON | WR_FLAG_ON_FLOOR;
        floor = 0.0f;
        self->moveDelta[1] = -90.0 / (f32)D_800F9888[sid];
        break;
    case 2:
        self->flags = (self->flags & ~WR_FLAG_ON_APRON) | WR_FLAG_ON_FLOOR;
        floor = 50.0f;
        break;
    case 3:
        self->flags = (self->flags & ~WR_FLAG_ON_APRON) | WR_FLAG_ON_FLOOR;
        floor = 90.0f;
        break;
    case 4:
        self->flags = (self->flags & ~WR_FLAG_ON_APRON) | WR_FLAG_IN_RING;
        floor = 100.0f;
        break;
    case 0:
    case 1:
    case 5:
        floor = 50.0f;
        break;
    default:
#ifdef TARGET_PC
        /* Never runs: func_800DACE4's callers are the handlers of states 0x65 to 0x6F (func_800DCB54, func_800DCFBC,
         * func_800DD370, func_800DD188 and func_800DDAC8, which D_800E2FF0 calls only for those states), and they
         * pass the wrestler whose state chose them, so state - 0x65 is one of the cases above. The N64 code leaves
         * floor unset here; the PC sets it to 0 (no minimum distance), so no read of an unset variable remains. */
        floor = 0.0f;
#endif
        break;
    }

    func_800D3890(&self->jointA[1].x, &other->jointA[self->move.targetJoint], &dir);

    switch ((s16)(self->moveId - 0xD1)) {
    case 15:
        d = func_800D3550(func_800D3684(dir.angle, D_800E3C90[self->ringSide]));
        if (d >= 0x400) {
            dir.y = 50.0f;
        } else {
            dir.y = func_800D3564((self->ringSide & 1) ? dir.x : dir.z);
        }
        dir.angle = func_800D35B0(self->heading, 0x800);
        break;
    case 16:
        if (self->flags & 0x8000000000ULL) {
            vec[0] = D_800E3FC0[self->ringSide][0];
            vec[2] = D_800E3FC4[self->ringSide][0];
            func_800D3890(&self->jointA[1].x, vec, &dir2);
            d = func_800D3684(dir2.angle, dir.angle);
            if ((u32)(d + 0x200) >= 0x201) {
                if (d > 0) {
                    dir.angle = dir2.angle;
                } else {
                    dir.angle = func_800D35B0(dir2.angle, 0x200);
                }
            }
        } else {
            vec[0] = D_800E3FE0[self->ringSide][0];
            vec[2] = D_800E3FE4[self->ringSide][0];
            func_800D3890(&self->jointA[1].x, vec, &dir2);
            d = func_800D3684(dir2.angle, dir.angle);
            if ((u32)d >= 0x201) {
                if (d < 0) {
                    dir.angle = dir2.angle;
                } else {
                    dir.angle = func_800D35B0(dir2.angle, -0x200);
                }
            }
        }
        break;
    case 13:
    case 22:
        d = func_800D3550(func_800D3684(dir.angle, D_800E3C90[self->dirIndex]));
        if (d < 0x401) {
            dir.y = 50.0f;
        } else {
            dir.y = func_800D3564((self->dirIndex & 1) ? dir.x : dir.z);
        }
        dir.angle = D_800E3CA0[self->dirIndex];
        break;
    case 14:
        dir.angle = D_800E3CC0[self->dirIndex];
        break;
    case 17:
    case 18:
    case 19:
    case 25:
        d = func_800D3550(func_800D3684(dir.angle, D_800E3CA0[self->ringSide]));
        if (d >= 0x400) {
            dir.y = 100.0f;
        } else {
            dir.y = func_800D3564((self->ringSide & 1) ? dir.x : dir.z);
        }
        dir.angle = self->heading;
        break;
    case 4:
    case 5:
    case 6:
        self->unk034 |= 2;
    case 0:
    case 1:
    case 23:
        r = D_800E3CC0[self->dirIndex];
        d = func_800D3684(r, dir.angle);
        if (func_800D3550(d) >= 0x1C8) {
            if (d < 0) {
                dir.angle = func_800D35B0(r, 0x1C7);
            } else {
                dir.angle = func_800D35B0(r, -0x1C7);
            }
        }
        break;
    case 8:
        self->unk034 |= 2;
    case 7:
    case 24:
        r = D_800E3CB0[self->dirIndex];
        d = func_800D3684(r, dir.angle);
        if (func_800D3550(d) >= 0x5C8) {
            if (d < 0) {
                dir.angle = func_800D35B0(r, 0x5C7);
            } else {
                dir.angle = func_800D35B0(r, -0x5C7);
            }
        }
        break;
    default:
        break;
    }

    cap = (f32)(((f64)self->move.range + (f64)self->move.range) * 0.1 * (f64)*(s8 *)(self->profile + 0x1B));
    if (cap <= dir.y) {
        dir.y = cap;
        self->unk034 |= 1;
    }
    if (dir.y <= floor) {
        dir.y = floor;
    }

#ifdef TARGET_PC
    /* PC: port_decls.h declares func_800D37C0 as its definition does, with the angle as an s32; the cast to void *
     * only matched this file's own declaration of it, which the PC build does not read. */
    func_800D37C0(dir.angle, dir.y, &dir);
#else
    func_800D37C0((void *)dir.angle, dir.y, &dir);
#endif
    *(f32 *)(D_800F9890 + sid * 16) = self->jointA[1].x + dir.x;
    *(f32 *)(D_800F9898 + sid * 16) = self->jointA[1].z + dir.z;
    return dir.angle;
}
