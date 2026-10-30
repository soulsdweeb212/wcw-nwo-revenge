/* @header
 * buildObjectDisplayListTail  (originally func_800060A4)
 * VRAM 0x800060A4 | ROM 0x6CA4 | size 0xD4
 * asm: asm/nonmatchings/main/buildObjectDisplayListTail.s
 */
#include "common.h"

typedef struct { u32 w0,w1; } Cmd60;
typedef struct { s8 f0,f1,count,start; s32 f4,f8,enabled; Cmd60 *commands; u32 next; } Obj60;
void buildObjectDisplayListTail(Obj60 *o) {
 Cmd60 *p=o->commands;
 if(o->enabled && o->count<9) { Cmd60 *c=p++; c->w0=0x03000000|((o->start*2)&0xFFFF); c->w1=((o->start+o->count)*2)&0xFFFF; }
 { Cmd60 *c=p++; c->w0=0xE200001C; c->w1=0x0F0A4000; }
 { Cmd60 *c=p++; c->w0=0xFC45FE8B; c->w1=0xFFFFF9FC; }
 if(o->next) { Cmd60 *c=p++; c->w0=0xDE010000; c->w1=o->next-0x80000000; }
 else { Cmd60 *c=p++; c->w0=0xDF000000; c->w1=0; }
}
