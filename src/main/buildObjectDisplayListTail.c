/* @header
 * buildObjectDisplayListTail  (originally func_800060A4)
 * VRAM 0x800060A4 | ROM 0x6CA4 | size 0xD4
 * asm: asm/nonmatchings/main/buildObjectDisplayListTail.s
 */
#include "common.h"

#ifdef TARGET_PC
/* On PC a command is port.h's 16-byte Gfx, and o is the display record in the PC layout of Nw2TextureDisplayObj
 * (common.h), whose pointers are 8 bytes: enabled is its vertex pointer colorPtr, commands its dl, next its next. On
 * N64 enabled and next are 32-bit integers holding pointers; on PC they are pointers, which keep the whole address. */
typedef Gfx Cmd60;
typedef struct { s8 f0,f1,count,start; s32 f4,f8; void *enabled; Cmd60 *commands; void *next; } Obj60;
_Static_assert(offsetof(Obj60, enabled) == offsetof(Nw2TextureDisplayObj, colorPtr) &&
                   offsetof(Obj60, commands) == offsetof(Nw2TextureDisplayObj, dl) &&
                   offsetof(Obj60, next) == offsetof(Nw2TextureDisplayObj, next),
               "Obj60 must follow the display record's PC layout");
#else
typedef struct { u32 w0,w1; } Cmd60;
typedef struct { s8 f0,f1,count,start; s32 f4,f8,enabled; Cmd60 *commands; u32 next; } Obj60;
#endif
void buildObjectDisplayListTail(Obj60 *o) {
    Cmd60 *p=o->commands;
    if(o->enabled && o->count<9) { Cmd60 *c=p++; c->w0=0x03000000|((o->start*2)&0xFFFF); c->w1=((o->start+o->count)*2)&0xFFFF; }
    { Cmd60 *c=p++; c->w0=0xE200001C; c->w1=0x0F0A4000; }
    { Cmd60 *c=p++; c->w0=0xFC45FE8B; c->w1=0xFFFFF9FC; }
#ifdef TARGET_PC
    /* The branch target goes into the command as the whole pointer (port.h's DL_ADDR). */
    if(o->next) { Cmd60 *c=p++; c->w0=0xDE010000; c->w1=DL_ADDR(o->next); }
#else
    if(o->next) { Cmd60 *c=p++; c->w0=0xDE010000; c->w1=o->next-0x80000000; }
#endif
    else { Cmd60 *c=p++; c->w0=0xDF000000; c->w1=0; }
}
