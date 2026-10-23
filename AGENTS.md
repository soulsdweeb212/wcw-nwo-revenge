# Working on this decompilation

- Goal: C that the original compiler turns into exactly the original bytes. `python3 build.py` must end with
  "identical".
- Pick a function from `asm/nonmatchings/`, write it as `src/<segment>/<name>.c` (one function, `#include
  "common.h"` first), add an entry `{"kind": "c", "src": ..., "obj": ...}` to `build.json` objects and point the
  function's line in `game.ld` at the new object.
- Shared types and prototypes go in `include/common.h`. Never edit `baserom*`, `asm/` or the addresses in
  `game.ld` to force a match.
