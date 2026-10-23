#include "common.h"

extern Nw2IdSubTable lookupSubTables[];
extern u16 D_8003A4FC[][4];
s32 findIdSubTableIndex(s32 id) {
 s32 i,j; u32 result;
 if(id&0x1000) {
 id &= 0xFFF;
 for(i=12;i>=0;i--) {
  for(j=0;j<D_8003A4FC[i][0];j++) {
   if(lookupSubTables[i].entries[j]->id==id) {result=(i<<8)+j; goto done;}
  }
 }
 } else {
 for(i=0;i<11;i++) {
  for(j=0;j<D_8003A4FC[i][0];j++) {
   if(lookupSubTables[i].entries[j]->id==id) {result=(i<<8)+j; goto done;}
  }
 }
 }
 result=-1;
 done:
 return (result>>8)&0xF;
}
