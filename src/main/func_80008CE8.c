#include "common.h"

typedef struct {
    s16 A8, AA, AC, AE;
    s32 B0;
    u8 padC[0xC];
    s16 C0, C2;
    f32 mtx[16];
    u8 pad5C[0xA0];
} Rec8CE8;

typedef struct {
    f32 f0, f4, f8, fC, f10, f14;
    u8 pad18[0x30];
    f32 f48, f4C, f50, f54, f58, f5C, f60, f64, f68, f6C, f70, f74, f78;
} Bone8CE8;

typedef struct {
    u8 pad0[0x5C];
    f32 m[16];
} Obj8CE8;

typedef struct {
    Obj8CE8 *obj;
    u8 pad4[0x18];
    f32 m1C[16];
    f32 m5C[16];
    u8 pad9C[0x40];
} Node8CE8;

extern f64 D_8003B138;
extern f64 D_8003B140;
extern s32 D_800485A0[];
extern Node8CE8 D_800651A0[][23];
extern s16 D_800669CE[][2];
extern Rec8CE8 D_800706A8[];
extern Bone8CE8 D_80070C40[][23];

void func_8000A310(s16);
void func_8000A3DC(s16, s32);
void func_8000AD00(s16, s16);
void func_8000B2B8(s16, s16);
void func_80009D98(s16, s16, s8);
void initializeResourceStream(s16, s16);
void updateBodyPartTransforms(s16);
void func_80007E14(f32 *, f32);
void func_80007E04(f32 *, f32, f32, f32);
void func_8001B3EC(f32 *, f32, f32, f32, f32 *, f32 *, f32 *);
void func_80001DC4(void *);
void nw2Mat4Mul(f32 *, f32 *, f32 *);
void multiplyMatrix4x4(f32 *, f32 *, f32 *);

void func_80008CE8(s16 entity, s16 anim, s16 frame, f32 *pos, f32 *vec, u8 flags) {
    f32 scratch[16];
    f32 old[3];
    f32 f0;
    s16 loaded;
    s16 updated;
    u32 i;
    Node8CE8 *nd;
    Bone8CE8 *b;
    f32 *t;
    Bone8CE8 *b2;

    loaded = 0;
    f0 = -(((f32)*(s32 *)&pos[3] + 2048.0f) * D_8003B138);
    updated = 0;
    if (anim != D_800706A8[entity].C0) {
        D_800706A8[entity].C2 = -1;
        frame = 0;
    }
    if (frame == 0 && D_800706A8[entity].C2 != 0) {
        D_800706A8[entity].AA = (anim == D_800706A8[entity].C0);
        func_8000B2B8(entity, anim);
        D_800706A8[entity].C0 = -1;
    }
    if (anim != D_800706A8[entity].C0) {
        if (D_800706A8[entity].AA != 0 && D_800706A8[entity].AE == 0) {
            D_800706A8[entity].AC = anim;
            D_800706A8[entity].B0 = D_800485A0[entity];
        } else {
            initializeResourceStream(entity, anim);
        }
        D_800706A8[entity].C0 = anim;
        if (D_800706A8[entity].A8 == 0) {
            old[0] = D_80070C40[entity][1].f54;
            old[2] = D_80070C40[entity][1].f5C;
            loaded = 1;
        }
    }
    if (frame != D_800706A8[entity].C2) {
        s32 n, m;
        D_800706A8[entity].C2 = frame;
        n = D_800669CE[anim][0];
        m = n << 16;
        if (frame < n) {
            if (!(frame & 1) || frame == (m >> 16) - 1) {
                func_8000A310(entity);
            } else {
                func_8000A3DC(entity, 0);
            }
            if (flags & 2) {
                if (D_800706A8[entity].A8 == 0 && frame < 5 && D_800706A8[entity].AA == 0) {
                    func_80009D98(entity, frame, flags);
                }
            }
            if (vec != 0) {
                D_80070C40[entity][5].f0 = vec[0] + D_8003B140;
                D_80070C40[entity][5].f4 = vec[1];
                D_80070C40[entity][5].f8 = 180.0f;
            }
            updateBodyPartTransforms(entity);
            updated = 1;
        }
    }
    if ((flags & 1) && loaded) {
        Obj8CE8 *o;
        nd = &D_800651A0[entity][1];
        b = D_80070C40[0] + 1;
        o = nd->obj;
        b += entity * 23;
        t = &b->f54;
        func_80007E14(o->m, f0);
        func_80007E04(nd->obj->m, D_80070C40[entity][0].fC, D_80070C40[entity][0].f10, D_80070C40[entity][0].f14);
        nw2Mat4Mul(D_800706A8[entity].mtx, nd->obj->m, nd->obj->m);
        multiplyMatrix4x4(nd->m1C, nd->obj->m, nd->m5C);
        func_8001B3EC(nd->m5C, b->f48, b->f4C, b->f50, &t[0], &t[1], &t[2]);
        t[0] = -t[0];
        pos[0] += old[0] - t[0];
        pos[2] += old[2] - t[2];
    }
    D_80070C40[entity][0].fC = -pos[0];
    D_80070C40[entity][0].f10 = pos[1];
    D_80070C40[entity][0].f14 = pos[2];
    func_80007E14(scratch, f0);
    func_80007E04(scratch, D_80070C40[entity][0].fC, D_80070C40[entity][0].f10, D_80070C40[entity][0].f14);
    multiplyMatrix4x4(D_800706A8[entity].mtx, scratch, D_800651A0[entity][0].m1C);
    func_80001DC4(D_800651A0[entity]);
    D_80070C40[entity][0].f78 = f0;
    for (i = 1; i < 23; i++) {
        if (i != 20) {
            Node8CE8 *n0 = D_800651A0[0] + i;
            D_80070C40[entity][i].f78 = D_80070C40[entity][i].f4 + f0;
            b2 = (Bone8CE8 *)((u8 *)D_80070C40[entity] + i * sizeof(Bone8CE8));
            nd = (Node8CE8 *)((u32)(entity * sizeof(D_800651A0[0])) + (u32)n0);
            t = &b2->f54;
            func_8001B3EC(nd->m5C, b2->f48, b2->f4C, b2->f50, t, &b2->f58, &b2->f5C);
            *t = -*t;
            t = &b2->f6C;
            func_8001B3EC(nd->m5C, b2->f60, b2->f64, b2->f68, t, &b2->f70, &b2->f74);
            *t = -*t;
        }
    }
    if (updated) {
        func_8000AD00(entity, frame + 1);
    }
    if (D_800706A8[entity].A8 != 0) {
        D_800706A8[entity].A8 = 0;
    }
}
