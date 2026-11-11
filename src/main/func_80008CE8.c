/* @header
 * func_80008CE8
 * VRAM 0x80008CE8 | ROM 0x98E8 | size 0x784
 * asm: asm/nonmatchings/main/func_80008CE8.s
 */
#include "common.h"

#ifndef TARGET_PC /* on PC the stream record is Nw2AnimStream (common.h), read by field name */
typedef struct {
    s16 A8, AA, AC, AE;
    s32 B0;
    u8 padC[0xC];
    s16 C0, C2;
    f32 mtx[16];
    u8 pad5C[0xA0];
} Rec8CE8;
#endif

typedef struct {
    f32 f0, f4, f8, fC, f10, f14;
    u8 pad18[0x30];
    f32 f48, f4C, f50, f54, f58, f5C, f60, f64, f68, f6C, f70, f74, f78;
} Bone8CE8;

typedef struct {
    u8 pad0[0x5C];
    f32 m[16];
} Obj8CE8;

#ifdef TARGET_PC
/* PC: D_800651A0 holds the game's 0xDC-byte objects (Nw2SceneObj, common.h), which keep their N64 layout on PC, so
 * this view keeps it too: obj, the object's parent (+0x0), is a 4-byte handle (port.h's PTR_TO_SLOT) that the code
 * turns back into the address with SLOT_TO_PTR; m1C and m5C are the object's local and world matrices, and Obj8CE8's
 * m the parent's world matrix. The asserts check both views against Nw2SceneObj. */
typedef struct {
    u32 obj;
    u8 pad4[0x18];
    f32 m1C[16];
    f32 m5C[16];
    u8 pad9C[0x40];
} Node8CE8;
_Static_assert(offsetof(Node8CE8, obj) == offsetof(Nw2SceneObj, parent) &&
                   offsetof(Node8CE8, m1C) == offsetof(Nw2SceneObj, local) &&
                   offsetof(Node8CE8, m5C) == offsetof(Nw2SceneObj, world) && sizeof(Node8CE8) == sizeof(Nw2SceneObj),
               "Node8CE8 must follow Nw2SceneObj");
_Static_assert(offsetof(Obj8CE8, m) == offsetof(Nw2SceneObj, world), "Obj8CE8's m must be Nw2SceneObj's world");
#else
typedef struct {
    Obj8CE8 *obj;
    u8 pad4[0x18];
    f32 m1C[16];
    f32 m5C[16];
    u8 pad9C[0x40];
} Node8CE8;
#endif

extern f64 D_8003B138;
extern f64 D_8003B140;
#ifndef TARGET_PC /* on PC, port_decls.h declares D_800485A0 */
extern s32 D_800485A0[];
#endif
extern Node8CE8 D_800651A0[][23];
#ifdef TARGET_PC
/* PC: port_decls.h declares D_800706A8. D_800669CE is not a variable: it lies 0xE39 records before the table of
 * per-animation frame counts D_8006A2B2 (4 bytes per animation id), so that an animation id indexes it directly; on
 * the N64 that address falls inside D_800651A0, and the PC has no symbol there. So this file reads D_8006A2B2 by the
 * id minus 0xE39, with func_8000946C's view of it. */
typedef struct {
    s16 a;
    s16 b;
} A2B2Rec;
extern A2B2Rec D_8006A2B2[];
#else
extern s16 D_800669CE[][2];
extern Rec8CE8 D_800706A8[];
#endif
extern Bone8CE8 D_80070C40[][23];

void func_8000A310(s16);
void func_8000A3DC(s16, s32);
void func_8000AD00(s16, s16);
void func_8000B2B8(s16, s16);
void func_80009D98(s16, s16, s8);
void initializeResourceStream(s16, s16);
void updateBodyPartTransforms(s16);
void func_80007E14(f32 *, f32);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_80007E04 */
void func_80007E04(f32 *, f32, f32, f32);
#endif
void guMtxXFMF(f32 *, f32, f32, f32, f32 *, f32 *, f32 *);
void func_80001DC4(void *);
void guMtxCatF(f32 *, f32 *, f32 *);
#ifdef TARGET_PC
/* PC: the types of multiplyMatrix4x4's definition, 4x4 matrices; the calls below pass this file's f32[16] matrices
 * as such. */
void multiplyMatrix4x4(f32 arg0[4][4], f32 arg1[4][4], f32 arg2[4][4]);
#else
void multiplyMatrix4x4(f32 *, f32 *, f32 *);
#endif

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
#ifdef TARGET_PC
    /* PC: the stream record is Nw2AnimStream (common.h), read by field name: the N64's A8 is fresh, AA replay, AC id,
     * AE firstFrame, B0 cursor (a pointer here, so the buffer's address stays whole), C0 anim and C2 frame. */
    if (anim != D_800706A8[entity].anim) {
        D_800706A8[entity].frame = -1;
        frame = 0;
    }
    if (frame == 0 && D_800706A8[entity].frame != 0) {
        D_800706A8[entity].replay = (anim == D_800706A8[entity].anim);
        func_8000B2B8(entity, anim);
        D_800706A8[entity].anim = -1;
    }
    if (anim != D_800706A8[entity].anim) {
        if (D_800706A8[entity].replay != 0 && D_800706A8[entity].firstFrame == 0) {
            D_800706A8[entity].id = anim;
            D_800706A8[entity].cursor = D_800485A0[entity];
        } else {
            initializeResourceStream(entity, anim);
        }
        D_800706A8[entity].anim = anim;
        if (D_800706A8[entity].fresh == 0) {
            old[0] = D_80070C40[entity][1].f54;
            old[2] = D_80070C40[entity][1].f5C;
            loaded = 1;
        }
    }
