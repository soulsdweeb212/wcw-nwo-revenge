/* @header
 * decodeAnimationMetadata  (originally func_800086A4)
 * VRAM 0x800086A4 | ROM 0x92A4 | size 0x138
 * asm: asm/nonmatchings/main/decodeAnimationMetadata.s
 */
#include "common.h"

extern u16 D_8006A2B0[][2];
extern u16 D_8006A2B2[][2];
typedef struct { u8 b[36]; } AnimSource;
extern AnimSource *D_8007BD38;
typedef struct { s32 offset; u8 b[24]; } AnimDest;
/* Decodes the packed animation metadata for animation id arg1 (>= 0xE39) into
 * the destination record: the source offset from the lookup table plus the
 * unpacked bytes copied from the packed 36-byte source record. */
void decodeAnimationMetadata(void *arg0, s16 arg1) {
 AnimDest *d=arg0; AnimSource *p; u8 *s; s32 i;
 if(arg1>=0xE39) {
 i=arg1-0xE39; p=D_8007BD38;
 d->offset=(D_8006A2B0[i][0]&0x3FF)*4;
 d->b[0]=D_8006A2B2[i][0];
 d->b[3]=D_8006A2B0[i][0]>>10;
 s=p[arg1-0xE39].b;
 d->b[1]=s[1]>>7; d->b[2]=s[0]&15;
 d->b[4]=s[3];d->b[5]=s[4];d->b[6]=s[18];d->b[7]=s[19];
 d->b[8]=s[5];d->b[9]=s[6];d->b[10]=s[7];d->b[11]=s[8];
 d->b[12]=s[9];d->b[13]=s[10];d->b[14]=s[11];d->b[15]=s[12];
 d->b[16]=s[17];d->b[17]=s[16];d->b[18]=s[2];d->b[19]=s[0]>>4;
 d->b[20]=s[13];d->b[21]=s[14];d->b[22]=s[15];
 }
}
