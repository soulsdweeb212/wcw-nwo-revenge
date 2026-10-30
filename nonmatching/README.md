# Functions that still do not match

`src/` holds C that builds to the exact original bytes. This folder holds the closest C we have for every function that
does **not** yet, plus why. `build.py` ignores it (it only compiles `src/`); move a file to `src/<segment>/<name>.c` and add
`"c"` (and, for jump tables or constants, `"own"`) to its `build.json` entry only when `build.py` says *identical* and
`python3 tools/check_rodata.py` still reports 0 not found. `STATUS.md` is the generated list (`python3 tools/list_nonmatching.py --md`).

## How a draft is measured

`~/.local/share/uv/tools/decompnet/bin/python tools/permute_run.py FUNC nonmatching/FUNC.c MINUTES [WORKERS]` compiles the draft
with the project's compiler and counts the instructions that differ from the ROM's bytes (0 = identical apart from relocations).
The counts below are that number. A count of 4 does not mean "4 lines of C": GCC 2.7.2 chooses instruction order, delay-slot
fills and registers with internal heuristics, so a one-instruction difference can need a different shape of source, and the
only way to learn the shape is to try (by hand, or with the permuter's random rewrites).

## Why each remaining function is not matched

### 1. Cut in half by a segment boundary (2 functions)
| function | what happens |
|---|---|
| `func_8009C218` (ROM 0x48988) | The listing ends after two instructions (`addiu $sp,$sp,-0x128; sw $s7,0x11C($sp)`). The code segment `code_80090000` stops at ROM 0x48990, but the function goes on: the bytes after it (`afbf0124 afbe0120 …`) are the rest of its prologue and body, which sit in the raw data blob `assets/48990.bin` and were never disassembled. |
| `func_800DDAC8` (ROM 0xD0F68) | Same thing at the end of `code_800BBA00`: two instructions (`lui $a2,%hi(D_800FAF5C); lw $a2,…`), then the function continues into `assets/D0F70.bin`. |

Nothing can be matched until the segment ends are moved so the rest of each function is disassembled (`splat.yaml` and
`build.json`, then re-split). Their real sizes are unknown (probably around a kilobyte each); they are two more large
functions, not two tiny ones.

### 2. Complete C, a few instructions off (scheduler or register differences)
These have the whole function written and the same structure as the ROM. What differs is how GCC ordered a few instructions
or numbered registers. Each is a search problem. "Draft" is the count for the C in this folder; "search" is the best count the
permuter reached (hundreds of thousands of variants in total) with rewritten code that is full of dummy locals and wrong
types, so it is not kept, only the number.

| function | size | draft | search | what differs |
|---|---|---|---|---|
| `func_8000A3DC` | 0x694 | 4 | 4 | a `sra`/`mult` pair for `arg1 % 3` sits two slots later than in the ROM. The draft needs a dummy `tq = a1 & 1; if (tq >> 1)` to reach 4; plain `%` gives 9–13. |
| `func_800900C0` | 0x240 | 6 | 2 | `v1` where the ROM uses `v0` for the callback-address temporaries (the `-1` stored later is created too early). The search's 2 uses `sb` where the ROM has `sw`, so it is not a real match. Display-list constants are kept in locals `c1..c5`; a `u8 pad[0x34]` local fixes the frame; changing the callees' return types alone does nothing. |
| `func_80012CD0` | 0x3C8 | 6 | 3 | in the `mode >= 11` branch the ROM loads `pz` after computing `y - py`; ours loads it earlier and adds a `neg.s`. |
| `func_800C0E44` | 0x458 | 10 | 5 | branch delay slots: the ROM leaves `nop`s where ours fills with `move a0,a2`. |
| `func_800291C0` | 0x3F4 | 6 | 6 | jump table. `beql` vs `beq` and `a0` vs `v0` in three places. |
| `func_80006178` | 0x594 | 9 | 7 | the placement of one `lw` and the order of two float operations. |
| `func_800A83DC` | 0x938 | 29 | 14 | jump table. One `beqzl`, and `index * 0x1A30` (built from shifts and subtracts) is scheduled in a different order in two places, which changes two registers. |
| `func_8000C91C` | 0x3FC | 40 | 18 | register numbering in the prologue (`s0`/`a2`/`t0`/`t1` swapped) that then runs through the whole function. The search got there with chained assignments in the init loop (`a[k] = (b[k] = -1)`) and different integer types, neither of which helps on its own. |
| `func_80095884` | 0xE28 | 45 | 36 | load order in one block and float register numbers (`$f4` vs `$f6`) in another. |
| `func_800C4C60` | 0x530 | 48 | 22 | jump table; decoded from the ROM this session. Structure is identical; the `fC++` / `D_800FABD8` block is scheduled earlier than in the ROM. Shares its last case with `func_800C5440`. |
| `func_800B6DEC` | 0x40C | 31 | 27 | jump table; decoded from the ROM this session. The ROM keeps a separate copy of the same flag test in six cases, while GCC merges two of them in ours; the evaluation order of case 0 differs. |

### 3. Draft incomplete: needs more decoding from the ROM
| function | size | how much exists | what is missing |
|---|---|---|---|
| `func_800B61EC` | 0x5A0 | 124 of 330 instructions | everything after the first third (float checks against `D_800E5510…D_800E5540`). |
| `func_800B71F8` | 0x838 | 289 of 526 | jump table; roughly half of the cases. |
| `func_8009A878` | 0xDF4 | outline complete, 98 structural differences in 893 | long straight-line code with the statements in a different order; too big for random search, needs careful reading. |
| `func_8009773C` | 0x6E0 | a stub (9 of 420) | a variant of `func_80096D8C` that moves the tiles along a sine (`sinf` twice, then `func_80096A6C`); nothing past the setup is written. |

## Findings that apply to several functions
- Labels and fallthrough matter even when they generate no code: a `case` placed in the middle of a body, or a
  `do { … } while (0)` around a loop body, changes how GCC fills delay slots (`func_800B8278`, `func_800C8A10`).
- `u16` accumulators, `s16` arguments and the order of operands in a comparison (`a > b` vs `b < a`) each change the schedule.
- A local array is always kept in memory; a plain local whose address is taken is too (`func_80098804`, `func_800900C0`).
- GNU as pads a function that starts with a floating-point op when it is the first thing in an object; compile such a
  function in the same file as its neighbour (`func_800D371C`).
