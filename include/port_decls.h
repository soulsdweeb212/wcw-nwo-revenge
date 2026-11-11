/* port_decls.h: the PC declarations of game functions and variables that game files declare with other types, PC only.
 *
 * common.h includes this file as the last line of its TARGET_PC section, so every game file sees it on the PC and none
 * sees it on the N64. It comes after port.h's types and renames and after common.h's PC layouts of the shared records
 * (Nw2Descr4BA8 and the others), so a declaration here can name those types. Each line below is the one declaration of
 * its name that the PC build uses:
 * - A function is declared with exactly the types of its definition. Where the definition has a PC version of its own
 *   ("PC definition" below), these are the PC version's types, and that version says why it differs from the N64's.
 * - A variable (the game's data: no C file defines one) is declared with the type of what it holds: a pointer where
 *   the game keeps an address in it, an integer where it keeps a number.
 * The game files' own declarations of these names keep the types that the matched N64 code was written with, and
 * those can differ: an s32 for a pointer, an s32 holding a float's bits, no parameters at all. On the N64 that does no
 * harm, because pointers, integers and floats are all 32 bits there, and most arguments travel in the same four
 * registers (the O32 calling convention); on a 64-bit PC such a call cuts a pointer in half or hands over another
 * number (docs/port.md, "Checking the calls between game files"). So where a file's own declaration differs from the
 * one here, it stands behind #ifndef TARGET_PC: the N64 build still reads it, and on the PC the compiler reads the
 * line here. A file that still declared one of these names in another way would stop the PC build with "conflicting
 * types" (clang says "redeclaration of 'X' with a different type" for a variable).
 * The compiler does not catch everything this way. Where a function here takes a float, a caller that passes an
 * integer holding the float's bits (an s32 variable, *(s32 *)&f, 0x3F800000) has that integer converted by value,
 * without a warning: an s32 holding 100.0f's bits arrives as 1120403456.0f. Such a caller's PC side must pass the
 * float itself. tools/port_calls.py finds the calls that do not: it compares each call with the same call in the
 * file's N64 view.
 *
 * Functions are grouped by the folder of the file that defines them (main, then overlay 2's four folders), in
 * address order, each with that file. A name is here only once every file of the developer program's set
 * (tools/port_filelist.py --set match) that uses it compiles against this declaration; a file outside the set that
 * uses it needs the same #ifndef TARGET_PC wrap before the PC build first compiles it. docs/port.md ("The PC
 * declarations: port_decls.h") says how to add a name. */
#ifndef PORT_DECLS_H
#define PORT_DECLS_H

/* ---- main: src/main ---- */

void func_80000580(void *arg0, void *arg1);                          /* func_80000580.c, PC definition */
void func_800005D0(void *arg0);                                      /* func_800005D0.c, PC definition */
void func_800014AC(void *arg0, f32 (*arg1)[4], f32 (*arg2)[4]);      /* func_800014AC.c, PC definition */
void func_800014D0(void *arg0, s16 arg1);                            /* func_800014D0.c */
void func_80002BC0(void *arg0);                                      /* func_80002BC0.c, PC definition */
s32 func_8000327C(s16 arg0);                                         /* func_8000327C.c, PC definition */
s32 func_800032A4(s16 a, s16 b, s16 c, s16 d, s32 e);                /* func_800032A4.c, PC definition */
s32 func_8000337C(void *arg0);                                       /* func_8000337C.c, PC definition */
void func_80004AFC(void *arg0);                                      /* func_80004AFC.c, PC definition */
void func_80004BA8(void *obj, void *rec, void *arena, s16 id, void *parent, void *child,
                   void *next);                                      /* func_80004BA8.c, PC definition */
void convertRgba16ToGrayscale(u16 *pixels, u16 pixelCount);          /* convertRgba16ToGrayscale.c */
void func_80005014(void *obj, void *rec, void *ownerA, void *ownerB); /* func_80005014.c, PC definition */
void func_80005204(void *obj, void *dl);                             /* func_80005204.c, PC definition */
void func_8000520C(void *obj, void *rec);                            /* func_8000520C.c, PC definition */
void func_80005304(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5,
                   f32 arg6);                                        /* func_80005304.c, PC definition */
void setupTiltedPerspectiveCamera(void *id, f32 tilt, f32 x, f32 y, f32 z, f32 tx, f32 ty,
                                  f32 tz); /* setupTiltedPerspectiveCamera.c, PC definition */
