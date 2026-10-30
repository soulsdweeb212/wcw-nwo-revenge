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

### 1. Cut off at a segment end
| function | size | what happens |
|---|---|---|
| `func_8009C218` | 0x2A40 | `func_8009C218.c` here is raw m2c output (about 1,500 lines, does not compile). The listing stops after two instructions at the end of `code_80090000`; the rest is in the blob `48990`. Mostly long hard-coded display lists: write them with the macros (see below). Its jump tables are at ROM 0x82830 and 0x82878, inside that blob. |

Keep the segment where it is until the C exists. The function runs to vram 0x8009EC58, past the start of `code_8009D7A0` at 0x8009D7A0, so if splat disassembles it, other code's calls to those addresses become global labels inside it and collide with the real functions (`multiple definition of func_8009D8D0`). Extending it only works in a tree with an existing `asm/`; a fresh checkout fails. Scoping the symbols with `segment:` does not help. When the C is ready, make the move in the same change: end `code_80090000` at ROM 0x4B3C8, change the blob's start and name to `4B3C8`, set the size in `symbol_addrs.txt`, and add `D_C9840` to `symbols`. `tools/extend_function.py` gives the full listing to work from.

The blob after it is not all data: code carries on straight after `func_8009C218` (at least 16 more `jr $ra` in the next 15 KB), so there are functions that are not in `build.json` at all, and 1345 is an undercount.

### 2. Complete C, a few instructions off (scheduler or register differences)
These have the whole function written and the same structure as the ROM. What differs is how GCC ordered a few instructions
or numbered registers. Each is a search problem. "Draft" is the count for the C in this folder; "search" is the best count the
permuter reached (hundreds of thousands of variants in total) with rewritten code that is full of dummy locals and wrong
types, so it is not kept, only the number.

| function | size | draft | search | what differs |
|---|---|---|---|---|
| `func_80012CD0` | 0x3C8 | 8 | - | in the `mode >= 11` branch the ROM computes `y - py` before `z - pz`; ours does the stack argument first. The draft is now a plain `z - pz` with the right instruction count. Temporaries in any order, and `px`/`py`/`pz` as an array or struct, give the same output. Also tried: a pointer to the entry, locals for `x`/`y`/`z`, storing the differences in `px`/`py`/`pz` or an array (8-68). The search reached 7. From the RTL dumps: `x - px` and `y - py` merge straight into `a2`/`a3`, and `z` goes through a pseudo to the stack slot. `-(pz - z)` had the right order, so `z` needs one extra step that vanishes after scheduling. Not it: `-ffast-math` (8), inline wrappers (8-21), `register` temporaries (8). |
| `func_800291C0` | 0x3F4 | 6 | 2 | jump table. `off` lives in `a0` in the ROM and is copied to `t0` for its use in only one of the two glyph-size branches; ours keeps it in `v0`. The two uses are written as shifts in the source: plain `i * 72` / `i * 30` expand differently (score 13-31). Variants that keep `off` alive past the copy make both branches use `a0` (13). The search's 2 is mangled and leaves out the `move t0,a0`. Also tried: unsigned `i`, `break` and `for (;;)` search loops, and one variable for `ch` and `off` (6-24). Typed pointers (`u32 *` + `i * 18`, `[18]` rows) fold back to `i * 72` (31), so the shifts are written by hand. By the CSE rule a copy that is canonical in one branch is canonical in both, so the source must be something other than a plain `t0 = off`. |
| `func_80006178` | 0x594 | 9 | 7 | the placement of one `lw` and the order of two float operations. The odd `c = 0xF5080000` variable is needed: the dump shows it stops a constant group being hoisted, which removing it does (69). |
| `func_800A83DC` | 0x938 | 3 | 2 | jump table. A local `Anim83DC *t` for the table entry fixed the `index * 0x1A30` registers (29 to 3). Left: (1) the ROM folds the `+0x10` into the table address where ours adds it with an extra `addiu` in two places. Every form that folds it swaps `v0`/`v1` in the multiply (29): `u8 *`, array and struct pointers, a temp for the sum or the offset. Writing the multiply by hand gives 13-35. (2) one `beqzl` for the `0x5A`/`0x3C` store. A single store lets CSE share constants between the two `SETACT` blocks (42-44), so the two stores stay; `switch`, `goto` and `if`/`else` forms give 3-9. The search got a real `beqzl` (score 2) from noise: duplicate branches around the store, which suggests the target needs a second reference. Its code is unusable, and it never removed the `addiu`. |
| `func_8000C91C` | 0x3FC | 45 | 23 | The first loop's counter and the later `i` are one variable; with that the dummy `tq` block is unnecessary and only 2 opcodes differ. The rest is allocator priority: `arg2` lands in `s2` where the ROM has `t8`, which renumbers the pointers the loops hoist. |
| `func_80095884` | 0xE28 | 45 | 36 | load order in one block and float register numbers (`$f4` vs `$f6`) in another. |

