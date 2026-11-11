/* @header
 * func_80011764
 * VRAM 0x80011764 | ROM 0x12364 | size 0x3C0
 * asm: asm/nonmatchings/main/func_80011764.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: a command is port.h's 16-byte Gfx. The player objects D_8005A3C0 (Desc117) and their work blocks (Sub117) keep
 * their N64 layout (Nw2SceneObj and Nw2SceneWork, common.h), so their address fields hold handles (port.h's
 * PTR_TO_SLOT); the asserts check these views against those types. The animation-command records D_8005AAA0 and the
 * picture pairs D_8005B220 are declared in port_decls.h (Nw2AnimatedCi4State, Nw2TexPair); the labels D_8005AAAC to
 * D_8005AAAF have no PC symbol, so the body reads D_8005AAA0[n] by field name. func_800015AC is declared with its
 * definition's type. */
typedef Gfx Cmd117;
typedef struct { s32 f0; u8 pad4[0x28]; s16 f2C, f2E; u32 f30, f34; } Sub117;
typedef struct { u8 pad0[12]; u32 fC; u8 pad10[4]; u32 f14; u8 pad18[2]; u8 f1A; u8 pad1B[0xC1]; } Desc117;
_Static_assert(offsetof(Sub117, f0) == offsetof(Nw2SceneWork, kind) &&
                   offsetof(Sub117, f2C) == offsetof(Nw2SceneWork, count) &&
                   offsetof(Sub117, f2E) == offsetof(Nw2SceneWork, start) &&
                   offsetof(Sub117, f30) == offsetof(Nw2SceneWork, vtx) &&
                   offsetof(Sub117, f34) == offsetof(Nw2SceneWork, dl),
               "Sub117 must follow Nw2SceneWork");
_Static_assert(offsetof(Desc117, fC) == offsetof(Nw2SceneObj, vtx) &&
                   offsetof(Desc117, f14) == offsetof(Nw2SceneObj, work) &&
                   offsetof(Desc117, f1A) == offsetof(Nw2SceneObj, lit) && sizeof(Desc117) == sizeof(Nw2SceneObj),
               "Desc117 must follow Nw2SceneObj");
extern Desc117 D_8005A3C0[]; extern void *D_8005B218; extern u8 D_8007E010[]; extern s8 D_8007E013[];
extern u16 D_800307A0;
extern u8 D_80036DEC[],D_80036DF4[],D_80036DFC[],D_80036E04[],D_80036E0C[],D_80036E14[];
Cmd117 *buildCi4TextureDisplayList(void *,Cmd117 *,u16); void func_800015AC(void *,s8);
#else
typedef struct { u32 w0,w1; } Cmd117;
typedef struct { Cmd117 *buf[3]; u8 slot,type,frame; s8 timer; } Anim117;
typedef struct { s8 v; u8 pad[15]; } Byte117; typedef struct { u8 v; u8 pad[15]; } UByte117;
typedef struct { volatile s32 f0; u8 pad4[0x28]; volatile s16 f2C,f2E; volatile u32 f30,f34; } Sub117;
typedef struct { u8 pad0[12]; void *fC; u8 pad10[4]; Sub117 *f14; u8 pad18[2]; u8 f1A; u8 pad1B[0xC1]; } Desc117;
extern Anim117 D_8005AAA0[]; extern u8 D_8005AAAC[],D_8005AAAD[]; extern UByte117 D_8005AAAE[]; extern Byte117 D_8005AAAF[]; extern Desc117 D_8005A3C0[]; extern void *D_8005B218; extern u8 D_8005B220[],D_8007E010[]; extern s8 D_8007E013[]; extern u16 D_800307A0; extern u8 D_80036DEC[],D_80036DF4[],D_80036DFC[],D_80036E04[],D_80036E0C[],D_80036E14[];
Cmd117 *buildCi4TextureDisplayList(void *,void *,u16); u32 osVirtualToPhysical(void *); void func_800015AC(void *,s32);
#endif
#define CMD117(a,b) { Cmd117 *g=p++; g->w0=(a); g->w1=(b); }
#ifdef TARGET_PC
/* PC: as on the N64, with the PC types above. tail117 stores handles (PTR_TO_SLOT) of the vertices D_8005B218 and of
 * the buffer that holds the new list into the work block, and of the vertices into the object. */
