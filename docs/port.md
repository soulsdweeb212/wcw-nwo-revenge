# The PC port and TARGET_PC

The PC port, Turnbuckle Dive (a separate repository built on LibUltraShip, "LUS"), compiles the game's C straight from
this tree's `src/`. It keeps no copy of it. This page explains how one set of files builds both the matching N64 ROM
and the PC program, what [`include/port.h`](../include/port.h) provides, and how the game's ROM loader works on PC.

## TARGET_PC

- The PC build defines the preprocessor symbol `TARGET_PC` when it compiles game files. `build.py`, the N64 build,
  never defines it.
- Where the PC needs different code, the file gets an `#ifdef TARGET_PC` block with the PC version, and the N64 code
  stays as it was in the `#else` branch. Every block starts with a comment that says why the PC differs.
- Where a whole function differs, the block holds a second definition of the function; the N64 definition follows in
  the `#else` branch, unchanged.
- When the PC version of a function takes different types, `port.h` declares it once for the PC, and the game files'
  own declarations of it go behind `#ifndef TARGET_PC` (they keep the types the matched N64 code depends on).

## The N64 build does not change

Without `TARGET_PC`, `port.h` is one typedef and macros that stand for the original code, and every `TARGET_PC` block
is skipped, so the N64 compiler produces the same code as before. Two checks prove it; run both in `source/` after
every change for the port:

```
python3 build.py                 # must end with "identical": the built ROM equals baserom.z64 byte for byte
python3 tools/check_rodata.py    # must report 0 not found: the jump tables and constants of the C match the ROM
```

## What port.h provides

These have an N64 and a PC form:

| Name | On N64 | On PC | Why |
| :-- | :-- | :-- | :-- |
| `uptr` | `u32` | `uintptr_t` | An integer as wide as a pointer, for arithmetic on addresses. A `u32` would cut a 64-bit address in half. |
| `READ_BE16/32/64(p)` | `*(u16 *)(p)` and so on | reads the bytes one at a time, big-endian | ROM data is big-endian like the N64; a PC is little-endian. |
| `DL_ADDR(p)` | `(u32)(p) - 0x80000000` | the pointer itself; an odd address stops the program | An address written into a display list. The N64 code writes physical addresses, such as the link constant `D_C95B8`, and `DL_ADDR(D_800C95B8)` compiles to the same instructions. LUS takes host pointers, and reads a value with bit 0 set as a segment number, which it looks up in a table of 16 segments. Used by the builders under "Display lists on PC". |
| `PTR_TO_SLOT(p)`, `SLOT_TO_PTR(s)` | the argument itself | a 32-bit handle from the port's handle table, and back | For a pointer kept in a 4-byte field of a record whose layout other code depends on, such as the pad records `D_8006E178`. Not used yet. |

These exist only under `TARGET_PC`:

- `Gfx`: one display-list command, two words as wide as a pointer (16 bytes), laid out like LUS's `Gfx`.
- `RomAddr`: a ROM address, that is an offset into the cartridge image. Never a host pointer.
- `ResDesc`: the 16-byte resource descriptor (start and end ROM addresses, size once loaded, packed size).
- `ROM_RES_BASE`, `ROM_RES_TABLE`, `ROM_SEG1_INIT` and the other `ROM_` names: the ROM addresses of the decomp's ROM
  symbols (`D_000DAC50` and so on), which the PC build does not link.
- The PC declarations of `readRomSynchronousChunks`, `lookupResourceDescriptor` and `func_80003684`.
- Declarations of functions the port implements: `port_rom_read`, `port_res_loaded`, `port_fatal` (print a message
  and stop), and `port_ptr_to_slot`/`port_slot_to_ptr` behind the slot macros.