#else
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
#endif
#ifdef TARGET_PC
    /* PC: frame is the N64's C2; the frame count of animation anim is read from D_8006A2B2 (see the declarations). */
    if (frame != D_800706A8[entity].frame) {
        s32 n, m;
        D_800706A8[entity].frame = frame;
        n = D_8006A2B2[anim - 0xE39].a;
#else
    if (frame != D_800706A8[entity].C2) {
        s32 n, m;
        D_800706A8[entity].C2 = frame;
        n = D_800669CE[anim][0];
#endif
        m = n << 16;
        if (frame < n) {
            if (!(frame & 1) || frame == (m >> 16) - 1) {
                func_8000A310(entity);
            } else {
                func_8000A3DC(entity, 0);
            }
            if (flags & 2) {
#ifdef TARGET_PC
                /* PC: fresh and replay are the N64's A8 and AA. */
                if (D_800706A8[entity].fresh == 0 && frame < 5 && D_800706A8[entity].replay == 0) {
#else
                if (D_800706A8[entity].A8 == 0 && frame < 5 && D_800706A8[entity].AA == 0) {
#endif
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
#ifdef TARGET_PC
        /* PC: obj holds a handle (see Node8CE8). */
        o = SLOT_TO_PTR(nd->obj);
#else
        o = nd->obj;
#endif
        b += entity * 23;
        t = &b->f54;
        func_80007E14(o->m, f0);
#ifdef TARGET_PC
        /* PC: the parent object is o, which the N64 reads again through nd->obj (a handle here). mtx is the stream
         * record's field (Nw2AnimStream). multiplyMatrix4x4 takes 4x4 matrices, as its declaration above says. */
        func_80007E04(o->m, D_80070C40[entity][0].fC, D_80070C40[entity][0].f10, D_80070C40[entity][0].f14);
        guMtxCatF(D_800706A8[entity].mtx, o->m, o->m);
        multiplyMatrix4x4((f32 (*)[4])nd->m1C, (f32 (*)[4])o->m, (f32 (*)[4])nd->m5C);
#else
        func_80007E04(nd->obj->m, D_80070C40[entity][0].fC, D_80070C40[entity][0].f10, D_80070C40[entity][0].f14);
        guMtxCatF(D_800706A8[entity].mtx, nd->obj->m, nd->obj->m);
        multiplyMatrix4x4(nd->m1C, nd->obj->m, nd->m5C);
#endif
        guMtxXFMF(nd->m5C, b->f48, b->f4C, b->f50, &t[0], &t[1], &t[2]);
        t[0] = -t[0];
        pos[0] += old[0] - t[0];
        pos[2] += old[2] - t[2];
    }
    D_80070C40[entity][0].fC = -pos[0];
    D_80070C40[entity][0].f10 = pos[1];
    D_80070C40[entity][0].f14 = pos[2];
    func_80007E14(scratch, f0);
    func_80007E04(scratch, D_80070C40[entity][0].fC, D_80070C40[entity][0].f10, D_80070C40[entity][0].f14);
#ifdef TARGET_PC
    /* PC: as the declaration above; mtx is the stream record's field (Nw2AnimStream). */
    multiplyMatrix4x4((f32 (*)[4])D_800706A8[entity].mtx, (f32 (*)[4])scratch, (f32 (*)[4])D_800651A0[entity][0].m1C);
#else
    multiplyMatrix4x4(D_800706A8[entity].mtx, scratch, D_800651A0[entity][0].m1C);
#endif
    func_80001DC4(D_800651A0[entity]);
    D_80070C40[entity][0].f78 = f0;
    for (i = 1; i < 23; i++) {
        if (i != 20) {
            Node8CE8 *n0 = D_800651A0[0] + i;
            D_80070C40[entity][i].f78 = D_80070C40[entity][i].f4 + f0;
            b2 = (Bone8CE8 *)((u8 *)D_80070C40[entity] + i * sizeof(Bone8CE8));
#ifdef TARGET_PC
            /* PC: the N64 adds the byte offset of the entity's row to node i's address in 32 bits, which would cut a
             * 64-bit address; the PC adds it to the pointer, which gives the same node, D_800651A0[entity][i]. */
            nd = (Node8CE8 *)((u8 *)n0 + entity * (s32)sizeof(D_800651A0[0]));
#else
            nd = (Node8CE8 *)((u32)(entity * sizeof(D_800651A0[0])) + (u32)n0);
#endif
            t = &b2->f54;
            guMtxXFMF(nd->m5C, b2->f48, b2->f4C, b2->f50, t, &b2->f58, &b2->f5C);
            *t = -*t;
            t = &b2->f6C;
            guMtxXFMF(nd->m5C, b2->f60, b2->f64, b2->f68, t, &b2->f70, &b2->f74);
            *t = -*t;
        }
    }
    if (updated) {
        func_8000AD00(entity, frame + 1);
    }
#ifdef TARGET_PC
    /* PC: fresh is the N64's A8. */
    if (D_800706A8[entity].fresh != 0) {
        D_800706A8[entity].fresh = 0;
    }
#else
    if (D_800706A8[entity].A8 != 0) {
        D_800706A8[entity].A8 = 0;
    }
#endif
}
