/* @header
 * func_80012B38
 * VRAM 0x80012B38 | ROM 0x13738 | size 0x198
 * asm: asm/nonmatchings/main/func_80012B38.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: a view record is a 0xDC-byte scene object (D_8005A730, and the 23 objects of each 0x13C4-byte block of
 * D_800651A0), which keeps its N64 layout on PC (Nw2SceneObj, common.h), so its address fields hold handles (port.h's
 * PTR_TO_SLOT): link (+0x0) is the object's parent, the object whose world matrix this one's follows, and part
 * (+0x14) is its work block (Nw2SceneWork), whose first word is the block's kind and z its depth bias (+0x24). */
typedef struct { u32 flags; u8 pad4[32]; f32 z; } ViewPart;
typedef struct { u32 link; u8 pad4[16]; u32 part; u8 pad18[196]; } ViewRecord;
_Static_assert(offsetof(ViewRecord, link) == offsetof(Nw2SceneObj, parent) &&
                   offsetof(ViewRecord, part) == offsetof(Nw2SceneObj, work) &&
                   sizeof(ViewRecord) == sizeof(Nw2SceneObj) &&
                   offsetof(ViewPart, flags) == offsetof(Nw2SceneWork, kind) &&
                   offsetof(ViewPart, z) == offsetof(Nw2SceneWork, bias),
               "ViewRecord must follow Nw2SceneObj, and ViewPart Nw2SceneWork");
#else
typedef struct { u32 flags; u8 pad4[32]; f32 z; } ViewPart;
typedef struct { void *link; u8 pad4[16]; ViewPart *part; u8 pad18[196]; } ViewRecord;
#endif
extern ViewRecord D_8005A730[];
#ifndef TARGET_PC /* on PC, port_decls.h declares D_8005B0F8, the addresses of the six display lists */
extern s32 D_8005B0F8[];
#endif
extern Nw2Descr4BA8 D_8005B110[];
extern ViewRecord D_800651A0[][23];
extern s8 D_80070478[][2],D_80070479[][2];
#ifndef TARGET_PC /* on PC, port_decls.h declares func_80007874, which takes the display list as a pointer */
void func_80007874(void *,void *,s32,s32);
#endif
/* Change the visible model part of the view record `arg0` to model `arg1`
 * (variant `arg2`). arg1 == 6 (or larger) hides the part (flag 0x80 + null link).
 * Caches the current (model, variant) pair in D_80070478/79. */
#ifdef TARGET_PC
/* PC: the object's parent and work block through their handles, as ViewRecord above says. */
void func_80012B38(s16 arg0,s16 arg1,s16 arg2) {
    ViewRecord *p=&D_8005A730[arg0];
    if(arg1!=D_80070478[arg0][0]) {
        ViewPart *part=SLOT_TO_PTR(p->part);
        part->flags&=~0x80;
        if((u16)arg1<6) func_80007874(p,&D_8005B110[arg1],D_8005B0F8[arg1],0);
        else { part->flags|=0x80; arg1=-1; }
        if(arg1!=-1) {p->link=PTR_TO_SLOT(&D_800651A0[arg0][arg2]);part->z=-10.0f;} else p->link=0;
        D_80070478[arg0][0]=arg1;
        D_80070479[arg0][0]=arg2;
    }
}
#else
void func_80012B38(s16 arg0,s16 arg1,s16 arg2) {
    ViewRecord *p=&D_8005A730[arg0];
    if(arg1!=D_80070478[arg0][0]) {
        p->part->flags&=~0x80;
        if((u16)arg1<6) func_80007874(p,&D_8005B110[arg1],D_8005B0F8[arg1],0);
        else { p->part->flags|=0x80; arg1=-1; }
        if(arg1!=-1) {p->link=&D_800651A0[arg0][arg2];p->part->z=-10.0f;} else p->link=NULL;
        D_80070478[arg0][0]=arg1;
        D_80070479[arg0][0]=arg2;
    }
}
#endif
