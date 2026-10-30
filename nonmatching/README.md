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
| `func_800900C0` | 0x240 | 4 | - | `move a0,s1; li a1,1` sit after the two callback stores where the ROM has them before. The draft uses the real symbol `D_C5B90` (the old `sceneNodeCallback5C50 - 0x800000C0` was a hack) and `pad[0x3C]`. Storing both callbacks through one local `cb` fixed the `v0`/`v1` register, a hint from a permuter result that scored 0 but was unusable (it read an uninitialized variable). Type changes to `cb`, a block-scoped `cb` and inline constants do not fix the order. |
| `func_80012CD0` | 0x3C8 | 8 | - | in the `mode >= 11` branch the ROM computes `y - py` before `z - pz`; ours does the stack argument first. The draft is now a plain `z - pz` with the right instruction count. Temporaries in any order, and `px`/`py`/`pz` as an array or struct, give the same output. |
| `func_800291C0` | 0x3F4 | 6 | 2 | jump table. `off` lives in `a0` in the ROM and is copied to `t0` for its use in only one of the two glyph-size branches; ours keeps it in `v0`. The two uses are written as shifts in the source: plain `i * 72` / `i * 30` expand differently (score 13-31). Variants that keep `off` alive past the copy make both branches use `a0` (13). The search's 2 is mangled and leaves out the `move t0,a0`. |
| `func_80006178` | 0x594 | 9 | 7 | the placement of one `lw` and the order of two float operations. |
| `func_800A83DC` | 0x938 | 3 | 3 | jump table. A local `Anim83DC *t` for the table entry fixed the `index * 0x1A30` registers (29 to 3). Left: the ROM folds the `+0x10` into the table address where ours adds it with an extra `addiu` in two places, and one `beqzl`. Folding it (any form tried) brings the register swap back; a single store for the `beqzl` breaks the rest of the function (score 42-70). |
| `func_8000C91C` | 0x3FC | 40 | 18 | register numbering in the prologue (`s0`/`a2`/`t0`/`t1` swapped) that then runs through the whole function. The search got there with chained assignments in the init loop (`a[k] = (b[k] = -1)`) and different integer types, neither of which helps on its own. |
| `func_80095884` | 0xE28 | 45 | 36 | load order in one block and float register numbers (`$f4` vs `$f6`) in another. |

### 3. Draft incomplete: needs more decoding from the ROM
| function | size | how much exists | what is missing |
|---|---|---|---|
| `func_8009773C` | 0x6E0 | whole function, 84 differences in 420 | a sine-warped tile quad builder (one function: the `func_8009786C` etc. labels are mid-function, and other code calls them, so they need `symbols` entries, as do `D_800D6078`/`D_800D6080`). GCC's loop pass hoists the `(t << 21) >> 16` terms out of the inner loop, which takes the registers `cols` needs. Reusing a variable stops the hoist, but then the scheduler moves that block and the frame grows by 8. |

## Findings that apply to several functions
- GCC's CSE keeps a copy `t = r` only if `t` outlives the block and outlives `r`; otherwise it folds the copy. A `move` the ROM shows just before a test can mean the tested variable is reused later: in `func_800B61EC`, `t = r; if (t)` followed by `t = mode & 4` took the score from 5 to 0.
- A small type shows up at the use, not the assignment: an `s16` local assigned constants is sign-extended (`sll`/`sra`) where it is read (`k` in `func_800B61EC`, `lvl` and `val` in `func_800B71F8`).
- Search loops: `for (i = 0;; i++) { if (x >= T[i].lim) { val = T[i].val; break; } }` gives the ROM's shape where the first test and the result are duplicated with `i` folded to 0, which `while (x < T[i].lim) i++;` does not. GCC only duplicates a short exit body with no labels, so a long body, or one with an `if`, keeps a single test, and invariants after the loop are hoisted before it (`func_800B71F8`, cases 1 and 8; that case 1 went from 366 to 23 in one edit).
- `a - b - c` can come out with `c` subtracted first; swap the operands when a subtraction chain is scheduled in the wrong order (`func_800B71F8`, case 4).
- A branch's delay slot depends on whether the assignment is inside the `if`: `val = 1000; if (x) break;` and `if (x) { val = 1000; break; }` fill it differently (`func_800B71F8`, case 11).
- Check `case` positions against the jump table instead of trusting a draft: in `func_800C4C60` `fC++` belongs to case 2 and `case 3` starts after it. The label also ends the CSE block, which is why the ROM reloads the pointer there.
- GCC evaluates a call's `?:` argument late; a temp for it (`n = x ? 0x10 : 8; f(p, q, n);`) puts it before the other arguments (`func_800C4C60`, 30 to 6).
- Assign a local array's elements directly and read them back (`v[0] = ...; x = v[0] - v[1] - v[2];`) rather than through temporaries; that fixed `func_800B6DEC`'s registers (21 to 0).
- `func_800BF2FC` returns `s32` where the ROM uses the result without extending it, and `s16` otherwise. Give an external function's declaration the type its use in this function shows.
- A large round constant passed to a function may be a float: `0x40000000` in `a1` is `2.0f`. The two load in a different order, which also moves delay slots (`func_800C0E44`, 10 to 2). Check `src/` for an existing prototype first.
- Sharing one C variable between unrelated blocks makes it a global pseudo, which takes a register and changes what reload spills through. In `func_8009A878`, splitting `k` and giving the overlay block its own temporaries fixed every register and the whole frame (481 differences to 3).
- Two stores in an if/else can be cross-jumped into one, and that gives `beqz` where a single store after a temp gives `beqzl` (`func_8009A878`).
- Labels and fallthrough matter even when they generate no code: a `case` placed in the middle of a body, or a
  `do { … } while (0)` around a loop body, changes how GCC fills delay slots (`func_800B8278`, `func_800C8A10`).
- `u16` accumulators, `s16` arguments and the order of operands in a comparison (`a > b` vs `b < a`) each change the schedule.
- A local array is always kept in memory; a plain local whose address is taken is too (`func_80098804`, `func_800900C0`).
- GNU as pads a function that starts with a floating-point op when it is the first thing in an object; compile such a
  function in the same file as its neighbour (`func_800D371C`).
