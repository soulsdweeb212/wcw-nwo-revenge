/* @header
 * func_800133AC
 * VRAM 0x800133AC | ROM 0x13FAC | size 0xE0
 * asm: asm/nonmatchings/main/func_800133AC.s
 */
#include "common.h"

/* Takes the next voice index from arg0's pool (decrementing the counter at
 * +0xFB/+0x140) and, when one remains, loads its cached parameters into the
 * voice fields (+0x100.. and +0x110/+0x120/+0x130/+0x138/+0x144/+0x148) and
 * recomputes +0x38. Returns the voice's id or arg1 if the pool is empty.
 * Always resets the output/pan/volume fields to their defaults. */
s32 func_800133AC(void *arg0, s32 arg1) {
    u8 count;
    u8 next;
    s32 i;
    void *p;
    void *q;
    void *r;
    void *b;
    i=*(u8 *)(arg0+0xFB)-1;
    p=arg0+i;
    count=*(u8 *)(p+0x140);
    if ((count & 0xFF)!=0xFF) {
        next=count-1;
        *(u8 *)(p+0x140)=next;
        if (!(next & 0xFF)) {*(u8 *)(arg0+0xFB)=i; i=-1;}
    }
    if (i>=0) {
        q=(void *)(i*4+(u32)arg0);
        arg1=*(s32 *)(q+0x100);
        *(s32 *)(arg0+0x4C)=*(s32 *)(q+0x110);
        *(s32 *)(arg0+0x48)=*(s32 *)(q+0x120);
        b=arg0+i;
        *(u8 *)(arg0+0xDC)=*(u8 *)(b+0x144);
        *(f32 *)(arg0+0x90)=(f32)*(u8 *)(b+0x148);
        r=(void *)(i*2+(u32)arg0);
        *(u16 *)(arg0+0xC2)=*(u16 *)(r+0x130);
        *(u16 *)(arg0+0xC4)=*(u16 *)(r+0x138);
        *(f32 *)(arg0+0x38)=*(f32 *)(arg0+0x90)* *(f32 *)(arg0+0x8C);
    }
    *(u16 *)(arg0+0xC0)=0xFFFF;
    *(u8 *)(arg0+0xEC)=0xFF; *(u8 *)(arg0+0xDE)=0xFF; *(u8 *)(arg0+0xDD)=0x40;
    *(f32 *)(arg0+0x3C)=99.9f;
    *(f32 *)(arg0+0x8C)=0.03125f;
    return arg1;
}
