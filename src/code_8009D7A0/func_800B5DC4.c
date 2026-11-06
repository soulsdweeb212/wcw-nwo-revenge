/* @header
 * func_800B5DC4
 * VRAM 0x800B5DC4 | ROM 0xA9264 | size 0x160
 * asm: asm/nonmatchings/code_8009D7A0/func_800B5DC4.s
 */
#include "common.h"

extern f64 D_800E54E0,D_800E54E8,D_800E54F0;
void translateEntityXZ(Wrestler *,f32 *);
/* Distance of w's pelvis (jointA[1]) toward the side dirIndex: jointA[1].z for 0, .x for 1, -z for 2, -x for 3.
 * mode 0: returns 1 when D_800E54E0 <= pos < D_800E54E8 (130..180). Nonzero mode: when pos >= D_800E54F0 (180),
 * moves w and its joints back along that axis so pos is 180 (translateEntityXZ) and returns 1. Otherwise 0. */
s8 func_800B5DC4(Wrestler *w,s16 mode) {
    f32 vec[3];
    f32 pos;
    switch(w->dirIndex) {
    case 0:pos=w->jointA[1].z;break;
    case 1:pos=w->jointA[1].x;break;
    case 2:pos=-w->jointA[1].z;break;
    case 3:pos=-w->jointA[1].x;break;
    }
    if(mode==0) {
        if(D_800E54E0<=pos && pos<D_800E54E8)return 1;
    } else if(D_800E54F0<=pos) {
        vec[0]=0;vec[2]=0;
        switch(w->dirIndex) {
        case 0:vec[2]=D_800E54F0-pos;break;
        case 1:vec[0]=D_800E54F0-pos;break;
        case 2:vec[2]=pos-D_800E54F0;break;
        case 3:vec[0]=pos-D_800E54F0;break;
        }
        translateEntityXZ(w,vec);
        return 1;
    }
    return 0;
}