void func_800056F4(void *arg0, f32 arg1, f32 arg2, f32 arg3);        /* func_800056F4.c, PC definition */
void func_80006178(Gfx **glistp, void *timg, s32 fmt, u32 siz, u32 width, u32 height, s32 stepX, s32 stepY,
                   s32 startX, s32 startY, s32 endX, s32 endY, f32 fx, f32 fy); /* func_80006178.c */
void func_80007818(void *obj, void *recs, void *dl, s16 index);      /* func_80007818.c, PC definition */
void func_80007874(void *obj, void *recs, void *dl, s16 index);      /* func_80007874.c, PC definition */
void func_80007960(u16 *arg0, s32 arg1);                             /* func_80007960.c */
void func_800079D8(u16 *arg0, s32 arg1);                             /* func_800079D8.c */
void func_80007E04(void *arg0, f32 arg1, f32 arg2, f32 arg3);        /* func_80007E04.c, PC definition */
u8 *func_8000AA70(u8 *p, f32 *out, void *vec);                       /* func_8000AA70.c, PC definition */
s8 func_8000B710(s32 arg0);                                          /* func_8000B710.c */
void func_8000B884(u16 *out, s16 entity, s16 slot);                  /* func_8000B884.c */
void func_8000D424(u8 *dst, f32 x, f32 y, f32 z);                    /* func_8000D424.c */
void func_8000D718(void *objs, void *recs);                          /* func_8000D718.c, PC definition */
void func_8000F710(u8 *arg0, s32 side);                              /* func_8000F710.c */
void func_80010200(s16 id, s16 side, f32 angleArg);                  /* func_80010200.c, PC definition */
s32 func_800291C0(u8 *str, u8 *dst, s32 base, s32 pitch, s32 mult, u32 flags); /* func_800291C0.c */
void *func_8002A2FC(ResKey key, u16 flags);                          /* func_8002A2FC.c, PC definition */
u8 *func_8002AD04(s32 a, s32 b);                                     /* func_8002AD04.c, PC definition */
u8 *func_8002AD34(s32 a, s32 b);                                     /* func_8002AD34.c, PC definition */
u8 func_8002B5AC(s32 arg0);                                          /* func_8002B5AC.c */
u8 *func_8002B790(s32 arg0, u32 arg1);                               /* func_8002B790.c, PC definition */

/* ---- overlay 2: src/ovl2_80090000 ---- */

void func_8009A714(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5); /* func_8009A714.c, PC definition */

/* ---- overlay 2: src/code_8009D7A0 ---- */

void func_800B3B90(Wrestler *o, u8 *g, s16 dir);                     /* func_800B3B90.c */

/* ---- overlay 2: src/code_800BBA00 ---- */

s32 func_800BF150(Wrestler *arg0, s8 *arg1);                         /* func_800BF150.c */
void applyEntityMovementC8D84(Wrestler *ent, Wrestler *other, u16 flags,
                              f32 scale);                            /* applyEntityMovementC8D84.c */
s32 func_800D05E4(Wrestler *self, Wrestler *opponent, s16 arg2);    /* func_800D05E4.c */
s8 func_800D2670(Wrestler *w, f32 divisor);                          /* func_800D2670.c */
s32 func_800D2B64(Wrestler *w, f32 divisor, u16 dirMask, s32 bodyMask); /* func_800D2B64.c */
s32 func_800D36E8(f32 x, f32 y);                                     /* func_800D36E8.c, PC definition */
void func_800D37C0(s32 arg0, f32 arg1, void *arg2);                  /* func_800D37C0.c */
s32 func_800D3B24(void *arg0, void *arg1, f32 arg2, void *arg3);     /* func_800D3B24.c */
u16 getEntityPairFacingFlags(Wrestler *a, Wrestler *b);              /* getEntityPairFacingFlags.c */
s32 func_800D4D44(Wrestler *w, s16 action, f32 timer);               /* func_800D4D44.c */
s16 func_800D5438(Wrestler *w, s32 arg1);                            /* func_800D5438.c */
s32 func_800D6610(Wrestler *w, s32 arg1);                            /* func_800D6610.c, PC definition */
s32 func_800D6658(Wrestler *w, Wrestler *other, u16 arg2, s32 arg3,
                  f32 arg4);                                         /* func_800D6658.c, PC definition */
s32 func_800D9814(Wrestler *w);                                      /* func_800D9814.c */

/* ---- overlay 2: src/code_800DE9C0 ---- */

