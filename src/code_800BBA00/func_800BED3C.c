/* @header
 * func_800BED3C
 * VRAM 0x800BED3C | ROM 0xB21DC | size 0x2DC
 * asm: asm/nonmatchings/code_800BBA00/func_800BED3C.s
 */
#include "common.h"

extern f64 D_800E5858;
extern f64 D_800E5860;

/* For every other wrestler (not w, not other) that is present and in the ring or on the apron, whose pelvis
 * (jointA[1]) is past the D_800E5858 / D_800E5860 bound on side w->dirIndex, sets a bit for which side of w's pelvis
 * it is on along that edge (0x100/0x200 along X for sides 0/2, 0x400/0x800 along Z for sides 1/3). Returns the bits. */
s32 func_800BED3C(Wrestler *w, Wrestler *other, u32 mask) {
    s32 a3 = 0;
    s16 i;
    s32 t0;
    s8 ok;

    for (i = 0; i < 4; i++) {
        t0 = 0;
        if (i != w->id && i != other->id && D_800F9D10[i].characterId != -1 &&
            (D_800F9D10[i].flags & (WR_FLAG_IN_RING | WR_FLAG_ON_APRON))) {
            switch (w->dirIndex) {
            case 0:
                if (D_800E5858 < D_800F9D10[i].jointA[1].z) t0 = 1;
                break;
            case 1:
                if (D_800E5858 < D_800F9D10[i].jointA[1].x) t0 = 1;
                break;
            case 2:
                if (D_800F9D10[i].jointA[1].z < D_800E5860) t0 = 1;
                break;
            case 3:
                if (D_800F9D10[i].jointA[1].x < D_800E5860) t0 = 1;
                break;
            }
            ok = t0;
            if (ok) {
                switch (w->dirIndex) {
                case 0:
                    if (D_800F9D10[i].jointA[1].x < w->jointA[1].x) {
                        a3 |= 0x200;
                    } else {
                        a3 |= 0x100;
                    }
                    break;
                case 1:
                    if (D_800F9D10[i].jointA[1].z > w->jointA[1].z) {
                        a3 |= 0x800;
                    } else {
                        a3 |= 0x400;
                    }
                    break;
                case 2:
                    if (D_800F9D10[i].jointA[1].x > w->jointA[1].x) {
                        a3 |= 0x100;
                    } else {
                        a3 |= 0x200;
                    }
                    break;
                case 3:
                    if (D_800F9D10[i].jointA[1].z < w->jointA[1].z) {
                        a3 |= 0x400;
                    } else {
                        a3 |= 0x800;
                    }
                    break;
                }
            }
        }
    }
    return a3 & 0xFFFF;
}
