/* @header
 * func_80004B34
 * VRAM 0x80004B34 | ROM 0x5734 | size 0x74
 * asm: asm/nonmatchings/main/func_80004B34.s
 */
#include "common.h"

void initializeTransformNode(void *,s8,f32,f32,f32);
/* Initializes a transform node and clears its 0x28-byte sub-record. */
#ifdef TARGET_PC
/* PC: p is a display record, whose PC layout is Nw2Descr4BA8 (common.h, 0x50 bytes, its addresses 8 bytes wide). The
 * N64 clear below (bytes 0-5 and the words at +0xC to +0x24) is exactly func_80004AFC's N64 body; at those offsets
 * the PC would clear halves of the addresses. So the PC calls func_80004AFC, which clears the same fields by name. */
void func_80004B34(void *obj, u8 *p, s8 type, f32 x, f32 y, f32 z) {
    initializeTransformNode(obj, type, x, y, z);
    func_80004AFC(p);
}
#else
void func_80004B34(void *obj,u8 *p,s8 type,f32 x,f32 y,f32 z) {
    f32 a=z; f32 b=*(volatile f32 *)&y;
    initializeTransformNode(obj,type,x,b,a);
    p[0]=0;p[1]=0;p[2]=0;p[3]=0;p[4]=0;p[5]=0;
    *(s32 *)(p+12)=0;*(s32 *)(p+16)=0;*(s32 *)(p+20)=0;*(s32 *)(p+24)=0;*(s32 *)(p+28)=0;*(s32 *)(p+32)=0;*(s32 *)(p+36)=0;
}
#endif