s32 func_800DECAC(Wrestler *w, s32 arg1, s32 arg2, s32 arg3);         /* func_800DECAC.c, PC definition */
s32 func_800DF3E4(Wrestler *self, Wrestler *other, s32 flags, f32 distance); /* func_800DF3E4.c */

/* ---- Variables: the segment their data lies in, and what they hold ---- */

/* main .data: the addresses of the three framebuffers (D_801B7800, D_8017F400, D_80147000, which func_80003098
 * clears); func_80002CC4 puts their handles (PTR_TO_SLOT) into the frame record, which keeps its N64 layout. */
extern void *D_8002EEB0[];
/* main .bss: the addresses of the four render-list records (Nw2RenderList in common.h, heap blocks), which
 * func_80001260 allocates at boot and never frees; buildSceneSetupDisplayList starts a frame's list in
 * D_80044590[D_8002EEBC]->dl, and submitGraphicsTask fills that record's task and sends it. */
extern Nw2RenderList *D_80044590[];
/* main .bss: the record of the view to draw, which func_80002BC0 stores (overlay 2 passes &D_800EB360[n]) and
 * func_80002CC4 reads; func_80002BA0, func_80002C0C and func_80002C74 clear it. */
extern void *D_800467FC;
/* main .bss: the draw table, the addresses of up to 512 work blocks (Nw2SceneWork, common.h), D_80047062 of them, which
 * func_80001544 registers, one per object; func_80001EA8 sorts it, func_80002324 and func_80002110 read it. The work
 * blocks keep their N64 layout and hold handles, but this table is a plain array of pointers. */
extern void *D_80046860[512];
/* main .bss: the draw lists, one row of up to 512 work-block addresses per frame bank, in draw order: func_80002110
 * fills a row from D_80046860, func_80002454 and func_80002CC4 read it. A plain array of pointers on PC, like
 * D_80046860; the work blocks (Nw2SceneWork) keep their N64 layout. */
extern void *D_80047070[2][512];
/* main .bss: the address of the sound-effect bank, which func_80003120 loads into a heap buffer on the N64;
 * func_8000327C and func_800032A4 hand it to libmus. On PC nothing sets it until audio is ported, so it stays NULL. */
extern void *D_800482D4;
/* main .bss: the cartridge's PI handle (an OSPiHandle *), which func_80008810 gets from osCartRomInit; the resource
 * streams (func_8000946C, initializeResourceStream, func_80009990) hand it to osEPiStartDma. */
extern void *D_8004859C;
/* main .bss: the four 0x6200-byte heap buffers of the resource streams, one per stream slot; func_80008810 allocates
 * them and func_80008AF0 frees them; func_8000946C, initializeResourceStream and func_80008CE8 point their slot's
 * stream at them. */
extern u8 *D_800485A0[];
/* main .bss: four slots of 23 display records (Nw2Descr4BA8, common.h), one slot per wrestler, beside the 23 objects
 * of D_800517D0's slot: buildObjectChain fills records 0-19 of a slot (func_8000C91C passes D_80050800[n]) and
 * func_8000D718 frees them (func_8000CD84). A slot is 0x3F4 bytes on the N64 and Nw2Descr4BA8[23] on PC. */
extern Nw2Descr4BA8 D_80050800[4][23];
/* main .bss: the ring's 23 display records, beside the objects of D_80057030: func_8000E920 fills them, func_8000EDE0
 * frees them through func_8000520C. */
extern Nw2Descr4BA8 D_800583F8[23];
/* main .bss: the display lists that func_8000E920 builds with func_80007020 (its result, the list's address);
 * func_8000EDE0 frees them. */
extern void *D_800587EC;
extern void *D_800588F8;
extern void *D_80058984;
/* main .bss: the display records of those three lists, which func_8000E920 builds with func_80007020 and
 * func_8000EDE0 frees. */
extern Nw2Descr4BA8 D_800587F0[6];
extern Nw2Descr4BA8 D_80058900[3];
extern Nw2Descr4BA8 D_80058988[3];
/* main .bss: the display lists that func_8000EF90 builds with func_80007020 for the arena's two resource sets (its
 * result, the list's address); func_8000F314 binds them to the arena's objects, func_8000F408 frees and clears them.
 * func_8000F4FC frees and rebuilds the first two when the arena changes. */
