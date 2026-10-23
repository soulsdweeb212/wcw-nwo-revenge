#include "common.h"

void func_80001930(void *);
typedef struct { f32 x, y, z; } Nw2Vec3;
extern f32 D_80048270, D_80048274, D_80048278, D_8004827C, D_80048280;

/* Stores the face-shading parameters (diffuse scale, ambient term and light
 * direction vector) into the globals consumed by the shading pass in
 * func_80001930, then runs that pass over the node tree. */
void func_800018C4(void *node, f32 *lightDir, u8 scale, u8 ambient) {
    Nw2Vec3 *dir = (Nw2Vec3 *)lightDir;
    f32 x = dir->x, y = dir->y, z = dir->z;
    D_80048270 = scale;
    D_80048274 = ambient;
    D_80048278 = x;
    D_8004827C = y;
    D_80048280 = z;
    func_80001930(node);
}
