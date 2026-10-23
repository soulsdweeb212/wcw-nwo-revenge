#include "common.h"

typedef struct E88Node E88Node;
struct E88Node { E88Node *next; s32 pad4; s32 (*callback)(E88Node *, s32, void *); };
typedef struct { E88Node *child; u8 pad4[0x16]; s16 state; u8 pad1C[0x1C]; s32 active; E88Node *head; E88Node *tail; s32 pad44; s32 stopped; } E88Object;
s32 func_8001E88C(E88Object *arg0, s32 arg1, E88Node *arg2) {
 E88Object *o = arg0;
 switch(arg1) {
 case 1: arg0->child=arg2; break;
 case 3:
  if(arg0->tail) arg0->tail->next=arg2;
  else arg0->head=arg2;
  o->tail=arg2; break;
 case 4:
  arg0->active=1; arg0->stopped=0; arg0->state=1;
  if(arg0->child) arg0->child->callback(arg0->child,4,arg2);
  break;
 case 9:
  arg0->stopped=1;
  if(arg0->child) arg0->child->callback(arg0->child,9,arg2);
  break;
 default:
  if(arg0->child) arg0->child->callback(arg0->child,arg1,arg2);
  break;
 }
 return 0;
}
