/* @header
 * func_8000BDD0
 * VRAM 0x8000BDD0 | ROM 0xC9D0 | size 0x3E8
 * asm: asm/nonmatchings/main/func_8000BDD0.s
 */
#include "common.h"

extern u16 D_8006A2A4[];
extern s16 D_8007DFBC[];
extern s16 D_8007DFB0[];
extern u16 *D_80031998[];
extern s16 **D_80032B44[][1];
extern u16 ***D_800360F0[];
extern s16 *D_800317F0[];
extern s8 D_80031088[];
extern u8 D_800651A0[];
#ifndef TARGET_PC /* on PC, port_decls.h declares D_80073EB0: four rows of 23 display records */
extern u8 D_80073EB0[];
#endif
#ifndef TARGET_PC /* on PC, port_decls.h declares D_8007C3D0: the players' mesh arenas */
extern u8 D_8007C3D0[][16];
#endif
extern u8 D_80070450[];
#ifndef TARGET_PC /* on PC, port_decls.h declares func_80004BA8, which takes the child object as a pointer */
void func_80004BA8(void *, void *, void *, s16, void *, s32, void *);
#endif
void func_80005014(void *, void *, void *, void *);

#ifdef TARGET_PC
/* PC: an object is the scene graph's Nw2SceneObj (common.h), which keeps the N64's 0xDC bytes, so the byte offsets
 * below still reach the same fields; its address fields hold handles (PTR_TO_SLOT). A display record is Nw2Descr4BA8,
 * 0x50 bytes on PC, so a row of D_80073EB0 is stepped by its size, not by 0x2C. */
typedef Nw2SceneObj ObjDC;
typedef Nw2Descr4BA8 Slot2C;
#else
typedef struct { u8 d[0xDC]; } ObjDC;
typedef struct { u8 d[0x2C]; } Slot2C;
#endif