- Renames of SDK functions the port replaces, such as `#define osRecvMesg port_osRecvMesg`. A rename changes the
  calls, the declarations and the game's own definition alike, so the game never defines a function under a name that
  LUS or the C library also has. `port.h` says for each group why:
  - `sinf` and `cosf` become `n64_sinf` and `n64_cosf` (the game's own libultra versions, compiled for the PC);
  - `bzero` and `bcopy` become `port_bzero` and `port_bcopy`;
  - `__floatdisf` and `__udivdi3` (N64 compiler runtime) become `port_floatdisf` and `port_udivdi3`;
  - the controller, rumble, PI DMA and message-queue functions become `port_` plus their name: LUS has most of them,
    but they work on LUS's own, larger record layouts (larger pad records; 64-bit pointers in queues and `OSPfs`)
    instead of the N64-sized storage the game gives them, or do nothing (LUS's `osEPiStartDma` copies nothing).

The renames apply only to text that comes after `port.h`, which `common.h` includes last. So a game file that needs a
system header includes it before `common.h`; otherwise the renames would also rename the header's declarations.

## The ROM loader on PC

The port reads the user's ROM file, converts it to big-endian (.z64) byte order, checks its SHA-1 and keeps it in
memory. Game code reaches it through the same functions as on the N64:

1. `readRomSynchronousChunks(src, dst, size)` copies `size` bytes from ROM address `src`. On the N64 it runs PI DMA
   transfers of up to 512 bytes and waits for each. On PC it calls `port_rom_read`, one copy from the image, which
   stops the program if the range lies outside it.
2. At boot, `initializeAssetSizeTable` copies the resource offset table (`ROM_RES_TABLE`) unchanged into
   `D_800482E0`, and fills `D_800482E4` with each resource's size once loaded. For a compressed resource that size is
   the big-endian word at its start. On PC the table words and that size word are read with `READ_BE32`, and the sizes
   are stored in the PC's byte order.
3. `lookupResourceDescriptor(out, id)` writes the descriptor of resource `id` (1 to `RES_COUNT`). Its start and end
   are table words with bit 0 cleared plus `ROM_RES_BASE`; bit 0 set means LZSS-compressed. On the N64 the descriptor
   is `{u8 *, u8 *, s32, s32}` whose pointers hold ROM addresses. On PC it is `ResDesc`, whose `RomAddr` fields keep
   it at 16 bytes, so the callers' `s32[4]` and `u8[16]` buffers still fit. An unknown id stops the program with a
   message (the N64 loops forever).
4. `func_80003684(out, id, buf)` loads resource `id` into `buf`. A compressed resource is read into a temporary heap
   block and unpacked by `func_800037F4` (the same LZSS code on both, with `READ_BE32` for its size word); any other
   is read straight into `buf`. On PC it then calls `port_res_loaded(id, buf, size)`: every whole resource passes
   there, so the port can track loaded buffers and convert byte order in one place.
5. Two boot functions read ROM by fixed ROM symbols. On PC, `func_80001260` reads the segment-1 block by
   `ROM_SEG1_INIT`, and `func_80003120` skips the sound banks, because until the port has audio the libmus functions
   are empty stand-ins.

The resource streams (`func_8000946C`, `initializeResourceStream`) run their own DMA and have no PC version yet.

`func_80008810` also reads the first 4 bytes of resources 0xE39 to 0x1DE9 straight from ROM with
`readRomSynchronousChunks` and keeps them as two `u16` in `D_8006A2B0`. Those bytes do not pass `port_res_loaded`, so
on PC they stay big-endian until the code that reads them uses `READ_BE16`.

## Display lists on PC

The game draws by building display lists in RAM: lists of commands for the N64's graphics chip, each command two
32-bit words. On PC the port hands the same lists to Fast3D, LUS's renderer, which reads commands of two 64-bit words.
The game's list builders work on PC like this:

1. A command is a `Gfx` from `port.h`, 16 bytes. On the N64 each game file defines its own 8-byte command type. On PC
   the builder files make theirs `Gfx` (for example `typedef Gfx Nw2Gfx;`), and the files that define a type named
   `Gfx` themselves keep it behind `#ifndef TARGET_PC`, so it does not clash with `port.h`'s.
2. A command word that holds an address gets it from `DL_ADDR(p)`, which on PC is the whole pointer. The N64 code
   computes such words in 32 bits, with a `(u32)` cast and a subtraction of 0x80000000, which on PC would cut the
   pointer in half.
3. A pointer that a record keeps in a field becomes a pointer-typed field on PC. That moves the fields after it: a
   64-bit pointer takes 8 bytes and starts at a multiple of 8. Where several functions read one record through structs
   of their own, one struct is the reference, and on PC the others place their fields by it with `offsetof` and check
   them with `_Static_assert`, so a PC build stops if the layouts ever disagree.

The first such record is the game's display record of a mesh or a picture, 0x2C bytes on the N64 (`func_8000498C`
fills one per mesh). Its reference is `Nw2TextureDisplayObj` in `common.h`, which covers its first 0x20 bytes: on the
N64 its five pointers sit at +0xC to +0x1C; on PC they sit at +0x10, +0x18, +0x20, +0x28 and +0x30, and the struct is
0x38 bytes. `buildVertexDisplayList`, `buildObjectDisplayListTail` and `func_80004E08` read the same record and follow
that layout on PC.

The builders with PC code so far: `buildVertexDisplayList` (a mesh's triangles), `buildObjectDisplayListTail` and
`buildCiTextureDisplayList` (the mesh's material list, which ends with a branch to its triangles),
`buildCi4TextureDisplayList` (a 4-bit texture), `func_80004E08` (loads a mesh's texture and palette), and overlay 1's
`func_80096A6C` and `func_80096D8C` (a picture drawn as texture rectangles). `func_8000486C`, which decodes a mesh's
vertices, needs no PC code: its 16-byte vertex records hold no pointer, and the CPU writes them in its own byte order,
which is the order LUS reads vertices in.

## Checking the PC side of a file

Until the port compiles all of `src/`, a host compiler can check one file's PC code, from `source/`:

```
gcc -std=gnu17 -fsyntax-only -DTARGET_PC -DNON_MATCHING -DAVOID_UB -fno-strict-aliasing -fwrapv -fsigned-char \
    -Wall -Werror=implicit-function-declaration -Werror=int-conversion -Werror=pointer-to-int-cast \
    -Werror=int-to-pointer-cast -Iinclude src/main/readRomSynchronousChunks.c
```

An error about a cast between a pointer and a 32-bit integer marks code that still keeps a pointer in 32 bits.
