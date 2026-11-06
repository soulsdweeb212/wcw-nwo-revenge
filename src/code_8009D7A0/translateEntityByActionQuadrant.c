/* @header
 * translateEntityByActionQuadrant  (originally func_800A7968)
 * VRAM 0x800A7968 | ROM 0x9AE08 | size 0x1D0
 * asm: asm/nonmatchings/code_8009D7A0/translateEntityByActionQuadrant.s
 */
#include "common.h"

/* Move w along the X or Z axis by the per-frame distance D_800E32AC[animFrame] (animations 0xEF5 / 0xEF7) or
 * D_800E32C4[animFrame] (0xEF6 / 0xEFA), in the direction given by dirIndex (0 +Z, 1 +X, 2 -Z, 3 -X). */
extern f32 D_800E32AC[],D_800E32C4[];
void translateEntityXZ(void *,void *);
void translateEntityByActionQuadrant(Wrestler *w) {
    f32 offset[3];
    switch(w->animId) {
    case 0xEF5: case 0xEF7:
        switch(w->dirIndex) {
        case 0: offset[0]=0.0f; offset[2]=D_800E32AC[w->animFrame]; break;
        case 1: offset[0]=D_800E32AC[w->animFrame]; offset[2]=0.0f; break;
        case 2: offset[0]=0.0f; offset[2]=-D_800E32AC[w->animFrame]; break;
        case 3: offset[0]=-D_800E32AC[w->animFrame]; offset[2]=0.0f; break;
        } break;
    case 0xEF6: case 0xEFA:
        switch(w->dirIndex) {
        case 0: offset[0]=0.0f; offset[2]=D_800E32C4[w->animFrame]; break;
        case 1: offset[0]=D_800E32C4[w->animFrame]; offset[2]=0.0f; break;
        case 2: offset[0]=0.0f; offset[2]=-D_800E32C4[w->animFrame]; break;
        case 3: offset[0]=-D_800E32C4[w->animFrame]; offset[2]=0.0f; break;
        } break;
    }
    translateEntityXZ(w,offset);
}
