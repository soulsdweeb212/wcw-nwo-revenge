#include "common.h"

typedef struct {
  s8 f0;
  u8 pad[7];
  s16 f8;
  u8 padA[0x362];
  u8 f36C;
  u8 pad36D[3];
  u8 f370;
  u8 f371;
  u8 pad372[6];
  u8 f378;
  u8 pad379[2];
  u8 f37B;
  u8 f37C;
  u8 pad37D[5];
  u8 f382;
} Nw2ObjD427C;
extern s16 D_800EB680[];
extern s32 D_800EB6B8[];
s32 decodeAnimationMetadata(void *, s16);
/* Start an animation on the object: record the previous animation id per entity
 * slot, then if it actually changed, decode the new animation's metadata into
 * the object's part records, resolve the 0/0xFF sentinel blend/timer bytes to
 * the animation's default duration (f36C), reset the +4/+6 timers and store the
 * caller's mode into the per-entity mode table D_800EB6B8. */
void func_800D427C(Nw2ObjD427C *e, s16 animId, s32 mode) {
    D_800EB680[e->f0] = e->f8;
    e->f8 = animId;
    if (animId != D_800EB680[e->f0]) {
        D_800EB680[e->f0] = animId;
        decodeAnimationMetadata((u8 *)e + 0x368, e->f8);
        if (e->f370 == 0) {
            e->f370 = 1;
        }
        if (e->f370 == 0xFF) {
            e->f370 = e->f36C;
        }
        if (e->f371 == 0) {
            e->f371 = 1;
        }
        if (e->f371 == 0xFF) {
            e->f371 = e->f36C;
        }
        if (e->f37B == 0xFF) {
            e->f37B = e->f36C;
        }
        if (e->f378 == 0) {
            e->f378 = 1;
        }
        if (e->f37C == 0) {
            e->f37C = 1;
        }
        if (e->f382 == 0) {
            e->f382 = e->f36C;
        }
        *(s16 *)((u8 *)e + 6) = 0;
        *(s16 *)((u8 *)e + 4) = e->f36C;
        D_800EB6B8[e->f0] = mode;
    }
}
