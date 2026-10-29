# Near-miss drafts

C that is close to a function's original code but does not match it byte for byte. These are not built (`build.py` only
looks in `src/`); they are kept so the work isn't lost. Move one to `src/<segment>/<name>.c` only when `build.py` says
*identical*. `STATUS.md` lists every function that is still assembly (`python3 tools/list_nonmatching.py --md`).

| file | how far off | what is known |
|---|---|---|
| `func_80012CD0.c` | 8 of 242 instructions | in the `mode >= 11` branch the original computes `x-px`, `y-py`, `z-pz` in that order, ours loads `pz` earlier; `0.087890625` must be a literal so it is hoisted into `fs0`; `Ent` is the 0x5C-byte record from `func_80012364.c` |
| `func_800900C0.c` | 47 of 144 instructions (was 68) | structure matches (tail-merged `initializeTransformNode` call, hoisted constants, the `+8` and `+0x166` second pointers). A 0x40-byte address-taken local (`u8 spill[0x40]`, referenced once) fixes the frame size (the ROM has a 64-byte hole between the argument area and the saved registers). Still open: register numbering (ROM keeps `arg0` in `s5`, ours in `s8`; the permuter reached 19 only with mangled C) |

`tools/permute_run.py` tried `func_80012CD0` for 20,700 variants without a match (best 7 -> 6, mangled C).
| `func_80098804.c` | 71 of 271 instructions (permuter reached 14 only with unusable mangled C) | structure is right: 12 display-list commands (the four 0x0218000x words are the rect vertices, doubles 7.0/4.0/35.0/21.0), then three `func_800B600C` texture draws. `p` and the copy `q` must be address-taken (stored at sp+0x28/0x30); `fy`/`top` are computed between `func_8002AD68` and `func_800B600C`; one extra address-taken pad local makes `q` land at sp+0x30. Open: the original has all of s0-s7 busy so `&q` is recomputed (`addiu a0,sp,48`) at each use, while ours keeps it in a register; keeping `x-8`/`x+8` in their own variables (as the ROM does) makes ours need s8. Register numbering of out/id/arg2/x/color (ROM: s6/s4/s7/s3/s5) also differs |
| `func_80018140.c` | 124 raw (31 ignoring register names) of 251 instructions | structure decoded: allocates the output record, picks a parameter table from the descriptor kind (jump table: 1 -> D_80036F60, 2 -> D_80036FC8, 5 -> D_80037050, 3 -> D_80037078, 4 -> D_800370A0, 6 -> desc->f20, else D_800370C8; cases must be written in that order 1,2,5,3,4,6), then fills the regions. Open: the ROM uses 7 saved registers and shares `s0` between the `out` argument and the region pointer, mine uses 8; the ROM's table index is an `int` masked with `(u16)` at each use; the float conversion of `tbl[idx]` is a fresh `lwc1` in the ROM. `initAudioStream` is the same code behind a registration call. Needs `own` .rodata at 0x8003B430 when it matches |
