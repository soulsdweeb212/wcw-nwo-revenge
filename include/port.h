/* port.h: what the game's C needs to build both for the N64 and for the PC port (Turnbuckle Dive).
 *
 * common.h includes this file at its end, after the types it uses, so every game file sees it. The PC build compiles
 * the game files with TARGET_PC defined; build.py, the N64 build, never defines it.
 * - On N64 every macro here stands for the original code (READ_BE32(p) is *(u32 *)(p), and so on) and the only other
 *   item is one typedef, so the compiler produces the same code and the ROM stays byte-identical.
 * - Under TARGET_PC the same names do the 64-bit, little-endian equivalent. Gfx, the display-list command, is defined
 *   only there, and the PC-only part at the end declares the ROM loader's PC interface and renames the SDK functions
 *   that the port replaces.
 * docs/port.md explains how the two builds fit together. */
#ifndef PORT_H
#define PORT_H

#ifdef TARGET_PC
/* Besides the PC forms of the macros and their helpers, these exist only under TARGET_PC: port_fatal below,
 * WRITE_BE16/32 (PC code that writes into data that stays big-endian), the check that the CPU is little-endian, Gfx
 * (the display-list command), and the PC-only part at the end of this file: the ROM loader's PC interface (RomAddr,
 * ResDesc, the ROM_ addresses and the loader's declarations), PortIoMesg (a cartridge read request), ResKey (the key
 * of the resource-name cache) and the renames of the SDK functions that the port replaces.
 * This file does not include port_decls.h (the PC declarations of game functions and variables that game files declare
 * with other types): common.h includes it as the last line of its TARGET_PC section, after the PC layouts of the
 * shared records, whose types it uses.
 *
 * System headers go before the renames at the end of this file, which would otherwise rename their declarations too
 * (bzero in <strings.h>, for example). A game file that needs a system header includes it before common.h.
 * <stddef.h> gives game files offsetof, which their PC layout checks use. It comes after common.h's NULL and replaces
 * it with its own, which is the same. */
#include <stddef.h>
#include <stdint.h>

/* Prints a printf-style message and stops the program. The port implements it; the PC code calls it where the N64
 * would hang or crash, for example on a resource id that does not exist. */
_Noreturn void port_fatal(const char *fmt, ...);
#endif

/* uptr: an unsigned integer as wide as a pointer, for code that does arithmetic on addresses. The N64 code casts
 * pointers to u32; on a 64-bit PC that would cut the address in half. */
#ifdef TARGET_PC
typedef uintptr_t uptr;
#else
typedef u32 uptr;
#endif

/* READ_BE16, READ_BE32, READ_BE64: read a big-endian value, such as a field of a resource loaded from ROM. The N64 is
 * big-endian, so the game reads such a value with a plain *(u32 *)p; a PC is little-endian and would see its bytes
 * reversed. The PC versions assemble the value one byte at a time, which also works at any alignment. */
#ifdef TARGET_PC
static inline u16 port_be16(const void *p) {
    const u8 *b = (const u8 *)p;
    return (u16)((b[0] << 8) | b[1]);
}
static inline u32 port_be32(const void *p) {
    const u8 *b = (const u8 *)p;
    return ((u32)b[0] << 24) | ((u32)b[1] << 16) | ((u32)b[2] << 8) | (u32)b[3];
}
static inline u64 port_be64(const void *p) {
    return ((u64)port_be32(p) << 32) | port_be32((const u8 *)p + 4);
}
#define READ_BE16(p) port_be16((const void *)(p))
#define READ_BE32(p) port_be32((const void *)(p))
#define READ_BE64(p) port_be64((const void *)(p))
/* WRITE_BE16, WRITE_BE32 (PC only): store a value in the N64's byte order, into data that stays big-endian on PC:
 * textures and palettes, which Fast3D reads big-endian (DecodePaletteEntry in LUS's src/fast/interpreter.cpp). The
 * N64 code stores such a value with a plain assignment, so these are used only inside TARGET_PC blocks, and the N64
 * build has no form of them. */
