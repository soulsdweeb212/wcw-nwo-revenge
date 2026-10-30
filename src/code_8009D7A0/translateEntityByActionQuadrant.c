/* @header
 * translateEntityByActionQuadrant  (originally func_800A7968)
 * VRAM 0x800A7968 | ROM 0x9AE08 | size 0x1D0
 * asm: asm/nonmatchings/code_8009D7A0/func_800A7968.s
 */
#include "common.h"

/* Move an entity along the X/Z axis by a distance selected from one of two
 * speed tables (D_800E32AC / D_800E32C4) based on its action id and the
 * facing quadrant in +0x3E. */
extern f32 D_800E32AC[],D_800E32C4[];
void translateEntityXZ(void *,void *);
void translateEntityByActionQuadrant(void *self) {
 f32 offset[3];
 switch(*(s16 *)((u8 *)self+8)) {
 case 0xEF5: case 0xEF7:
 switch(*(s16 *)((u8 *)self+0x3E)) {
 case 0: offset[0]=0.0f; offset[2]=D_800E32AC[*(s16 *)((u8 *)self+6)]; break;
 case 1: offset[0]=D_800E32AC[*(s16 *)((u8 *)self+6)]; offset[2]=0.0f; break;
 case 2: offset[0]=0.0f; offset[2]=-D_800E32AC[*(s16 *)((u8 *)self+6)]; break;
 case 3: offset[0]=-D_800E32AC[*(s16 *)((u8 *)self+6)]; offset[2]=0.0f; break;
 } break;
 case 0xEF6: case 0xEFA:
 switch(*(s16 *)((u8 *)self+0x3E)) {
 case 0: offset[0]=0.0f; offset[2]=D_800E32C4[*(s16 *)((u8 *)self+6)]; break;
 case 1: offset[0]=D_800E32C4[*(s16 *)((u8 *)self+6)]; offset[2]=0.0f; break;
 case 2: offset[0]=0.0f; offset[2]=-D_800E32C4[*(s16 *)((u8 *)self+6)]; break;
 case 3: offset[0]=-D_800E32C4[*(s16 *)((u8 *)self+6)]; offset[2]=0.0f; break;
 } break;
 }
 translateEntityXZ(self,offset);
}
