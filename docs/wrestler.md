# The wrestler record

Everything the match engine knows about a wrestler during a match lives in one 0x3B0-byte record. There are four,
one per player slot, in an array at `D_800F9D10` (0x800F9D10..0x800FABD0, overlay 2's BSS). This page explains what is
in a record: where the wrestler is, what they are doing (including grapples), how the game knows whether they are in
the ring, on the apron or outside, and their health and spirit. [`include/wrestler.h`](../include/wrestler.h) is the
record as a C struct. Its 84 field offsets and its size are checked with the game's compiler. common.h includes it,
and the matched C reaches the records through it (`D_800FAF5C->x`, `D_800F9D10[i].state`). A handful of accesses stay
as casts because only that form compiles to the original code: a 32-bit read across `moveMode` (+0x28) or
`pairSignals` (+0x360), the flags copied a word at a time (`WrFlagWords`), and two stores the compiler would otherwise
reorder.

Status (2026-11-06): five mapping passes (layout, position, state, ring, vitals) each had their claims re-checked in
the code by an independent verifier. Nothing was refuted; about 50 claims were corrected, and the corrections are
folded in here. **Confidence** in the tables: *proven* = the code shows it; *likely* = consistent everywhere it is
used, but the exact gameplay meaning is inferred; *guess* = plausible, not shown. Nothing has been checked in a
running game yet.

## Contents

- [Where the records are and how they are updated](#where-the-records-are-and-how-they-are-updated)
- [Coordinates](#coordinates)
- [In the ring, on the apron, outside](#in-the-ring-on-the-apron-outside)
- [States and grapples](#states-and-grapples)
- [Health, spirit, special, counts](#health-spirit-special-counts)
- [Field map](#field-map)
- [The flag word (+0x20)](#the-flag-word-0x20)
- [Function names that are wrong](#function-names-that-are-wrong)
- [Open questions](#open-questions)

## Where the records are and how they are updated

- **Four slots, no referee.** Slot *i* is player *i*, and `+0x00` holds *i*. A slot is empty when `characterId`
  (`+0x02`) is -1, for example the hidden run-in slots of a singles match. Every loop over the records runs `i < 4`, and
  the global right after the array (`D_800FABD0`) is an AI pointer, so there is no fifth record. The referee is not a
  wrestler: the pin count and count-out are rule code (globals, below) plus what is drawn on screen.
- **Match setup.** `resetMatchState` and `loadPlayerResourceSet` copy each slot's character and controller port and
  load three blocks per wrestler from ROM:
  - a 64-byte character profile, pointed to by `+0x364`: health regeneration, speed tier, offence and defence per body
    part, and ability bits;
  - the wrestler's move table, used through `+0x384`/`+0x386`;
  - a third block, not traced.

  Then `func_800BA770` fills the record: spirit 50, Y 90, links cleared, and health plus body parts carried over from
  the previous match. `func_800BAC30` places the wrestlers by match type, sets CPU control, the team bit, the opponent
  (`+0x353`) and the partner (`+0x355`), and turns everyone to face their opponent.
- **Every tick (1/30 s).** `func_800BBA00` runs the match:
  1. `copyPartCoordinateFields` copies the skeleton's joint positions into the records.
  2. Each wrestler is updated by `func_800BBFD8`:
     - it reads the controller of its port, or, when flag `0x4` (CPU) is set, runs the AI (`startEntityAction`, table
       `D_800E3660`), which presses virtual buttons;
     - it calls `func_8009D8D0`, which sets the role pointers below, clears the per-tick flags, updates side, spirit and
       health timers, and calls the handler for the current state from the 146-entry table `D_800E2FF0[state]`.

     A wrestler leading a paired move (flag `0x40000000`) is updated first, then the wrestlers attached to it, so both
     animations stay in step. A record whose state changed during someone else's update (flag `0x10000000`) is run
     again in a third pass.
  3. `func_800D43DC` advances each animation and poses the skeleton.

  CPU and human wrestlers go through exactly the same state machine; only the source of the buttons differs.
- **Role pointers.** These are set before each wrestler's update, so handler code rarely indexes the array itself:

| global | is | from |
| :-- | :-- | :-- |
| `D_800FAF5C` (= `D_800EB408`) | the wrestler being updated | `D_800FADB8` = its slot |
| `D_800F9B00` (= `D_800EB40C`) | its current opponent | slot `+0x353`, also in `D_800FABE4` |
| `D_800FABE0` (= `D_800EB410`) | its tag partner (itself if none) | `+0x355` |
| `D_800F9B64` (= `D_800EB414`) | whoever is holding or attacking it | `+0x351` |
| `D_800FAF7C` (= `D_800EB418`) | the second attacker of a double team | `+0x352` |
| `D_800FAF58`, `D_800F9B60`, `D_800FAF80`, `D_800FADDC` | AI only: self, opponent, partner, partner's opponent | set by `startEntityAction` |

## Coordinates

A map of the arena in world units, seen from above (not to scale), Y up:

```
            +Z (entrance aisle: |x| <= 174, z 280..1250; walk-ins start at z 1150)
                              ^
   floor / barricade at 528   |
   +---------------------------------------------+
   |   ring platform edge at 280                 |
   |   +---------------------------------+       |
   |   | apron standing line 265          |      |
   |   |  +---------------------------+   |      |
   |   |  | ropes at 230               |  |      |
   |   |  |  corner posts (+-230,+-230)|  |      |
   |   |  |          (0,0)             |  | ---> +X
   |   |  |   start corners +-180      |  |      |
   |   |  +---------------------------+   |      |
   |   +---------------------------------+       |
   +---------------------------------------------+
```

- **Root position `x, y, z` (`+0x4C`, `+0x50`, `+0x54`)**, f32 (*proven*). This is where the wrestler is. Y is 90 on
  the mat and on the apron and 0 on the floor; only `func_800D4B10` sets it, from the zone. Dives use a vertical speed,
  and the drop-in entrance starts at Y 1500.
- **Heading `+0x58`**, s32 (*proven*). 0x1000 = a full turn, kept in -0x800..0x7FF. Heading 0 faces +Z and 0x400 faces
  +X; forward = (sin h, cos h). The normal turn rate is 0x155 per tick; flag `0x100000000` keeps turning the wrestler
  toward its opponent.
- **Joint positions** (*proven* for the arrays, *likely* for the joint names). There are two 23-entry arrays of
  {x,y,z,pad}:
  - `jointA` at `+0x5C`;
  - `jointB` at `+0x1CC`, the far end of each bone, used by the limb-strike hit test.

  Only joints 1..19 are filled, copied each tick from the real skeleton in main (`D_80070C40`, 4 x 23 bones of 0x7C
  bytes). From the skeleton's parent table:

  | joints | body part |
  | :-- | :-- |
  | 1 | pelvis |
  | 2..5 | spine up to the head (5) |
  | 7/6/8 | right hip, knee, foot |
  | 14/13/15 | left hip, knee, foot |
  | 12/11/9/10 | right shoulder, elbow, wrist, hand |
  | 19/16/17/18 | left shoulder, elbow, wrist, hand |

  **`jointA[1]` (`+0x6C`, the pelvis) is "where the body is"** for most distance, bearing and hit tests. The root is the
  animation anchor. Joints 9, 17, 18 and 19 are the attack hit points.
- **Moving.** Scripted movement adds `moveDelta` (`+0x33C`) and `turnPerTick` (`+0x348`) each tick.
  `translateEntityXZ` shifts the root and every cached joint together, so collision stays valid until the next pose.
  The walking speed table `D_800E3F64` has four speed tiers (from the profile): 3.75, 4.5, 5.25 and 6.0 units per tick
  forward. Running is twice that, and diagonals use 0.7071. Run-to-opponent moves follow a quadratic spline
  (`D_800FACF8`, parameter `D_800F97F0`).
- **Spacing.** Standing wrestlers are kept 100 units apart, pelvis to pelvis, and a downed wrestler's root has an
  ellipse 50 units larger (`func_800D2758`).
- **For a port.** Game X is negated when the model is drawn, and the model is rotated by -(heading + 0x800). Check the
  handedness in an emulator before writing a camera.

## In the ring, on the apron, outside

**Zone flags** (`flags` bits, *proven*):

| bit | zone | Y |
| :-- | :-- | :-- |
| `0x40` | inside the ropes | 90 |
| `0x80` | on the apron | 90 |
| `0x100` | the arena floor, including the aisle | 0 |

- Normally exactly one is set. `0xC0` appears while climbing in from the apron and `0x180` while diving off to the
  floor.
- Most interactions require `self.flags & other.flags & 0x140`, meaning both in the ring or both on the floor.
- An animation can change the zone. Its metadata byte `endZone` (`+0x36E`: 1 ring, 2 floor, 3 apron) is applied when
  the animation reaches its cancel frame (`updateEntityModeFlags`).
- The explicit moves between zones are states:
  - `0x60`: ring to apron, or apron to floor;
  - `0x61`: floor to apron, or apron to ring;
  - `0x62`: knocked out of the ring, randomly to the floor or the apron;
  - `0x63`..`0x69`: dives and springboards between zones.

**Side and corner:**

- **`ringSide` (`+0x3C`)**, *proven*: the side the root is on, recomputed every tick: 0 = +Z, 1 = +X, 2 = -Z, 3 = -X.
  The ring is cut along its diagonals into four triangles. On the apron it is the side you stand on; on the floor, the
  side of the ring you are next to.
- **`dirIndex` (`+0x3E`)**: a side or corner index for the current action, so its meaning depends on the state. It
  can be:
  - the rope side you run into or walk along;
  - the corner post you climb (from `findBoundaryQuadrant`, -1 = none nearby);
  - the direction you approach a downed opponent from.

**Boundaries.** `func_800D2CAC` clamps a wrestler to one of 13 boxes in `D_800E3D30`, chosen by zone and side. Each box
is {maxZ, maxX, minZ, minX}:

| box | area | limits |
| :-- | :-- | :-- |
| 0 | inside the ropes | ±230 |
| 3..6 | floor beside each side of the ring | 280 .. 528 out, ±528 along |
| 7..10 | apron line of each side | 265, ±178 along |
| 11 | entrance aisle | \|x\| ≤ 174, z 280..1250 |
| 12 | aisle mouth | \|x\| ≤ 528, z 280..1250 |
| 1, 2 | whole arena, ring platform | never selected |

- In the ring and on the floor, the box is applied to the centre of the joints' bounding box, padded by ±30. On the
  apron it is applied to the root, and `snapEntityToRingBoundary` puts the root back on the 265 line facing the ring.
- The function sets a bit for each wall touched. Those bits feed the "against the ropes / barricade / aisle rail"
  reactions.

**Other ring constants** (all from `.rodata` / `.data`, read from the ROM):

| what | value |
| :-- | :-- |
| corner posts (`D_800E3C50`) | (230,230), (230,-230), (-230,-230), (-230,230) |
| inner corner points | ±205 |
| standing in a corner | 73.5 units from the post |
| turnbuckle climb positions | 229.15 inside, 230.85 from the apron |
| "at the ropes" test | beyond ±150 with your back to that side |
| leave through the ropes | in-ring band 185..200 |
| roll back in | floor band 280..335 |
| Irish whip impact, ropes | beyond 130, stops at 190 |
| Irish whip impact, turnbuckle | beyond 150 on both axes, stops at (190,190) |
| Irish whip impact, barricade | 488 |
| Irish whip impact, aisle rail | 134 |
| Irish whip into the apron from the floor | stops at 320 |
| headings per side, facing out (`D_800E3C90`) | {0, 0x400, 0x800, -0x400} |
| headings per side, facing in (`D_800E3CA0`) | {0x800, -0x400, 0, 0x400} |

The -X barricade whip threshold is -380 where the other sides use 428, perhaps because something stands on that side
(not checked).

**Count-out** (globals, not record fields):

- `D_800FACE8` counts down the counts that are left. It starts at 10 or 20 (`D_800E3978`, set by the ring-out rule
  option `D_8007E8C0+0x66C`); 0 = counted out. This is the GameShark "infinite time out of ring" address.
- It ticks every 30 ticks per unit: 2 units per count while 6 or more remain, 3 while 3..5 remain, 4 for the last two.
  So the count speeds up at the end.
- It pauses during cut-scene states (`func_800A93C0`).
- Only legal wrestlers (`0x200`) on the floor are counted.
- Rule bit `D_8007F0A0 & 4` turns the count off and walks floor wrestlers back to the ring. `& 0x400` (likely the
  battle-royal over-the-top rule) freezes or eliminates wrestlers who reach the floor, and makes whips not rebound off
  the ropes.

## States and grapples

- **`state` (`+0x0A`)** picks the handler from the 146-entry table `D_800E2FF0`.
- **`step` (`+0x0C`)** is the step inside it; `animFramesLeft` (`+0x04`) reaching 0 or 1 usually ends a step.
- **State changes** go through helpers (`func_800A6BE0`/`6C48`/`6CDC`/`6D80`). They set the new state and clear `step`,
  `stepFlags` and `pairSignals`; one variant also unlinks a pair, and some callers write `+0x0A` directly.
- **Choosing the next state.** Most moves end through `beginEntityActionA8D8C`, which looks at the end pose of the
  animation (`anim.endPose` → `pose` `+0x42`):

  | end pose | next state |
  | :-- | :-- |
  | 0/1 | `0x2B` settle |
  | 2 | `0x2E` dazed |
  | 3 | `0x2D` on the ropes |
  | 4/5 | `1` standing |
  | 7..32 | `0x2C` lying on the mat (odd and even toggle flag `0x200000`, the lying orientation) |

**Identified states.** H = high confidence, M = medium, G = guess. Pairs are attacker / victim.

| id | state | conf. |
| :-- | :-- | :-- |
| 00 | pre-match, waiting to start | H |
| 01 | standing, under control (all button actions start here) | H |
| 02 | apron: moving toward a corner post | G |
| 03 | walking | H |
| 04 | running | M |
| 05 | bumped into another wrestler (both walking; or the other blocks) | H |
| 06..08, 1B..1F, 20..23, 25..27 | strikes and attacks (hits resolve in `func_800C3A78`) | M |
| 09 | block pressed on the apron | G |
| 0A | climbing / standing on the turnbuckle | H |
| 0B / 0C | Irish whip: whipper / whipped (0C can reverse) | H |
| 0D/0E, 0F/10 | whip-like pairs from a grapple across the ropes | M |
| 14 | running into the ropes and rebounding | M |
| 17 | taunt (turns full spirit into SPECIAL) | H |
| 19 | dodge or leapfrog a running opponent | M |
| 24, 55, 56 | strike on a downed opponent (stomp) | M |
| 28 | hit reaction (`+0x30` describes the hit) | H |
| 29 / 2A | knocked out / dazed (KO needs health < 25 and the KO match option) | M |
| 2B | settling after a move | H |
| 2C | lying on the mat | H |
| 2D | leaning on the ropes or in the corner | G |
| 2E | dazed | G |
| 2F | stagger | H |
| 30/31 | running attack on a downed opponent | M |
| 32/33 | picking up a downed opponent | M |
| 38 / 39 | pin (cover after a move): pinner / pinned | H |
| 3A / 3B | ground grapple: attacker / downed victim | H |
| 3C / 3D | submission hold: holder / held | H |
| 3E / 3F | pin that is a move from the move list (victim takes damage every 31 ticks) | H |
| 40 | blocking (pressed in its first 3 ticks = counter window) | H |
| 41 | blocked a hit | H |
| 43 | getting up from the mat | M |
| 44 | grapple: reaching | H |
| 45 / 46 | grapple: tied up | H |
| 47 / 48 | lock-up between characters with the lock-up ability | G |
| 49 / 4A | grapple move: performing / taking | H |
| 58..5E | counters to strikes | M |
| 5F | grapple dodged | M |
| 60, 61, 62, 70, 82 | moving between ring, apron and floor | H |
| 63..69, 6B..6F | dives and springboards (6B..6F from the top rope, can land in a pin) | M |
| 72/73, 79/7A, 87/88, 7B/7C, 8B/8C, 4F/50 | grapple variants: on the apron, floor to ring, floor to apron, on the turnbuckle, two flag-driven variants | M |
| 71, 76..78 | double team (76/77 attackers, 78 victim) | M |
| 7F..81 | tag: exchange, partner reaching from the apron | M |
| 89 / 8A | step over a downed opponent (standing / walking) | G |
| 8F | run-in: a new wrestler entering (from the rafters, Y 1500, or the aisle, z 1150) | H |

The rest (02, 09, 11..13, 15, 16, 18, 1A, 42, 4B..54, 76..7C, 83..91 in part) are unidentified or only guessed; see the
open questions.

**How a grapple works.**

1. Pressing grapple while standing (state 1) on a downed opponent starts a ground grapple (`3A`/`3B`). Otherwise the
   wrestler reaches (`44`); holding the button 8 or more ticks makes it a strong grapple (`grappleCtx |= 2`).
2. On contact, `selectPairedActionCD3F8` picks the pair: normally `45`/`46` (tied up), or one of the variants for the
   apron, floor, turnbuckle and lock-up.
3. **Tied up.** The grappler's `stateTimer` (`+0x16`) runs down: 60 ticks weak, 90 strong, 30 if the opponent has
   SPECIAL. When it runs out, the two break apart.
4. **Choosing a move.** A or B plus a direction picks the move from `D_800E3C20[strong][button][direction]`
   (`D_800E3C38` from behind). Then the pair becomes `49`/`4A` (performing / taking).
5. **Reversals.** The victim can reverse: a roll in `func_800D0700` sets flag `0x2000000` (and `0x4000000`, so
   mashing doesn't help). The roles then swap.
6. **Linking.** `beginPairedEntityActions(a, …, b, …)` links the two:
   - **a**: flag `0x40000000` (leader), `attached[0]` = b, `heldById` = -1;
   - **b**: `heldById` = a;
   - **both**: `opponentId` = each other.

   During the grapple the two sides signal each other through `pairSignals` (`+0x360`): 1 break, 2 choosing a move,
   4 reversed or rope break, 8 repositioning.

**Testing "is this wrestler in a grapple?"**:

1. **By state (most reliable).** `state` is one of `44`..`4A`, `3A`/`3B`, `0B`/`0C`, `72`/`73`, `79`/`7A`, `7B`/`7C`,
   `87`/`88`, `8B`/`8C`, `4F`/`50` or `76`..`78`.
2. **By link.** Either it leads, with `flags & 0x40000000` and `attached[0] != -1`, or some other record leads with
   this wrestler in its `attached[]` (`heldById` names that leader).
3. **Holds and pins.** `flags & 0x200000000000` = applying a hold or pin; `flags & 0x400000000000` = held or pinned.
   Both are re-set every tick by the handlers.

## Health, spirit, special, counts

**Health (`+0x10`), *proven*.** Health is hidden: the HUD shows only spirit.

- It is 0..255, starts at 255 or is carried over from the last match, and damage subtracts the full total.
- `healthMax` (`+0x12`) falls by a quarter of each hit's damage, but never below 128; health regenerates up to it,
  every 60 ticks by the profile's rate.
- `updateEntityHealthLevel` sorts health into three levels: ≥ 128 good, ≥ 64 hurt, below that bad. The level picks the
  get-up animations and slows kick-outs and get-ups.
- While SPECIAL is active the game reads `healthMax` instead of health.

**Body parts (`+0x34C`, 5 bytes), *likely*.**

- Each part starts at 50 and only decreases; at 0 the part is injured and limb submissions can win.
- Each move names the part it hits (`move.targetPart`) and the damage to each part (`move.partDamage`).
- Part 3 sets the walking speed, so it is probably the legs; parts 0..2 are not identified.
- Parts below 25 give hurt idle animations.

**Spirit (`+0x14`), *proven*.** The meter on screen, 0..100. GameShark `0x800F9D25` is its low byte.

- It starts at 50, rises and falls by the move's `spiritGainSelf` / `spiritDeltaTarget`, drifts back toward 50 every
  120 ticks, and drains while you are outside and your opponent is not.
- At 100, flag `0x40000` is set; a taunt (state `17`) then turns it into **SPECIAL**, flag `0x80000`. GameShark
  `+0x25 = 8` writes this byte.
- SPECIAL lasts 600 ticks, shortened by 60 per hit taken, and gives ×1.2 damage. It is needed for the
  no-kick-out pin (state `3F`, about a 50% roll).
- Spirit 0 sets `0x20000` for 300 ticks.
- Flag `0x1` caps spirit at 99, so that character can never get SPECIAL.

**Pins.**

- The pinned wrestler's `escapeTimer` (`+0x18`) is the kick-out countdown, at least 15 ticks; mashing lowers it. Being
  hurt, low health and earlier kick-outs (`D_800F9B80`) make it longer.
- The count itself is a clock per wrestler, `D_800FAF60` (seconds field = count 0..3). `D_800EB46F` is the wrestler
  being counted and `D_800EB46E` the count shown.
- Reaching the ropes sets the pinner's `pairSignals |= 4` (rope break), if the match options allow rope breaks.
- GameShark "no count once downed" (`+0x14 = 0x64` as a 16-bit write) does not set a "no count" switch. It makes spirit
  huge: the victim always kicks out at the 15-tick floor, before the first count at 30 ticks. It also makes that
  wrestler hit enormously hard.

**Submissions.** The hold (`3C`/`3D`) does damage every 31 ticks while the victim mashes `escapeTimer` down. The
give-up chance per roll depends on health (`D_800E3860`): 12.5% at ≥ 196, 25% at ≥ 128, 50% at ≥ 64, otherwise
certain. Results go into `pairSignals`: 2 escaped, 4 rope break, 8 gave up.

**Match globals:**

- clock `D_800FAF84` {min, sec, ticks}, with time limits {none, 5, 10, 15, 30, 60} minutes;
- result `D_8007E848`: pin, submission, KO, count-out, time up, draw;
- the last hit's size per wrestler (`D_800FAF50`), which sets how hard they stagger.

## Field map

Offsets in hex. The names are the ones in `include/wrestler.h`.

| off | type | name | meaning | conf. |
| :-- | :-- | :-- | :-- | :-- |
| 000 | s8 | id | own slot 0..3 | proven |
| 002 | s16 | characterId | wrestler id (0xBNN: bank bits 8..11, index+1 in the low byte); -1 = slot empty | proven |
| 004 | s16 | animFramesLeft | frames left in the current animation | proven |
| 006 | s16 | animFrame | frames since the animation started | proven |
| 008 | s16 | animId | animation index | proven |
| 00A | s16 | state | action state (table above) | proven |
| 00C | s16 | step | step inside the state | proven |
| 00E | u16 | stepFlags | per-state scratch bits | likely |
| 010 | s16 | health | hidden health 0..255 | proven |
| 012 | s16 | healthMax | recoverable ceiling, ≥ 128 | proven |
| 014 | s16 | spirit | spirit 0..100 | proven |
| 016 | s16 | stateTimer | per-state timer (tie-up length, block age ...) | proven |
| 018 | s16 | escapeTimer | kick-out / submission escape / stay-down countdown | proven |
| 020 | u64 | flags | see below | proven |
| 028 | u16 | moveMode | locomotion and whip bits: 0x20 running, 0x2 whipped, 0x40 strong whip, 0x8 rope run | likely |
| 02C | u32 | grappleCtx | grapple context: 1 SPECIAL available, 2 strong, 0x40 from behind, 0x80 caught off the ropes, 0x100 target on apron, 0x200 self on apron, 0x300 across the ropes, 0x4000/0x8000 left/right double-teamer, 0x10000/0x20000 floor-to-apron/ring pair, 0x200000 special-move path | likely |
| 030 | u32 | hitInfo | descriptor of the incoming hit that picks the reaction; also the sub-mode of state 0x28 | likely |
| 035 | u8 | koFlags | 1 KO, 2 stun, 4 was running off the ropes, 8 knocked flat, 0x40 hit by a SPECIAL ... | likely |
| 037 | u8 | frameStatus | bit 0 = rebounding off the ropes this tick | proven |
| 03A | s16 | counterKind | kind of opponent strike being countered / move variant | likely |
| 03C | s16 | ringSide | side of the ring 0..3 | proven |
| 03E | s16 | dirIndex | side or corner of the current action | likely |
| 040 | s16 | knockdowns | knockdowns since last standing free; each cuts down time by 80 | likely |
| 042 | u8 | pose | end pose of the last animation | proven |
| 043 | u8 | comboHits | consecutive hits taken, max 4 | likely |
| 044 | u16 | lastMoveTakenId | last move received (the finisher, saved at match end) | likely |
| 048 | u16 | nextCharacterId | next entrant for the slot (battle royal) | proven |
| 04C | f32×3 | x, y, z | root position | proven |
| 058 | s32 | heading | facing, 0x1000 per turn | proven |
| 05C | 23×16 | jointA | joint positions; `jointA[1]` = pelvis | proven |
| 1CC | 23×16 | jointB | far end of each bone | likely |
| 33C | f32×3 | moveDelta | per-tick displacement | proven |
| 348 | s32 | turnPerTick | per-tick heading change | proven |
| 34C | s8×5 | bodyPart | body part condition | likely |
| 351 | s8 | heldById | who holds or attacks me; also the last attacker (credited with the fall) | proven |
| 352 | s8 | secondAttackerId | second attacker of a double team | proven |
| 353 | s8 | opponentId | current opponent | proven |
| 354 | s8 | steppedOverId | downed wrestler last stepped over | likely |
| 355 | s8 | partnerId | tag partner (own id if none) | proven |
| 358 | u64 | partnerFlags | partner's flags at the start of the tick | proven |
| 360 | u16 | pairSignals | handshake between the two sides of a pair or hold | proven |
| 362 | s8×2 | attached | records driven by my move | proven |
| 364 | ptr | profile | 64-byte character profile | proven |
| 368 | struct | anim | animation metadata: turn, length, end zone, end pose, hit / busy / active windows, cancel frame | proven |
| 384 | s8 | moveOwnerId | whose move table | proven |
| 386 | s16 | moveId | index in that table | proven |
| 388 | s16 | moveStatKind | statistics category of the current move, 0..0x56 (0x57 = not counted); row of the per-player 87-row counter table at `D_8007EF30 + 0x1B0`, set and counted by `func_800A7F6C`, second word counted by `func_800A837C` | proven |
| 38C | struct | move | current move: power, spirit changes, KO/stun bits, body parts, joints, range, flags (`+0x3AC`) | proven / likely |

Unused or unknown bytes: `001`, `01A..01F`, `02A`, `034`, `036`, `038`, `039`, `046`, `04A`, `356`, `38A`, and parts of
`anim` and `move`.

## The flag word (+0x20)

Bits checked in the code (the ones with a `WR_FLAG_` name in the header):

| bit | meaning |
| :-- | :-- |
| `0x4` | CPU-controlled; set from the match settings (raw Z can toggle it when the options allow) |
| `0x40` / `0x80` / `0x100` | in the ring / on the apron / on the floor |
| `0x200` | legal man / active participant |
| `0x20000` | spirit empty |
| `0x40000` | spirit full: taunt for SPECIAL |
| `0x80000` | SPECIAL active |
| `0x10000000` | state changed: run the handler again this tick |
| `0x20000000` | updated this tick |
| `0x40000000` | leads a paired move |
| `0x100000000` | keep facing the opponent |
| `0x200000000` | team / side bit |

Likely, from consistent use:

| bit | meaning |
| :-- | :-- |
| `0x1` | cannot grapple or block, spirit capped at 99; in run-in matches, ringside companions start on the floor |
| `0x2` | parked run-in |
| `0x8` | takes double damage |
| `0x400` | pin count running |
| `0x800` | eliminated over the top |
| `0x1000` | gave up |
| `0x2000` | KO loss |
| `0x4000` / `0x8000` | winner / loser |
| `0x100000` | walking |
| `0x200000` | lying orientation (face up or down; which is which is not known) |
| `0x400000` | down on the mat / vulnerable; re-set every tick by the down states, and required for ground grapples, stomps and stepping over |
| `0x2000000` / `0x4000000` | reversal accepted / reversal attempt used |
| `0x1000000000` | busy |
| `0x200000000000` | applying a hold or pin |
| `0x400000000000` | held or pinned |
| `0x4000000000000` | injured (saved after the match) |
| `0x1000000000000000` | took damage in the last 30 ticks |
| `0x2000000000000000` | Z held |

`func_8009D8D0` clears the per-tick bits (`0x2C407C7110500000`) at the start of every update; `0x200000204` survives a
match reset.

## Function names that are wrong

Earlier passes named these from partial reads. The mapping shows what they really do; they should be renamed when the
overlay functions are named:

| function | what it does |
| :-- | :-- |
| `startEntityGrapple` | walking collision: two wrestlers bump (state 5), or a blocker / rope-runner reacts |
| `updateEntityStunTimer`, `addEntityHealthDelta` | both act on spirit (`+0x14`) and its timers, not stun or health |
| `updateEntityBoundaryFlags` | picks which way to move along a rope or apron side (states 0xD and 15), from the d-pad and who is in the way |
| `updateRingLeapAction` | approach offsets around an opponent by the attacker's direction relative to the opponent's facing; not the ring |
| `updateEntityGrabActionState` | strike on a downed opponent (states 0x24/0x55/0x56) |
| `snapEntityToRingBoundary` | the apron snap: root onto the 265 line, facing the ring; it does not move the joints |

## Open questions

- **States** 02, 09, 11..13, 15, 16, 18, 1A, 42, 4B..54, 71..7C and 83..91 are unidentified or only guessed.
- **Flag `0x200000`**: which value is face-up and which face-down. It needs the pose-to-animation table `D_800E3262`
  checked against the animations.
- **Body parts 0..2 and 4**: which part each is.
- **Bytes and words without a known meaning**: `+0x28`'s other bits, `+0x30` beyond hit reactions, `+0x34`, `+0x36`,
  `+0x38`, `+0x3A`, and most of the move bytes 0x390..0x3A9.
- **Match-type bits**: `D_8007E280` bit 0x100 is probably singles with run-ins, and 0x400 probably battle royal.
  Which menu options set them was not checked.
- **The third resource block** per wrestler (`D_8007C438+0x180+i*0x600`) and the animation metadata resource 0x20F are
  not decoded.
- **Handedness on screen** (game X is negated for drawing) and the 30 Hz tick should be confirmed in a running game.
  An emulator with a debugger would also settle most of the guesses above in minutes: set a breakpoint on a state
  change and watch what the wrestler does.
