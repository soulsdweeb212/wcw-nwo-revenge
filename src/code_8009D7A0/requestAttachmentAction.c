/* @header
 * requestAttachmentAction  (originally func_800AC208)
 * VRAM 0x800AC208 | ROM 0x9F6A8 | size 0x190
 * asm: asm/nonmatchings/code_8009D7A0/func_800AC208.s
 */
#include "common.h"

extern u8 *D_800FABD0,*D_800FAF58;
s8 func_800D4198(s16); void func_800AD958(s32);
/* Requests the action tied to the action object's current attachment.
 * Returns 1 (after calling func_800AD958 with the action id) when a matching
 * animation id is found, 0 otherwise. The id is read from the attachment
 * record's +0x24 table when the object is facing up (f3C >= 65) or +0x26 when
 * facing down; both compare the f3C/f58 float fields to pick the dispatch. */
s8 requestAttachmentAction(void){
 s16 id;
 if(!func_800D4198(*(s16 *)(D_800FABD0+0x12))) return 0;
 id=-1;
 if(*(s16 *)(D_800FABD0+0x24)>=65){
 if(func_800D4198(500)) id=*(u16 *)(*(u8 **)(D_800FAF58+0x364)+0x24)-1;
 }else{
 if(func_800D4198(500)) id=*(u16 *)(*(u8 **)(D_800FAF58+0x364)+0x26)-1;
 }
 if(*(f32 *)(D_800FABD0+0x3c)>*(f32 *)(D_800FABD0+0x58)){
 switch(id){case 0xb1:func_800AD958(0x38);return 1;case 0xd5:func_800AD958(0x2f);return 1;case 0xe3:func_800AD958(0x30);return 1;}
 }else{
 switch(id){case 175:func_800AD958(0x36);return 1;case 176:func_800AD958(0x37);return 1;case 177:func_800AD958(0x38);return 1;case 196:func_800AD958(0x39);return 1;case 198:func_800AD958(0x3a);return 1;case 200:func_800AD958(0x3b);return 1;case 202:func_800AD958(0x3c);return 1;case 213:func_800AD958(0x2f);return 1;case 227:func_800AD958(0x30);return 1;}
 }
 return 0;
}
