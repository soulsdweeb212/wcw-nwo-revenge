/* @header
 * copyPartCoordinateFields  (originally func_800D49A0)
 * VRAM 0x800D49A0 | ROM 0xC7E40 | size 0x130
 * asm: asm/nonmatchings/code_800BBA00/copyPartCoordinateFields.s
 */
#include "common.h"

extern f32 D_80070C94, D_80070C98, D_80070C9C, D_80070CAC, D_80070CB4;
#define AT(n,o) (*(volatile f32 *)((u8 *)&n+(o)))
/* Copies two points of joints 1..19 of all four wrestlers from the source array at D_80070C94 (0x7C bytes per
 * joint, 0xB24 per slot): the floats at +0x0/+0x4/+0x8 go to jointA[j].x/.y/.z and those at +0x18/+0x1C/+0x20 to
 * jointB[j].x/.y/.z of each wrestler record (dst = j * 0x10 + i * 0x3B0). */
void copyPartCoordinateFields(void) {
    s16 i,j;
    s32 dst,src;
    for(i=0;i<4;i++) {
        for(j=1;j<20;j++) {
#ifdef TARGET_PC
            /* PC: a wrestler record is sizeof(Wrestler) bytes (0x3B8), not the N64's 0x3B0, so the byte offset of slot n is n * sizeof(Wrestler). */
            dst=j*0x10+i*(s32)sizeof(Wrestler);
#else
            dst=j*0x10+i*0x3B0;
#endif
            src=j*0x7C+i*0xB24;
            AT(D_800F9D10[0].jointA[0].x,dst)=AT(D_80070C94,src);
            AT(D_800F9D10[0].jointA[0].z,dst)=AT(D_80070C9C,src);
            AT(D_800F9D10[0].jointA[0].y,dst)=AT(D_80070C98,src);
            AT(D_800F9D10[0].jointB[0].x,dst)=AT(D_80070CAC,src);
            AT(D_800F9D10[0].jointB[0].z,dst)=AT(D_80070CB4,src);
            AT(D_800F9D10[0].jointB[0].y,dst)=AT(D_80070CAC,src+4);
        }
    }
}
