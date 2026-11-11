/* @header
 * func_8000E920
 * VRAM 0x8000E920 | ROM 0xF520 | size 0x4A4
 * asm: asm/nonmatchings/main/func_8000E920.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: an EntE920 is a 0xDC-byte scene object (Nw2SceneObj, common.h), which keeps its N64 layout on PC, so its links
 * a0, a4 and a8 (parent, child, next) are 4-byte handles (port.h's PTR_TO_SLOT) and the objects still step by 0xDC.
 * A PartE920 is a display record, whose PC layout is Nw2Descr4BA8 (0x50 bytes), so parts[n] steps by its size. */
typedef struct EntE920 {
    u32 a0;
    u32 a4;
    u32 a8;
    u8 padC[0x10];
    f32 mtx[4][4];
    u8 pad5C[0x80];
} EntE920;
_Static_assert(offsetof(EntE920, a0) == offsetof(Nw2SceneObj, parent) &&
                   offsetof(EntE920, a4) == offsetof(Nw2SceneObj, child) &&
                   offsetof(EntE920, a8) == offsetof(Nw2SceneObj, next) &&
                   offsetof(EntE920, mtx) == offsetof(Nw2SceneObj, local) && sizeof(EntE920) == sizeof(Nw2SceneObj),
               "EntE920 must follow Nw2SceneObj");
typedef Nw2Descr4BA8 PartE920;
#else
typedef struct EntE920 {
    struct EntE920 *a0;
    struct EntE920 *a4;
    struct EntE920 *a8;
    u8 padC[0x10];
    f32 mtx[4][4];
    u8 pad5C[0x80];
} EntE920;
typedef struct {
    u8 pad[0x2C];
} PartE920;
#endif

extern EntE920 D_80057030[];
extern PartE920 D_800583F8[];
#ifndef TARGET_PC /* on PC, port_decls.h declares D_800587F0, D_80058900 and D_80058988 (display records) */
extern u8 D_800587F0[];
extern u8 D_80058900[];
extern u8 D_80058988[];
#endif
extern u8 D_80036C68[];
extern u8 D_80036C8C[];
extern u8 D_80036CFC[];
extern u8 D_80036D04[];
extern void *D_80036C74[];
extern void *D_80036C94[];
extern s16 D_80036C50[];
extern u16 D_80036C58[];
extern s16 D_80036C60[];
#ifndef TARGET_PC /* on PC, port_decls.h declares these three pointers (the display lists func_80007020 returns) */
extern s32 D_800587EC;
extern s32 D_800588F8;
extern s32 D_80058984;
#endif
extern s16 D_80059D80;
extern s16 D_80059D82;
extern f64 D_8003B220;
extern f64 D_8003B228;

#ifdef TARGET_PC
/* PC: func_80007020 returns the display list it built, a pointer (Gfx7020 *, a type of its own file), and takes the
 * record count as an s16; its pointer parameters stay void * here. port_decls.h declares func_80007818, which takes
 * that display list as a pointer. */
void *func_80007020(void *, void *, void *, s16);
#else
s32 func_80007020(void *, void *, void *, s32);
void func_80007818(void *, void *, s32, s32);
#endif
void func_80001544(void *);
void func_80001DC4(void *);
void func_80004B34(void *, void *, s32, f32, f32, f32);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_80004BA8 */
void func_80004BA8(void *, void *, s32, s32, s32, s32, void *);
#endif
void func_80004F80(void *, s16, s16);
void func_80007E14(void *, f32);
void func_8000EF90(void);
void guMtxCatF(void *, void *, void *);
void bcopy(void *, void *, s32);

void func_8000E920(void *unused, s16 arg1)
{
    f32 mtx[4][4];
    u32 i;
    u32 j;
    s32 n;
    f64 fv;
    EntE920 *ents = D_80057030;
    PartE920 *parts = D_800583F8;

    D_80059D82 = arg1;
    if (arg1 >= 6) {
        D_80059D82 = 0;
    }
    if (D_80036C74[D_80059D82] != NULL) {
        D_800587EC = func_80007020(D_800587F0, D_80036C68, D_80036C74[D_80059D82], 6);
    }
    D_800588F8 = func_80007020(D_80058900, D_80036C8C, D_80036C94[D_80059D82], 3);
    D_80058984 = func_80007020(D_80058988, D_80036CFC, D_80036D04, 3);
    func_80004B34(&ents[0], &parts[0], 6, 0.0f, 0.0f, 0.0f);
    if (D_80036C74[D_80059D82] != NULL) {
        func_80007818(&ents[0], D_800587F0, D_800587EC, 0);
        func_80001544(&ents[0]);
    }
#ifdef TARGET_PC
    /* PC: the links are handles (see EntE920). */
    ents[0].a8 = PTR_TO_SLOT(&ents[1]);
#else
    ents[0].a8 = &ents[1];
#endif
    n = 1;
    for (i = 0; i < 4; i++) {
        fv = (s32)i;
        if ((s32)i < 0) {
            fv += D_8003B220;
        }
        func_80007E14(mtx, fv * D_8003B228);
        for (j = 0; j < 3; j++) {
            func_80004B34(&ents[n], &parts[n], 3, 0.0f, 0.0f, 0.0f);
            func_80004BA8(&ents[n], &parts[n], 0, D_80036C50[j], 0, 0, &ents[n + 1]);
            if (D_80036C58[j] != 0) {
                func_80004F80(&parts[n], D_80036C58[j], D_80036C60[j]);
            }
            guMtxCatF(mtx, ents[n].mtx, ents[n].mtx);
            n++;
        }
        func_80004B34(&ents[n], &parts[n], 0, 0.0f, 0.0f, 0.0f);
        func_80007818(&ents[n], D_80058900, D_800588F8, 0);
        func_80001544(&ents[n]);
#ifdef TARGET_PC
        /* PC: handles, as above; 0 stands for none. */
        ents[n].a0 = 0;
        ents[n].a8 = PTR_TO_SLOT(&ents[n + 2]);
        ents[n].a4 = PTR_TO_SLOT(&ents[n + 1]);
#else
        ents[n].a0 = NULL;
        ents[n].a8 = &ents[n + 2];
        ents[n].a4 = &ents[n + 1];
#endif
        bcopy(mtx, ents[n].mtx, 0x40);
        n++;
        if (i != 0) {
            func_80004B34(&ents[n], &parts[n], 5, 0.0f, 0.0f, 0.0f);
            func_80007818(&ents[n], D_80058988, D_80058984, 0);
            func_80001544(&ents[n]);
#ifdef TARGET_PC
            /* PC: handles, as above. */
            ents[n].a0 = PTR_TO_SLOT(&ents[n - 1]);
            ents[n].a8 = 0;
            ents[n].a4 = 0;
#else
            ents[n].a0 = &ents[n - 1];
            ents[n].a8 = NULL;
            ents[n].a4 = NULL;
#endif
            n++;
        }
    }
    D_80059D80 = (s8)n + 1;
    func_80001DC4(ents);
    func_8000EF90();
}
