/* @header
 * func_800B4B3C
 * VRAM 0x800B4B3C | ROM 0xA7FDC | size 0x124
 * asm: asm/nonmatchings/code_8009D7A0/func_800B4B3C.s
 */
#include "common.h"

extern s32 D_800E3CA0[];
extern f64 D_800E5490,D_800E5498,D_800E54A0;
/* Tests whether wrestler w (only when WR_FLAG_IN_RING) has its pelvis (jointA[1]) more than 150 units out toward
 * the side dirIndex: side 0 jointA[1].z > 150, 1 .x > 150, 2 .z < -150, 3 .x < -150 (D_800E5490/98/A0). When it
 * is, returns 1 if heading is within 0x3C7 of D_800E3CA0[dirIndex] (0x800, -0x400, 0, 0x400: facing the ring
 * centre from that side), else 0. */
s32 func_800B4B3C(Wrestler *w) {
    s32 outside, result;
    if(w->flags&WR_FLAG_IN_RING) {
        outside=0;
        switch(w->dirIndex) {
        case 0: if(w->jointA[1].z>D_800E5490) outside=1; result=outside; break;
        case 1: if(w->jointA[1].x>D_800E5498) outside=1; result=outside; break;
        case 2: if(w->jointA[1].z<D_800E54A0) outside=1; result=outside; break;
        case 3: if(w->jointA[1].x<D_800E54A0) outside=1; result=outside; break;
        default: result=outside; break;
        }
        if(result) {
            if(func_800D3550(func_800D3684(D_800E3CA0[w->dirIndex],w->heading))<0x3C7) return 1;
        }
    }
    return 0;
}
