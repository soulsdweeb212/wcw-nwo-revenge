# Near-miss drafts

C that is close to a function's original code but does not match it byte for byte. These are not built (`build.py` only
looks in `src/`); they are kept so the work isn't lost. Move one to `src/<segment>/<name>.c` only when `build.py` says
*identical*. `STATUS.md` lists every function that is still assembly (`python3 tools/list_nonmatching.py --md`).

| file | how far off | what is known |
|---|---|---|
| `func_80012CD0.c` | 8 of 242 instructions | in the `mode >= 11` branch the original computes `x-px`, `y-py`, `z-pz` in that order, ours loads `pz` earlier; `0.087890625` must be a literal so it is hoisted into `fs0`; `Ent` is the 0x5C-byte record from `func_80012364.c` | Update: the earlier attempt in `progress/best` scores 7 and a permuter run reached 3 (mangled C).
| `func_800900C0.c` | 47 of 144 instructions (this draft); the earlier attempt in `progress/best` scores 6 | the earlier attempt keeps the display-list constants in locals (`c1 = 0xE7000000`, `c2 = 0xFA000000`, `c3 = 0xDE000000`, `c4 = (s32)sceneNodeCallback5C50 - 0x800000C0`, `c5 = 0xDF000000`, `z = 0.0f`), has a `u8 pad[0x34]` local and a `s16 m` temporary, and walks both pools with plain `u8 *` and offsets. Only the temporary used for the two callback stores differs (the ROM uses `v0`, it gets `v1`). A permuter run from it reached 0 but only with mangled C (a `volatile` temporary and dozens of dummies), so it is not kept |

`tools/permute_run.py` tried `func_80012CD0` for 20,700 variants without a match (best 7 -> 6, mangled C).
