# WCW / nWo  REVENGE (decompilation)

A matching decompilation of WCW / nWo  REVENGE for the Nintendo 64, started with [decompdecomp](https://github.com/n-delic/decompdecomp).
1266 of 1361 functions are C that compiles to exactly the original code; the rest are still assembly.
`build.py` rebuilds the game from this tree and checks it against your original, byte for byte.

## Build

1. Put your own copy of the game here as `baserom.z64`
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
| `objdiff.json` | Per-function units for [objdiff](https://github.com/encounter/objdiff). |

Keep going with any tool: write a function in C under `src/`, add it to `build.json` (see the existing entries),
run `build.py`. When it says *identical*, the function matches. This is the base for ports and mods: once
everything is C, the game can be rebuilt, changed and moved to other platforms.

The game's code and data belong to their rights holder

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
- `func_800DBB80`: kept as assembly, its own data isn't laid out like the game's
