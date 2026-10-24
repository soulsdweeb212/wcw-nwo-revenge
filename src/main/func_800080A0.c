#include "common.h"

s64 __divdi3(s64, s64);
f32 signed64ToFloatTrunc(s64);

typedef struct {
    s16 x, y, z;
    s16 pad[5];
} Vtx80A0;

void func_800080A0(u8 *entity, f32 *avg, f32 *maxOut, f32 *minOut)
{
    s64 sx, sy, sz;
    s64 maxX, minX, maxY, minY, maxZ, minZ;
    Vtx80A0 *v;
    u32 count;
    u32 i;

    sx = 0;
    sy = 0;
    sz = 0;
    count = (s8)entity[0x1B];
    v = *(Vtx80A0 **)(entity + 0xC);
    if (count != 0) {
        maxX = minX = v[0].x;
        maxY = minY = v[0].y;
        maxZ = minZ = v[0].z;
        for (i = 0; i < count; i++) {
            sx += v[i].x;
            sy += v[i].y;
            sz += v[i].z;
            if (v[i].x > maxX) maxX = v[i].x;
            if (v[i].x < minX) minX = v[i].x;
            if (v[i].y > maxY) maxY = v[i].y;
            if (v[i].y < minY) minY = v[i].y;
            if (v[i].z > maxY) maxZ = v[i].z;
            if (v[i].z < minY) minZ = v[i].z;
        }
        avg[0] = signed64ToFloatTrunc(sx / count);
        avg[1] = signed64ToFloatTrunc(sy / count);
        avg[2] = signed64ToFloatTrunc(sz / count);
        maxOut[0] = signed64ToFloatTrunc(maxX);
        maxOut[1] = signed64ToFloatTrunc(maxY);
        maxOut[2] = signed64ToFloatTrunc(maxZ);
        minOut[0] = signed64ToFloatTrunc(minX);
        minOut[1] = signed64ToFloatTrunc(minY);
        minOut[2] = signed64ToFloatTrunc(minZ);
    }
}
