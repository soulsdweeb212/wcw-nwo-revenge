/* @header
 * func_8002BAB8
 * VRAM 0x8002BAB8 | ROM 0x2C6B8 | size 0xE0
 * asm: asm/nonmatchings/main/func_8002BAB8.s
 */
#include "common.h"

extern Nw2IdSubTable lookupSubTables[];
extern Nw2IdTableEntry D_8003A59C;
extern u8 *D_8003A594;
void buildWrestlerNameRecord(u16, s32, void *);
/* Builds 80 groups of 4 0x2A-byte name records into the D_8003A594 buffer:
 * for each group value, resolves its id by searching the first 11 lookup
 * subtables (falling back to D_8003A59C) and emits all four variants. */
void func_8002BAB8(void) {
 u8 *out=D_8003A594;
 s32 value,variant,k,j;
 Nw2IdTableEntry *e;
 for(value=0;value<80;value++) {
  for(variant=0;variant<4;) {
   for(k=0;k<11;k++) {
    for(j=0;j<lookupSubTables[k].count;j++) {
     e=lookupSubTables[k].entries[j];
     if(e->value==value) goto found;
    }
   }
   e=&D_8003A59C;
found:
   buildWrestlerNameRecord(e->id,variant++,out);
   out+=0x2A;
  }
 }
}