void func_8000BDD0(s16 arg0) {
    u32 i;
    u16 w;
    s32 bank;
    s32 idx;
    u16 *a3;
    s16 *s2;
    Slot2C *s4;
    ObjDC *s3;
    s16 *tbl;
    u16 a2;

    w = D_8006A2A4[arg0];
    bank = (w >> 8) & 0x1F;
    idx = (w & 0x1F) - 1;
#ifdef TARGET_PC
    /* PC: the same address arithmetic in an integer as wide as a pointer (uptr); a u32 would cut the table's
     * 64-bit address in half. idx can be -1, which steps back 2 bytes on both. */
    a3 = (u16 *)(idx * 2 + (uptr)D_80031998[bank]);
#else
    a3 = (u16 *)(idx * 2 + (u32)D_80031998[bank]);
#endif
    s2 = ((s16 ***)D_80032B44[bank][0])[idx][D_8007DFB0[arg0]];
    a2 = *D_800360F0[*a3 & 0x7F][D_8007DFBC[arg0]][0];
#ifdef TARGET_PC
    /* PC: player arg0's row of 23 display records, by index; the N64 steps 0x3F4 bytes, 23 records of 0x2C. */
    s4 = D_80073EB0[arg0];
#else
    s4 = (Slot2C *)(D_80073EB0 + arg0 * 0x3F4);
#endif
    tbl = D_800317F0[a2 & 0x7F];
    s3 = (ObjDC *)(D_800651A0 + arg0 * 0x13C4);
    D_80070450[arg0] = a2;
#ifdef TARGET_PC
    /* PC: object 0's child (+0x4) is a 4-byte field, so it holds object 1's handle. */
    s3->child = PTR_TO_SLOT(&s3[1]);
#else
    *(void **)((u8 *)s3 + 4) = &s3[1];
#endif
    for (i = 1; i < 0x14; i++) {
        s8 c = D_80031088[i];
        if (c < 0) {
            switch (i) {
            case 4:
#ifdef TARGET_PC
                /* PC: arena arg0's address; D_8007C3D0 is an array of Nw2MeshArena records on PC, not of 16-byte
                 * rows. */
                func_80004BA8(&s3[4], &s4[4], &D_8007C3D0[arg0], s2[0], s3, NULL, &s3[5]);
#else
                func_80004BA8(&s3[4], &s4[4], D_8007C3D0[arg0], s2[0], s3, 0, &s3[5]);
#endif
                break;
            case 5:
#ifdef TARGET_PC
                /* PC: arena arg0's address, as above. */
                func_80004BA8(&s3[5], &s4[5], &D_8007C3D0[arg0], s2[1], s3, NULL, &s3[6]);
#else
                func_80004BA8(&s3[5], &s4[5], D_8007C3D0[arg0], s2[1], s3, 0, &s3[6]);
#endif
                break;
            }
        } else {
#ifdef TARGET_PC
            /* PC: arena arg0's address, as above. */
            func_80004BA8(&s3[i], &s4[i], &D_8007C3D0[arg0], tbl[c], s3, NULL, &s3[i + 1]);
#else
            func_80004BA8(&s3[i], &s4[i], D_8007C3D0[arg0], tbl[c], s3, 0, &s3[i + 1]);
#endif
        }
    }
    *(s32 *)((u8 *)s3 + 0x105C) = 0;
    if (s2[2] != 0) {
        *((u8 *)s3 + 0x1148) = *((u8 *)s3 + 0x464);
#ifdef TARGET_PC
        /* PC: arena arg0's address, as above. Object 5's child (+0x450 is object 5's +0x4) then holds the handle
         * of object 20 (+0x1130). */
        func_80004BA8(&s3[20], &s4[20], &D_8007C3D0[arg0], s2[2], &s3[5], NULL, NULL);
        s3[5].child = PTR_TO_SLOT(&s3[20]);
#else
        func_80004BA8((u8 *)s3 + 0x1130, &s4[20], D_8007C3D0[arg0], s2[2], &s3[5], 0, NULL);
        *(void **)((u8 *)s3 + 0x450) = (u8 *)s3 + 0x1130;
#endif
    } else {
#ifdef TARGET_PC
        /* PC: object 20's first work block (+0x1144 is object 20's +0x14) is a handle; turn it into the block's
         * address once and clear the block's fields through it by name (+0x30 vtx, +0x2C count, +0x2E start, +0x34
         * dl). The N64 reads the same address again for each store. Object 5's child goes back to 0. */
        Nw2SceneWork *v1 = SLOT_TO_PTR(s3[20].work);
        *((u8 *)s3 + 0x1148) = 0x80;
        *(s32 *)((u8 *)s3 + 0x1130) = 0;
        if (v1 != NULL) {
            v1->vtx = 0;
            v1->count = 0;
            v1->start = 0;
            v1->dl = 0;
        }
        s3[5].child = 0;
#else
        void *v1 = *(void **)((u8 *)s3 + 0x1144);
        *((u8 *)s3 + 0x1148) = 0x80;
        *(s32 *)((u8 *)s3 + 0x1130) = 0;
        if (v1 != NULL) {
            *(s32 *)((u8 *)v1 + 0x30) = 0;
            *(s16 *)((u8 *)*(void **)((u8 *)s3 + 0x1144) + 0x2C) = 0;
            *(s16 *)((u8 *)*(void **)((u8 *)s3 + 0x1144) + 0x2E) = 0;
            *(s32 *)((u8 *)*(void **)((u8 *)s3 + 0x1144) + 0x34) = 0;
        }
        *(void **)((u8 *)s3 + 0x450) = NULL;
#endif
    }
    func_80005014(&s3[2], &s4[2], &s3[1], &s3[3]);
    func_80005014(&s3[4], &s4[4], &s3[3], &s3[5]);
    func_80005014(&s3[7], &s4[7], &s3[6], &s3[1]);
    func_80005014(&s3[14], &s4[14], &s3[13], &s3[1]);
    func_80005014(&s3[11], &s4[11], &s3[9], &s3[12]);
    func_80005014(&s3[16], &s4[16], &s3[17], &s3[19]);
    func_80005014(&s3[1], &s4[1], &s3[7], &s3[14]);
#ifdef TARGET_PC
    /* PC: the same stores into the first work blocks of objects 12, 19, 3, 4, 7, 14, 6, 13, 8 and 15. The N64 reads
     * each object's +0x14 (0xA64 is object 12's, 0x1068 object 19's, and so on) as the block's address; on PC that
     * field is a handle, which SLOT_TO_PTR turns back into the address. In the block, +0x10 is center[1], +0x14
     * center[2] and +0x24 bias (Nw2SceneWork, common.h). */
    ((Nw2SceneWork *)SLOT_TO_PTR(s3[12].work))->center[1] -= 5.0f;
    ((Nw2SceneWork *)SLOT_TO_PTR(s3[19].work))->center[1] -= 5.0f;
    ((Nw2SceneWork *)SLOT_TO_PTR(s3[3].work))->center[2] = ((Nw2SceneWork *)SLOT_TO_PTR(s3[4].work))->center[2];
    ((Nw2SceneWork *)SLOT_TO_PTR(s3[7].work))->bias = -5.0f;
    ((Nw2SceneWork *)SLOT_TO_PTR(s3[14].work))->bias = -5.0f;
    ((Nw2SceneWork *)SLOT_TO_PTR(s3[6].work))->bias = -7.0f;
    ((Nw2SceneWork *)SLOT_TO_PTR(s3[13].work))->bias = -7.0f;
    ((Nw2SceneWork *)SLOT_TO_PTR(s3[8].work))->bias = 7.0f;
    ((Nw2SceneWork *)SLOT_TO_PTR(s3[15].work))->bias = 7.0f;
#else
    *(f32 *)(*(u8 **)((u8 *)s3 + 0xA64) + 0x10) -= 5.0f;
    *(f32 *)(*(u8 **)((u8 *)s3 + 0x1068) + 0x10) -= 5.0f;
    *(f32 *)(*(u8 **)((u8 *)s3 + 0x2A8) + 0x14) = *(f32 *)(*(u8 **)((u8 *)s3 + 0x384) + 0x14);
    *(f32 *)(*(u8 **)((u8 *)s3 + 0x618) + 0x24) = -5.0f;
    *(f32 *)(*(u8 **)((u8 *)s3 + 0xC1C) + 0x24) = -5.0f;
    *(f32 *)(*(u8 **)((u8 *)s3 + 0x53C) + 0x24) = -7.0f;
    *(f32 *)(*(u8 **)((u8 *)s3 + 0xB40) + 0x24) = -7.0f;
    *(f32 *)(*(u8 **)((u8 *)s3 + 0x6F4) + 0x24) = 7.0f;
    *(f32 *)(*(u8 **)((u8 *)s3 + 0xCF8) + 0x24) = 7.0f;
#endif
}
