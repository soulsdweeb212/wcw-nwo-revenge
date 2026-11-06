/* @header
 * func_800D7E80
 * VRAM 0x800D7E80 | ROM 0xCB320 | size 0xEF4
 * asm: asm/nonmatchings/code_800BBA00/func_800D7E80.s
 */
#include "common.h"

extern f32 D_800E3C50[];
extern f32 D_800E3C54[];
extern s32 D_800E3C90[];
extern s32 D_800E3CA0[];
extern s32 D_800E3CB0[];
extern s32 D_800E3CC0[];
extern f64 D_800E6FC8, D_800E6FD0, D_800E6FD8, D_800E6FE0;
extern u16 D_800FAF8E[];

void func_800A7328(Wrestler *);
s32 func_800D35B0(s32, s32);
s32 func_800D3940(f32 *, f32 *);
void func_800D3E40(f32 *, f32 *, s32, f32 *);
void func_800D3838(void *, void *, s16, void *);

/* Sets up a scripted move of e (o is its opponent; some callers pass 0, and only the states that read o need it).
 * By e->state it picks a target XZ point c, a target heading `ang` and a tick count n: either c directly (corner
 * constants, or e's pelvis jointA[1] with a coordinate often replaced by a constant chosen by e->dirIndex), or
 * c = anchor a plus offset b rotated by ang2 (func_800D3E40), where the anchor is a D_800E3C50/54 table entry by
 * e->dirIndex or o's pelvis / root. Then func_800A7328(e) shifts e (root and joints) in XZ so the root lands where
 * the pelvis was, and the movement is stored for func_800D8D74 to play back: e->moveDelta = (c - root) / n in x and
 * z (moveDelta[1] is not written), e->turnPerTick = (ang - e->heading) / n (wrapped angle difference),
 * e->stateTimer = n. */
