/* @header
 * func_800D7128
 * VRAM 0x800D7128 | ROM 0xCA5C8 | size 0x204
 * asm: asm/nonmatchings/code_800BBA00/func_800D7128.s
 */
#include "common.h"

extern f64 D_800E6D80,D_800E6D88,D_800E6D90;
extern f32 D_800E3E20[],D_800F9800[]; extern s32 D_800F97F0[]; extern s8 D_800FADB8;
f32 func_800D3890(void *,void *,void *); s32 func_800D35B0(s32,s32); s32 func_800D3E40(void *,void *,s32,void *);
/* Builds the three 16-byte points of the quadratic spline that moves self
 * (the wrestler being updated) toward target, using opp's root position
 * (callers pass the opponent and the current wrestler). With func_800D3890
 * (XZ distance and heading) and func_800D3E40 (offset a point by a distance
 * along a heading) it writes the middle point at out+0x10 (from opp, on the
 * bisector of the headings to self and to target, at D_800E6D80 times the
 * summed distances), the start point at out+0x00 (from self) and the end point
 * at out+0x20 (from target). The total length is scaled by D_800E3E20[turn /
 * 113] and D_800E6D88; the slot's spline parameter D_800F97F0 is reset to 0
 * and its step D_800F9800 set to D_800E6D90 / len. Returns len + D_800E6D90
 * as an integer. */
s16 func_800D7128(Wrestler *opp, Wrestler *self, void *target, u8 *out) {
    Nw2DirectionResult d; f32 dist; s32 ang; s32 idx; f32 len;
    void *pa=&opp->x; void *pb=&self->x;
    func_800D3890(pa,pb,&d);
    dist=d.y; ang=d.angle;
    func_800D3890(pa,target,&d);
    d.z=(dist+d.y)*D_800E6D80; d.x=0;
    ang=func_800D3684(ang,d.angle);
    func_800D3E40(pa,&d,func_800D35B0(d.angle,ang/2),out+0x10);
    pa=out+0x10;
    func_800D3890(pa,pb,&d);
    dist=d.y;
    ang=func_800D35B0(d.angle,0x800);
    d.x=0; d.z=d.y;
    func_800D3E40(pb,&d,d.angle,out);
    func_800D3890(pa,target,&d);
    dist+=d.y;
    idx=func_800D3550(func_800D3684(ang,d.angle))/113;
    d.x=0; d.z=d.y;
    func_800D3E40(target,&d,d.angle,out+0x20);
    len=dist*D_800E3E20[(s16)idx]*D_800E6D88;
    D_800F97F0[D_800FADB8]=0;
    D_800F9800[D_800FADB8]=D_800E6D90/len;
    return (s32)(len+D_800E6D90);
}
