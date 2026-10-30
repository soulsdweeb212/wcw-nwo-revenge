#include "common.h"

typedef struct { u8 pad[0x14]; void *f14; s32 pad18[2]; s32 f20,f24; } PartAux;
typedef struct { u16 f0; u8 pad2[0x26]; void *f28; } PartSubAux;
typedef struct { u32 f0,f4; u16 f8,fA,fC,padE; f32 f10,f14,f18,f1C; PartSubAux *f20; PartAux *f24; } PartEntry;
typedef struct { u8 pad0[0x14]; u16 *f14,*f18; u32 f1C; PartEntry *f20; u8 f24; } PartList;
typedef struct { u8 pad0[0x18]; s32 f18; u8 f1C; u8 pad1D[3]; s32 *f20; } PartDescriptor;
extern s32 D_80036F60[],D_80036FC8[],D_80037050[],D_80037078[],D_800370A0[],D_800370C8[];
s32 func_800202B0(s32,s32,s32,s32,s32);
void func_8001CEF0(void *);

/* Builds the part list for one entity/part from a descriptor.  The PartList
 * header gets two counts from the descriptor's s32 table, a zeroed u16 table
 * (f14/f18) of size f1C, and an array of PartEntry records (f20) of size f24
 * copied from that table; entries with animation data get a PartAux (f24) motion
 * block, and entries with extra data get a PartSubAux (f20) block.  Rates are
 * converted through the descriptor's f18 scale and the f64 D_8003B448.
 * func_800202B0(0,0,pool,1,size) is the pool allocator used for every block. */
void func_80018140(PartList **outList, PartDescriptor *descriptor, s32 pool) {
 PartList *list; s32 *table; u16 tableIndex; u16 i; u16 j; PartEntry *entry;
 list=(PartList*)func_800202B0(0,0,pool,1,0x2C); *outList=list;
 switch(descriptor->f1C) {case 1: table=D_80036F60;break; case 2:table=D_80036FC8;break;case 5:table=D_80037050;break;case 3:table=D_80037078;break;case 4:table=D_800370A0;break;case 6:table=descriptor->f20;break;default:table=D_800370C8;break;}
 list->f24=table[0]; list->f1C=table[1];
 list->f20=(PartEntry*)func_800202B0(0,0,pool,list->f24,0x28);
 list->f14=(u16*)func_800202B0(0,0,pool,list->f1C,2); list->f18=list->f14;
 tableIndex=2;
 for(j=0;j<list->f1C;j++) list->f14[j]=0;
 for(i=0;i<list->f24;i++) {
 entry=&list->f20[i];
 entry->f0=table[tableIndex++]; entry->f4=table[tableIndex++]; entry->fA=table[tableIndex++]; entry->f8=table[tableIndex++]; entry->fC=table[tableIndex++];
 if(table[tableIndex]) {
 entry->f10=((f32)table[tableIndex++]/1000.0f)*2.0/descriptor->f18;
 entry->f1C=((f32)table[tableIndex++]/173123.404906676)* (entry->f4-entry->f0);
 entry->f14=1.0f; entry->f18=0.0f;
 entry->f24=(PartAux*)func_800202B0(0,0,pool,1,0x34);
 entry->f24->f14=(void*)func_800202B0(0,0,pool,1,0x20);
 entry->f24->f20=0;entry->f24->f24=1;
 } else { entry->f24=0;tableIndex+=2; }
 if(table[tableIndex]) {
 entry->f20=(PartSubAux*)func_800202B0(0,0,pool,1,0x30);
 entry->f20->f28=(void*)func_800202B0(0,0,pool,1,8);
 entry->f20->f0=table[tableIndex++];func_8001CEF0(entry->f20);
 }else {entry->f20=0;tableIndex++;}
 }
}