static inline void tail117(Desc117 *d, void *v, Cmd117 *p) {
    Sub117 *sub;

    d->f1A = 0;
    d->fC = PTR_TO_SLOT(v);
    func_800015AC(d, 4);
    sub = SLOT_TO_PTR(d->f14);
    sub->f0 = 1;
    sub->f2C = 4;
    sub->f30 = 0;
    sub->f34 = 0;
    sub->f2E = 0;
    sub->f30 = PTR_TO_SLOT(v);
    sub->f34 = PTR_TO_SLOT(p);
}
/* PC: the record's countdown is an s8; storing countdown - 1 keeps the low byte, as the N64's byte store does, and a
 * frame is built when it goes below 0. The list goes into buffer slot, which holds 0x200 / 8 commands of sizeof(Gfx)
 * bytes (at most 26 are written): the picture pair frame + D_80036DF4[type] (&D_8005B220[...], a Nw2TexPair) and the
 * vertices' address as DL_ADDR. The colour words are built as u32, as the N64's 32-bit command word holds them. */
void func_80011764(s16 arg0) {
    u16 slot, type;
    u8 frame;
    Cmd117 *p, *g;
    Desc117 *d;
    Nw2AnimatedCi4State *anim = &D_8005AAA0[arg0];

    anim->countdown--;
    if (anim->countdown < 0) {
        slot = anim->slot;
        frame = anim->frame;
        type = anim->type;
        p = anim->buffers[slot];
        d = &D_8005A3C0[arg0];
        if (frame < D_80036DEC[type]) {
            if (D_800307A0 == 1) {
                if (type == 6) {
                    CMD117(0xFA000000, 0xFFFFFF7F);
                } else {
                    CMD117(0xFA000000, 0x7F7F7F7F);
                }
            } else {
                CMD117(0xFA000000, ((u32)D_80036DFC[type] << 24) | ((u32)D_80036E04[type] << 16) |
                                       ((u32)D_80036E0C[type] << 8) | D_80036E14[type]);
            }
            p = buildCi4TextureDisplayList(&D_8005B220[frame + D_80036DF4[type]], p, type);
            CMD117(0xD9DFFFFB, 0);
            CMD117(0xE3001001, 0xC000);
            g = p++;
            g->w0 = 0x01004008;
            g->w1 = DL_ADDR(D_8005B218);
            CMD117(0x06000204, 0x00040206);
            CMD117(0xE7000000, 0);
            CMD117(0xD9FFFFFF, 0x200004);
            CMD117(0xE2001E01, 0);
            CMD117(0xE3001001, 0x8000);
            CMD117(0xDF000000, 0);
            anim->frame++;
        } else {
            D_8007E010[arg0 * 92] = 1;
            D_8007E013[arg0 * 92] = -1;
            p->w0 = 0xDF000000;
            p->w1 = 0;
        }
        tail117(d, D_8005B218, anim->buffers[slot]);
        slot++;
        anim->countdown = 1;
        anim->slot = slot % 3;
    }
}
#else
static inline void tail117(Desc117 *d, void *v, Cmd117 *p) { Sub117 *sub; d->f1A=0;d->fC=v;func_800015AC(d,4);sub=d->f14;sub->f0=1;sub->f2C=4;sub->f30=0;sub->f34=0;sub->f2E=0;sub->f30=(u32)v;sub->f34=(u32)p; }
void func_80011764(s16 arg0) { u16 slot,type; u8 frame; Cmd117 *p,*g; Desc117 *d; Anim117 *anim=&D_8005AAA0[arg0]; anim->timer=D_8005AAAF[arg0].v-1; if(D_8005AAAF[arg0].v<0) { slot=D_8005AAAC[arg0*16]; frame=D_8005AAAE[arg0].v; type=D_8005AAAD[arg0*16]; p=anim->buf[slot]; d=&D_8005A3C0[arg0]; if(frame<D_80036DEC[type]) { if(D_800307A0==1) { if(type==6) {CMD117(0xFA000000,0xFFFFFF7F);} else {CMD117(0xFA000000,0x7F7F7F7F);} } else {CMD117(0xFA000000,(D_80036DFC[type]<<24)|(D_80036E04[type]<<16)|(D_80036E0C[type]<<8)|D_80036E14[type]);} p=buildCi4TextureDisplayList(D_8005B220+(frame+D_80036DF4[type])*8,p,type); CMD117(0xD9DFFFFB,0); CMD117(0xE3001001,0xC000); g=p++;g->w0=0x01004008;g->w1=osVirtualToPhysical(D_8005B218); CMD117(0x06000204,0x00040206); CMD117(0xE7000000,0); CMD117(0xD9FFFFFF,0x200004); CMD117(0xE2001E01,0); CMD117(0xE3001001,0x8000); CMD117(0xDF000000,0); D_8005AAAE[arg0].v++; } else { D_8007E010[arg0*92]=1; D_8007E013[arg0*92]=-1; p->w0=0xDF000000;p->w1=0; } tail117(d, D_8005B218, D_8005AAA0[arg0].buf[slot]); slot++; D_8005AAAF[arg0].v=1;D_8005AAAC[arg0*16]=slot%3; } }
#endif
