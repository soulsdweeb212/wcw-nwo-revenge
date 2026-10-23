#include "common.h"

typedef struct {
    u8 id;
    u8 pad1[0x1F];
    u64 flags;
    u8 pad28[0x4];
    u32 f2C;
    u8 pad30[0x28];
    s32 f58;
    u8 pad5C[0x2F5];
    u8 f351;
    u8 f352;
    u8 f353;
    u8 pad354[0xE];
    u8 f362;
    u8 f363;
} Entity;

void func_800A6CDC(void *, s32);
s32 func_800D3684(s32, s32);

/* Links three entities into a facing group: orders s0/s1 by heading (the one
 * facing "less" gets the 0x4000 flag, the other 0x8000), starts animations
 * 0x76/0x77/0x78, raises their group flags, and cross-references each entity's
 * id into the others' f351/f352/f353 slots. */
void setupEntityFacingGroup(Entity *s0, Entity *s1, Entity *s2, s32 s3) {
    register int tmp;
    if (func_800D3684(s0->f58, s1->f58) < 0) {
        s0->f2C |= 0x4000;
        s1->f2C |= 0x8000;
    } else {
        s0->f2C |= 0x8000;
        s1->f2C |= 0x4000;
    }
    func_800A6CDC(s0, 0x76);
    func_800A6CDC(s1, 0x77);
    func_800A6CDC(s2, 0x78);
    s0->flags |= 0x1060000000ULL;
    s1->flags |= 0x1020000000ULL;
    s2->flags |= 0x1020000000ULL;
    s0->f2C |= (s1->f2C & 2) | (s3 & 0xFFFF);
    s0->f362 = s1->id;
    s0->f363 = s2->id;
    s0->f353 = s2->id;
    s0->f352 = s1->id;
    tmp = s1->f2C & 0xC040;
    s1->f353 = s2->id;
    s1->f352 = s0->id;
    s1->f2C = tmp;
    s1->f2C = tmp | (s0->f2C & 0x3800);
    s2->f353 = s0->id;
    s2->f351 = s0->id;
    s2->f352 = s1->id;
}
