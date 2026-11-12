/* @header
 * func_80001260
 * VRAM 0x80001260 | ROM 0x1E60 | size 0x24C
 * asm: asm/nonmatchings/main/func_80001260.s
 */
#include "common.h"

extern s16 D_8002EEC4;
extern s32 osTvType;
extern u8 D_8007FC4F;
extern s32 D_8007E228;
typedef struct {u32 words[20];} VideoMode;
extern VideoMode D_80037540,D_80037590;
#ifndef TARGET_PC /* on PC, port_decls.h declares D_80044590 (the addresses of the four render-list records) */
extern u32 D_80044590[];
#endif
extern void *D_800445A0,*D_800445A4,*D_800445A8;
extern u8 D_800445B0[],D_80046760[],D_80046768[],D_80046780[],D_800467C0[],D_800467D8[],D_800467E0[],D_800467F8[],D_80046808[];
extern s32 D_80046810,D_80046828,D_80046830,D_80046844;
extern void *D_80046858;
extern s16 D_80047060,D_80047062,D_80047064,D_80047066;
extern u8 D_3C6D0[],D_3C770[];
#ifndef TARGET_PC /* on PC, port.h declares the loader functions */
extern s32 readRomSynchronousChunks(void *, void *, s32);
#endif
#ifndef TARGET_PC /* on PC, port_decls.h declares func_80000580 (it returns nothing) */
extern s32 func_80000580(void *, void *);
#endif
extern void *allocateHeap(u32);
extern s32 osSetIntMask(s32);
extern s32 osCreateMesgQueue(void *, void *, s32);
extern s32 osCreateThread(void *, s32, void *, s32, void *, s32);
extern void osStartThread(void *);
extern s32 osViSetMode(void *);
extern void osViSetSpecialFeatures(s32);
extern void osViBlack(s32);
extern s32 bcopy(void *, void *, s32);
extern void func_80002CC4(void);
static __inline__ void initRenderQueue(u8 *q) {osCreateMesgQueue(q,D_80046780,16);func_80000580(D_80046760,q);}
static __inline__ void setVideoModeFromWidth(s32 *width) {osViSetMode((u8 *)width-8);}
#ifdef TARGET_PC
/* PC: the segment-1 block. On the N64 func_80001260 copies it from the ROM (ROM_SEG1_INIT, 0xA0 bytes) into a buffer
 * at 0x8007FC40: the viewport (eight s16) at +0, then from +0x10 the display list that every frame's first task runs
 * (buildSceneSetupDisplayList branches to it): the viewport, clipping, the scissor and the render modes, as the N64's
 * 8-byte commands. Both are big-endian, and Fast3D needs the viewport in the PC's byte order and the list as port.h's
 * 16-byte commands, which take twice the room. So the PC builds the block in a buffer of its own: the viewport, then
 * the commands. The list's only address is the viewport's (G_MOVEMEM, segment 1 offset 0), which Fast3D would take for
 * a pointer as it stands, so it becomes the block's own address; another address would stop the program. */