static inline void port_write_be16(void *p, u16 v) {
    u8 *b = (u8 *)p;
    b[0] = (u8)(v >> 8);
    b[1] = (u8)v;
}
static inline void port_write_be32(void *p, u32 v) {
    port_write_be16(p, (u16)(v >> 16));
    port_write_be16((u8 *)p + 2, (u16)v);
}
#define WRITE_BE16(p, v) port_write_be16((void *)(p), (u16)(v))
#define WRITE_BE32(p, v) port_write_be32((void *)(p), (u32)(v))
/* The PC code assumes a little-endian CPU, as the PCs the port runs on are (x86-64, and ARM64 under Windows, macOS and
 * Linux). Where the N64 code reads a value through a view of another width, such as a u64 as two u32 or a u16 and the
 * u16 after it as one u32, its PC version is written for that byte order (func_800B955C, func_8009EDBC). GCC and
 * Clang, the compilers that build the game's C, define __BYTE_ORDER__. */
_Static_assert(__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__, "the PC code assumes a little-endian CPU");
#else
#define READ_BE16(p) (*(u16 *)(p))
#define READ_BE32(p) (*(u32 *)(p))
#define READ_BE64(p) (*(u64 *)(p))
#endif

/* Gfx: one display-list command, PC only.
 * - On N64 a command is two u32 words, 8 bytes. Each game file that builds display lists defines its own type for it,
 *   as libultra's gbi.h would: Gfx in some files, Nw2Gfx, Gfx96, Nw2RdpCmd and other names elsewhere.
 * - On PC a command is two pointer-wide words, 16 bytes, laid out like LUS's Gfx. The second word can then hold a whole
 *   pointer, and a list that the game builds can be handed to Fast3D (LUS's renderer) as it is.
 * - Game files never include LUS's headers, whose Gfx would clash with their own. On PC, the game files that define a
 *   type named Gfx keep it behind #ifndef TARGET_PC, and the files whose lists the port draws make their command type
 *   this Gfx.
 * - common.h refers to it as struct Gfx (its Nw2RdpCmd) before this file defines it. C allows that for a type that is
 *   only used through pointers until its definition. */
#ifdef TARGET_PC
typedef struct Gfx {
    uintptr_t w0;
    uintptr_t w1;
} Gfx;
_Static_assert(sizeof(Gfx) == 16, "Gfx must be 16 bytes, like LUS's Gfx on a 64-bit PC");
#endif

/* DL_ADDR(p): the address of display-list data (another display list, vertices, a texture) as it is written into a
 * display-list word. The N64 code writes the physical address: a link constant such as D_C95B8 is the address of the
 * data (D_800C95B8) minus 0x80000000. The N64 form computes the same, and the compiler folds the subtraction into the
 * address it loads, so DL_ADDR(D_800C95B8) gives the same instructions as (u32)D_C95B8. On PC the word holds the
 * pointer itself, so it must be even: Fast3D reads a word with bit 0 set as a segmented address, takes its bits 24 and
 * up as a segment number and looks that up in its table of 16 segments (Interpreter::SegAddr in LUS's
 * src/fast/interpreter.cpp). For a pointer at 0x10000000 or above that number is past the end of the table, and a lower
 * pointer would be read as an offset into a segment. The PC version stops the program on an odd address instead. */
#ifdef TARGET_PC
static inline uintptr_t port_dl_addr(const void *p) {
    if ((uintptr_t)p & 1) {
        port_fatal("DL_ADDR: odd address %p", p);
    }
    return (uintptr_t)p;
}
#define DL_ADDR(p) port_dl_addr((const void *)(p))
#else
#define DL_ADDR(p) ((u32)(p) - 0x80000000)
#endif

/* PTR_TO_SLOT(p) and SLOT_TO_PTR(s): a pointer kept in a 4-byte field of a record whose layout other code depends on,
 * such as the 12-byte pad records D_8006E178 (filled in func_80003D20, read in func_800C5718). A 64-bit pointer does
 * not fit there, so on PC the field holds a 32-bit handle, and the port's handle table turns pointers into handles
 * and back. On N64 both macros give back their argument. */
