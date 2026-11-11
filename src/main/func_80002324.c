/* @header
 * func_80002324
 * VRAM 0x80002324 | ROM 0x2F24 | size 0x130
 * asm: asm/nonmatchings/main/func_80002324.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: Obj2324 is a work block, which keeps its N64 layout (Nw2SceneWork in common.h), so its owner at +4 holds a
 * 4-byte handle (port.h's PTR_TO_SLOT). The assert checks the view against Nw2SceneWork. */
typedef struct { s32 f0; u32 f4; } Obj2324;
_Static_assert(offsetof(Obj2324, f4) == offsetof(Nw2SceneWork, owner), "Obj2324 must follow Nw2SceneWork");
#else
typedef struct { s32 f0; u8 *f4; } Obj2324;
#endif
#ifndef TARGET_PC /* on PC, port_decls.h declares D_80046860 */
extern Obj2324 *D_80046860[];
#endif
extern s16 D_80047062;
extern u16 D_80047064, D_80047066;
extern u8 D_80048070[];
void func_80002110();
void func_80002324(s16 arg0) {
    s32 pad[2];
    u32 i;
    Obj2324 *obj;
    u8 v;
    D_80047066=0;
    D_80047064=D_80047062;
    i=0;
    if((u16)D_80047062!=0) {
        do {
            obj=D_80046860[i];
#ifdef TARGET_PC
            /* PC: the owner is a handle (see Obj2324 above); its +0x18 is the object's draw group. */
            v=((Nw2SceneObj *)SLOT_TO_PTR(obj->f4))->group;
#else
            v=obj->f4[0x18];
#endif
            D_80048070[i]=v;
            if(v&0x80) D_80048070[i]=0xFF;
            else if(v==6) D_80047064=i;
            else if(obj->f0==1) { if(v!=0) D_80048070[i]=5; }
            i++;
        }while(i<(u32)D_80047062);
    }
    func_80002110(arg0,0,0);
    func_80002110(arg0,0,1);
    func_80002110(arg0,6,0);
    func_80002110(arg0,3,0);
    func_80002110(arg0,5,1);
    func_80002110(arg0,5,0);
}
