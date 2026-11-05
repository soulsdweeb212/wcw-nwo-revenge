# Functions that still do not match

`src/` holds C that builds to the exact original bytes. This folder holds the closest C we have for any function that
does **not** yet, plus why (none at the moment). `build.py` ignores it (it only compiles `src/`); move a file to `src/<segment>/<name>.c` and add
`"c"` (and, for jump tables or constants, `"own"`) to its `build.json` entry only when `build.py` says *identical* and
`python3 tools/check_rodata.py` still reports 0 not found. `STATUS.md` is the generated list (`python3 tools/list_nonmatching.py --md`).

## How a draft is measured

`~/.local/share/uv/tools/decompnet/bin/python tools/permute_run.py FUNC nonmatching/FUNC.c MINUTES [WORKERS]` compiles the draft
with the project's compiler and counts the instructions that differ from the ROM's bytes (0 = identical apart from relocations).
The counts below are that number. A count of 4 does not mean "4 lines of C": GCC 2.7.2 chooses instruction order, delay-slot
fills and registers with internal heuristics, so a one-instruction difference can need a different shape of source, and the
only way to learn the shape is to try (by hand, or with the permuter's random rewrites).

## The real ROM map
The game's overlay table is at ROM 0x37A30 (vram 0x80036E30). There are two overlays and both load at 0x80090000, only one at a time:

| overlay | ROM | text | data | bss end |
|---|---|---|---|---|
| 1 | 0x3C770-0x834A0 | 0x80090000-0x800C5AD0 (ROM to 0x72240) | to 0x800D6D30 | 0x800EA350 |
| 2 | 0x834A0-0xDAC50 | 0x80090000-0x800E2B10 (ROM to 0xD5FB0) | to 0x800E77B0 | 0x800FAFA0 |

`splat.yaml` declares them as segments `overlay1` and `overlay2` with one `exclusive_ram_id`, so neither sees the other's symbols. Each overlay function in `symbol_addrs.txt` carries `rom:` and `segment:`; without them splat drops the name. The source folders keep their names: `code_80090000` is overlay 1; `ovl2_80090000`, `code_8009D7A0`, `code_800BBA00` and `code_800DE9C0` are overlay 2 in ROM order. `build.json` marks each segment with `overlay`, and `build.py check` reads only the function's own overlay, so jump tables can be validated there now.

Two overlays can hold different things at one address. When an old name was already taken, the new function has `_ovl1` or `_ovl2` on the end (four so far, such as `func_800A1550_ovl1`). The names of overlay 1's data used to be overlay 2 function names; they are `D_` addresses now. An address at or above 0x80090000 in C belongs to the overlay of the file using it. `tools/ghidra.py new` should stay at 0.

## The last four (matched 2026-11-05)
Every function matches now, so this folder holds no drafts. These four were the last, each stuck for days at a few
instructions with permuter runs that could not finish them. What each needed:

| function | stuck at | what matched it |
|---|---|---|
| `func_80006178` | 9 | Rewritten with the real libultra `gbi.h` macros (`gDPLoadTextureTile`, `gDPLoadTextureTile_4b`, `gSPTextureRectangle` written out, defined at the top of the file because `common.h` has none) instead of raw command words. The `0.5` is a literal double, so the function owns its `.rodata` at 0x8003B120. Two non-obvious shapes: `rx <<= 2; ry <<= 2;` before the rectangle, and the clamps compare against `(u32)` values, which the ROM's `sltu` needs. |
| `func_8000C91C` | 45 | The entry lookup is a static inline with its real signature, `getEntry(u32 id, s16 n)` returning `D_80032B44[bank][idx][n]`. `arg5`/`arg6` are copied into `s16` locals `first`/`second` before the `arg3` clamp, `arg1` is `u16`, and `D_80075440` is an `s16[][3]` table. That fixed the allocator priorities that put `arg2` in `s2`. |
| `func_80012CD0` | 8 | The else branch gets its own block-local `u8 *m2`, assigned once (`m2 = obj + 0x1C;` after the `func_800056CC` call), and calls `func_80007E04(m2, x, y, z)` itself; the if branch keeps `m`. Set once, the pointer counts as a register birth in the first scheduling pass, which gives the ROM's order (`y - py` before `z - pz`); the two `func_80007E04` tails are still cross-jumped into one. |
| `func_800291C0` | 6 | `charIndex(u8 c, s32 flag)` is copied word for word as a static inline from the matched sibling `func_80028E28`, and the glyph pointer is chosen the way that sibling's glyphData does it (`rec = (u8 *)&D_80064AD4[n * 9]` / `D_80064AD0 + n * 15`), with `D_80064AD4` as `s32 *`. The function owns its `.rodata` at 0x8003B9F0 (two jump tables). |

The lesson repeats the findings below: for a stuck function, look for a matched sibling that touches the same globals and
copy its helpers and types exactly, before trying to reorder the instructions in the one function.

## Findings that apply to several functions
- A dead initialiser can separate two GCC decisions. In loop.c a user variable is movable only if its first mention is the
  set being hoisted, so `u32 c = 0;` at function scope (dead) keeps a later `c = 0xF5080000` inside the loop; flow then deletes
  the dead init, so the first scheduling pass still sees one set and gives it the "birthing" priority (sched.c adjust_priority,
  ties broken by insn order). That fixed both remaining differences in an alternative `func_80006178` match (worker A,
  2026-11-05); the installed version uses gbi.h macros instead and needs no such variable.
- A `beql` can need a branch that later disappears. In `func_800A83DC`, `if (x) { if (b) { y = 0x5A; } else { y = 0x5A; } } else { y = 0x3C; }` reads `v0` on the fall-through path during the delay-slot pass, so the slot is annulled; the identical arms are then merged away. The inner test must not use `x` itself (score 1-3). The permuter found this; `tools/reduce_match.py` left noise, but the one odd `if` was the whole answer.
- An inlined function is worth writing as one, with its real signature. Check `src/` for a matched function with the same shape first. A helper's parameter copies add insns during register allocation that vanish later, and that one step of lifetime can flip every register choice: writing `func_800A7C40` as an inline took `func_800A83DC` from 29 to 1.
- Local-alloc orders values by `floor_log2(refs) * refs / life`. When two register chains are swapped, count both from the `.lreg` dump: the result shows how many insns of lifetime are missing.
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
