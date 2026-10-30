/* @header
 * func_8000DFD0
 * VRAM 0x8000DFD0 | ROM 0xEBD0 | size 0xCC
 * asm: asm/nonmatchings/main/func_8000DFD0.s
 */
#include "common.h"

s32 func_8000327C(s32);
s32 func_800032A4(s16,s32,s32,s32,s32);
s16 func_8000335C(s32);
extern s16 D_80030D38[];
extern s32 D_80036738, D_800566F0[], D_80056948;

/* Initialize/attach a handle for index arg0. When arg0 > 0, look up the id at
 * D_80030D38[arg0]; if valid, ensure the handle slot D_800566F0[id] exists by creating it
 * via func_800032A4(id, 128, 128, 0, -1) whenever func_8000335C reports it is not already
 * loaded. When arg0 == 0 and D_80036738 is still unset, allocate it via func_8000327C(52)
 * and clear the 151-entry array ending at D_80056948. */
void func_8000DFD0(s16 arg0) {
    s16 id;
    s32 *handle;
    s32 *base;
    s32 *p;
    s32 i;
    if(arg0>0) {
        id=D_80030D38[arg0];
        if(id>=0) {
            base=D_800566F0;
            handle=base+id;
            if(func_8000335C(*handle)!=1) *handle=func_800032A4(id,128,128,0,-1);
        }
    } else if(!D_80036738) {
        D_80036738=func_8000327C(52);
        i=150; p=&D_80056948;
        do { *p=0; i--; p--; } while(i>=0);
    }
}
