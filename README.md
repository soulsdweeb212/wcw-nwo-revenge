# WCW / nWo  REVENGE (decompilation)

A matching decompilation of WCW / nWo  REVENGE for the Nintendo 64, started with [decompdecomp](https://github.com/n-delic/decompdecomp).
1274 of 1359 functions are C that compiles to exactly the original code; the rest are still assembly.
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
- `func_80018140`: kept as assembly, its own data isn't laid out like the game's
- `setAudioRegionParameter`: kept as assembly, its own data isn't laid out like the game's
- `func_8001A490`: kept as assembly, no longer matches
- `func_8001A65C`: kept as assembly, no longer matches
- `func_8001A980`: kept as assembly, no longer matches
- `func_8001AD00`: kept as assembly, no longer matches
- `initAudioStream`: kept as assembly, its own data isn't laid out like the game's
- `setAudioStreamRegionParameter`: kept as assembly, its own data isn't laid out like the game's
- `func_800DACE4`: kept as assembly, its own data isn't laid out like the game's
- `func_800D371C`: kept as assembly, no longer matches (the C compiles 4 bytes too large: an extra leading nop)
- `func_800DBB80`: kept as assembly, its own data isn't laid out like the game's

### Hand-written assembly (not expected to become C)
These were written in assembly in the original (CP0/TLB/cache/FPU access, or hand-scheduled `.set noreorder` code with
`nop` delay slots, which neither KMC GCC nor IDO produces from C). They are meant to stay assembly.
- `func_80026AF0` (reads CP0 Count), `func_80026B00` / `func_80026C20` (read / write CP0 Status), `func_80028100` (writes CP0 Compare)
- `func_80026C10` (reads and writes the FPU control register)
- `nw2DisableInterrupts`, `nw2RestoreInterrupts` (edit CP0 Status)
- `func_8001C860` (data-cache `cache` loop), `func_80026C30`, `func_80026C80` (TLB setup)
- `func_800266B4`, `func_800266FC` (thread queue insert / pop: tried in C with KMC GCC and IDO 5.3/7.1, delay slots and registers differ)

Probably assembly too, not confirmed: `func_800284F4` (64-bit multiply), `func_80028860`, `func_80028880`, `__divdi3`, `__moddi3`,
`__fixsfdi`, `signed64ToFloatTrunc` (libgcc-style 64-bit helpers).
