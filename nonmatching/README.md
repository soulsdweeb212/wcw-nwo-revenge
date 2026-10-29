# Near-miss drafts

C that is close to a function's original code but does not match it byte for byte. These are not built (`build.py` only
looks in `src/`); they are kept so the work isn't lost. Move one to `src/<segment>/<name>.c` only when `build.py` says
*identical*. `STATUS.md` lists every function that is still assembly (`python3 tools/list_nonmatching.py --md`).

| file | how far off | what is known |
|---|---|---|
| `func_80012CD0.c` | 8 of 242 instructions | in the `mode >= 11` branch the original computes `x-px`, `y-py`, `z-pz` in that order, ours loads `pz` earlier; `0.087890625` must be a literal so it is hoisted into `fs0`; `Ent` is the 0x5C-byte record from `func_80012364.c` |
| `func_800900C0.c` | 68 of 144 instructions | structure matches (tail-merged `initializeTransformNode` call, hoisted constants, the `+8` and `+0x166` second pointers); register numbering and the 0x40-byte spill area differ (the original keeps `arg0` in `s5`, ours in `s8`) |

`tools/permute_run.py` tried `func_80012CD0` for 20,700 variants without a match (best 7 -> 6, mangled C).
