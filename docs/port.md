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
- When game files declare a function with other types than its definition (an `s32` for a pointer or for a float's
  bits), or a variable with another type than what it holds (an `s32` for a pointer),
  [`include/port_decls.h`](../include/port_decls.h) declares it once for the PC with the right types, and the game
  files' own declarations of it go behind `#ifndef TARGET_PC` (they keep the types the matched N64 code depends on);
  a variable whose readers are not all fixed yet gets the right type in each file under `TARGET_PC` instead
  (`D_800F9B0C`; see below). The ROM loader's functions are declared the same way in `port.h`. See "The PC
  declarations: port_decls.h" below.
- A call then passes what the definition takes on the PC (`1.0f`, not `0x3F800000`). `tools/port_calls.py` finds the
  calls that do not. It compares each call with the same call in the file's N64 view, so it also finds an integer
  variable or `*(s32 *)&x` that holds a float's bits, once the caller sees a float parameter on the PC.
- A `TARGET_PC` block that repeats a change explained earlier in the same file still starts with a comment of its
  own, which can be one line that refers to the earlier one ("as above").

## The N64 build does not change

Without `TARGET_PC`, `port.h` is one typedef and macros that stand for the original code, and every `TARGET_PC` block
is skipped, so the N64 compiler produces the same code as before. Two checks prove it; run both in `source/` after
every change for the port:

```
python3 build.py                 # must end with "identical": the built ROM equals baserom.z64 byte for byte
python3 tools/check_rodata.py    # must report 0 not found: the jump tables and constants of the C match the ROM
```

## What port.h provides

These have an N64 and a PC form, apart from `WRITE_BE16/32`, which only PC code uses:

| Name | On N64 | On PC | Why |
| :-- | :-- | :-- | :-- |
| `uptr` | `u32` | `uintptr_t` | An integer as wide as a pointer, for arithmetic on addresses. A `u32` would cut a 64-bit address in half. |
| `READ_BE16/32/64(p)` | `*(u16 *)(p)` and so on | reads the bytes one at a time, big-endian | ROM data is big-endian like the N64; a PC is little-endian. |
| `WRITE_BE16/32(p, v)` | none: used only inside `TARGET_PC` blocks | writes the bytes one at a time, big-endian | Textures and palettes stay big-endian on PC (see "Byte order on PC"); PC code that writes into one, such as a palette entry, uses these. |
| `DL_ADDR(p)` | `(u32)(p) - 0x80000000` | the pointer itself; an odd address stops the program | An address written into a display list. The N64 code writes physical addresses, such as the link constant `D_C95B8`, and `DL_ADDR(D_800C95B8)` compiles to the same instructions. LUS takes host pointers, and reads a value with bit 0 set as a segment number, which it looks up in a table of 16 segments. Used by the builders under "Display lists on PC". |
| `PTR_TO_SLOT(p)`, `SLOT_TO_PTR(s)` | the argument itself | a 32-bit handle from the port's handle table, and back | For a pointer kept in a 4-byte field of a record whose layout other code depends on, such as the pad records `D_8006E178`. `D_8007E228` holds the segment-1 buffer this way (see "Shared records on PC"). The port implements the handle table when it links the game's code. |

These exist only under `TARGET_PC`:

- `Gfx`: one display-list command, two words as wide as a pointer (16 bytes), laid out like LUS's `Gfx`.
- `RomAddr`: a ROM address, that is an offset into the cartridge image. Never a host pointer.
- `ResDesc`: the 16-byte resource descriptor (start and end ROM addresses, size once loaded, packed size).
- `ResKey` and the `RES_KEY_` macros: the key of the resource-name cache (see "Shared records on PC").
- A check that the CPU is little-endian, as the PCs the port runs on are: the PC code is written for that byte order
  where the N64 code reads a value through a view of another width (see "Byte order on PC").
- `ROM_RES_BASE`, `ROM_RES_TABLE`, `ROM_SEG1_INIT` and the other `ROM_` names: the ROM addresses of the decomp's ROM
  symbols (`D_000DAC50` and so on), which the PC build does not link.
