/* @header
 * func_80093DAC
 * VRAM 0x80093DAC | ROM 0x4051C | size 0x2A8
 * asm: asm/nonmatchings/code_80090000/func_80093DAC.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: the N64 reaches the overlay's variables as fields of other labels: D_800DB4FC + 0x178 is D_800DB674, + 0x184
 * D_800DB680, + 0x188 D_800DB684, + 0x18C D_800DB688, + 0x194 D_800DB690, + 0x19C D_800DB698, + 0x1A0 D_800DB69C and
 * + 0x1A4 D_800DB6A0; D_800DB874 + 0x34 is D_800DB8A8 and + 0x3C D_800DB8B0; D_800DBB80 + 0x1CC is D_800DBD4C;
 * D_800C9014 + 0x80 is D_800C9094; D_800C8D84 + 0x100 is the scenes D_800C8E84. On PC no label lies inside another
 * variable and an address takes 8 bytes, so the PC names each by its own label, with the type of what it holds
 * (func_80094054 frees the heap blocks by the same names). The scene D_800C8E84[D_800DB688] is common.h's
 * Nw2EncScene, read by field name.
 * The heap blocks hold as many records as on the N64: D_800DB698 0x200 vertices (16 bytes on both), D_800DB690 0x300
 * display-list commands (func_80090908 builds the parts' lists in it) and D_800DB8B0 0xC00 commands (two halves of
 * 0x600, one per frame: func_80094AE4); a command is port.h's 16-byte Gfx on PC.
 * The scene objects keep their N64 layout (common.h's Nw2SceneObj), so their links, vertices and display list are
 * handles (port.h's PTR_TO_SLOT): a is b's child, and the 72 objects after a are a's children, each linked to the one
 * after it; D_800DB674 holds the first one's address. The vertices D_800C5AD0 and the display list D_800C5C50 are
 * overlay 1's data (the vertices declared with port.h's Vtx, as func_800900C0 does; the list is its PC copy). */
extern Nw2SceneObj *D_800DB674;
extern Nw2EncScene *D_800DB680;
extern Nw2EncSpot *D_800DB684;
extern s32 D_800DB688;
extern Gfx *D_800DB690;
extern Vtx *D_800DB698;
extern u8 *D_800DB69C;
extern u8 *D_800DB6A0;
extern s32 D_800DB8A8;
extern Gfx *D_800DB8B0;
extern s32 D_800DBD4C;
extern s32 D_800C9094;
extern Nw2EncScene D_800C8E84[];
extern Vtx D_800C5AD0[];
extern u8 D_800C5C50[];
extern f32 D_800E7508, D_800E7510, D_800E74F8, D_800E74FC, D_800E7500, D_800E750C, D_800E7504;
extern s32 D_800E74C4, D_800E8210, D_800E79BC, D_800E9F70, D_800E74E8;
extern s16 D_800E74D2, D_800E74D0, D_800E74CE, D_800E74CC;
/* PC: the definitions' types. */
void initializeTransformNode(u8 *node, u8 type, f32 x, f32 y, f32 z);
void func_800015AC(void *object, s8 mode);
void func_80001544(void *);
void guPositionF(void *, f32, f32, f32, f32, f32, f32, f32);
void *allocateHeap(u32);
void *bcopy(const void *src, void *dst, s32 len);

