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
extern u32 D_80044590[];
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
void func_80001260(void) {
    s32 t; u8 *v; u32 *p; u32 i; s16 two; s32 *width; u8 *q;
    if(D_8002EEC4) {
        D_8002EEC4=0;
#ifdef TARGET_PC
        /* PC: D_8007E228 is the first word of a block that 42 of the developer program's files (74 across src/) name,
         * and most of them read its other fields at their N64 offsets (some through labels of their own, such as
         * D_8007E280 for +0x58). So it keeps its 4 bytes, and holds the segment-1 buffer as a 32-bit handle (port.h's
         * PTR_TO_SLOT) instead of the buffer's address, which 32 bits would cut in half. The buffer starts at
         * D_8007FC4F's address rounded down to a multiple of 16 (0x8007FC40 on the N64). */
        D_8007E228=PTR_TO_SLOT(((uptr)&D_8007FC4F>>4)<<4);
#else
        D_8007E228=(s32)(((u32)&D_8007FC4F>>4)<<4);
#endif
#ifdef TARGET_PC
        /* PC: the ROM symbols D_3C6D0/D_3C770 are not linked; the same block is read by its ROM address, into the
         * buffer that D_8007E228's handle stands for. */
        readRomSynchronousChunks(ROM_SEG1_INIT,SLOT_TO_PTR(D_8007E228),ROM_SEG1_INIT_END-ROM_SEG1_INIT);
#else
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
        two=2;p=D_80044590;
#ifdef TARGET_PC
        /* PC: not ported yet; the program stops here. Each of the four render-list records (0x4078 bytes) holds a
         * display list of 8-byte N64 commands up to +0x4000, the task at +0x4000/+0x4010 (pointer fields in
         * submitGraphicsTask's Nw2OSTask), the queue's address at +0x4050 and the address of +0x4058 at +0x4054; and
         * D_80044590, declared u32[] here and a table of pointers in submitGraphicsTask.c and
         * buildSceneSetupDisplayList.c, holds their addresses. On PC the commands are 16 bytes and the addresses 8, so
         * the record needs one PC layout, which the port's renderTaskThread must also read; until it is decided
         * (docs/port.md, "Shared records on PC"), storing the addresses here would cut them in half. */
        (void)v; (void)p; (void)two; (void)i;
        port_fatal("func_80001260: the render-list record (D_80044590) has no PC layout yet");
#else
        do {v=allocateHeap(0x4078);p[i]=(u32)v;*(s16 *)(v+0x4058)=two;*(u8 **)(v+0x4050)=D_80046768;*(u32 *)(v+0x4054)=p[i]+(unsigned)0x4058;i += 1;}while(i<4);
#endif
        D_80046858=allocateHeap(0x17000);
    }
    D_80047060=0;D_80047062=0;D_80047064=0;D_80047066=0;
}