- The PC declarations of `readRomSynchronousChunks`, `lookupResourceDescriptor` and `func_80003684`.
- `PortIoMesg`: a cartridge read request (libultra's `OSIoMesg`) with real pointers, 0x28 bytes, which the port's
  `osEPiStartDma` takes and the game's animation streams keep (`Nw2AnimStream` in `common.h`).
- Declarations of functions the port implements: `port_rom_read`, `port_res_loaded`, `port_fatal` (print a message
  and stop), `port_ptr_to_slot`/`port_slot_to_ptr` behind the slot macros, and `port_heap_alloc`/`port_heap_free`,
  the game's heap on PC: `allocateHeap` and `releaseHeapBlock` call them, because the N64's heap cannot run on a 64-bit
  PC (its 16-byte block header grows to 24 bytes, while the code counts 16-byte units). `D_8007C430` still counts the
  blocks in use. `port_present` takes the game's frame hand-offs (`func_80002BC0`, `func_80002C0C`, `func_80002C74`),
  which on the N64 message the render thread; the PC runs no render thread. The port allocates exactly the bytes
  asked for, so a PC record must be allocated by its `sizeof`: the
  resource cache's nodes are 0x18 bytes on PC, and `func_80007020`, `func_80004580` and `func_800074A4` ask for
  `sizeof` of their node on PC, not the N64's 0xC.
- Renames of SDK functions the port replaces, such as `#define osRecvMesg port_osRecvMesg`. A rename changes the
  calls, the declarations and the game's own definition alike, so the game never defines a function under a name that
  LUS or the C library also has. `port.h` says for each group why:
  - `sinf` and `cosf` become `n64_sinf` and `n64_cosf` (the game's own libultra versions, compiled for the PC);
  - `bzero` and `bcopy` become `port_bzero` and `port_bcopy`;
  - `__floatdisf` and `__udivdi3` (N64 compiler runtime) become `port_floatdisf` and `port_udivdi3`;
  - the controller, rumble, PI DMA and message-queue functions become `port_` plus their name: LUS has most of them,
    but they work on LUS's own, larger record layouts (larger pad records; 64-bit pointers in queues and `OSPfs`)
    instead of the N64-sized storage the game gives them, or do nothing (LUS's `osEPiStartDma` copies nothing).

The renames apply only to text that comes after `port.h`, which `common.h` includes after all its N64 types. So a
game file that needs a system header includes it before `common.h`; otherwise the renames would also rename the
header's declarations.

`port.h` does not include `port_decls.h`, the PC declarations of the other game functions and variables that game
files declare with other types. `common.h` includes it as the last line of its `TARGET_PC` section, after `port.h` and
after the PC layouts of the shared records, so that a declaration there can name those layouts' types (see "The PC
declarations: port_decls.h").

## The PC declarations: port_decls.h

A game file often declares a function or a variable it uses with types of its own, and those can differ from the
function's definition or from what the variable holds: an `s32` where the function takes a pointer, an `s32` that
holds a float's bits where it takes an `f32`, no parameters where it takes two, an `s32` variable that holds an
address. The decompilation keeps these declarations, because the N64 code it must match depends
on them, and on the N64 they do no harm ("Checking the calls between game files" below says why). On a 64-bit PC the
same calls can cut a pointer in half or hand the function another number.
[`include/port_decls.h`](../include/port_decls.h) gives each such name one PC declaration with the right types.
`common.h` includes it as the last line of its `TARGET_PC` section, after `port.h` and after the PC layouts of the
shared records ("Shared records on PC"), so every game file sees it on the PC and none sees it on the N64, and a
declaration in it can name a PC layout's type (an array of `Nw2Descr4BA8`, for example).

It holds:

- Functions, each declared with exactly the types of its definition. Where the definition has a PC version of its own,
  these are the PC version's types, and the line's comment says "PC definition". The functions are grouped by the
  folder of the file that defines them (main, then overlay 2's four folders), in address order, and each line names
  that file.
- Variables (the game's data, which no C file defines), each declared with the type of what it holds: a pointer where
  the game keeps an address in it, an integer where it keeps a number. A comment above each says what it holds and
  which functions write and read it.

There is one declaration, in one place, so that a change to a definition is made once, and so that no file can miss
it: C accepts a name declared several times only when the types agree, so a file that still declares the name another
way stops the PC build with "conflicting types" (clang says "redeclaration of 'X' with a different type" for a
variable). A game file therefore hides its own declaration from the PC instead of writing a PC copy of it:

```
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D4D44 */
s32 func_800D4D44(void *, s32, s32);
#endif
```

The N64 build still reads the line, unchanged; on the PC only `port_decls.h`'s line counts. The comment on the
`#ifndef` line is the block's comment. A file whose own declaration already has `port_decls.h`'s types may keep it as
it is. Where one N64 line declares several names and only some differ, the PC side gets a copy of that line without
them, in an `#ifdef TARGET_PC` block with the N64 line in its `#else` branch (`func_800A4FB8.c` has one).

To add a name:

1. Write its line in `port_decls.h`, in its group and in address order, with the definition's types (the PC
   definition's, if it has one) and the defining file in the comment. A variable gets the type of what it holds and a
   comment that says what that is.
2. Find every file of the developer program that declares the name (`python3 tools/port_filelist.py --set match`
   lists them; search those for the name), and wrap each declaration whose types differ, as above. A name goes in only
   once every file of that set that uses it is wrapped. Files outside the set, such as the menus, are not compiled for
   the PC yet; each needs the same wrap before the PC build first compiles it.
3. Check what each call passes. Once a file sees `port_decls.h`'s types, the compiler checks its calls against them,
   and with the port's flags a pointer passed for an integer, or an integer for a pointer, stops the build. An integer
   passed for a float parameter does not: C converts its value to a float, without a warning. The N64 code often
   passes a float's bits in an integer: an `s32` variable that holds a float (`D_800F9B0C`, the distance to the
   opponent), a float read through an integer pointer (`*(s32 *)&f`), or a constant (`0x3F800000`, which is 1.0f's
   bits). The N64 function reads those bits as the float; on the PC the conversion makes 100.0f's bits 1120403456.0f.
   Such a call's PC side must pass the float itself: the variable declared `f32` under `TARGET_PC`, the float read as
   an `f32`, the constant written `1.0f`.
4. Prove it. `python3 tools/port_check.py --set match -j 8` compiles every file of the developer program, and a file
   that still declares the name another way fails check 3 with "conflicting types" (clang says "redeclaration of 'X'
   with a different type" for a variable). `python3 tools/port_calls.py` rates every call that still disagrees with
   the definition. It compares each call with the same call in the file's N64 view, so it also reports an integer
   holding a float's bits that the PC now converts (class C1, wrong value).
   Then each changed file goes through `port_check.py` as usual ("Checking a change for the port" below).

Not in `port_decls.h` yet: the variables that the developer program's files read both as a pointer and as an integer,
which `port_calls.py --externs` lists as "pointer and integer views": `D_8007C438`, `D_80070458`, `D_80046860`,
`D_8005AAA0` and `D_80044590`. Each holds addresses in 4-byte fields and is among the records whose PC layout is not
decided yet ("Shared records on PC" below), and its readers are fixed when that layout is. A variable that a few files
read with the wrong type can instead get the right type in those files, under `TARGET_PC`: `D_800F9B0C` is declared
`f32` that way in each file that reads it as an `s32`.

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
they arrive big-endian. On PC `func_80008810` converts them with `READ_BE16` as it stores them, so the code that reads
the table (`decodeAnimationMetadata`, and `func_8000946C` through `D_8006A2B2`, 2 bytes on) needs no PC version.
`func_800084AC`, which is not among the developer program's files, fills the same table the same way and needs the
same conversion when it is compiled for the PC.

## Byte order on PC

The N64 is big-endian: a 16-bit or 32-bit value is stored with its most significant byte first. A PC is
little-endian, with the least significant byte first. On PC the game's data is kept like this:

- Textures and palettes stay big-endian, in the ROM's byte order. Fast3D reads a texel or a palette colour a byte at a
  time, the high byte first (`DecodePaletteEntry` in LUS's `src/fast/interpreter.cpp`), so the port leaves them as they
  are. PC code that reads or writes a value in one uses `READ_BE16` and `WRITE_BE16`: `convertRgba16ToGrayscale` (a
  palette's colours) and `applyTextureTransparencyMask` (the colour count in a texture's header and a palette entry).
  The masks that `applyTextureTransparencyMask` applies are game data in the ROM's byte order as well; it reads them
  with `READ_BE32`.
- Values that the CPU works out and stores itself are in the PC's byte order: vertices (`func_8000486C`) and display
  lists, for example.
- A value read from ROM bytes that the CPU then uses as a number is converted where it is stored, so the code that
  reads it later needs no PC version (`func_80008810`, above).
- Where the N64 code reads a value through a view of another width, such as a `u64` as two `u32`, or a `u16` and the
  `u16` after it as one `u32`, its PC version is written for the PC's byte order (`func_800B955C`, `func_8009EDBC`).
  `port.h` stops the build on a big-endian CPU.
- The same holds where two files declare one variable at different widths: one writes an `s32` and the other reads
  its byte 3 (`func_800D43DC`, the animation mode `func_800D427C` stores), or its first two bytes as a `u16`
  (`func_800D6350`), or a label names the second byte of an `s16` (`D_800EB37B`, read in `func_8009D7A0`). In the
  N64's byte order those are the value's low byte or upper half; on PC the reading file takes the same part of the
  value by arithmetic (`(u8)x`, `x >> 16`). Turnbuckle Dive's byte-order check (its docs/TESTING.md, "The byte-order
  check") runs a match and lists every read whose value differs from the N64's.
- A table that `tools/port_data.py` converts gets its widths from the files' types, so a file that declares a label
  inside a table at another width changes how those bytes are converted. `D_800E3CFC`, which three files declare as
  an `s32` array and index from 1 (it is `D_800E3D00` one entry back), sits on the last two `u16` entries of
  `D_800E3CF0`; on PC those three files read `D_800E3D00` instead, so no file names `D_800E3CFC` and the two entries
  are converted as `u16`. A list that runs past the next label is described in TABLES with `Data(w, to_zero=True)`
  (`D_800E2CF4`'s last list ends in the table's own first word).

## Display lists on PC

The game draws by building display lists in RAM: lists of commands for the N64's graphics chip, each command two
32-bit words. On PC the port hands the same lists to Fast3D, LUS's renderer, which reads commands of two 64-bit words.
The game's list builders work on PC like this:

1. A command is a `Gfx` from `port.h`, 16 bytes. On the N64 each game file defines its own 8-byte command type. On PC
   the builder files make theirs `Gfx` (for example `typedef Gfx Nw2Gfx;`), and the files that define a type named
   `Gfx` themselves keep it behind `#ifndef TARGET_PC`, so it does not clash with `port.h`'s.
2. A command word that holds an address gets it from `DL_ADDR(p)`, which on PC is the whole pointer. The N64 code
   computes such words in 32 bits, with a `(u32)` cast and a subtraction of 0x80000000, or with `osVirtualToPhysical`,
   which returns a `u32`; on PC either would cut the pointer in half.
3. A pointer that a record keeps in a field becomes a pointer-typed field on PC. That moves the fields after it: a
   64-bit pointer takes 8 bytes and starts at a multiple of 8. Where several functions read one record through structs
   of their own, one struct is the reference, and on PC the others place their fields by it with `offsetof` and check
   them with `_Static_assert`, so a PC build stops if the layouts ever disagree.
4. A buffer for a display list holds the same number of commands on PC as on the N64, at 16 bytes each: where the
   N64 code allocates `n * 8` bytes for one, the PC code allocates `n * sizeof(Gfx)` (`func_8000498C`, overlay 2's
   `func_80090380`).

The first such record is the game's display record of a mesh or a picture, 0x2C bytes on the N64 (`func_8000498C`
fills one per mesh). Its reference is `Nw2TextureDisplayObj` in `common.h`, which covers its first 0x20 bytes: on the
N64 its five pointers sit at +0xC to +0x1C; on PC they sit at +0x10, +0x18, +0x20, +0x28 and +0x30, and the struct is
0x38 bytes. `Nw2Descr4BA8` is the whole record (see "Shared records on PC"). `buildVertexDisplayList`,
`buildObjectDisplayListTail`, `func_80004E08`, `func_80005CE0`, `applyTextureTransparencyMask` and overlay 2's
`func_80090380` read the same record through structs of their own and follow that layout on PC.

The builders with PC code so far: `buildVertexDisplayList` (a mesh's triangles), `buildObjectDisplayListTail` and
`buildCiTextureDisplayList` (the mesh's material list, which ends with a branch to its triangles),
`buildCi4TextureDisplayList` (a 4-bit texture), `func_80004E08` (loads a mesh's texture and palette), `func_80005CE0`
(the material list of a textured rectangle), `func_80006178` (a large texture drawn as a grid of texture rectangles;
on PC the texture address it is given must be the texture's own address), `func_80002454` (the matrices and vertices
of the objects in a bank), `buildSceneSetupDisplayList` (the setup at the start of a frame's list), overlay 1's
`func_80096A6C` and `func_80096D8C` (a picture drawn as texture rectangles), and overlay 2's `func_80090380` (a
textured quad). `func_8000486C`, which decodes a mesh's vertices, needs no PC code: its 16-byte vertex records hold no
pointer, and the CPU writes them in its own byte order, which is the order LUS reads vertices in.

`buildSceneSetupDisplayList` branches to a display list 0x10 bytes into the segment-1 block. On the N64,
`func_80001260` copies that block from the ROM (`ROM_SEG1_INIT`): 8 `s16` of viewport, then 18 commands of 8 bytes in
the ROM's byte order. On PC it builds the block instead (`makeSegment1Block`): the viewport's values in the PC's byte
order, then the same commands as 16-byte `Gfx`, and the one address among them, the viewport's (a `G_MOVEMEM` from
segment 1, offset 0), as the block's own address. `func_80002454` takes each object's list from its work block,
whose fields hold handles on PC (`Nw2SceneWork` in `common.h`).

## Shared records on PC

Some records that many files read hold addresses, which are 4 bytes on the N64 and 8 on a 64-bit PC. Each such record
has one PC layout, at the end of `common.h` (its `TARGET_PC` section), and every file that reads the record follows it.
Two ways are used:

- **A PC struct with real pointers.** The record grows, so code steps through an array of them by `sizeof`, never by
  the N64 size, and reads the fields by name or by `offsetof`. Most records are done this way.
- **The N64 layout, with handles.** A few records are reached through many labels or N64 strides, so they keep every
  N64 offset, and their 4-byte address fields hold a handle instead of the address: code stores `PTR_TO_SLOT(p)` and
  reads `SLOT_TO_PTR(field)` (`port.h`). A handle of 0 stands for NULL.

**Labels.** Many records are also reached through labels, names the N64 build gives to a field inside a record (for
example `D_800706AC`, +4 of the stream record `D_800706A8`). On PC no label exists: the `TARGET_PC` lines read the
record by its own name and a field name or index. A label left in PC code fails to link, which shows where.

**Address tables** (records that hold nothing but addresses) are plain arrays of pointers on PC: the draw tables
`D_80046860` and `D_80047070`, the render-list table `D_80044590`, and the texture-cache table `D_8007C438`.

**`port_decls.h`** declares each of these variables once for the PC, with its PC type, and a game file that declares it
its own N64 way wraps that line in `#ifndef TARGET_PC` (see "The PC declarations" above).

The records:

1. **The display record of a mesh or a picture** (0x2C bytes on the N64): `Nw2Descr4BA8`, 0x50 bytes on PC. Its first
   0x20 bytes follow `Nw2TextureDisplayObj`, as an assert checks. `fC` to `f1C` (the vertices, the material list, the
   list of vertices and triangles, the texture and the palette), `f20` and `f24` (the work blocks of its two vertex
   groups, or NULL) and `f28` (the arena its buffers come from, or NULL) are pointers. Every file of the developer
   program steps through these records by `sizeof(Nw2Descr4BA8)`, and the arrays of them are declared as arrays of
   `Nw2Descr4BA8` in `port_decls.h`, including the 0x3F4-byte slots of 23 records (`D_80050800[4][23]`).
2. **The resource-name cache**: 128 entries of `Nw2ResourceEntryHashed`, in a heap block whose address `D_8007FC34`
   holds. An entry's key is 0 (free), -1 (waiting to be freed), the address of the resource's name, or a resource id
   tagged with bit 0x40000000, which no N64 address has. A PC address can have that bit, so on PC the key is
   `port.h`'s `ResKey`, as wide as a pointer, and an id's tag is bit 62 (`RES_KEY_ID_TAG`). `RES_KEY_IS_ID(k)` tests a
   key, `RES_KEY_ID(id)` makes the key of an id, and `RES_KEY_NAME(p)` makes the key of a name's address and stops the
   program if the address has the tag. An entry is then 0x20 bytes on PC (0x18 on the N64), with the allocation at +8
   and the sizes in `reserved` from +0x10, so code that steps through the entries or reads one by offset goes by the
   struct on PC (`releaseResourcePool`, `func_8002A5F4`, `func_8002A2FC`, `func_8002AA28`). `func_8002A2FC` hands each
   new entry to `func_80028F3C`, `func_800295B4`, `slantNibbleBitmapRows`, `fillNibblePixelLevels` and
   `func_8002A1C4` (and through the last two to `countNibblePixelNeighbors`), which read it through views of their
   own; on PC those views follow `Nw2ResourceEntryHashed`, as an assert in each of the first five checks.
   `D_8007FC3C` holds the address of a heap block of 40 name buffers (`Nw2KeyedBufferEntry`); they hold no address
   and keep their layout. `freeCachedResource`, `func_8002A820` and `func_8002A658` (which steps through the entries
   by 0x18), which are not among the developer program's files, need the same changes when they are compiled for the
   PC.
3. **The segment-1 block `D_8007E228`.** Its first word holds the address of the segment-1 buffer. 42 of the
   developer program's files (74 across `src/`) name the block, and most of them read its other fields at their N64
   offsets (some through labels of their own, such as `D_8007E280` for +0x58). So the word keeps its 4 bytes on PC and
   holds a handle of the address, `PTR_TO_SLOT(buffer)`: `func_80001260` sets it, and code that needs the address
   takes `SLOT_TO_PTR(D_8007E228)` (`buildSceneSetupDisplayList`). On the N64 the buffer is `D_8007FC4F`'s address
   rounded down to a multiple of 16; on PC it is a heap block that `func_80001260` builds (see "Display lists on PC").
4. **The scheduler's queue and the graphics task.** `func_80000580` registers a client with the scheduler, which keeps
   the client's message queue in a 4-byte field (+4 of the client record), and `func_800005D0` sends the address of a
   graphics task as a 4-byte message. On PC both go as handles, `PTR_TO_SLOT(queue)` and `PTR_TO_SLOT(task)`, so the
   port's stand-ins for the scheduler (`osScAddClient` and `__scMain`, which send the retrace messages to the queue,
   and `renderTaskThread`, which receives the task) turn them back with `SLOT_TO_PTR`.
5. **The scene graph: the 0xDC-byte object and its work block** (`Nw2SceneObj`, `Nw2SceneWork`). The object is a node
   of the scene graph (links, matrices, the vertices and display list it draws); its work block, 0xB8 bytes from the
   pool in `D_80046858`, says what to draw. About 45 files step arrays of objects by 0xDC and 0x13C4 (23 objects), and
   20 labels reach their fields, so both keep their N64 layout and hold handles. `func_80004BA8`, `func_80005014`,
   `func_80005204`, `func_8000520C`, `func_8000D718`, `func_80007818`, `func_80007874`, `func_80010E6C` and
   `func_80011764` have PC definitions that read and write them this way.
6. **The players' mesh arenas** (`D_8007C3D0`, `Nw2MeshArena`): two pools per player that display records take their
   vertices and display-list commands from. Pointers on PC, 0x20 bytes; the second pool holds 16-byte `Gfx` commands.
7. **The animation streams** (`D_800706A8`, `Nw2AnimStream`): one per wrestler. The read cursor and the destination are
   pointers, the cartridge requests are `port.h`'s `PortIoMesg`, and the queues keep the N64's 0x18 bytes and 4-byte
   messages. 0x140 bytes on PC.
8. **Pictures** (`Nw2TexPair`): the texture and palette buffers of a 2D picture, two pointers, 16 bytes on PC
   (`D_80070458`, `D_8005B220`, overlay 2's picture arrays such as `D_800E78A8`). The two HUD icons `D_800EB19C` and
   `D_800EB1AC` are `Nw2HudIcon`, 0x10 bytes on PC.
9. **The render lists** (`D_80044590`, `Nw2RenderList`): four records, each a display list of 0x800 16-byte commands,
   the graphics task (`Nw2ScTask`) and its done message. `func_80001260` allocates them with `sizeof(Nw2RenderList)`.
   The task's framebuffer is a pointer; its message is a handle, because a message in the game's queues is 4 bytes.
10. **The texture-cache table** (`D_8007C438`): per player, 23 addresses of heap blocks, `void *[4][23]` on PC. On the
    N64 four rows of animation ids follow it at +0x180; on PC they are their own array, `D_8007C5B8[4][0x300]`.
11. **The animation-command records** (`D_8005AAA0`, `Nw2AnimatedCi4State`): per player, three buffer pointers, then
    the slot, type, frame and countdown bytes, 0x20 bytes on PC.
12. **The controller seats** (`D_8006E178`): four 12-byte records, whose first word `func_80003D20` sets to the address
    of the seat's status (`D_80048310`). The developer program's files read the rest at N64 offsets, so the records
    keep their layout and the word holds a handle. Overlay 1's `func_800C5718` reads the address back and will need
    `SLOT_TO_PTR` when overlay 1 is compiled for the PC.

Five `port_fatal` calls are left in the developer program's files. None waits for a decision; each stops on input the
N64 would mishandle: a resource id out of range (`lookupResourceDescriptor`), a negative length (`bcopy`), a display
record not on a record boundary (`func_8000498C`), a display list longer than its render list (`submitGraphicsTask`),
and a hit with no hit class (`func_800C72DC`).

Still open:

- **Labels of records outside this list.** `initializeMatchResources` and `func_80011764` still name labels inside the
  0x5C-byte entity records of `D_8007E010` (`D_8007E012` to `D_8007E028`) and `D_80070479`; `func_80094A9C` reads
  `D_8007E280` and `func_800922C0` reads `D_8007E228` at offsets. On PC these variables keep their N64 offsets ("The
  game's variables", below), so the labels reach the same bytes as on the N64.
- **A range check in `func_80094A9C`** (overlay 2's picture index past the end of its array), not added yet.

## The game's variables on PC: tools/port_data.py

The game files use about 1,250 variables of the N64's data and BSS sections. The port defines all of them, from one
map, [`port/game_vars.tsv`](../port/game_vars.tsv), which [`tools/port_data.py`](../tools/port_data.py) writes and
Turnbuckle Dive turns into C when it configures (its `docs/GAME_CODE.md`, "The game's variables"). The map holds no
byte of the game: names, addresses, sizes and byte-order patterns. Run the tool after a change to the files the port
compiles, to their declarations of game variables, or to the PC types in `include/`, and commit the new map with the
change. With `--check` it only compares and exits with 1 when the map is out of date. It needs pyelftools, which
decompdecomp's Python has, and gcc:

```
~/.local/share/uv/tools/decompnet/bin/python tools/port_data.py
~/.local/share/uv/tools/decompnet/bin/python tools/port_data.py --check
```

A wrestler record is `sizeof(Wrestler)` bytes on PC (0x3B8), so code that steps from one wrestler to the next by a
byte offset uses `n * sizeof(Wrestler)` on PC where the N64 code has `n * 0x3B0` (`copyPartCoordinateFields`,
`func_800AB2B4`, `runMatchPhaseStateMachine`, `updateEntityTargetLookAngles`, `func_8009D8D0`). The render records
(0x13C4) and scene objects (0xDC) keep their N64 strides, because they keep their N64 layout.

The tool takes a variable's width from the files' declarations of it. A file that only takes a variable's address
may declare it as bytes (`extern u8 X[]`) and hand it to a function that reads it at another width; such a declaration
gets a PC version with the real type (`func_8000E920` and `func_8000EF90` for `func_80007020`'s arrays, the AI files
for `func_800ADA38`'s tables), or the variable would keep the N64's byte order. A table of addresses read through a
byte declaration gets a pointer declaration on PC and a `TABLES` entry (`D_80031060` in `func_8000E4FC`). So does a
read through a cast to another width (`*(u16 *)(D_800E3F30 + i)` of a variable declared `u8[]`): the PC declares the
variable with the width it is read at (`func_800D54A0`, `applyEntityMovementC8D84`), or reads a table inside a variable
by the table's own label (`func_800D5438` reads the u16 table at `D_80030560 + 0x10` as `D_80030570`, because
`D_80030560`'s first byte is a byte).

How it works:

1. It compiles the developer program's files (`tools/port_filelist.py`) and the asset viewer's two overlay-1 files for
   the PC with debug information, and reads each file's type for every variable it declares with `extern`. A name
   that the files use and none defines is a game variable. (clang leaves extern declarations out of its debug
   information, so the tool uses gcc.)
2. A variable's N64 address comes from `build.json` (its symbols and functions) or a label of `asm/data/`; the address
   gives its section, and the next variable's address its extent. Names that share an address are one variable.
3. A variable whose type holds no address keeps its N64 offset in one block of PC memory per section ("block"): such a
   type has the same layout on both machines, so labels inside records and arrays read as one keep working. A variable
   whose type holds an address gets storage of its own, as big as its PC type ("own"); an open array gets as many
   elements as its extent holds on the N64, each of its PC size.
4. The address tables: the variables that hold addresses and that the ROM starts (24) are described by hand in the
   tool's `TABLES`: each one's shape, down to what its addresses point at (another table, data read at a given width,
   a function, a framebuffer). The tool follows every address in the ROM and checks it against the description: in
   main's data each word must be an address exactly where splat marked one in `asm/data/` (the name tables, which
   splat wrote as 16-bit values, pass when the word is an address in a data section); in overlay 2's data each
   address must be 0 or an address the shape allows; a function address must start a function the port compiles; no
   address may land inside another table. Each table, and each array or record that holds addresses and that a table
   reaches, gets its PC layout and a fill line; the data the addresses point at gets a swap range, up to the next
   label.
5. For the sections the ROM fills, each byte gets the width the files' types read it at, and each variable a swap
   pattern; an open array, or a type smaller than its extent, repeats over the extent, but not past a place a table
   points at, where other data begins (splat's labels inside a table, such as `D_8003A4FE`, do not stop it). Two files
   that read one byte at different widths, a bit-field in a variable of these sections, or a type bigger on the N64
   than its extent stop the tool with a message.
6. An old name of a function that some file still calls (`func_800E2400` for `tryBeginBlockReaction`) gets a
   "function" line; the port's linker gives the function that second name. Only names of the game's own form count:
   `build.json` also puts `sqrtf` at `nw2Sqrtf`'s address, but on PC `sqrtf` is the C library's.

The columns, tab-separated: name, address, section (`main.data`, `main.bss`, `ovl1.data`, `ovl2.data`, `ovl2.bss`;
`other` for the few the port provides; `code` for functions), storage, bytes, and the last column. The storages:

- `block`: bytes is the extent; the last column is the swap pattern. `P:o.w,o.w` swaps a w-byte value at each offset
  o, again every P bytes (hex), as long as it fits in the extent; `-` means none (BSS).
- `data`: a range that a table points at, outside every block variable (named `td_data_` and its address): swapped
  like a block variable, with no name of its own in the C.
- `own`: bytes is the PC size. For an address table the last column is its fill, `count:N:P:o.p.k,...` (hex): count
  elements of N bytes on the N64 and P bytes on PC, each field at N64 offset o and PC offset p, of kind k: 1, 2, 4 or
  8 (a value of that width), `p` (an address), `f` (a function's address) or `z` (an entry the game never reads, NULL
  on PC). Arrays and records that only tables reach are named `td_anon_` and their address.
- `alias` (a second name at the same address; bytes is the first name), `port` (the port provides it), `function` (an
  old name of a function; bytes is its name) and `entry` (a function that an address table holds).

## Checking a change for the port

The port's developer program is the PC program that a developer switch starts straight into a match (overlay 2),
without the menus (overlay 1). Turnbuckle Dive does not have it yet; the three tools below prepare the game files it
will compile. A change for the port goes through these steps, each run in `source/`:

1. The change sits inside `TARGET_PC` blocks only, as "TARGET_PC" above describes.
2. `python3 tools/port_check.py FILE...` (or `--changed` for every changed file) proves each file on its own: its N64
   side is unchanged, and its PC side compiles with gcc and clang, with no new warning and no asm. Its PC compile uses
   every flag the port gives game files. After a change to a header, `python3 tools/port_check.py --set match -j 8`
   compiles every file of the developer program, because a header's PC side is compiled only through the files that
   include it.
3. `python3 tools/port_calls.py --only FILE...` lists the calls made in those files that a 64-bit PC would get wrong:
   those rated crash or wrong value. Fixing them is part of fixing the file; a call that must wait for a later step
   goes into an allow file, with the reason.
4. `python3 tools/port_filelist.py --set match` must still exit with 0: a change can make a file use a name that the
   tool cannot find, or add files to the developer program's list.
5. Whoever integrates a batch of changes runs `build.py` and `tools/check_rodata.py`, as "The N64 build does not
   change" describes. They stay the proof for the whole ROM; `port_check.py` proves one file at a time, so that
   several people can work at once between two runs of `build.py`.

The port's compiler settings are copied into the three tools: `PC_DEFINES` in `tools/port_filelist.py`, and
`PC_FLAGS` in `tools/port_check.py` and `tools/port_calls.py`. They mirror `td_game_code()` in Turnbuckle Dive's
`CMakeLists.txt`, and all three change with it. The tools need Python 3.8 or later and nothing outside its standard
library. `port_check.py` also needs gcc, clang and decompdecomp (as `build.py` does), and `port_calls.py` needs clang.

## The developer program's files: tools/port_filelist.py

The developer program compiles only part of `src/`: the files that its start-up reaches, and the files that those
reach in turn. [`tools/port_filelist.py`](../tools/port_filelist.py) works out that list from the decompilation's own
files. Run it in `source/`:

```
python3 tools/port_filelist.py --set match                  # the list: one path per line, sorted (src/main/bcopy.c ...)
python3 tools/port_filelist.py --explain src/main/bcopy.c   # how the list reached one file
python3 tools/port_filelist.py --surface                    # what the listed files use outside the list
python3 tools/port_filelist.py --self-test                  # the negative controls described below
```

The list goes to standard output. A summary goes to standard error: how many files come from main's game code, from
the SDK code the port keeps and from overlay 2, which tables of function addresses the walk followed and how many
functions each holds, and how many replaced files the listed files call into. The tool needs a decompilation that has
been set up: the first run of `build.py` extracts `asm/data/` and `assets/` from the ROM, and every run writes
`build/game.ld` (without `build/game.ld` the tool goes by `build.json` alone). It only reads the decompilation.

### How it works

1. **It reads the C as the port compiles it.** The tool reads every C file named in `build.json` with `TARGET_PC`,
   `NON_MATCHING`, `AVOID_UB` and `F3DEX_GBI_2` defined, the settings of the port's compiler, so it follows the PC side
   of every `#ifdef TARGET_PC` and expands the macros of `include/`. For each function it notes the names that the
   function uses but does not declare itself: the functions it calls or takes the address of, and the variables it
   reads or writes.
2. **It finds what each name is.** A name can be a function of a C file (a `static` one counts only in its own file),
   an old name of a function that `build.json` keeps as a symbol at the function's address (`func_800E2400` is
   `tryBeginBlockReaction`), a variable (a `build.json` symbol, a label in `asm/data/`, or a C definition), a
   function the port supplies, declared in `port.h`, or a name that only the PC has, declared in `port_decls.h`. The
   tool reads those two headers on their own, with `common.h`'s typedefs, because it keeps no other declaration of a
   header. A name that is none of these is an error: the tool names the file and line that use it, still prints the
   list it found, and exits with 1, because the name could be a function that the list is missing.
3. **It follows function addresses in data.** Some functions are reached only through a table of their addresses:
   overlay 2 calls many of its functions through the tables `D_800E2FF0` and `D_800E3660`. The tool reads the `.word`
   entries of main's data in `asm/data/`, and every 32-bit word of overlay 2's data (`assets/D5FB0.bin`) that equals
   the address where a function starts. Each such word belongs to the label it lies in (an `asm/data/` label in main, a
   `build.json` symbol in overlay 2's data), so a file that uses the label reaches every function in its table. In
   overlay 2's data a run of function addresses that goes on past the next label is an error: a label inside a table
   would cut it in two, and the functions after the label would be lost.
4. **It walks from the roots.** The walk starts at the functions the developer program calls itself: the four calls
   that open the N64's boot loop (`func_80001260`, `func_80003120`, `func_80003D20` and `initializeAssetSizeTable`),
   `func_8002B750`, which builds the table of wrestler names (on the N64 the menus call it), and overlay 2's entry
   `func_80090000_ovl2`. A file is compiled whole, so every name that any function of a listed file uses counts. The
   walk does not go into code that the port replaces: the Nintendo SDK apart from libultra's gu library, `bzero`,
   `bcopy` and `__floatdisf` (s64 to f32, which drops the low bits where a PC conversion would round them), and eight of the game's own files in `src/main` (the entry point, the start-up thread and the one that
   starts the boot loop, the scheduler's two task threads and a helper of theirs, and two files that nothing calls). A
   listed file that uses a name of overlay 1, the menus, is an error, because the developer program does not have
   overlay 1.
5. **It checks its inputs.** `build/game.ld` must define the same symbols as `build.json` and place each C object at
   its function's address: `build.py` writes it from `build.json`, so a difference means it is out of date. Each row of
   the table in `docs/sdk_functions.md` must name a function of main at its address. Every name in the port's choices
   (below) must be one the decompilation has, because a misspelt name would change the list without an error.

The port's choices sit in one marked section at the top of the tool, each with its reason: the macros, the roots, the
SDK code the port keeps and the game files it replaces. `tools/port_calls.py` reads the last two from there too.

`--explain FILE` prints the chain from the file back to a root: each line names the file, the file and line that use
it, and the name they use. `--surface` prints, instead of the list, one tab-separated row for each replaced file with
the names the listed files use in it (the port must supply them), one for each table of function addresses the walk
followed, with its functions, and one for each other kind of name with every name of that kind: data (which the port
must fill from the ROM), port names (declared only in `port.h` or `port_decls.h`), inline helpers of the headers, and
addresses inside main's code that are not where a function starts.

### Exit status

- 0: the list is complete (`--explain`: and the file was reached).
- 1: a name could not be found, or a listed file uses overlay 1, so the list may be short. Each error names the file
  and line. (`--explain`: also when the file was not reached.)
- 2: the inputs are missing or disagree, for example `build/game.ld` does not match `build.json`, a label splits a
  table of function addresses, or a name in the port's choices is not in the decompilation. Also a wrong command line,
  and a fault in the tool itself.

### Output for a build system

```
python3 tools/port_filelist.py --set match --output FILE --depends FILE
```

`--output` writes the list to FILE instead of standard output. `--depends` writes the files the list depends on, one
absolute path per line, for CMake's `CMAKE_CONFIGURE_DEPENDS`: every file the tool read (each C file that `build.json`
names, the headers they include, the data files, `build.json`, `build/game.ld` and `docs/sdk_functions.md`) and the
tool itself. Both files must lie outside the decompilation. They are written only when the list is complete, and only
when their text changes, so that a build system watching them does not run again for nothing.

### The self-test

`--self-test` checks that the tool notices the mistakes that would otherwise only make the list shorter, without an
error. It notes every file the tool reads, copies exactly those files into a temporary folder once for each control,
changes each copy in one way, runs the tool on every copy as a separate program and checks how each run ends:

1. The copy unchanged: exit status 0, the same list as the decompilation itself, and in the summary the tables
   `D_800E2FF0` and `D_800E3660` with every function their data holds.
2. `func_800E2400`, the old name of `tryBeginBlockReaction`, removed from `build.json` and `build/game.ld`: exit status
   1, an error at the line of `src/code_8009D7A0/func_8009DD60.c` that calls it, and
   `src/code_800DE9C0/tryBeginBlockReaction.c` gone from the list.
3. The table `D_800E3660` removed from both: exit status 1, an error at the line of
   `src/code_8009D7A0/startEntityAction.c` that calls through it, and files of the table's functions gone from the list.
4. A label added 0x10 bytes into the table `D_800E2FF0`, in both: exit status 2 and the error that a run of function
   addresses goes on from `D_800E2FF0` into the new label.
5. A PC-only name, `port_filelist_pc_only`, declared in `include/port_decls.h` alone and used in a function added to
   `src/main/func_80001260.c`: exit status 0 and the same list as the decompilation itself.
6. The same copy, with the tool's reading of `port_decls.h` left out (the option `--skip-port-decls`, which exists only
   for this control): exit status 1 and an error at the line that uses the name. This proves that the name is found
   through that reading.

The self-test gets what it compares with without the tool's own readers: the line that a control expects from a plain
text search of the copy (a line of that file where the name appears inside braces, comments left out), the file of the
function that the old name stands for from `build.json`, and the functions of each table from the bytes of the data.
It exits with 0 when every control behaved as expected, 1 when one did not, and 2 when the tool cannot run on the
decompilation itself. It writes nothing into the decompilation.

### Experiments

`--root FUNCTION` (repeatable) starts the walk from other functions than the set's roots, and `--redirect OLD=NEW`
reads every use of the name OLD as NEW. They are for trying other starting points: the summary then calls the set
custom, and a build system runs `--set match` without them. For example, this walks from the N64's whole boot loop and
reads its calls into overlay 1's entry as calls into overlay 2's:

```
python3 tools/port_filelist.py --root func_80013108 --root func_8002B750 --root func_80090000_ovl2 \
    --redirect func_80090000=func_80090000_ovl2
```

## Proving a TARGET_PC edit one file at a time: tools/port_check.py

`build.py` proves that the N64 build is unchanged, but only for the whole tree, and only one person can run it at a
time, because it writes `build/`. [`tools/port_check.py`](../tools/port_check.py) proves the same for single C files,
so several people can fix different files at once: each checks only their own files, and the person who integrates
the batch runs `build.py` and `tools/check_rodata.py` once for all of them. It compares each file with its version in
HEAD, git's last commit, which is the state `build.py` last proved identical. It writes nothing into the source tree:
its work files go to a temporary folder that it deletes at the end.

Run it from `source/`:

```
python3 tools/port_check.py src/main/bcopy.c src/main/func_8000B630.c   # the files given, under src/ or include/
python3 tools/port_check.py --changed                                   # every file under src/ or include/ that
                                                                        # differs from HEAD: changed, new or deleted
python3 tools/port_check.py --set match -j 8                            # checks 3 and 4 for every file of the
                                                                        # developer program, 8 files at a time
```

`--set match` takes its list from `tools/port_filelist.py --set match`. `--files-from LIST` gives the files in a list
instead, one path per line; with `--set match` it replaces the list from `port_filelist.py`. `--gcc` and `--clang`
name other compilers than the `gcc` and `clang` on the path.

### The four checks

1. **N64 view.** The file as the N64 compiler reads it. The N64 build never defines `TARGET_PC`, so every
   `#ifdef TARGET_PC` block is dropped and its `#else` branch kept, every `#ifndef TARGET_PC` block is kept, and the
   directive lines themselves are dropped. This view must equal the same view of HEAD's version byte for byte, which
   means every change sits inside `TARGET_PC` blocks. The tool finds directives the way a C preprocessor does, so a
   directive inside a comment does not count. Only plain tests are accepted: `#ifdef TARGET_PC`,
   `#ifndef TARGET_PC`, `#if defined(TARGET_PC)` and `#if !defined(TARGET_PC)`. An `#elif` in a `TARGET_PC` block, an
   `#elif` that tests `TARGET_PC`, and any other condition on `TARGET_PC` are refused with a message, because the view
   cannot follow them.

   Then the N64's own preprocessor, KMC GCC's, reads both versions (the command `build.py` uses, with `-E` in place of
   `-c`). It must read this version without an error, and give the same text as for HEAD's version, apart from spaces
   and line breaks. It reads a few things differently from today's compilers: a quote that does not close on its line
   stops it even in a skipped block (an apostrophe in an `#error` message, for example), and a directive inside the
   arguments of a macro call is not a directive to it. A header is preprocessed after `common.h`, as game files
   include it.

   A new file fails, because HEAD has nothing to compare it with, and so does a deleted file, because the N64 build
   would lose it; `build.py` proves those. For a header this is the only N64 check, and `build.py` proves the files
   that include it.

   `include/port_decls.h` is a PC-only header: `common.h` includes it inside its `TARGET_PC` section, so the N64
   never reads it and its N64 view is empty, whatever it holds. Lines are added to it without `TARGET_PC` tests. For
   it, check 1 proves instead that `common.h`'s PC view includes it (an `#include` directive, not one inside a
   comment or inside another conditional such as `#if 0`), and that no file under `src/` or `include/` includes it
   outside a `TARGET_PC` block.
2. **N64 object**, for C files. The file and HEAD's version are compiled with KMC GCC 2.7.2, each with its own
   `include/`, in two temporary copies of the tree. The command is the one `build.py` uses: the tool asks decompdecomp
   for it, with `build.json`'s flags and its `compiler_ranges`, which give `nw2Sqrtf` `-ffast-math`. The two objects
   must hold the same code, relocations, data and symbols. Sections that the link throws away, such as `.comment`,
   are not compared.
3. **PC compile**, for C files. A real compile (`-c`) with gcc and with clang, with exactly the flags the port gives
   game files: `PC_FLAGS` at the top of the tool. clang also gets `-ferror-limit=0`, so that it reports every error.
   There must be no errors. Among them, a cast between a pointer and a 32-bit integer marks code that still keeps a
   pointer in 32 bits, and "conflicting types" (for a variable, clang says "redeclaration of 'X' with a different
   type") a declaration that `port_decls.h` has with other types and the file has not hidden behind
   `#ifndef TARGET_PC` ("The PC declarations: port_decls.h"). A second compile adds
   `-Wall -Wextra`, for both the file and HEAD's version, and the file must have no warning that HEAD's version does
   not also have. Warnings are matched by their message and the text of the line they point at, so lines that an edit
   only moves still match. In this compile the errors that the port's flags make out of pointer and declaration
   problems count as warnings, so that a version that does not compile yet still goes through every pass that warns.
   Where HEAD's version still has errors in this compile, a compiler skips some of its warnings there (clang leaves
   out its warning about a missing return value, for example), so a new warning on a line that HEAD's version also has
   is printed as a note and does not fail the check.
4. **No asm**, for C files. The file's preprocessed PC text, from `gcc -E` and from `clang -E`, must not contain
   `asm`, `__asm__` or `__asm`. A compile cannot catch MIPS assembly, because the x86 assemblers read some MIPS
   instructions as other instructions: `bcopy`'s `add` compiles and then stops the program with an illegal
   instruction. The text of the file and of `include/` is searched; system headers are not, because the C library
   uses `__asm__` to name functions in declarations.

### Output

One line per file and check, starting with `pass`, `FAIL`, or `n/a` where a check does not apply: checks 2 to 4 do not
apply to a header. Then a summary with the totals of each check: for check 3 the errors of each compiler and the number
of files they are in, for check 4 the files with asm. `-v` prints the details under each failed check (the lines whose
N64 view differs, the first differences between the objects, the compilers' errors and new warnings, the place of
each asm) and check 3's notes. `--keep DIR` keeps the work files in `DIR`: both versions of the files, the objects, the
preprocessed text and each compile's messages. `DIR` must be new or empty, and outside the source tree.

The exit status is 0 when every check passed, 1 when a check failed, and 2 when the tool could not run or was stopped,
with a message that says why: the folder is not a git repository, gcc, clang or decompdecomp is missing, a path is not
under `src/` or `include/`, `tools/port_filelist.py` failed, or the tool itself has a fault.

### How check 2 is known to compile like build.py

`--against-build` compiles each C file as check 2 does and compares the object with the one `build.py` made in
`build/`:

```
python3 tools/port_check.py --against-build --files-from <(git ls-files 'src/*.c') -j 8
```

The only difference it accepts is the one `build.py` makes itself after compiling: it shrinks the code section to
where the last function ends, when everything after that is zero bytes, which are MIPS `nop` instructions, and no
relocation points there. The assembler pads the code section to a multiple of 16 bytes, and each function is placed at
its own address, so the padding would run into the next function. The tool applies the same shrinking to its own
object and then requires the two files to be identical byte for byte.

## Checking the calls between game files: tools/port_calls.py

A game file often calls a function through a declaration of its own, and that declaration can differ from the
function's definition: an `s32` where the function takes a pointer, an `s32` holding a float's bits where it takes an
`f32`, no parameters where it takes two. On the N64 such a call still does what the original did: pointers, integers
and floats are all 32 bits there, and most arguments travel in the same four 32-bit registers (the O32 calling
convention). The decompilation keeps these declarations because the N64 code it must match depends on them. On a
64-bit PC (x86-64, System V calling convention) pointers are 64 bits and floats travel in registers of their own, so
the same call can cut a pointer to 32 bits or give the function a different number.
[`tools/port_calls.py`](../tools/port_calls.py) finds every such call in the developer program's files and rates what
it would do. Run it in `source/`:

```
python3 tools/port_calls.py                                   # every call rated crash or wrong value, and a summary
python3 tools/port_calls.py --tsv /tmp/calls.tsv --externs /tmp/externs.tsv   # every flagged call; the extern table
python3 tools/port_calls.py --allow FILE                      # FILE lists calls that wait for a later step
python3 tools/port_calls.py --only src/main/func_8000BDD0.c   # report only the calls made in the files named
```

All the files go after one `--only`: a second `--only` replaces the first.

It needs clang. It writes nothing but the files named with `--tsv` and `--externs`, which must lie outside the
decompilation. Its exit status is 0 when no call is rated crash or wrong value apart from those the allow file lists,
1 when one is, and 2 when it cannot run: no clang, no file set, an incomplete file set (below), a file clang gives no
syntax tree for, a reported file whose N64 view clang gives no syntax tree for, a malformed allow file, or a fault in
the tool itself. `--quiet` prints the summary only, `--decomp DIR` checks the decompilation in DIR (a copy, for
example) instead of the one the script sits in, and `--clang` and `--jobs` choose the clang to run and how many files
it reads at a time.

### How it works

1. It takes the file set from `tools/port_filelist.py --set match`. `--files-from LIST` gives the set as a list of
   paths instead, one per line.
2. clang reads every C file of the main program and of overlay 2 with the port's flags (`PC_FLAGS` at the top of the
   script) and dumps each file's syntax tree as JSON. From it the script takes every function definition, with its
   parameters and how the function uses each one; every call, with the types the caller sees for the function and for
   each argument, and what the expressions around the call do with its result; and every extern variable declaration.
3. For each call made in the set it finds the definition the call reaches, as the N64 link does: a static function of
   the caller's own file first, then the global function of that name, then a function's other name (an
   `__attribute__((alias))`, or a name that `build.json`'s `symbols` puts at a function's address, such as
   `func_800E2400` for `tryBeginBlockReaction`). A call through a table of function addresses in overlay 2's data,
   such as `D_800E3660`, reaches every function the table holds, and each is rated against the type the call uses.
4. For every argument it works out where the caller puts it and where the definition reads it, on the N64 (the first
   four argument words in `$a0` to `$a3`, an 8-byte value starting on an even word, and the first two arguments in
   `$f12` and `$f14` instead when they are floats and only floats come before them) and on the PC (integers and
   pointers in six integer registers, floats in eight `xmm` registers, the rest on the stack). It also compares integer
   widths and the result. Each difference is a finding with a class and an effect; a call's effect is that of its
   worst finding.
5. clang also reads each reported file the way the N64 compiler does (`N64_FLAGS`: no `TARGET_PC`, so the file's own
   declarations count; 32-bit MIPS; C89, in which a call to an undeclared function declares it), and pairs each call
   with the same call there: the call to the same function on the same line, or failing that the call in the same
   place among the calls to that function from that function, when both views make the same number of them. An
   argument that the PC declaration converts from an integer to a float is flagged C1 when the N64 view does not
   convert it too: the N64 passed the integer's bits, which the function reads as a float, and the PC passes the
   integer's value (100.0f's bits arrive as 1120403456.0f). It is not flagged when the N64's own declaration has a
   float there, or for a literal 0. A call written only for the PC, with no N64 partner, is flagged when the integer is
   a float read through an integer pointer, an extern variable another file declares as a float, or a constant of
   2^24 or more. Other forms in such a call, such as an `s32` local or an integer-typed table that holds a float's
   bits, are not seen; a call written only for the PC should pass the `f32` itself. The summary line "calls with no
   partner in the N64 view (written only for the PC)" counts the calls that found no partner.
6. A call to a function outside the set must reach code that the port replaces, as the choices at the top of
   `tools/port_filelist.py` name it: Nintendo SDK code listed in `docs/sdk_functions.md`, which the port replaces with
   a stand-in, or one of the game files that it replaces with its own version. Any other function outside the set
   means that the set is incomplete, and the tool stops with exit status 2.
7. A call through a function pointer is flagged when the pointer is made from an integer, or read through a pointer to
   integers, as from a table declared `u8[]`.

### Effects and classes

The effects:

- **crash**: a pointer is cut to 32 bits, or the function reads a pointer from a place that holds something else.
- **wrong value**: the function gets, or the caller gets back, a different number than on the N64.
- **clang-only**: an integer argument wider than the parameter. GCC at any optimisation and clang at `-O0` narrow it in
  the called function, as the N64 code does; clang at `-O1` and above counts on the caller to have narrowed it.
- **harmless**: the two sides differ, but the PC does what the N64 does.
- **SDK**: the function is Nintendo SDK code that the port replaces with a stand-in. The decompilation's C of an SDK
  function often declares a pointer parameter as `s32`, as the N64 code it matches allows, where the stand-in takes
  the pointer, so the function's own types do not decide. A finding on the caller's side counts whatever the
  stand-in's types are: an integer passed where the function reads a pointer (A2), a pointer result read as an integer
  (B), or a missing argument (D). Such a call is rated crash or wrong value like any other.
- **replaced**: the function is game code that the port replaces with its own version, which decides.
- **not rated**: clang reported an error inside the call, so the call cannot be read. The compile check covers it.

Crash and wrong value block: they give exit status 1. The classes:

- **A1**: the caller passes a pointer into an integer parameter: the function keeps its low 32 bits.
- **A2**: the function reads a pointer where the caller passes an integer (a pointer cast to `s32`, an `s32` variable
  or field, a constant), or a literal 0 on the stack, which leaves the pointer's upper half unset.
- **B**: the function returns a pointer and the caller reads an integer, or the reverse.
- **C1**: a float and an integer in each other's place: the N64 passes both in the same register, the PC in different
  ones. Also an integer that the caller's PC declaration converts to a float by value where the N64 passed the integer
  itself: a constant such as `0x3F800000` (1.0f's bits, which the conversion makes 1065353216.0f), an `s32` variable
  holding a float, or `*(s32 *)&f`.
- **C2**: a 64-bit argument after the N64's alignment pad: on the N64 a 64-bit argument starts on an even register, so
  a definition can have an unused parameter that only fills the gap; on the PC the arguments after that parameter move.
- **D**: the function reads a parameter that the caller does not pass.
- **E**: the caller uses the result of a function defined to return nothing: on the PC the register it reads holds no
  defined value.
- **F1**: an integer argument wider than the parameter (clang-only).
- **F2**: a narrow result (`s16`, `u8`) read as `s32`. Used at full width it is a wrong value: GCC at any optimisation
  and clang at `-O1` and above leave the register's upper bits unset. It is harmless when only its low bits can
  matter: converted back to its own width or narrower, masked with a constant within that width, or shifted left so far
  that only those bits are left, perhaps after `+`, `-`, `*`, `&`, `|`, `^` or `~` with other values.
- **G**: a call through a function pointer made from an integer or read from a table of integers.
- **H**: a struct passed by value, which the two conventions split differently.
- **O**: another difference in how a value travels (64-bit and 32-bit integers, a float where a double is read).
- **Z**: a difference without effect: a literal 0 for a pointer passed in a register, more arguments than the function
  reads, a parameter the function never reads, an integer cast to a pointer and read back as an integer.
- **X**: a compile error inside the call.

Each blocking call is printed as `FILE:LINE: effect: callee (class and its name): reason`, and the summary counts the
flagged calls by class and effect; a call through a table counts once for each function it reaches. The `--tsv` file
has one row per flagged call: its location, the caller, the callee, the class, the effect, the declaration the caller
sees, the definition and where it is, the reason, the allow file's reason if it lists the call, and the call's text.

### The allow file

The allow file lists calls rated crash or wrong value that wait for a later step, one per line: the location
(`src/main/x.c:12`), the callee as the report names it, and the reason, separated by tabs. Lines that start with `#`
are comments. A listed call is not printed and does not block; the summary counts it, and the `--tsv` file shows the
allow file's reason in its `allowed` column. An entry that matches no blocking call is printed on standard error.

### The extern table

The `--externs` file lists the extern variables that the set's files declare with more than one type: for each, its
kind, how many files declare it, and each type with its number of declarations and an example:

| Kind | Effect on the PC |
| :-- | :-- |
| pointer and integer views | a 64-bit pointer read or written through a 32-bit view |
| struct and other views, different struct views | the offsets move if a struct holds a pointer |
| different widths | a narrower view reads other bytes on a little-endian PC |
| same width | none for the variable itself: signedness, `f32` and `s32` views of the same bits, an array or a scalar |

"None" is about the variable alone: a call that passes a same-width variable's `s32` view to a float parameter is a C1
row in the call report (`D_800F9B0C` was one).