#ifdef TARGET_PC
/* The rules of handles on PC:
 * - A handle lives only in a 4-byte field whose width something outside its struct fixes: a field of a record that
 *   keeps its N64 layout (the scene objects and work blocks in common.h, the frame records D_800EB360 with their two
 *   framebuffers at +0 and +4, the pad records), or a message in one of the game's queues (4 bytes each). Every other
 *   record gets a PC layout with real pointers.
 * - A handle names an address, not an allocation: PTR_TO_SLOT gives the same handle for the same address every time,
 *   and a handle stays valid for the whole run (there is no release). A handle kept after its heap block is freed
 *   means what the N64's stale 32-bit address meant.
 * - PTR_TO_SLOT(NULL) is 0 and SLOT_TO_PTR(0) is NULL. SLOT_TO_PTR of a value that PTR_TO_SLOT never gave stops the
 *   program (port_fatal), and so does a full table.
 * - A field that holds a handle is never stepped by arithmetic: code turns it into a pointer first and moves that.
 *   Never pass PTR_TO_SLOT the address of a local variable. */
u32 port_ptr_to_slot(void *p);
void *port_slot_to_ptr(u32 slot);
#define PTR_TO_SLOT(p) port_ptr_to_slot((void *)(p))
#define SLOT_TO_PTR(s) port_slot_to_ptr((u32)(s))
#else
#define PTR_TO_SLOT(p) (p)
#define SLOT_TO_PTR(s) (s)
#endif

#ifdef TARGET_PC
/* ---- PC only: the ROM loader ---- */

/* A ROM address: an offset into the cartridge image, which the N64 code hands to the PI DMA. On PC the port keeps the
 * checked ROM in memory and port_rom_read copies from it. A RomAddr is never a host pointer. */
typedef u32 RomAddr;

/* The resource descriptor that lookupResourceDescriptor and func_80003684 write. On N64 it is {u8 *, u8 *, s32, s32},
 * and the two "pointers" hold ROM addresses. On PC those two fields are RomAddr, so the record stays 16 bytes: the
 * callers keep it in s32[4], u8[16] and other 16-byte buffers, which a layout with 64-bit pointers (24 bytes) would
 * overflow. */
typedef struct {
    RomAddr start; /* ROM address of the resource's data */
    RomAddr end;   /* ROM address where the next resource starts */
    s32 size;      /* size in RAM once loaded (decompressed) */
    s32 packed;    /* end - start if the resource is LZSS-compressed, else 0 */
} ResDesc;
_Static_assert(sizeof(ResDesc) == 16, "ResDesc must stay 16 bytes, like the N64 descriptor");

/* ROM addresses the PC code uses in place of the decomp's ROM symbols (build.json), which the PC build does not
 * link: on PC, ROM data is reached only by offset, through port_rom_read. */
#define ROM_RES_BASE      0x000DAC50u /* D_000DAC50: the resource archive; the table's offsets count from here */
#define ROM_RES_TABLE     0x00CE2752u /* D_00CE2752: resource offset table, a big-endian u32 per id plus one */
#define ROM_RES_TABLE_SZ  0x77A8u     /* its size in bytes */
#define RES_COUNT         0x1DE9u     /* resource ids run from 1 to RES_COUNT */
#define ROM_SEG1_INIT     0x0003C6D0u /* D_3C6D0: the block func_80001260 copies to segment 1 (viewport, setup list) */
#define ROM_SEG1_INIT_END 0x0003C770u /* D_3C770: its end */
#define ROM_MUS_BANK      0x00CE9F00u /* D_00CE9F00: libmus pointer bank for songs, up to ROM_MUS_WAVES */
#define ROM_MUS_WAVES     0x00CEC610u /* D_00CEC610: the wave bank libmus plays those songs' samples from */
#define ROM_SFX_BANK      0x00E35070u /* D_00E35070: libmus pointer bank for sound effects, up to ROM_SFX_WAVES */
#define ROM_SFX_WAVES     0x00E3B300u /* D_00E3B300: the wave bank of the sound effects */

/* The loader functions, declared once with ROM addresses typed as RomAddr. Game files keep their own declarations of
 * these behind #ifndef TARGET_PC: those take pointers where the PC takes a RomAddr, and the matched N64 code depends
 * on their exact types. */
