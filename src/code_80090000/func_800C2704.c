/* @header
 * func_800C2704
 * VRAM 0x800C2704 | ROM 0x6EE74 | size 0x5A8
 * asm: asm/nonmatchings/code_80090000/func_800C2704.s
 */
#include "common.h"

typedef struct { f32 x, y, z; s32 a; } Cam;
typedef struct {
    u8 pad0[0x680];
    Cam cam;
    u8 pad690[0x6BC - 0x690];
    s16 f6BC;
    u8 pad6BE[0x6D0 - 0x6BE];
} P;
typedef struct { s16 x, z; u16 f; u16 pad; } Ent;
typedef struct { f32 x; f32 pad4; f32 z; f32 padC; f32 a; f32 pad14[3]; } Pt;

extern P *D_800E79B8;
extern s32 D_800E7CC0[3][2];
extern s32 D_800E74B8[];
extern s32 D_800E74D8;
extern s32 D_800EA0A8[];
extern Ent *D_800D5DA0[];
extern Ent *D_800D5990[];
extern f64 D_800D6C68;
s32 func_800966B8(void);
s32 func_800B5E18(s32, s32);
f32 nw2Sqrtf(f32);
void buildScaledRotationTranslationMatrix(void *, f32, f32, f32, f32, f32, f32, f32);
void func_8001B3EC(void *, f32, f32, f32, f32 *, f32 *, f32 *);

static inline Ent *getPoint(s32 idx, Pt *out, s32 path) {
    Ent *t;

    if (D_800E74D8 == -9) {
        t = &D_800D5DA0[path][idx];
    } else {
        t = &D_800D5990[func_800966B8() * 4 + path][idx];
    }
    out->x = t->x;
    out->z = t->z;
    out->a = t->f & 0xFC0;
    return t;
}

s32 func_800C2704(s32 n) {
    Pt pt;
    f32 m[16];
    P *p = &D_800E79B8[n];
    s32 done = 0, d = 0, lim, path, end, dx, dz, a, b, t;
    Ent *e;

    lim = p->f6BC == 0xE6E ? 12 : 4;
    path = D_800E7CC0[0][n];
    if (path < 0) {
        return 0;
    }
    e = getPoint(D_800E74B8[n], &pt, path);
    end = (e->f & 0xF) * 4;
    if (D_800E74B8[n] == 0) {
        p->cam.x = (s32)pt.x;
        p->cam.z = (s32)pt.z;
        p->cam.y = 0.0f;
        p->cam.a = (s32)pt.a & 0xF00;
        a = D_800E74B8[n] + 1;
        D_800E74B8[n] = a;
        getPoint(a, &pt, D_800E7CC0[0][n]);
        a = func_800B5E18(pt.x - p->cam.x, pt.z - p->cam.z);
        if (a >= 0) {
            p->cam.a = a;
        }
    } else if (D_800EA0A8[n] >= end || D_800EA0A8[n] < end - 3) {
        /* do/while(0): loop depth doubles dx/dz refs so they outrank p in global alloc (dz s1, dx s2, p s3). */
        do {
            dx = pt.x - p->cam.x;
            dz = pt.z - p->cam.z;
            a = func_800B5E18(dx, dz);
        } while (0);
        if (a >= 0) {
            b = p->cam.a;
            if (b != a) {
                if ((b - a) & 0x800) {
                    b += 0x40;
                    if (!((b - a) & 0x800)) {
                        b = a;
                    }
                } else {
                    b -= 0x40;
                    if ((b - a) & 0x800) {
                        b = a;
                    }
                }
            }
            p->cam.a = b & 0xFFF;
            d = nw2Sqrtf(dx * dx + dz * dz);
            if (d < lim) {
                done = 1;
            }
            if (d > lim) {
                d = lim;
            }
            a += p->cam.a;
            a /= 2;
        } else {
            d = 0;
            done = 1;
            a = p->cam.a;
        }
        buildScaledRotationTranslationMatrix(m, 0.0f, a * D_800D6C68, 0.0f, 1.0f, p->cam.x, p->cam.y, p->cam.z);
        func_8001B3EC(m, 0.0f, 0.0f, d, &p->cam.x, &p->cam.y, &p->cam.z);
        if (done) {
            if ((s32)pt.a & 0x80) {
                if (p->f6BC == 0xE6E) {
                    p->f6BC = -6;
                }
                t = p->cam.a;
                if (t != ((s32)pt.a & 0xF00)) {
                    if ((t - ((s32)pt.a & 0xF00)) & 0x800) {
                        t += 0x80;
                        if (!((t - ((s32)pt.a & 0xF00)) & 0x800)) {
                            t = (s32)pt.a & 0xF00;
                        }
                    } else {
                        t -= 0x80;
                        if ((t - ((s32)pt.a & 0xF00)) & 0x800) {
                            t = (s32)pt.a & 0xF00;
                        }
                    }
                }
                p->cam.a = t & 0xFFF;
                done = (p->cam.a == ((s32)pt.a & 0xF00)) ? done : 0;
            }
            if (done) {
                if (D_800EA0A8[n] >= end) {
                    D_800E74B8[n]++;
                } else if (D_800EA0A8[n] < end - 3) {
                    D_800EA0A8[n] = end - 3;
                }
            }
        }
    }
    return d;
}
