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
void func_80005304(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5,
                   f32 arg6);                                        /* func_80005304.c, PC definition */
void setupTiltedPerspectiveCamera(void *id, f32 tilt, f32 x, f32 y, f32 z, f32 tx, f32 ty,
                                  f32 tz); /* setupTiltedPerspectiveCamera.c, PC definition */
void func_800056F4(void *arg0, f32 arg1, f32 arg2, f32 arg3);        /* func_800056F4.c, PC definition */
void func_80006178(Gfx **glistp, void *timg, s32 fmt, u32 siz, u32 width, u32 height, s32 stepX, s32 stepY,
                   s32 startX, s32 startY, s32 endX, s32 endY, f32 fx, f32 fy); /* func_80006178.c */
void func_80007E04(void *arg0, f32 arg1, f32 arg2, f32 arg3);        /* func_80007E04.c, PC definition */
s8 func_8000B710(s32 arg0);                                          /* func_8000B710.c */
void func_8000D424(u8 *dst, f32 x, f32 y, f32 z);                    /* func_8000D424.c */
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

s32 func_800DF3E4(Wrestler *self, Wrestler *other, s32 flags, f32 distance); /* func_800DF3E4.c */

/* ---- Variables: the segment their data lies in, and what they hold ---- */

/* main .bss: the record of the view to draw, which func_80002BC0 stores (overlay 2 passes &D_800EB360[n]) and
 * func_80002CC4 reads; func_80002BA0, func_80002C0C and func_80002C74 clear it. */
extern void *D_800467FC;
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
/* main .bss: the display lists that func_8000E920 builds with func_80007020 (its result, the list's address);
 * func_8000EDE0 frees them. */
extern void *D_800587EC;
extern void *D_800588F8;
extern void *D_80058984;
/* main .bss: the display lists that func_8000EF90 builds with func_80007020 for the arena's two resource sets (its
 * result, the list's address); func_8000F314 binds them to the arena's objects, func_8000F408 frees and clears them.
 * func_8000F4FC frees and rebuilds the first two when the arena changes. */
extern void *D_80058A0C;
extern void *D_80058F90;
extern void *D_80059520;
extern void *D_80059898;
extern void *D_80059C10;
extern void *D_80059CC8;
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
/* main .bss: the six display lists that initializeMatchResources builds with func_80007020, one per record of
 * D_8005B110; releaseAllResources1211C frees and clears them, and func_80012B38 binds one to a view's object. */
extern void *D_8005B0F8[];
/* main .bss: the heap block of four vertices (16 bytes each) that initializeMatchResources allocates and fills;
 * func_80011764 draws them, releaseAllResources1211C frees it and clears the address. */
extern void *D_8005B218;
/* main .bss: the heap table of 0x24-byte animation records (resource 0x20F), which func_80008810 loads and
 * func_80008AF0 frees; decodeAnimationMetadata, func_800085E4, func_800087DC and func_8000AD00 read record
 * id - 0xE39. */
extern u8 *D_8007BD38;
/* overlay 2 .data: the addresses of six 16-colour palettes in overlay 2's own data (0x800E2DC0 to 0x800E2E60, 0x20
 * bytes apart), one per icon id; func_800986DC reads one into its palette command. The port must fill it with the
 * host addresses of those palettes, not the N64 words. */
extern void *D_800E2E80[];
/* overlay 2 .data: the heading (a 4096-unit angle) of each of the four directions that a wrestler's dirIndex picks;
 * read only. func_800D1EA8 declared it void *[] only to pass an entry to its own declaration of func_800D37C0. */
extern s32 D_800E3C90[];
/* overlay 2 .bss: the display list that func_80098560 has just built (one of its three buffers, D_800EB18C);
 * func_800984C8 clears it. */
extern void *D_800EB0C0;
/* overlay 2 .bss: the display list that func_80099968 has just built (one of its three buffers, D_800EB29C);
 * func_800998EC clears it. */
extern void *D_800EB1D0;
/* overlay 2 .bss: the heading (a 4096-unit angle) from the current wrestler's pelvis to its opponent's, which
 * func_800A712C writes for func_8009D8D0 each frame, beside the distance D_800F9B0C; the state handlers read it. On
 * the N64 it is the angle of the match-distance block (Nw2DirectionResult), 8 bytes after D_800F9B0C. */
extern s32 D_800F9B14;

#endif /* PORT_DECLS_H */