extern void *D_80058A0C;
extern void *D_80058F90;
extern void *D_80059520;
extern void *D_80059898;
extern void *D_80059C10;
extern void *D_80059CC8;
/* main .bss: the display records of those six lists, sized as the N64 reserves them: func_8000EF90 (and func_8000F4FC
 * for the first two) builds them with func_80007020, func_8000F408 frees them. */
extern Nw2Descr4BA8 D_80058A10[32];
extern Nw2Descr4BA8 D_80058FA0[32];
extern Nw2Descr4BA8 D_80059528[20];
extern Nw2Descr4BA8 D_800598A0[20];
extern Nw2Descr4BA8 D_80059C18[4];
extern Nw2Descr4BA8 D_80059CD0[4];
/* main .bss: the four per-player animation-command records (Nw2AnimatedCi4State, common.h): three heap blocks of
 * display-list commands that initializeMatchResources allocates and releaseAllResources1211C frees, then the slot,
 * type, frame and countdown bytes that func_80012364 sets and func_80011764 and func_80011B24 read. The N64 labels
 * D_8005AAAC to D_8005AAAF (those four bytes) have no PC symbol: code reads D_8005AAA0[n] by field name. */
extern Nw2AnimatedCi4State D_8005AAA0[4];
/* main .bss: the display lists that initializeMatchResources builds with func_80007020, one per display record of
 * D_8005AAE8 to D_8005B070; releaseAllResources1211C frees them, and func_80012364 hands them to func_80007874. */
extern void *D_8005AAE0;
extern void *D_8005AB40;
extern void *D_8005ABA0;
extern void *D_8005AC2C;
extern void *D_8005ACB4;
extern void *D_8005AD3C;
extern void *D_8005ADC4;
extern void *D_8005AE4C;
extern void *D_8005AEA8;
extern void *D_8005AFE4;
extern void *D_8005B06C;
/* main .bss: the display records of those eleven lists: initializeMatchResources builds them with func_80007020,
 * initializeMatchResources and func_80012364 hand them to func_80007874, releaseAllResources1211C frees them. */
extern Nw2Descr4BA8 D_8005AAE8[2];
extern Nw2Descr4BA8 D_8005AB48[2];
extern Nw2Descr4BA8 D_8005ABA8[3];
extern Nw2Descr4BA8 D_8005AC30[3];
extern Nw2Descr4BA8 D_8005ACB8[3];
extern Nw2Descr4BA8 D_8005AD40[3];
extern Nw2Descr4BA8 D_8005ADC8[3];
extern Nw2Descr4BA8 D_8005AE50[2];
extern Nw2Descr4BA8 D_8005AEB0[7];
extern Nw2Descr4BA8 D_8005AFE8[3];
extern Nw2Descr4BA8 D_8005B070[3];
/* main .bss: the six display lists that initializeMatchResources builds with func_80007020, one per record of
 * D_8005B110; releaseAllResources1211C frees and clears them, and func_80012B38 binds one to a view's object. */
extern void *D_8005B0F8[];
/* main .bss: the six display records of those lists (initializeMatchResources builds them; func_80012B38 binds one). */
extern Nw2Descr4BA8 D_8005B110[6];
/* main .bss: the heap block of four vertices (16 bytes each) that initializeMatchResources allocates and fills;
 * func_80011764 draws them, releaseAllResources1211C frees it and clears the address. */
extern void *D_8005B218;
/* main .bss: 26 picture pairs (Nw2TexPair, common.h) that initializeMatchResources loads and tints (func_800079D8),
 * func_80011764 draws and releaseAllResources1211C frees. The N64 label D_8005B224 (the first pair's pal) has no PC
 * symbol. */
extern Nw2TexPair D_8005B220[26];
/* main .bss: one picture pair per player: func_8000C1B8 loads it, func_8000B728 copies it into the player's display
 * record 5, func_8000CD84 frees it. The N64 label D_8007045C (the first pair's pal) has no PC symbol. */
extern Nw2TexPair D_80070458[4];
/* main .bss: the four stream records, one per wrestler's animation stream (Nw2AnimStream, common.h: a read cursor and
 * a destination inside D_800485A0[n], the ROM address of the next chunk, the cartridge requests and their queues).
 * func_80008810 sets them up; initializeResourceStream and func_8000946C start a stream; func_80009990 reads on;
 * func_8000A310 and func_8000A3DC decode frames at the cursor; func_80008CE8 plays a frame; func_8000AD00 and
 * func_800085E4 read id; func_80008C94 sets mtx. On the N64 its labels (D_800706AC, D_800706B0, D_800706C2,
 * D_800706C4 and others) reach its fields; on PC they do not exist, and files read the records by field name. */
