/* @header
 * func_800B5AE0
 * VRAM 0x800B5AE0 | ROM 0x62250 | size 0x240
 * asm: asm/nonmatchings/code_80090000/func_800B5AE0.s
 */
#include "common.h"


typedef struct { f32 v; s16 t; } K;
typedef struct { K *k; s32 n; } S;
void bzero(void *, s32);

void func_800B5AE0(S *s, f64 *out) {
    s32 h[34];
    f64 d[33];
    K *k;
    s32 n, m, i;

    bzero(out, 0x100);
    n = s->n;
    k = s->k;
    out[0] = 0.0;
    m = n - 1;
    out[m - 1] = 0.0;
    for (i = 0; i < m - 1; i++) {
        h[i] = k[i + 1].t - k[i].t;
        d[i + 1] = (k[i + 1].v - k[i].v) / h[i];
    }
    out[1] = d[2] - d[1] - h[0] * out[0];
    d[1] = (k[2].t - k[0].t) * 2;
    for (i = 1; i < m - 2; i++) {
        f32 w = h[i] / d[i];
        out[i + 1] = d[i + 2] - d[i + 1] - out[i] * w;
        d[i + 1] = (f32)((k[i + 2].t - k[i].t) * 2) - h[i] * w;
    }
    out[m - 2] -= h[m - 2] * out[m - 1];
    i = m - 2;
    if (i > 0) {
        /* Placeholder: the ROM adds the scaled index first (addu s1,v0,s1) into out's own
           register, which a plain `out += i` (addu s1,s1,v0) does not give. */
        f64 *p = (f64 *)(i * 8 + (s32)out);
        out = p;
        do {
            *out = (*out - h[i] * out[1]) / d[i];
            out--;
            i--;
        } while (i > 0);
    }
}
