#include "common.h"

typedef struct { u8 pad[0x14]; s16 value; u8 pad16[0xA]; u64 flags; } BF62Entity;
/* Adds arg1 to the entity's health value (+0x14) unless it is flagged 0xE0000.
 * At 100 it either clamps to 99 (flag bit 0) or sets 100 and raises 0x40000; at
 * zero or below it clamps to 0 and raises 0x20000. */
void addEntityHealthDelta(BF62Entity *arg0, s32 arg1) {
 if (!(arg0->flags & 0xE0000ULL)) {
  arg0->value += arg1;
  if (arg0->value >= 100) {
   if (arg0->flags & 1) arg0->value = 99;
   else { arg0->value = 100; arg0->flags |= 0x40000ULL; }
  }
  if (arg0->value <= 0) { arg0->value = 0; arg0->flags |= 0x20000ULL; }
 }
}