extern Nw2AnimStream D_800706A8[4];
/* main .bss: four slots of 23 display records, one slot per wrestler's body parts, beside the objects of
 * D_800651A0's slot: func_8000C91C clears them, func_8000BDD0 and func_8000C1B8 load them, func_8000CD84 frees them.
 * Record 5 is the head, whose texture and palette func_8000B728 refills and applyEntityTextureMasks and
 * func_8000C784 mask (with records 3 and 4). The N64 labels D_80073ECC, D_80073F34, D_80073FA4 and D_80073FA8 have no
 * PC symbol: code reads D_80073EB0[n][k] by field name. */
extern Nw2Descr4BA8 D_80073EB0[4][23];
/* main .bss: the heap table of 0x24-byte animation records (resource 0x20F), which func_80008810 loads and
 * func_80008AF0 frees; decodeAnimationMetadata, func_800085E4, func_800087DC and func_8000AD00 read record
 * id - 0xE39. */
extern u8 *D_8007BD38;
/* main .bss: the players' mesh arenas (Nw2MeshArena, common.h; room for 6, players 0-3 use 0-3), which hand out the
 * vertex and display-list buffers of a player's meshes: func_8000C91C clears both bases the first time and sizes arena
 * n with func_80007A74, func_8000BDD0 passes &D_8007C3D0[n] to func_80004BA8 (a display record's f28), func_8000CFD4
 * empties it (func_80007AFC) and func_8000CD84 frees it (func_80007B08). The N64 label D_8007C3D8 (arena 0's cmds)
 * has no PC symbol. */
extern Nw2MeshArena D_8007C3D0[NW2_MESH_ARENA_COUNT];
/* main .bss: the texture-cache table: per player and body part, the heap block that loadTextureIntoCacheSlot loads
 * the part's colours and category ids into, or NULL (D_8007C318 holds each block's size in halfwords). func_8000C91C
 * clears it, func_8000CD84 and func_8000CFD4 free a player's blocks, func_8000B884 reads them. On the N64 it is the
 * first 0x170 bytes of a 0x1980-byte block whose animation rows start at +0x180; on PC those rows are D_8007C5B8. */
extern void *D_8007C438[4][23];
/* main .bss, a PC-only name: the four 0x600-byte rows of animation ids, one per player, which loadPlayerResourceSet
 * and func_800C0354 load and func_800D5438 reads. On the N64 they lie at D_8007C438 + 0x180 (0x8007C5B8), where the
 * N64 has no symbol; on PC the table before them is 0x2E0 bytes, so they are a variable of their own. */
extern u16 D_8007C5B8[4][0x300];
/* overlay 2 .data: the addresses of six 16-colour palettes in overlay 2's own data (0x800E2DC0 to 0x800E2E60, 0x20
 * bytes apart), one per icon id; func_800986DC reads one into its palette command. The port must fill it with the
 * host addresses of those palettes, not the N64 words. */
extern void *D_800E2E80[];
/* overlay 2 .data: the heading (a 4096-unit angle) of each of the four directions that a wrestler's dirIndex picks;
 * read only. func_800D1EA8 declared it void *[] only to pass an entry to its own declaration of func_800D37C0. */
extern s32 D_800E3C90[];
/* overlay 2 .bss: the picture pairs (Nw2TexPair, common.h) that func_800922C0 loads and func_80094424 frees. The N64
 * labels D_800E9BE0 and D_800E9C30, which func_80094A9C indexes from 1, lie one pair before D_800E9BE8 and nine pairs
 * into it; they have no PC symbol, and code reads D_800E9BE8[n - 1] and D_800E9BE8[n + 9]. */
extern Nw2TexPair D_800E78A8[19];
extern Nw2TexPair D_800E7DA0[11];
extern Nw2TexPair D_800E9BE8[20];
extern Nw2TexPair D_800EA0E0[4];
extern Nw2TexPair D_800EA100[2];
extern Nw2TexPair D_800EA110[20];
extern Nw2TexPair D_800EA5D8;
extern Nw2TexPair D_800EA5E0;
extern Nw2TexPair D_800EA748[2];
/* overlay 2 .bss: the display records of the HUD and the match overlays (Nw2Descr4BA8, common.h), which func_800922C0
 * builds with func_80090380 and func_80094424 frees with releaseObjectHeapBlocks. The N64 labels D_800E7F8C and
 * D_800E8014, one record before D_800E7FB8 and D_800E8040, have no PC symbol: code reads D_800E7FB8[k - 1] and
 * D_800E8040[k - 1]. */
