/* @header
 * buildColorOverlayDisplayList  (originally func_80006B84)
 * VRAM 0x80006B84 | ROM 0x7784 | size 0x190
 * asm: asm/nonmatchings/main/buildColorOverlayDisplayList.s
 */
#include "common.h"

void *allocateHeap(u32); void func_800015AC(void *,s32);void func_80001544(void *);
#ifdef TARGET_PC
/* PC: obj is a 0xDC-byte scene object (D_800F99C0), which keeps its N64 layout on PC (Nw2SceneObj, common.h), so its
 * display list (+0x10) and work block (+0x14) are handles (port.h's PTR_TO_SLOT): the code stores PTR_TO_SLOT(p) and
 * reads SLOT_TO_PTR(field). A command is port.h's 16-byte Gfx, which Fast3D draws as it is, and the buffer holds the
 * N64's 0x300 / 8 commands. bias is the work block's depth bias (+0x24), flat the object's +0x19. */
void buildColorOverlayDisplayList(u8 *obj, u8 red, u8 green, u8 blue, u8 alpha) {
    Nw2SceneObj *o = (Nw2SceneObj *)obj;
    Gfx *dl;
    u32 i;
    u32 r = red, g = green, b = blue, a = alpha;

    if (!o->dl) {
        o->dl = PTR_TO_SLOT(allocateHeap(0x300 / 8 * sizeof(Gfx)));
        func_800015AC(obj, 0);
        func_80001544(obj);
        ((Nw2SceneWork *)SLOT_TO_PTR(o->work))->bias = -15000.0f;
        o->flat = 1;
    }
    dl = SLOT_TO_PTR(o->dl);
    { Gfx *q = dl++; q->w0 = 0xe7000000; q->w1 = 0; }
    { Gfx *q = dl++; q->w0 = 0xfa000000; q->w1 = (r << 24) | (g << 16) | (b << 8) | a; }
    { Gfx *q = dl++; q->w0 = 0xe200001c; q->w1 = 0x504240; }
    { Gfx *q = dl++; q->w0 = 0xfcffffff; q->w1 = 0xfffdf6fb; }
    for (i = 0; i < 8; i++) {
        Gfx *q = dl++;
        q->w0 = 0xf677c000 | (((i + 1) * 120) & 0xff8);
        q->w1 = (i * 120) & 0xff8;
    }
    { Gfx *q = dl++; q->w0 = 0xe7000000; q->w1 = 0; }
    { Gfx *q = dl++; q->w0 = 0xdf000000; q->w1 = 0; }
}
#else
void buildColorOverlayDisplayList(u8 *obj,u8 red,u8 green,u8 blue,u8 alpha){
    Nw2GfxCommand *dl;u32 i;u32 r=red,g=green,b=blue,a=alpha;
    if(!*(void **)(obj+0x10)){
        *(void **)(obj+0x10)=allocateHeap(0x300);func_800015AC(obj,0);func_80001544(obj);*(f32 *)(*(u8 **)(obj+0x14)+0x24)=-15000.0f;obj[0x19]=1;
    }
    dl=*(Nw2GfxCommand **)(obj+0x10);
    {Nw2GfxCommand *q=dl++;q->w0=0xe7000000;q->w1=0;}
    {Nw2GfxCommand *q=dl++;q->w0=0xfa000000;q->w1=(r<<24)|(g<<16)|(b<<8)|a;}
    {Nw2GfxCommand *q=dl++;q->w0=0xe200001c;q->w1=0x504240;}
    {Nw2GfxCommand *q=dl++;q->w0=0xfcffffff;q->w1=0xfffdf6fb;}
    for(i=0;i<8;i++){
        Nw2GfxCommand *q=dl++;q->w0=0xf677c000|(((i+1)*120)&0xff8);q->w1=(i*120)&0xff8;
    }
    {Nw2GfxCommand *q=dl++;q->w0=0xe7000000;q->w1=0;}
    {Nw2GfxCommand *q=dl++;q->w0=0xdf000000;q->w1=0;}
}
#endif