void func_800D7E80(Wrestler *e, Wrestler *o)
{
    f32 a[3];
    f32 b[3];
    f32 c[3];
    s32 ang;
    s16 n;
    s32 ang2;
    s16 calc;

    calc = 1;
    switch (e->state) {
    case 10:
        b[0] = 0.0f;
        b[2] = 73.539108f;
        a[0] = D_800E3C50[e->dirIndex * 2];
        a[2] = D_800E3C54[e->dirIndex * 2];
        n = 8;
        ang = D_800E3CB0[e->dirIndex];
        ang2 = D_800E3CC0[e->dirIndex];
        break;
    case 123:
        b[0] = 0.0f;
        b[2] = 91.923881f;
        a[0] = D_800E3C50[e->dirIndex * 2];
        a[2] = D_800E3C54[e->dirIndex * 2];
        n = 10;
        ang = D_800E3CB0[e->dirIndex];
        ang2 = D_800E3CC0[e->dirIndex];
        break;
    case 124:
        calc = 0;
        n = 6;
        if (o->grappleCtx & 0x40) {
            ang = D_800E3CB0[e->dirIndex];
            switch (e->dirIndex) {
            case 0:
                c[0] = 229.15f;
                c[2] = 229.15f;
                break;
            case 1:
                c[0] = 229.15f;
                c[2] = -229.15f;
                break;
            case 2:
                c[0] = -229.15f;
                c[2] = -229.15f;
                break;
            case 3:
                c[0] = -229.15f;
                c[2] = 229.15f;
                break;
            }
        } else {
            ang = D_800E3CC0[e->dirIndex];
            switch (e->dirIndex) {
            case 0:
                c[0] = 230.85f;
                c[2] = 230.85f;
                break;
            case 1:
                c[0] = 230.85f;
                c[2] = -230.85f;
                break;
            case 2:
                c[0] = -230.85f;
                c[2] = -230.85f;
                break;
            case 3:
                c[0] = -230.85f;
                c[2] = 230.85f;
                break;
            }
        }
        break;
    case 80:
        b[0] = 0.0f;
        b[2] = 80.0f;
        a[0] = o->jointA[1].x;
        a[2] = o->jointA[1].z;
        n = 6;
        ang = func_800D35B0(o->heading, 0x800);
        ang2 = o->heading;
        break;
    case 125:
        ang = D_800E3C90[(s16)(e->dirIndex & ~0x2000)];
        c[0] = e->jointA[1].x;
        c[2] = e->jointA[1].z;
        calc = 0;
        n = 6;
        if (e->dirIndex & 0x2000) {
            switch ((s16)(e->dirIndex & ~0x2000)) {
            case 1:
                c[0] = 119.0f;
                break;
            case 3:
                c[0] = -119.0f;
                break;
            }
        } else {
            switch ((s16)(e->dirIndex & ~0x2000)) {
            case 0:
                c[2] = 473.0f;
                break;
            case 1:
                c[0] = 473.0f;
                break;
            case 2:
                c[2] = -473.0f;
                break;
            case 3:
                c[0] = -473.0f;
                break;
            }
        }
        break;
    case 89:
        b[0] = 0.0f;
        b[2] = 100.0f;
        a[0] = o->x;
        a[2] = o->z;
        n = 6;
        ang = func_800D35B0(o->heading, 0x800);
        ang2 = o->heading;
        break;
    case 100:
        ang = D_800E3C90[e->dirIndex];
        c[0] = e->jointA[1].x;
        c[2] = e->jointA[1].z;
        calc = 0;
        n = 7;
        switch (e->dirIndex) {
        case 0:
            c[2] = 183.0f;
            break;
        case 1:
            c[0] = 183.0f;
            break;
        case 2:
            c[2] = -183.0f;
            break;
        case 3:
            c[0] = -183.0f;
            break;
        }
        break;
    case 101:
        ang = D_800E3C90[e->dirIndex];
        c[0] = e->jointA[1].x;
        c[2] = e->jointA[1].z;
        calc = 0;
        n = 7;
        switch (e->dirIndex) {
        case 0:
            c[2] = 180.0f;
            break;
        case 1:
            c[0] = 180.0f;
            break;
        case 2:
            c[2] = -180.0f;
            break;
        case 3:
            c[0] = -180.0f;
            break;
        }
        break;
    case 102:
        b[0] = 0.0f;
        b[2] = 70.710678f;
        a[0] = D_800E3C50[e->dirIndex * 2];
        a[2] = D_800E3C54[e->dirIndex * 2];
        n = 7;
        ang = D_800E3CB0[e->dirIndex];
        ang2 = D_800E3CC0[e->dirIndex];
        break;
    case 75:
        b[0] = 0.0f;
        b[2] = 130.0f;
        a[0] = o->jointA[1].x;
        a[2] = o->jointA[1].z;
        n = 6;
        ang = func_800D35B0(o->heading, 0x800);
        ang2 = o->heading;
        break;
    case 76:
        b[0] = 0.0f;
        if (e->move.moveCode >= 0x99 && e->move.moveCode <= 0xA6) {
            b[2] = 100.0f;
        }
        if (e->move.moveCode != 0 && e->move.moveCode < 0x3B) {
            b[2] = 73.5f;
        }
        if (e->move.moveCode >= 0x3D && e->move.moveCode <= 0x45) {
            b[2] = 53.5f;
        }
        a[0] = o->jointA[1].x;
        a[2] = o->jointA[1].z;
        n = 6;
        ang = func_800D35B0(o->heading, 0x800);
        ang2 = o->heading;
        break;
    case 98:
        calc = 0;
        n = 6;
        if (e->hitInfo & 0x1000) {
            ang = D_800E3C90[e->dirIndex];
        } else {
            ang = D_800E3CA0[e->dirIndex];
        }
        c[0] = e->jointA[1].x;
        c[2] = e->jointA[1].z;
        switch (e->dirIndex) {
        case 0:
            c[2] = 174.0f;
            break;
        case 1:
            c[0] = 174.0f;
            break;
        case 2:
            c[2] = -174.0f;
            break;
        case 3:
            c[0] = -174.0f;
            break;
        }
        break;
    case 96:
        ang = D_800E3C90[e->dirIndex];
        c[0] = e->jointA[1].x;
        c[2] = e->jointA[1].z;
        calc = 0;
        n = 6;
        switch (e->dirIndex) {
        case 0:
            c[2] = 173.0f;
            break;
        case 1:
            c[0] = 173.0f;
            break;
        case 2:
            c[2] = -173.0f;
            break;
        case 3:
            c[0] = -173.0f;
            break;
        }
        break;
    case 97:
        ang = D_800E3CA0[e->dirIndex];
        c[0] = e->jointA[1].x;
        c[2] = e->jointA[1].z;
        calc = 0;
        n = 6;
        switch (e->dirIndex) {
        case 0:
            c[2] = 335.0f;
            break;
        case 1:
            c[0] = 335.0f;
            break;
        case 2:
            c[2] = -335.0f;
            break;
        case 3:
            c[0] = -335.0f;
            break;
        }
        break;
    case 13: case 15:
        n = e->anim.frameCount;
        ang = e->heading;
        c[0] = e->jointA[1].x;
        c[2] = e->jointA[1].z;
        calc = 0;
        switch (e->dirIndex) {
        case 0:
        case 2:
            if ((D_800FAF8E[e->id] & 0x200) && e->jointA[1].x < D_800E6FC8) {
                c[0] = -125.0f;
            }
            if ((D_800FAF8E[e->id] & 0x100) && D_800E6FD0 < e->jointA[1].x) {
                c[0] = 125.0f;
            }
            break;
        case 1:
        case 3:
            if ((D_800FAF8E[e->id] & 0x400) && e->jointA[1].z < D_800E6FD8) {
                c[2] = -125.0f;
            }
            if ((D_800FAF8E[e->id] & 0x800) && D_800E6FE0 < e->jointA[1].z) {
                c[2] = 125.0f;
            }
            break;
        }
        break;
    case 128:
        if (e->step < 2) {
            b[0] = 0.0f;
            b[2] = 80.0f;
            a[0] = o->jointA[1].x;
            a[2] = o->jointA[1].z;
            ang = func_800D35B0(D_800E3CA0[o->ringSide], 0x800);
            n = 8;
            ang2 = D_800E3CA0[o->ringSide];
        } else {
            b[0] = 0.0f;
            b[2] = 80.0f;
            a[0] = o->jointA[1].x;
            a[2] = o->jointA[1].z;
            n = 8;
            ang = D_800E3CB0[o->dirIndex];
            ang2 = D_800E3CC0[o->dirIndex];
        }
        break;
    case 90:
        b[0] = 0.0f;
        b[2] = 100.0f;
        a[0] = o->jointA[1].x;
        a[2] = o->jointA[1].z;
        n = 6;
        ang = func_800D35B0(o->heading, 0x800);
        ang2 = o->heading;
        break;
    case 115:
        b[0] = 0.0f;
        b[2] = 73.0f;
        a[0] = o->x;
        a[2] = o->z;
        ang = o->heading;
        n = 6;
        ang2 = ang;
        break;
    case 134:
        if (e->flags & WR_FLAG_IN_RING) {
            ang = D_800E3C90[e->dirIndex];
            c[0] = e->jointA[1].x;
            c[2] = e->jointA[1].z;
            calc = 0;
            n = 6;
            switch (e->dirIndex) {
            case 0:
                c[2] = 150.0f;
                break;
            case 1:
                c[0] = 150.0f;
                break;
            case 2:
                c[2] = -150.0f;
                break;
            case 3:
                c[0] = -150.0f;
                break;
            }
        } else {
            calc = 0;
            ang = D_800E3C90[e->dirIndex];
            c[0] = e->jointA[1].x;
            c[2] = e->jointA[1].z;
            n = 6;
            switch (e->dirIndex) {
            case 0:
                c[2] = -335.0f;
                break;
            case 1:
                c[0] = -335.0f;
                break;
            case 2:
                c[2] = 335.0f;
                break;
            case 3:
                c[0] = 335.0f;
                break;
            }
        }
        break;
    case 24:
        b[0] = 0.0f;
        b[2] = 73.539108f;
        a[0] = D_800E3C50[e->dirIndex * 2];
        a[2] = D_800E3C54[e->dirIndex * 2];
        ang2 = D_800E3CC0[e->dirIndex];
        n = 8;
        if (e->move.flags & 0x18) {
            ang = ang2;
        } else {
            ang = D_800E3CB0[e->dirIndex];
        }
        break;
    case 52:
        b[0] = 0.0f;
        b[2] = 40.0f;
        a[0] = o->x;
        a[2] = o->z;
        n = 8;
        ang = func_800D35B0(o->heading, 0x800);
        ang2 = o->heading;
        break;
    case 93:
        c[0] = e->jointA[1].x;
        calc = 0;
        n = 6;
        c[2] = e->jointA[1].z;
        ang = func_800D3940(&e->jointA[1].x, &o->jointA[1].x);
        break;
    case 94:
        b[0] = 0.0f;
        b[2] = 100.0f;
        a[0] = o->x;
        a[2] = o->z;
        ang2 = func_800D3940(&o->jointA[1].x, &e->jointA[1].x);
        n = 6;
        ang = func_800D35B0(ang2, 0x800);
        break;
    }
    func_800A7328(e);
    if (calc) {
        func_800D3E40(a, b, ang2, c);
    }
    func_800D3838(&e->x, c, n, e->moveDelta);
    e->turnPerTick = func_800D3684(ang, e->heading) / n;
    e->stateTimer = n;
}