static u8 *makeSegment1Block(void) {
    u8 raw[ROM_SEG1_INIT_END - ROM_SEG1_INIT];
    u32 count = (sizeof(raw) - 0x10) / 8;
    u8 *block = allocateHeap(0x10 + count * sizeof(Gfx));
    s16 *vp = (s16 *)block;
    Gfx *dl = (Gfx *)(block + 0x10);
    u32 i;

    readRomSynchronousChunks(ROM_SEG1_INIT, raw, sizeof(raw));
    for (i = 0; i < 8; i++) {
        vp[i] = (s16)READ_BE16(raw + 2 * i);
    }
    for (i = 0; i < count; i++) {
        u32 w0 = READ_BE32(raw + 0x10 + 8 * i);
        u32 w1 = READ_BE32(raw + 0x10 + 8 * i + 4);
        u32 op = w0 >> 24;

        dl[i].w0 = w0;
        if (op == 0xDC && (w1 >> 24) == 0x01) {
            dl[i].w1 = DL_ADDR(block + (w1 & 0xFFFFFF)); /* G_MOVEMEM from segment 1 */
        } else if (op == 0xDC || op == 0xDE || op == 0x01 || op == 0xFD || op == 0xFF) {
            port_fatal("func_80001260: segment-1 command %08X %08X has an address the port does not convert", w0, w1);
        } else {
            dl[i].w1 = w1;
        }
    }
    return block;
}
#endif
void func_80001260(void) {
    s32 t; u8 *v; u32 *p; u32 i; s16 two; s32 *width; u8 *q;
    if(D_8002EEC4) {
        D_8002EEC4=0;
#ifdef TARGET_PC
        /* PC: D_8007E228 is the first word of a block that 42 of the developer program's files (74 across src/) name,
         * and most of them read its other fields at their N64 offsets (some through labels of their own, such as
         * D_8007E280 for +0x58). So it keeps its 4 bytes, and holds the segment-1 buffer as a 32-bit handle (port.h's
         * PTR_TO_SLOT) instead of the buffer's address, which 32 bits would cut in half. The buffer is a PC block of
         * its own (makeSegment1Block, above), which Fast3D can draw from. */
        D_8007E228=PTR_TO_SLOT(makeSegment1Block());
#else
        D_8007E228=(s32)(((u32)&D_8007FC4F>>4)<<4);
        readRomSynchronousChunks(D_3C6D0,(void *)D_8007E228,D_3C770-D_3C6D0);
#endif
        q=D_80046768;
        initRenderQueue(q);
        q=D_800445B0;
        osCreateThread(q,3,func_80002CC4,0,D_80046760,0x46);
        osCreateMesgQueue(D_800467C0,D_800467D8,1);
        osCreateMesgQueue(D_800467E0,D_800467F8,1);
        osStartThread(q);
        D_800445A0=allocateHeap(0x400);D_800445A4=allocateHeap(0xC00);D_800445A8=allocateHeap(0x10008);
        if(osTvType==1) bcopy(&D_80037540,D_80046808,0x50);
        else bcopy(&D_80037590,D_80046808,0x50);
        t=osSetIntMask(0x80401);
        width=&D_80046810;*width=0x1E0;D_80046828=0x300;D_80046830=0x3C0;D_80046844=0x3C0;
        i=0;
        osSetIntMask(t);
        setVideoModeFromWidth(width);
        osViSetSpecialFeatures(0x6A);osViBlack(1);
#ifdef TARGET_PC
        /* PC: D_80044590 is a table of pointers to the records (port_decls.h), which the u32 cursor p cannot step. */
        two=2;
#else
        two=2;p=D_80044590;
#endif
#ifdef TARGET_PC
        /* PC: each render-list record has its PC layout, Nw2RenderList (common.h): 0x800 16-byte commands, the
         * scheduler's task with 8-byte pointers, and the done message. So it is allocated by sizeof, its fields are
         * set by name, and D_80044590 holds the four addresses. The done message is a 4-byte value in the game's
         * queues, so the task holds a handle of the message's address (port.h's PTR_TO_SLOT), which func_80002CC4
         * turns back. The records are never freed, so their handles last as long as the program. */
        (void)v; (void)p;
        do {
            Nw2RenderList *rl = allocateHeap(sizeof(Nw2RenderList));
            D_80044590[i] = rl;
            rl->done.type = two;
            rl->sc.msgQ = D_80046768;
            rl->sc.msg = PTR_TO_SLOT(&rl->done);
            i += 1;
        } while (i < 4);
#else
        do {v=allocateHeap(0x4078);p[i]=(u32)v;*(s16 *)(v+0x4058)=two;*(u8 **)(v+0x4050)=D_80046768;*(u32 *)(v+0x4054)=p[i]+(unsigned)0x4058;i += 1;}while(i<4);
#endif
        D_80046858=allocateHeap(0x17000);
    }
    D_80047060=0;D_80047062=0;D_80047064=0;D_80047066=0;
}