void readRomSynchronousChunks(RomAddr src, void *dst, s32 size);
void lookupResourceDescriptor(void *out, u32 id);
void *func_80003684(void *out, s32 id, void *buf);

/* Implemented by the port. port_rom_read copies size bytes of the checked ROM image, starting at src, to dst; a range
 * outside the image stops the program. func_80003684 calls port_res_loaded once a whole resource is in RAM: the one
 * place where a whole resource loaded by func_80003684 can be tracked and its byte order converted. (Code that reads
 * ROM bytes with readRomSynchronousChunks directly, such as func_80008810, gets them unconverted.) */
void port_rom_read(void *dst, RomAddr src, u32 size);
void port_res_loaded(u32 id, void *buf, s32 size);

/* The game's heap on PC, implemented by the port; allocateHeap and releaseHeapBlock call them. The N64's heap cannot run
 * on a 64-bit PC as it is: its block header {next, size, magic} is 16 bytes there and 24 here, but it counts in 16-byte
 * units and finds a block's header 0x10 bytes before the block. port_heap_alloc returns a block of at least `bytes`
 * bytes, aligned for any type, filled with zeros (the N64's heap is all zeros until its blocks are reused), and stops
 * the program when the PC has no memory left. port_heap_free frees a block of port_heap_alloc. */
void *port_heap_alloc(u32 bytes);
void port_heap_free(void *block);

/* PortIoMesg: a cartridge read request, the OSIoMesg that the game hands to osEPiStartDma (port_osEPiStartDma on PC).
 * On the N64 it is 0x18 bytes: type, pri, status, then retQueue, dramAddr, devAddr, size and piHandle as 4-byte words.
 * On PC retQueue, dramAddr and piHandle are host pointers and devAddr is a RomAddr, so the request is 0x28 bytes. The
 * port's osEPiStartDma copies size bytes of the ROM at devAddr to dramAddr, sets piHandle, and sends a message to
 * retQueue, as the N64's PI manager does when the transfer ends. The game's streams (func_8000946C,
 * initializeResourceStream, func_80009990) keep three of these in each stream record (Nw2AnimStream, common.h). */
typedef struct {
    u16 type;        /* N64 +0x0: osEPiStartDma sets it */
    u8 pri;          /* N64 +0x2 */
    u8 status;       /* N64 +0x3 */
    void *retQueue;  /* N64 +0x4: the queue (0x18 bytes) that gets the message when the copy is done */
    void *dramAddr;  /* N64 +0x8: where the bytes go */
    RomAddr devAddr; /* N64 +0xC: the ROM address they come from */
    u32 size;        /* N64 +0x10 */
    void *piHandle;  /* N64 +0x14: osEPiStartDma stores its handle here */
} PortIoMesg;
_Static_assert(offsetof(PortIoMesg, retQueue) == 0x08 && offsetof(PortIoMesg, devAddr) == 0x18 &&
                   offsetof(PortIoMesg, size) == 0x1C && offsetof(PortIoMesg, piHandle) == 0x20 &&
                   sizeof(PortIoMesg) == 0x28,
               "PortIoMesg is 0x28 bytes on a 64-bit PC");

/* ---- PC only: the key of the resource-name cache ----
 * The resource-name cache is a heap block of 128 entries (Nw2ResourceEntryHashed in common.h), whose address
 * D_8007FC34 holds. Each entry has a key:
 * - 0 for a free entry, -1 for an entry waiting to be freed;
 * - the address of the resource's name, a string (often one of the 40 name buffers whose address D_8007FC3C holds);
 * - or a resource id, tagged so that it cannot be taken for an address.
 * On N64 the key is a u32 and the tag is bit 0x40000000, which no N64 address has (RAM starts at 0x80000000). On a PC
 * an address is 64 bits and its low 32 bits can have any value, so the N64 test would take some addresses for ids. On
 * PC the key is a ResKey, as wide as a pointer, and the tag is RES_KEY_ID_TAG, bit 62, the same place from the top as
 * the N64's bit 30. A program's addresses lie far below it on the 64-bit PCs the port runs on: below 2^57 on x86-64,
 * below 2^52 on ARM64, unless a system keeps a tag in an address's top byte. So RES_KEY_NAME checks every address it
 * turns into a key, and stops the program if one has the tag. An id sits in the key's low 30 bits on both.
 * - RES_KEY_IS_ID(k): whether key k is an id (N64: k & 0x40000000).
 * - RES_KEY_ID(id): the key of resource id (N64: id | 0x40000000).
 * - RES_KEY_NAME(p): the key of the name at p (N64: (u32)p). */
