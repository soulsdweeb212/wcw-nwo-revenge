#include "common.h"

typedef struct {u8 value; u8 pad[0xDB];} D238Entry;
extern D238Entry D_800651B8[][23];
extern D238Entry D_800517E8[][23];
extern u8 D_800662E8[];
extern u8 D_80030894[];
extern u8 D_800662D0[];
/* Resets entity arg0's 23 part bytes to arg1, clears its 0x80 status byte when
 * the entity's D_800662D0 word is zero, and copies the parts whose D_80030894
 * flag is set into D_800517E8 (others forced to 0x80). */
void func_8000D238(s16 arg0, s8 arg1) {
 u32 i;
 for(i=1;i<23;i++) D_800651B8[arg0][i].value=arg1;
 if(*(s32 *)(D_800662D0+arg0*0x13C4)==0) D_800662E8[arg0*0x13C4]=0x80;
 for(i=1;i<20;i++) {
  if(D_80030894[i]) D_800517E8[arg0][i].value=D_800651B8[arg0][i].value;
  else D_800517E8[arg0][i].value=0x80;
 }
}
