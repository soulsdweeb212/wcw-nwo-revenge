# WCW / nWo  REVENGE (decompilation)

A matching decompilation of WCW / nWo  REVENGE for the Nintendo 64, started with [decompdecomp](https://github.com/n-delic/decompdecomp).
1308 of 1345 functions build as C objects (97.2%). 25 of those are hand-written routines wrapped in a top-level `asm()` block
(see below), so 1283 are real C that compiles to exactly the original code; the other 37 functions are still plain assembly.
`build.py` rebuilds the game from this tree and checks it against your original, byte for byte.

## Build

1. Put your own copy of the game here as `baserom.z64` (it is in `.gitignore`; never commit it).
2. `python3 build.py` (it uses decompdecomp's period compiler and assembler, so decompdecomp must be installed).

## Layout

| Path | What it is |
| :-- | :-- |
| `src/<segment>/<function>.c` | Decompiled functions, one per file, each matching the original. |
| `asm/nonmatchings/` | Assembly of every function (the target for the decompiled ones). |
| `asm/data/`, `asm/*.s`, `assets/` | Data, start-up code and binary parts, still as assembly or binary. |
| `include/common.h` | Types, structs and prototypes worked out so far. |
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
- `tools/asm_to_c.py FUNC...` wraps a function's assembly in an `asm()` block so it builds as a C object.
- `nonmatching/` holds near-miss drafts that `build.py` does not compile (see its README for how far off each is).
- A source file can hold several consecutive functions: give each the same `"c"` in `build.json`; the object is placed once,
  at the first function's address. Needed when the original was compiled as one unit (`func_800D36E8.c` holds
  `func_800D36E8`, `func_800D371C` and `func_800D3744`: standalone, the assembler pads the first `mul.s` of
  `func_800D371C` with a `nop` the ROM does not have).
- Labels in the middle of a function that other code jumps to (`alabel` in the splat output) need an entry in the
  `symbols` table of `build.json`.
- A C function with a jump table or double constants needs its `own` `.rodata` base in `build.json` (the address of the
  table in the game, e.g. `setAudioRegionParameter` -> `0x8003B4F0`). `build.py check` cannot verify these when the table
  sits in another overlay's address range, so check with a full build.

### Still assembly, with a reason
- `func_80018140`, `initAudioStream`: jump-table functions (the `own` placement is understood now); a draft of
  `func_80018140` is in `nonmatching/` (register allocation still differs). `initAudioStream` is the same code with a
  registration call in front.
- `func_800DACE4`, `func_800DBB80`: jump-table functions, not yet attempted with `own` placement.
- `func_8001A490`, `func_8001A65C`, `func_8001A980`, `func_8001AD00`: kept as assembly, no longer match (cause not found;
  they begin with ordinary stack setup, so the leading-`nop` issue above does not explain them).

### Hand-written assembly (not expected to become C)
These were written in assembly in the original (CP0/TLB/cache/FPU access, or hand-scheduled `.set noreorder` code with
`nop` delay slots, which neither KMC GCC nor IDO produces from C). They build as `asm()` objects (`tools/asm_to_c.py`),
so the ROM is still byte-identical, but they are not decompiled.
- `func_80026AF0` (reads CP0 Count), `func_80026B00` / `func_80026C20` (read / write CP0 Status), `func_80028100` (writes CP0 Compare)
- `func_80026C10` (reads and writes the FPU control register)
- `nw2DisableInterrupts`, `nw2RestoreInterrupts` (edit CP0 Status)
- `func_8001C860` (data-cache `cache` loop), `func_80026C30`, `func_80026C80` (TLB setup)
- `func_800266B4`, `func_800266FC` (thread queue insert / pop: tried in C with KMC GCC and IDO 5.3/7.1, delay slots and registers differ)
- Also classified as hand-written by `tools/list_nonmatching.py` (CP0/cache/TLB instructions, or a "Handwritten" marker in the
  splat output); not all individually reviewed: `func_80021F60` (a `bzero` that aligns with a lone `swl`), `func_800264BC` (a helper inside the
  exception handler `func_80025F30`; it keeps its return address in `$s2`), `func_80025F30`, `func_8002BC40`,
  `func_80021C40`, `func_800265AC`, `func_8002670C`, `func_80026578`, `func_80026B50`, `func_8001C5B0`, `func_8001C660`,
  `func_8001C740`, `func_8001C7E0`.

Probably assembly too, not confirmed: the 64-bit helpers `func_800284F4` (a 64-bit multiply built from three 32x32
multiplies), `func_80028528` (unsigned 64-bit divide, shift-and-subtract), `func_80028624` (divide by a 32-bit divisor),
`func_80028860` / `func_80028880` (dispatchers that pick one of the two by checking the divisor's high word: they look like
`__udivdi3` / `__umoddi3`), `__divdi3`, `__moddi3`, `__fixsfdi`, `signed64ToFloatTrunc`. They use a non-standard calling
convention (`func_80028880` keeps `$ra` in `$t5`). This is from reading the assembly, not from a reference source.
