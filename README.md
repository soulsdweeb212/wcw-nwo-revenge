# WCW / nWo  REVENGE (decompilation)

A matching decompilation of WCW / nWo  REVENGE for the Nintendo 64, started with [decompdecomp](https://github.com/n-delic/decompdecomp).
All 1696 functions build as C objects (100% of the code by size): the main program and both overlays are fully matched. 35 of
those are hand-written assembly routines wrapped in a top-level `asm()` block (see below), so 1661 are real C that compiles to
exactly the original code. The Nintendo SDK code linked into the main program (libultra 2.0I, libaudio, n_audio,
libmus, the KMC GCC runtime) carries its SDK names, functions and data: [docs/sdk_functions.md](docs/sdk_functions.md) lists the 380
functions and 103 globals and how each was identified. The overlays contain no SDK code; they call main's.
`build.py` rebuilds the game from this tree and checks it against your original, byte for byte.
<!-- Working with this project's owner: read notes/MasterIndex.md first and keep it updated (local only, gitignored). -->

## Requirements

- **decompdecomp** ([github.com/n-delic/decompdecomp](https://github.com/n-delic/decompdecomp)) must be installed. The build
  uses its pinned period compiler (KMC GCC 2.7.2), its binutils and its Python packages (`decompnet`), which decompdecomp
  manages itself. The system `python3` does not have these packages, so `build.py` re-runs itself under
  decompdecomp's own Python. It finds that Python from the `decomp` command (the first line of `~/.local/bin/decomp`, or the
  `python` it launches) and, if `decomp` isn't on `PATH`, from the `uv tool install` location
  `~/.local/share/uv/tools/decompnet/bin/python`. If neither exists it stops with "install decompdecomp first".
- Your own copy of the game as `baserom.z64` (SHA-1 `e1711a2511394b9357b5f1ac8ca5cc17bd674836`). It is in `.gitignore`;
  never commit it.
- Linux or WSL (this tree has been built under WSL2).
- To use the permuter helper (`tools/permute_run.py`), decompdecomp's `decomp setup` must have installed decomp-permuter.

## Build

1. Install decompdecomp (above) and put your copy of the game here as `baserom.z64`.
2. `python3 build.py`. The first run extracts the assembly and data from your copy (splat); every run ends with
   `identical: build/game.z64 matches baserom.z64 byte for byte` when the tree reproduces the original.

If `build.py` can't find decompdecomp's Python, run it with that interpreter directly, for example
`~/.local/share/uv/tools/decompnet/bin/python build.py`, and the tools under `tools/` the same way.

## Layout

| Path | What it is |
| :-- | :-- |
| `src/<segment>/<function>.c` | Decompiled functions, one per file, each matching the original. |
| `asm/nonmatchings/` | Assembly of every function (the target for the decompiled ones). |
| `asm/data/`, `asm/*.s`, `assets/` | Data, start-up code and binary parts, still as assembly or binary. |
| `include/common.h` | Types, structs and prototypes worked out so far. |
| `docs/sdk_functions.md` | The Nintendo SDK functions in the main program, with the evidence for each name. |
| `game.ld` | Places every function and data block at its original address. |
| `build.json`, `build.py` | How each file is built, and the build. |
| `objdiff.json` | Per-function units for [objdiff](https://github.com/encounter/objdiff) (`python3 build.py targets` makes their targets). |

Keep going with any tool: write a function in C under `src/`, add it to `build.json` (see the existing entries),
run `build.py`. When it says *identical*, the function matches. This is the base for ports and mods: once
everything is C, the game can be rebuilt, changed and moved to other platforms.

The game's code and data belong to their rights holder: keep this tree to yourself unless you have the right to
share it.

## Notes

### Tools and conventions
- `tools/list_nonmatching.py [--md]` lists every function that is still assembly, grouped by what stands in the way
  (`nonmatching/STATUS.md` is its output). `asm in C` means a hand-written routine wrapped in `asm()`, not decompiled.
- `tools/permute_run.py FUNC DRAFT.c MINUTES [WORKERS]` scores a C draft against the original bytes (0 = identical apart
  from relocations) and can random-walk it with decomp-permuter's generator. A score is a guide; `build.py` saying
  *identical* is the proof. The permuter's output is often mangled C, so read it before keeping anything.
- m2c gives a first C draft of a function from its assembly. It does not match anything: it never runs the compiler or compares
  with the ROM. Run it with the installed copy:
  ```
  ~/.local/share/decompnet/toolchains/m2c/venv/bin/m2c -t mips-gcc-c -f FUNC asm/nonmatchings/<segment>/FUNC.s
  ```
  `-f` picks the function; `--context FILE` adds your structs and prototypes (the file must already be preprocessed), which makes
  the result much more readable. It prints C to the terminal with `extern` guesses at the top and placeholder names (`arg0`,
  `var_fs0`, `sp10`, `?` for unknown types). Functions with a jump table stop with "the corresponding jump table is not provided",
  because the `.s` files don't include the tables. Treat the output as a draft: put it in `nonmatching/FUNC.c`, fix the types and
  structure, score it with `tools/permute_run.py`, and adjust it until `build.py` says *identical*. Most of the work is in that
  last step, because code that does the right thing still isn't always the source that compiles to the same bytes.
- `tools/check_rodata.py` rebuilds the jump tables and constants the compiler generates for functions with an `own` `.rodata`
  and looks for them in the ROM; `tools/relabel_switch.py` repairs `case` labels from the ROM's tables (see "Switch tables are
  checked against the ROM" below). Run the checker after a full build.
- `tools/add_headers.py [--dry-run]` writes the `@header` block at the top of every file in `src/` (name, addresses, size, asm path) from
  `symbol_addrs.txt` and `build.json`. Rerun it after renaming a function; it updates the blocks in place.
- `tools/asm_to_c.py FUNC...` wraps a function's assembly in an `asm()` block so it builds as a C object.
- `tools/ghidra.py` uses decompdecomp's Ghidra (needs a JDK). `import` analyses the ROM once into `build/ghidra/`; then `decomp FUNC` prints its C, `unmatched` writes C for every function that is still assembly, `new` lists functions missing from `build.json`, `search` finds instruction sequences (one regex per instruction, `;` between them) and `bytes` finds raw words anywhere in the ROM.
- `tools/indent_c.py [--check] [--diff] [paths...]` re-indents C files (all of `src/` by default) with 4 spaces per level. It changes
  only leading whitespace, so the build stays identical; its docstring lists the style rules.
- `tools/rename_func.py [--dry-run] OLD NEW ... | --file MAP.tsv` renames functions and data symbols everywhere (`symbol_addrs.txt`, `build.json`,
  the file name, every whole-word mention in `src/`, `include/`, the READMEs and `objdiff.json`, the headers) and deletes `asm/`
  so the next build extracts it again with the new names. Rebuild afterwards: a name can change the code (see
  `docs/sdk_functions.md`, `nw2Sqrtf` and `unusedMuldi3`).
- `tools/ulpp.sh`, `tools/ul.py`, `tools/ulsweep.py` compare [decompals/ultralib](https://github.com/decompals/ultralib) source
  with the ROM (`ULTRALIB=` a checkout): preprocess one file for a libultra version, diff one function against a ROM function,
  or score all of ultralib against every function of the chosen segments (main by default). `tools/uldata.py MAP.tsv OUT.json` finds the SDK's data globals:
  it lines identified functions up with their SDK source and collects which SDK variable each data reference is.
- `nonmatching/` is where near-miss drafts go (`build.py` does not compile it). It is empty now that every function matches; its
  README keeps the matching findings collected along the way.
- A source file can hold several consecutive functions: give each the same `"c"` in `build.json`; the object is placed once,
  at the first function's address. Needed when the original was compiled as one unit (`func_800D36E8.c` holds
  `func_800D36E8`, `func_800D371C` and `func_800D3744`: standalone, the assembler pads the first `mul.s` of
  `func_800D371C` with a `nop` the ROM does not have).
- Labels in the middle of a function that other code jumps to (`alabel` in the splat output) need an entry in the
  `symbols` table of `build.json`.
- A C function with a jump table or double constants needs its `own` `.rodata` base in `build.json` (the address of the
  table in the game, e.g. `n_alFxParamHdl` -> `0x8003B4F0`). `build.py check` reads the function's own overlay, so it
  can verify these.

### Switch tables are checked against the ROM
`build.py` identical means the *code* is identical. A C function's own `.rodata` (jump tables, float/double constants) is placed
by the `own` entry but not written into the ROM (the ROM's bytes are used), so a `case` label pointing at the wrong body, or a
wrong constant, would still give an identical ROM. `tools/check_rodata.py` rebuilds those bytes from the compiled objects and looks
for them in the ROM; every function with an `own` `.rodata` passes it (118 at the time of writing). Run it after a full build
whenever you add or change a function with a `switch` or constants.

If it reports a function as NOT FOUND, its code is right but its `case` labels (or a constant) are not. The ROM's table says which
body each case value must reach; the bodies' order in the source decides their addresses. `tools/relabel_switch.py FUNC` rewrites
the labels from the tables (`--explain FUNC` prints the C and ROM tables and the switch's groups side by side, `--lines FUNC
OFFSET...` maps code offsets to source lines). It can't invent a label inside the middle of a body or restructure a fallthrough:
those take a manual edit, using the ROM's instructions at the target address to find the statement it starts. Rebuild after each
change; the ROM must stay identical.

### Still assembly
No function is left as plain assembly. The last four (`func_80006178`, `func_8000C91C`, `func_80012CD0` and `func_800291C0`,
all in the main program) were matched on 2026-11-05; `nonmatching/README.md` says what each one needed.

### Earlier attempts (`progress/`)
If you have the `progress/` folder decompdecomp saved next to this tree, `progress/src/<function>.c` holds C that its judge
accepted and `progress/best/<function>.c` the closest attempt at each function that did not match. Most of them score 0-10
differing instructions with `tools/permute_run.py` and are the best starting point for a function that is still assembly.
To use one here: add `#include "common.h"` as the first line (decompdecomp prepends the header itself), write the
function's float/double constants as literals instead of `extern` symbols (so the function's own `.rodata` is built and
placed with `own`; check the value against the ROM, because the build cannot see a wrong constant), and check with a full
build.

### Hand-written assembly (not expected to become C)
Each of these files now also explains the routine (what it does, its libultra name where it has one, its callers and the
hardware it touches) and holds an equivalent C version under `#ifdef NON_MATCHING`, with the original `asm()` under `#else`.
The normal build never defines `NON_MATCHING`, so it keeps using the asm and stays identical. The C is for reading: an
independent check traced each version against the assembly. It is not a working replacement build. Instructions C has no
form for (CP0, cache, TLB, `eret`) are one-line inline-asm helpers, and the exception-handler pieces are entered by
branches, not calls. `rspbootTextStart` is not CPU code at all: it is RSP code (libultra's `rspboot` plus the start of the
audio microcode), so its C model is under `#if 0`. The C versions of `__osEnqueueThread`, `__osPopThread` and the seven one- or two-instruction CP0/FPU accessors also compile to the original bytes (checked with
`lk.py`, not with a build), but they need register pinning to get there, so the asm stays the built version.

These were written in assembly in the original (CP0/TLB/cache/FPU access, or hand-scheduled `.set noreorder` code with
`nop` delay slots, which neither KMC GCC nor IDO produces from C). They build as `asm()` objects (`tools/asm_to_c.py`),
so the ROM is still byte-identical, but they are not decompiled.
- `osGetCount` (reads CP0 Count), `__osGetSR` / `__osSetSR` (read / write CP0 Status), `__osSetCompare` (writes CP0 Compare)
- `__osSetFpcCsr` (reads and writes the FPU control register)
- `__osDisableInt`, `__osRestoreInt` (edit CP0 Status)
- `osWritebackDCacheAll` (data-cache `cache` loop), `osUnmapTLBAll`, `osMapTLBRdb` (TLB setup)
- `__osEnqueueThread`, `__osPopThread` (thread queue insert / pop: tried in C with KMC GCC and IDO 5.3/7.1, delay slots and registers differ)
- Also classified as hand-written by `tools/list_nonmatching.py` (CP0/cache/TLB instructions, or a "Handwritten" marker in the
  splat output); not all individually reviewed: `bzero` (aligns with a lone `swl`), `send_mesg` (a helper inside the
  exception handler `__osExceptionPreamble`; it keeps its return address in `$s2`), `__osExceptionPreamble`, `rspbootTextStart`,
  `bcopy`, `__osEnqueueAndYield`, `__osDispatchThread`, `handle_CpU`, `__osProbeTLB`, `osInvalDCache`, `osInvalICache`,
  `osSetIntMask`, `osWritebackDCache`.

The compiler-runtime routines are hand-written assembly too and are built the same way: `bcmp` and the 64-bit helpers `unusedMuldi3`
(a 64-bit multiply from three 32x32 multiplies that nothing calls), `func_80028528` (unsigned 64-bit divide, shift-and-subtract), `func_80028624` (divide by a
32-bit divisor), `__udivdi3` / `__umoddi3` (dispatchers that pick one of the two by the divisor's high word), `__divdi3`, `__moddi3`, `__fixsfdi` and `__floatdisf`. They use `lwl`/`lwr`, `$t9` as scratch, tail
jumps between each other and `$ra` kept in `$t5`, which C cannot produce. (Identified from reading the assembly, not from a reference source.)