typedef uintptr_t ResKey;
#define RES_KEY_ID_TAG ((ResKey)1 << 62)
#define RES_KEY_IS_ID(k) (((ResKey)(k) & RES_KEY_ID_TAG) != 0)
#define RES_KEY_ID(id) (RES_KEY_ID_TAG | ((u32)(id) & 0x3FFFFFFFu))
static inline ResKey port_res_key_name(const void *name) {
    if ((ResKey)name & RES_KEY_ID_TAG) {
        port_fatal("RES_KEY_NAME: the name at %p has the id tag", name);
    }
    return (ResKey)name;
}
#define RES_KEY_NAME(p) port_res_key_name((const void *)(p))

/* ---- PC only: SDK functions the port replaces ----
 * Each name is renamed in every game file: calls, declarations and the game's own definitions alike (src/main/sinf.c
 * then defines n64_sinf). That keeps them from clashing with, or standing in for, a library's function of the same
 * name.
 * - sinf, cosf: the game's own (libultra's) versions are compiled for the PC so the results equal the N64's. Under
 *   their own names they would also replace the C library's sinf and cosf for LUS.
 * - bzero, bcopy: the game's own versions (src/main/bzero.c, bcopy.c) become port_bzero and port_bcopy. A compiler can
 *   turn memset(p, 0, n) into a call to bzero, so a PC bzero written with memset could otherwise call itself.
 * - __floatdisf, __udivdi3: routines of the N64 compiler's runtime (s64 to float, unsigned 64-bit divide) that game
 *   code calls by name. PC runtimes do not provide them (64-bit hosts) or have their own (32-bit hosts).
 * - Controller, rumble and PI DMA functions: LUS defines most of them, but with its own record layouts, which are
 *   larger than the N64's (its OSContPad adds gyro and right-stick fields, 20 bytes per pad on any PC, so its
 *   osContGetReadData clears 80 bytes where the game's pad buffer is 24; its OSPfs keeps channel at +0x10 on a 64-bit
 *   PC), or as stubs (its osEPiStartDma copies nothing). Defining a second function of the same name would clash with
 *   LUS at link time. osContStartQuery, osContGetQuery and osContSetCh are not in LUS; they are renamed with the rest
 *   so all controller access goes through the port.
 * - Message queues: LUS's OSMesgQueue is 40 bytes on a 64-bit PC, but the game gives each queue 0x18 bytes of storage
 *   (s32 queue[6] in func_80003D20, for example). The port's versions keep the N64 size. A queue is those 0x18 bytes
 *   at 4-byte alignment, and a message is 4 bytes, the N64 size, as all the game's message storage gives it
 *   (readRomSynchronousChunks' s32 message, func_80003D20's s32 msg[2], the 16 messages of D_80046780). A message
 *   that carries an address carries its handle (PTR_TO_SLOT), and the receiver turns it back (SLOT_TO_PTR). */
#define sinf n64_sinf
#define cosf n64_cosf
#define bzero port_bzero
#define bcopy port_bcopy
#define __floatdisf port_floatdisf
#define __udivdi3 port_udivdi3
#define osContInit port_osContInit
#define osContStartReadData port_osContStartReadData
#define osContGetReadData port_osContGetReadData
#define osContStartQuery port_osContStartQuery
#define osContGetQuery port_osContGetQuery
#define osContSetCh port_osContSetCh
#define osMotorInit port_osMotorInit
#define __osMotorAccess port_osMotorAccess
#define osEPiStartDma port_osEPiStartDma
#define osCreateMesgQueue port_osCreateMesgQueue
#define osSendMesg port_osSendMesg
#define osRecvMesg port_osRecvMesg
#define osSetEventMesg port_osSetEventMesg
#endif /* TARGET_PC */

#endif /* PORT_H */