### 3. Draft incomplete: needs more decoding from the ROM
| function | size | how much exists | what is missing |
|---|---|---|---|
| `func_8009773C` | 0x6E0 | 131 | 60 | The score went up but the structure is far closer: the frame, `$fp` for `cols`, the hoisting and the instruction count (420) all match, and most of the 131 is register numbers. It uses `gSPModifyVertex`-style macros. The dump shows `(t << 21) >> 16` hoists whenever lifetime x savings is large (`life 3, savings 2` still moves), so each is set twice with `lo \|= hi1`, as the ROM's `or v1,v1,a2` does, in separate variables for `t` and `t1`. Left: the scheduler puts the shifts before the stores where the ROM mixes them. |

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
- Fewer variables can be the fix: one `s16 e = arg0` used everywhere, instead of a copy plus casts, removed two dummy blocks and took `func_8000A3DC` to 0.
- Dump the compiler instead of guessing from the output. Build `a.c` from `include/common.h` plus the draft, then in that folder run `cccp -undef -D__GNUC__=2 -Dmips -D__mips__ -DLANGUAGE_C a.c a.i` and `cc1 -quiet -G0 -mips3 -mgp32 -mfp32 -O2 -dl -dg -dS -dR -dj -dc -dL a.i -o a.s` (both in `~/.local/share/decompnet/toolchains/gcc-2.7.2-kmc`). `a.i.greg` lists register dispositions and "Spilling reg N"; a pseudo missing from the dispositions has no hard register and is reloaded at each use.
- Reload can only pick an unused register first, so a ROM that uses `v0` for a value GCC reloads through `v1` means the value was never hoisted. The loop pass hoists by comparing a value's lifetime with the loop's insn count, so a loop that looks too small may be missing macro temporaries (`func_800900C0`).
- Write display lists with a macro and a moving pointer: `dl = (Gx *)(q + 0xE0); CMD(dl++, 0xE7000000, 0);` with `#define CMD(p, a, b) { Gx *_g = (Gx *)(p); ... }`. Commands `0xE7`, `0xFA`, `0xDE` and `0xDF` are gDPPipeSync, gDPSetPrimColor, gSPDisplayList and gSPEndDisplayList. Bare stores and a `do { } while (0)` macro both failed; this took `func_800900C0` to 0 and removed the old constant locals.
- The loop dump (`a.i.loop`) prints every hoist: `Insn N: regno R (life L), savings S moved to` or `not desirable`. A pseudo set more than once is never hoisted, so `x = a; x |= b;` keeps a shared term in the loop where a single assignment does not.
- Moving a segment end: run `tools/extend_function.py FUNC SIZE`, change `end` and the blob's `start` and name in `build.json`, the `bin` line in `splat.yaml`, and the size in `symbol_addrs.txt`, then require *identical* before writing C, and test a fresh clone (`rm -rf asm assets build` in a copy), because an existing `asm/` hides problems splat would hit. `asm/` and `assets/` are gitignored and regenerated by splat, so the blob must be renamed to its new start or a fresh checkout breaks. Jump tables for `code_80090000` are in the blob: search the ROM for runs of pointers into the function.
- m2c needs `jal`, `%hi`/`%lo` symbols and a `.rodata` file holding the tables; with those it gave a usable state machine for `func_800DDAC8`, which went from nothing to 0 in five edits.
- Sharing one C variable between unrelated blocks makes it a global pseudo, which takes a register and changes what reload spills through. In `func_8009A878`, splitting `k` and giving the overlay block its own temporaries fixed every register and the whole frame (481 differences to 3).
- Two stores in an if/else can be cross-jumped into one, and that gives `beqz` where a single store after a temp gives `beqzl` (`func_8009A878`).
- Labels and fallthrough matter even when they generate no code: a `case` placed in the middle of a body, or a
  `do { … } while (0)` around a loop body, changes how GCC fills delay slots (`func_800B8278`, `func_800C8A10`).
- `u16` accumulators, `s16` arguments and the order of operands in a comparison (`a > b` vs `b < a`) each change the schedule.
- A local array is always kept in memory; a plain local whose address is taken is too (`func_80098804`, `func_800900C0`).
- GNU as pads a function that starts with a floating-point op when it is the first thing in an object; compile such a
  function in the same file as its neighbour (`func_800D371C`).
