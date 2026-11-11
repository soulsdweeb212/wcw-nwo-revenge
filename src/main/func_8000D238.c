/* @header
 * func_8000D238
 * VRAM 0x8000D238 | ROM 0xDE38 | size 0xEC
 * asm: asm/nonmatchings/main/func_8000D238.s
 */
#include "common.h"

typedef struct {u8 value; u8 pad[0xDB];} D238Entry;
#ifndef TARGET_PC /* on PC these labels have no symbol: the PC code below reads them through their bases */
extern D238Entry D_800651B8[][23];
extern D238Entry D_800517E8[][23];
extern u8 D_800662E8[];
#endif
extern u8 D_80030894[];
#ifndef TARGET_PC /* on PC this label has no symbol: the PC code below reads it through its base */
extern u8 D_800662D0[];
#endif
/* Resets entity arg0's 23 part bytes to arg1, clears its 0x80 status byte when
 * the entity's D_800662D0 word is zero, and copies the parts whose D_80030894
 * flag is set into D_800517E8 (others forced to 0x80). */
#ifdef TARGET_PC
/* PC: the four labels are fields of the 0xDC-byte objects of D_800651A0 and D_800517D0 (23 objects, 0x13C4 bytes, per
 * entity), and no label has a symbol on PC, so this reads each one through its base at its N64 offset:
 * D_800651B8 = D_800651A0 + 0x18 (each object's draw group), D_800517E8 = D_800517D0 + 0x18 (the same in the second
 * array), D_800662D0 = D_800651A0 + 0x1130 (object 20's first word, its parent's handle, 0 for none) and
 * D_800662E8 = D_800651A0 + 0x1148 (object 20's draw group). The objects keep their N64 layout on PC (Nw2SceneObj,
 * common.h), so the strides are the N64's: 0xDC per object, 0x13C4 per entity. */
extern u8 D_800651A0[], D_800517D0[];
void func_8000D238(s16 arg0, s8 arg1) {
    u32 i;
    for(i=1;i<23;i++) D_800651A0[0x18+arg0*0x13C4+i*0xDC]=arg1;
    if(*(u32 *)(D_800651A0+0x1130+arg0*0x13C4)==0) D_800651A0[0x1148+arg0*0x13C4]=0x80;
    for(i=1;i<20;i++) {
        if(D_80030894[i]) D_800517D0[0x18+arg0*0x13C4+i*0xDC]=D_800651A0[0x18+arg0*0x13C4+i*0xDC];
        else D_800517D0[0x18+arg0*0x13C4+i*0xDC]=0x80;
    }
}
#else
void func_8000D238(s16 arg0, s8 arg1) {
    u32 i;
    for(i=1;i<23;i++) D_800651B8[arg0][i].value=arg1;
    if(*(s32 *)(D_800662D0+arg0*0x13C4)==0) D_800662E8[arg0*0x13C4]=0x80;
    for(i=1;i<20;i++) {
        if(D_80030894[i]) D_800517E8[arg0][i].value=D_800651B8[arg0][i].value;
        else D_800517E8[arg0][i].value=0x80;
    }
}
#endif