Nw2SceneObj *func_80093DAC(Nw2SceneObj *a, Nw2SceneObj *b) {
    f32 mat[20];
    Nw2SceneObj *p, *next;
    s32 i;
    f32 zero = 0.0f;

    initializeTransformNode((u8 *)b, 6, zero, zero, zero);
    b->child = PTR_TO_SLOT(a);
    initializeTransformNode((u8 *)a, 6, zero, zero, zero);
    a->parent = PTR_TO_SLOT(b);
    p = a + 1;
    a->child = PTR_TO_SLOT(p);
    D_800DB674 = p;
    D_800DBD4C = 0;
    guPositionF(mat, zero, zero, zero, 1.0f, zero, zero, zero);
    D_800DB698 = allocateHeap(0x200 * sizeof(Vtx));
    D_800DB690 = allocateHeap(0x300 * sizeof(Gfx));
    D_800DB8B0 = allocateHeap(0xC00 * sizeof(Gfx));
    D_800C9094 = 0;
    if ((u32)D_800DB688 < NW2_ENC_SCENE_COUNT) {
        D_800DB680 = &D_800C8E84[D_800DB688];
        D_800DB684 = D_800DB680->spots;
    } else {
        /* D_800DB688 is negative, as after this function (-1: no scene): the N64 takes a record before the table and
         * the word in it, which no code reads before func_800936DC sets both. */
        D_800DB680 = NULL;
        D_800DB684 = NULL;
    }
    for (i = 0; i < 72; i++) {
        initializeTransformNode((u8 *)p, 6, zero, zero, zero);
        p->vtx = PTR_TO_SLOT(D_800C5AD0);
        p->dl = PTR_TO_SLOT(D_800C5C50);
        func_800015AC(p, 1);
        func_80001544(p);
        next = p + 1;
        p->parent = PTR_TO_SLOT(a);
        p->next = PTR_TO_SLOT(next);
        p->group |= 0x80;
        bcopy(mat, p->local, 64);
        p = next;
    }
    D_800E7508 = zero;
    D_800E7510 = zero;
    D_800DB8A8 = 0;
    D_800E74C4 = 0;
    D_800E8210 = -1;
    D_800E79BC = 255;
    D_800E74D2 = 0;
    D_800E74D0 = 0;
    D_800E74CE = 0;
    D_800E74CC = 0;
    D_800E9F70 = -1;
    D_800DB688 = -1;
    D_800E74E8 = 0;
    D_800DB6A0 = NULL;
    D_800DB69C = NULL;
    D_800E74F8 = -868.0f;
    D_800E74FC = -565.0f;
    D_800E7500 = 3081.0f;
    D_800E750C = -34.0f;
    D_800E7504 = 1.0f;
    return p;
}
#else
extern u8 D_800DB4FC[],D_800DBB80[],D_800DB874[],D_800C8D84[],D_800C9014[],D_800C5AD0[],D_800C5C50[];
extern f32 D_800E7508,D_800E7510,D_800E74F8,D_800E74FC,D_800E7500,D_800E750C,D_800E7504;extern s32 D_800E74C4,D_800E8210,D_800E79BC,D_800E9F70,D_800E74E8;extern s16 D_800E74D2,D_800E74D0,D_800E74CE,D_800E74CC;
void initializeTransformNode(void*,s32,f32,f32,f32);void func_800015AC(void*,s32);void func_80001544(void*);void guPositionF(void*,f32,f32,f32,f32,f32,f32,f32);void *allocateHeap(u32);void bcopy(void*,void*,s32);
#define W(b,n) (*(s32*)((b)+(n)))
u8 *func_80093DAC(u8 *a,u8 *b){f32 mat[20];u8 *p,*next,*record;void *alloc;s32 i,rword;f32 zero=0.0f;initializeTransformNode(b,6,zero,zero,zero);W(b,4)=(s32)a;initializeTransformNode(a,6,zero,zero,zero);W(a,0)=(s32)b;
    { s32 t = (s32)a + 0xDC; W(a,4)=t; W(D_800DB4FC,0x178)=t; p=(u8*)t; }
    W(D_800DBB80,0x1CC)=0;guPositionF(mat,zero,zero,zero,1.0f,zero,zero,zero);W(D_800DB4FC,0x19C)=(s32)allocateHeap(0x2000);W(D_800DB4FC,0x194)=(s32)allocateHeap(0x1800);alloc=allocateHeap(0x6000);i=0;record=D_800C8D84+0x100+W(D_800DB4FC,0x18C)*52;rword=W(record,12);W(D_800DB874,0x3C)=(s32)alloc;W(D_800C9014,0x80)=0;W(D_800DB4FC,0x184)=(s32)record;W(D_800DB4FC,0x188)=rword;
    for(i=0;i<72;i++){initializeTransformNode(p,6,zero,zero,zero);W(p,12)=(s32)D_800C5AD0;W(p,16)=(s32)D_800C5C50;func_800015AC(p,1);func_80001544(p);next=p+0xDC;W(p,0)=(s32)a;W(p,8)=(s32)next;p[24]|=0x80;bcopy(mat,p+28,64);p=next;}
    D_800E7508=zero;D_800E7510=zero;W(D_800DB874,0x34)=0;D_800E74C4=0;D_800E8210=-1;D_800E79BC=255;D_800E74D2=0;D_800E74D0=0;D_800E74CE=0;D_800E74CC=0;D_800E9F70=-1;W(D_800DB4FC,0x18C)=-1;D_800E74E8=0;W(D_800DB4FC,0x1A4)=0;W(D_800DB4FC,0x1A0)=0;D_800E74F8=-868.0f;D_800E74FC=-565.0f;D_800E7500=3081.0f;D_800E750C=-34.0f;D_800E7504=1.0f;return p;}
#endif