extern Nw2Descr4BA8 D_800E7FB8[3];
extern Nw2Descr4BA8 D_800E8040[3];
extern Nw2Descr4BA8 D_800E8438[2][10];
extern Nw2Descr4BA8 D_800E87A8[2][10];
extern Nw2Descr4BA8 D_800E8CE8[2];
extern Nw2Descr4BA8 D_800E8D40[2];
extern Nw2Descr4BA8 D_800E8F60[7];
extern Nw2Descr4BA8 D_800E9098[7];
extern Nw2Descr4BA8 D_800E9398[2];
extern Nw2Descr4BA8 D_800E93F0[2];
extern Nw2Descr4BA8 D_800E97C0[2];
extern Nw2Descr4BA8 D_800E9818[2];
extern Nw2Descr4BA8 D_800E9C88[4];
extern Nw2Descr4BA8 D_800EA1B0[4];
extern Nw2Descr4BA8 D_800EA5E8[4];
extern Nw2Descr4BA8 D_800EA698[4];
extern Nw2Descr4BA8 D_800EAAC8[4];
extern Nw2Descr4BA8 D_800EAC58;
extern Nw2Descr4BA8 D_800EAFF8[4];
/* overlay 2 .bss: the object (Nw2SceneObj, common.h: the N64 layout, its addresses as handles) that draws the HUD's
 * display list: func_800982AC sets it up; func_80098560 puts the handle of the list it has just built (one of its three
 * buffers, D_800EB18C) into dl and sets or clears bit 0x80 of its work block's kind; func_800984C8 clears dl. The N64
 * labels D_800EB0C0 (dl), D_800EB0C4 (work) and D_800EB0C9 (flat) have no PC symbol. */
extern Nw2SceneObj D_800EB0B0;
/* overlay 2 .bss: the two HUD icons (Nw2HudIcon, common.h): func_800982AC sets them up, func_80097E34 and func_80097EF4
 * load their pictures, func_800984C8 frees them, func_800986DC draws one. The N64 labels D_800EB1A4 and D_800EB1B4
 * (their tex) have no PC symbol. */
extern Nw2HudIcon D_800EB19C;
extern Nw2HudIcon D_800EB1AC;
/* overlay 2 .bss: the object that draws func_80099968's display list in the same way: func_80099628 sets it up;
 * func_80099968 puts the handle of the list it has just built (one of D_800EB29C) into dl and sets or clears bit 0x80
 * of its work block's kind; func_800998EC clears dl. The N64 labels D_800EB1D0 (dl) and D_800EB1D4 (work) have no PC
 * symbol. */
extern Nw2SceneObj D_800EB1C0;
/* overlay 2 .bss: one 16-byte row per wrestler slot (D_800FADB8, four rows, up to D_800EB600): the offset from the
 * attacker that func_800D1014 hands to func_800D3E40 to place the opponent. x and y are 0, z is the distance from
 * func_800D3890 and angle a 4096-unit angle (a heading after step 0, a turn from the attacker's heading after
 * step 2). The N64 code names y, z and angle by the labels D_800EB5C4, D_800EB5C8 and D_800EB5CC, which have no
 * symbol on PC; func_800D1014 is the only file that uses the row. */
extern Nw2DirectionResult D_800EB5C0[];
/* overlay 2 .bss: the colour-overlay object (Nw2SceneObj, common.h): func_80099F70 sets it up and builds its list
 * (buildColorOverlayDisplayList); func_8009D7A0 and func_8009D844 rebuild the list and set or clear bit 0x80 of its
 * work block's kind; func_8009A5F4 frees its buffers (func_80006D14). The N64 label D_800F99D4 (its work) has no PC
 * symbol. common.h declares the object as an s32 for the N64 only. */
extern Nw2SceneObj D_800F99C0;
/* overlay 2 .bss: the heading (a 4096-unit angle) from the current wrestler's pelvis to its opponent's, which
 * func_800A712C writes for func_8009D8D0 each frame, beside the distance D_800F9B0C; the state handlers read it. On
 * the N64 it is the angle of the match-distance block (Nw2DirectionResult), 8 bytes after D_800F9B0C. */
extern s32 D_800F9B14;

#endif /* PORT_DECLS_H */
