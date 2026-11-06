# Nintendo SDK code in the main segment

The main segment (`src/main/`, 0x80000450..0x8002CA30, 676 functions) holds the game engine and, linked in after it, the
Nintendo 64 SDK libraries the game was built with. This page lists every SDK function identified there (2026-11-05):
380 of them are named now, 4 are SDK-looking but unnamed. The rest of the segment is game code. The SDK's data globals that
these functions use (103 of them) are named too: see [Data](#data) at the end. The two overlays hold no SDK code at all;
they only call into main's (see [The overlays](#the-overlays)).

Each renamed file starts (after its `@header`) with a one-line `/* SDK: ... */` comment saying where it comes from; the 35
hand-written assembly routines carry a longer explanation instead. The table below has the evidence for each one.

## How they were identified

- `tools/ulsweep.py` compiles every C file of the decomp community's reconstructed
  libultra source, [decompals/ultralib](https://github.com/decompals/ultralib), for versions 2.0I/J/K at -O2 and -O3 with
  this game's compiler (KMC GCC 2.7.2), and scores every resulting function against every main function of a similar size
  (instructions compared with addresses masked). About 180 scored 0 or close.
- Then, per address range, each function was checked: `ul.py` rebuilt the candidate from its source and diffed it against
  the ROM, ties between functions with identical code were broken by their real operands (which globals and registers
  they touch) and by the call graph, and "modified" functions were proved by editing the SDK source until it compiled to
  the ROM's bytes. A second, independent pass tried to refute every row; it changed 21 rows' wording or kind and one name.
- n_audio and libmus are not in ultralib. Their sources come from the
  [n64sdkmod](https://github.com/ModernN64SDKArchives/n64sdkmod) archive (libnaudio, libmus 3.14, the n64-demos audio
  manager), scored the same way.

Kinds in the table: **exact** = the SDK source compiles to these bytes (or, for tiny functions, the only reading the
operands and callers allow); **modified** = SDK code with differences, described in the evidence; **asm-identified** =
one of the 35 hand-written assembly routines, identified by reading (see the file's own explanation); **unknown** = looks
like SDK code, no name found.

## Which SDK

- **libultra 2.0I (libgultra_rom, -O3), patched.** The os/gu/libaudio code matches 2.0I only (osSetEventMesg,
  osAiSetNextBuffer, alEnvmixerPull, `_pullSubFrame`, osDestroyThread, the EPI functions and the `__assert` line numbers
  all fail on J). Assertions are compiled in but `__assert` is empty (no -DNDEBUG, but _FINALROM), as in the real 2.0I
  libgultra_rom. The controller pak / Rumble Pak code is the 2.0I_patch release (J-era code with pre-J returns), which
  ultralib cannot build, so 8 of those functions show up as "modified" (each proved by reverting one J change). The VI
  manager and osInitialize carry 2.0J backports.
- **n_audio** (the SDK's nualstl n_audio synthesizer), an early revision older than the archived libnaudio source.
- **libmus** (Software Creations' MusicTools, shipped in the SDK), a pre-3.x release, with an audio manager that is the SDK
  demo `audiomgr.c` adapted for libmus.
- **libaudio** (libultra's own `al*` synthesizer), exact 2.0I. The game links both it and n_audio; n_audio shares its heap
  and list helpers (alHeapInit, alHeapDBAlloc, alLink, alUnlink, alCopy) and `_doModFunc`.
- **The KMC GCC runtime**: the hand-written 64-bit helpers `__divdi3`, `__moddi3`, `__udivdi3`, `__umoddi3`, `__fixsfdi`,
  `__floatdisf` and two internal divide routines.

## Layout

| VRAM | what |
| :-- | :-- |
| 80000450..80013260 | game engine, except the libultra scheduler at 80000AF0..80000E0C (osCreateScheduler, osScAddClient, osScRemoveClient, osScGetCmdQ, `__scMain`), which the game rewrote: its own `rspTaskThread`/`renderTaskThread` replace the SDK's RSP/RDP handling, and those parts of sched.c are not in the ROM |
| 80013260..80017510 | libmus: player API, FIFO, the player, sequence commands (`F*`, named by their slot in the command table D_80036E80), the audio manager |
| 80017510..8001A480 | n_audio |
| 8001A480..8001C5B0 | gu (in libgultra's link order: sqrtf, align, cosf, lookat, mtxutil, mtxcatf, normalize, ortho, perspective, rotaterpy, scale, sinf, translate, position, random) |
| 8001C5B0..8001CEF0 | os: cache routines, messages, threads, `__assert` |
| 8001CEF0..80020A80 | libaudio |
| 80020A80..800255B0 | ai, sp, vi, controller, controller pak, Rumble Pak, cart/drive init, bcopy/bzero |
| 800255B0..800284F4 | pi/vi managers, exception handler, timers, raw SP/SI/PI I/O, access queues, device manager, bcmp |
| 800284F4..80028AB0 | KMC GCC 64-bit runtime |
| 80028AB0..8002BC40 | game code (kanji font, text cache, wrestler names) |
| 8002BC40 | `rspbootTextStart`: RSP boot code and the start of the audio microcode (data, not CPU code) |

## Names that are not the SDK name, and why

- `nw2Sqrtf` (0x8001A480) is libultra's `sqrtf`. GCC expands a call named `sqrtf` inline (a `sqrt.s` plus a fallback call),
  which is what libultra's own callers do in the ROM, while the game's code calls this address directly. So the function
  keeps the name `nw2Sqrtf`, and `sqrtf` is a second symbol for the same address in `build.json`.
- `unusedMuldi3` (0x800284F4) looks like `__muldi3` but nothing calls it and it reads its argument halves in the wrong
  order. Under the name `__muldi3` (or `__udivdi3`, `mul64` ...) KMC's assembler applies its VR4300 multiply fix, a nop
  before each `multu`, and the bytes change.
- Static functions keep their source names, so some names exist twice in the SDK: n_audio's copies of libaudio statics
  take n_audio's own `_n_` prefix (`_n_pullSubFrame`, `_n_getRate` ...), because libaudio's are also linked.
- Game code that only resembles SDK code keeps its name: `func_80007F70` is a transposed copy of `guMtxXFMF`
  (the real one is 0x8001B3EC), and the sweep's other score-0 hits in the game area are game stubs and getters.

## The overlays

The overlays (overlay 1: `code_80090000`, 367 functions; overlay 2: `ovl2_80090000`, `code_8009D7A0`, `code_800BBA00`,
`code_800DE9C0`, 653 functions) contain no Nintendo SDK, libc, libgcc or KMC-runtime code, unmodified or modified (checked
2026-11-05). All the SDK is linked once, into main, and the overlays call it there. How that was established:

- `tools/ulsweep.py` with the overlay segments scored all 1020 overlay functions against all of ultralib (I/J/K, -O2/-O3), and
  a second sweep scored them against the 384 SDK functions of main (which also catches copies and modified versions) and
  against every function of the archived libnaudio, libmus 3.14 and the demo audio manager. No overlay function longer than
  12 instructions comes near any of them; the score-0 hits are 1 to 7 instruction game stubs (empty functions, getters of
  game globals, one-call forwarders) that look like any small SDK function.
- No overlay function touches hardware: none uses mtc0/mfc0/cache/eret/syscall or a 0xA4xxxxxx register address (40 main
  functions do), none calls `__osDisableInt`/`__osRestoreInt`, and the overlays' raw data blobs (ROM 0x72240..0x837A0 and
  0xD5FB0..0xDAC50) contain no code.
- Three independent reviews then tried to find SDK code the sweeps could miss, by idiom (SDK structure offsets, gu
  fixed-point constants, ALHeap/ALLink code, assert line numbers), by other libraries (libgcc 64-bit helpers, KMC libc,
  libm-style math, NuSystem, the Controller Pak / SRAM samples, libleo, HVQM) and by re-reading every near miss and the end
  of each segment. They found none.

What the overlays call in main's SDK (34 functions, all from `code_80090000` unless noted):

- gu and math: `guRandom`, `nw2Sqrtf`, `sinf` and `cosf` (these four also from `ovl2_80090000` and `code_800BBA00`),
  `guPositionF`, `guMtxXFMF`, `guOrthoF` and `guLookAtF` (these two only from `ovl2_80090000`), `__udivdi3`.
- memory and display lists: `bcopy`, `bzero`, `osVirtualToPhysical` (also `ovl2_80090000`), `osInvalDCache`,
  `osWritebackDCache`.
- the save module, 0x800B88E0..0x800BB440: `osPfsInitPak`, `osPfsAllocateFile`, `osPfsFindFile`, `osPfsDeleteFile`,
  `osPfsFreeBlocks`, `osPfsNumFiles`, `osPfsFileState`, `osPfsRepairId`, `osMotorInit`, `osEPiStartDma`, `osRecvMesg`,
  `osCreateMesgQueue`, `osCreateThread`, `osStartThread`, `func_80000A40` (main's SRAM handle setup, see its row below), and the
  internal `__osContRamRead`/`__osContRamWrite` (from `func_800B8994`, which rewrites the first 256 bytes of the pak, a
  test or debug routine). It is game code: it uses the game's company and game codes (0x4538, 0x4E56504A), its own save
  magic (19 97 10 21) and checksum, and the game's heap and lock functions. Its SRAM transfers fill an `OSIoMesg` by hand the
  way Nintendo's SRAM sample does.
- libmus: `MusStop`, `MusHandleSetReverb` (`ovl2_80090000`), `MusHandleSetVolume`.

Not SDK, but not original game code either: `func_800B5AE0`, `func_800B5D20` and `func_800B5E18` in `code_80090000` look
like textbook routines retyped into the game's types: a natural cubic spline (second-derivative table, then binary-search
evaluation) and a continued-fraction arctangent (20 terms) turned into a 4096-unit atan2. The reviewers recognised them as
the spline and atan routines of Haruhiko Okumura's algorithm dictionary (1991). That comparison was made from memory of
the book, not against its source, so the names are left as they are.

## Reproducing the sweep

```
export ULTRALIB=<a decompals/ultralib checkout>; PY=~/.local/share/uv/tools/decompnet/bin/python
bash tools/ulpp.sh io/pimgr.c I > x.c       # preprocess one file for 2.0I
$PY tools/ul.py osCreatePiManager x.c osCreatePiManager   # diff it against the ROM (OPT=-O3 for -O3)
$PY tools/ulsweep.py sweep.json "I J K"     # everything against every main function
$PY tools/ulsweep.py ovl.json "I J K" all   # ... or against the given segments ("all" = every segment)
```

`tools/rename_func.py` did the renames (it updates `symbol_addrs.txt`, `build.json`, file names, every mention in `src/`,
`include/`, the READMEs and `objdiff.json`, and the headers).

## The functions

| VRAM | name | was | library | source | kind | evidence |
| :-- | :-- | :-- | :-- | :-- | :-- | :-- |
| 80000A40 | `func_80000A40` |  | ? |  | unknown | SRAM OSPiHandle init at D_8003DDB8, in the style of Nintendo's SRAM sample. Offsets checked against OSPiHandle: baseAddress (+0xC) != 0xA8000000, so it sets type(+4)=3 DEVICE_TYPE_SRAM, latency(+5)=5, pageSize(+6)=0xD, relDuration(+7)=2, pulse(+8)=0xC, domain(+9)=1, speed(+0x10)=0. Then bzero(transferInfo +0x14, 0x60 = sizeof __OSTranxInfo), osEPiLinkHandle(&h), return &h. No ultralib function matches (osCartRomInit is osCartRomInit at 80021AA0, score 0, and differs). Likely game code copied from the SDK sample. Callers: func_800BB0CC, func_800BB2A0. |
| 80000AF0 | `osCreateScheduler` | `func_80000AF0` | libultra (sched) | sched/sched.c | modified | score 117/142 against stock (I/K/L, -O2/-O3). OSSched layout matches: retraceMsg.type=1 at +0, prenmiMsg.type=4 at +0x20, interruptQ +0x40 with an 8-entry buffer at +0x58, thread +0xB0 with id 4, clientList +0x260, frameCount +0x27C. Callees in SDK order: osCreateMesgQueue, osCreateViManager(0xFE = OS_PRIORITY_VIMGR), osViSetMode(&osViModeTable[mode]) (0x50 stride), osViBlack(1). Then osViSetEvent(q,666,numFields) and osSetEventMesg for PRENMI(14,669), SP(4,667), DP(9,668). The stock order is SP, DP, PRENMI and osViSetEvent last. createThread/osStartThread for __scMain is stock. Only caller: func_800004B8(sc=D_8003DE30, stack D_800400C0, pri 0x78, mode 2 or 0x1E, numFields 1). Game changes: it creates 7 queues; SP and DP events go to their own queues (D_80044130, D_80044168); it starts rspTaskThread and renderTaskThread; it does not zero the audio/gfx lists or curRSP/curRDP; it stores sc in D_80044580. |
| 80000D28 | `osScAddClient` | `func_80000D28` | libultra (sched) | sched/sched.c | exact | score 0 (22/22) for 2.0I/K/L at -O2 and -O3. Real operands: osSetIntMask(1 = OS_IM_NONE) (osSetIntMask, asm-identified), c->msgQ at +4, c->next at +0, sc->clientList at +0x260. Callers: func_80000580 (wrapper on the global sched D_8003DE30) and the audio thread __amMain, which calls osScAddClient(D_80062558, client, queue). D_80062558 is the sched pointer that func_80003120 gets from func_80000610 (= &D_8003DE30). |
| 80000D80 | `osScRemoveClient` | `func_80000D80` | libultra (sched) | sched/sched.c | modified | stock score 27/32. I moved the client = sc->clientList read after osSetIntMask(1) and used client->next; the score is then 22/32 at -O2 and -O3. What is left is register allocation and loop rotation (the game C is a do-while). Same unlink of sc+0x260 between osSetIntMask(1) and osSetIntMask(mask). Only caller: func_800005AC (wrapper on D_8003DE30). The name is unused in build.json. |
| 80000E00 | `osScGetCmdQ` | `func_80000E00` | libultra (sched) | sched/sched.c | modified | 3 instructions (lui/jr/addiu): it ignores a0 and returns the global &D_800440C0 instead of &sc->cmdQ (sc+0x78). Only caller: __amHandleFrameMsg, osSendMesg(osScGetCmdQ(D_80062558 = OSSched*), task, BLOCK), the SDK audio-manager idiom. Checked in rspTaskThread: D_800440C0 is the task queue it blocks on (base = D_800440C0), and osCreateScheduler creates it (D_80044570-0x4B0). |
| 80000E0C | `__scMain` | `func_80000E0C` | libultra (sched) | sched/sched.c | modified | stock score 39/53. A copy that removes the RSP/RDP cases and inlines __scHandleRetrace as sc->frameCount++ (+0x27C) plus osSendMesg(client->msgQ, sc, NOBLOCK) to each client, and then scores 0 (53/53) at -O2 and -O3. The PRENMI (669) case sends &sc->prenmiMsg (+0x20) as in the SDK. Thread entry (id 4) created by osCreateScheduler. Static function, so it keeps the source name, which is unused in build.json. |
| 80013260 | `Fenvelope` | `func_80013260` | libmus | libmus/src/playerinc/player_commands.inc.c | exact | Sequence command 0x90: slot 0x10 of the command table D_80036E80 (43 entries, 0x80..0xAA) points here; the table matches libmus 3.14 index for index. It sits before MusInitialize, apart from the other commands. |
| 800133AC | `Fnext` | `func_800133AC` | libmus | libmus/src/playerinc/player_commands.inc.c | exact | Sequence command 0x96: slot 0x16 of the command table D_80036E80 (43 entries, 0x80..0xAA) points here; the table matches libmus 3.14 index for index. It sits before MusInitialize, apart from the other commands. |
| 8001348C | `MusInitialize` | `initializeAudioSystem` | libmus | libmus/src/player.c (+playerinc/player_api.inc.c) | modified | masked score 207 vs libmus 3.14; only caller game func_80003120; reads musConfig fields (control_flag, channels, sched, thread_priority, heap, ptr/wbk, fifo_length, syn_*); osTvType 50/60 Hz, mus_next_frame_time=1000000/rate, alHeapInit+alHeapDBAlloc channels(0x158)/voices(0x1C), MusSetMasterVolume(3,0x7fff), seed 0x12345678, handler=__MusIntMain, n_alSynAddPlayer, n_alSynAllocVoice per channel; old libmus layout |
| 800137F0 | `MusSetMasterVolume` | `func_800137F0` | libmus | libmus/src/player.c (+playerinc/player_api.inc.c) | exact | masked score 0 vs libmus 3.14; flags&1 (MUSFLAG_EFFECTS) -> D_800604E4, flags&2 (MUSFLAG_SONGS) -> D_800604E6 (both read by __MusIntSetVolumeAndPan); called by MusInitialize(3,0x7fff) |
| 8001381C | `MusStartSong` | `func_8001381C` | libmus | libmus/src/player.c (+playerinc/player_api.inc.c) | modified | masked score 90 vs libmus 3.14 (3.14 MusStartSong is a 12-insn wrapper of __MusIntStartSong; ROM has the body inline); remaps song ptrs via __MusIntRemapPtrs, __MusIntFindChannel+__MusIntInitialiseChannel per channel, handle=mus_current_handle++, then MusHandleUnPause(handle) |
| 80013994 | `MusStartEffect` | `func_80013994` | libmus | libmus/src/player.c (+playerinc/player_api.inc.c) | modified | masked score 46 vs libmus 3.14; (number) only; default vol/pan 0x80, priority table D_800604D8[number], free channel else lowest priority -> __MusIntStartEffect; old API (fx table from config, no FX bank) |
| 80013A48 | `MusStartEffect2` | `func_80013A48` | libmus | libmus/src/player.c (+playerinc/player_api.inc.c) | modified | masked score 88 vs libmus 3.14; (number,volume,pan,restartflag,priority) 5 args; restartflag reuses channel with same fx number, priority -1 -> table; called by Fstartfx |
| 80013B58 | `MusStop` | `func_80013B58` | libmus | libmus/src/player.c (+playerinc/player_api.inc.c) | exact | masked score 3 vs libmus 3.14 (u32 counter sltu/beqz and u16 fx_number lhu only); flags&1 effects / &2 songs; stopping=speed |
| 80013C24 | `MusAsk` | `func_80013C24` | libmus | libmus/src/player.c (+playerinc/player_api.inc.c) | exact | masked score 9 vs libmus 3.14: every diff is the u32 loop counter (sltu/beqz), u16 fx_number load (lhu vs lw) and the load scheduling that follows; counts playing channels by flags; same class as MusStop/MusHandle* rated exact |
| 80013CA4 | `MusHandleStop` | `func_80013CA4` | libmus | libmus/src/player.c (+playerinc/player_api.inc.c) | exact | masked score 2 vs libmus 3.14; per-handle (+0x60) stopping/stopping_speed, returns count; diff only u32 loop counter |
| 80013D58 | `MusHandleAsk` | `countAudioVoicesByKey` | libmus | libmus/src/player.c (+playerinc/player_api.inc.c) | exact | masked score 2 vs libmus 3.14; counts channels with handle==arg; diff only u32 counter |
| 80013DB0 | `MusHandleSetVolume` | `func_80013DB0` | libmus | libmus/src/player.c (+playerinc/player_api.inc.c) | exact | masked score 2 vs libmus 3.14 (blez/beqz + sltu/slt only); cp->volscale (+0xBE, used by SetVolumeAndPan) per handle |
| 80013E10 | `MusHandleSetPan` | `func_80013E10` | libmus | libmus/src/player.c (+playerinc/player_api.inc.c) | exact | masked score 2 vs libmus 3.14; cp->panscale (+0xD0) and old_pan(+0xDE)=0xFF per handle; diff only u32 counter |
| 80013E80 | `MusHandleSetFreqOffset` | `func_80013E80` | libmus | libmus/src/player.c (+playerinc/player_api.inc.c) | exact | masked score 2 vs libmus 3.14; freqoffset(+0x44)=offset+distort(+0xAC) per handle; diff only u32 counter |
| 80013EF0 | `MusHandleSetTempo` | `func_80013EF0` | libmus | libmus/src/player.c (+playerinc/player_api.inc.c) | exact | masked score 2 vs libmus 3.14; clamp 1..256, temscale and channel_tempo=(save*tempo)>>7; diff only u32 counter |
| 80013F7C | `MusHandleSetReverb` | `func_80013F7C` | libmus | libmus/src/player.c (+playerinc/player_api.inc.c) | exact | masked score 2 vs libmus 3.14; clamp 0..127, reverb_base(+0xEB), old_reverb(+0xEC)=0xFF; diff only u32 counter |
| 80014004 | `MusBankInitialize` | `func_80014004` | libmus | libmus/src/player.c (+playerinc/player_api.inc.c) | modified | pure tail call __MusIntRemapPtrBank(pbank,wbank) (a0/a1 passed through); 3.14 libmus.h keeps MusBankInitialize(pbank,wbank) as a compat macro for the 'previous sample bank functions' -> MusPtrBankInitialize, which also sets the default bank; caller game func_80003120 |
| 80014020 | `MusBankStartSong` | `func_80014020` | libmus | libmus/src/player.c (+playerinc/player_api.inc.c) | modified | no 3.14 function (removed API, compat macro only); (ipbank,addr): if ipbank && remapped flag (+0x10 <0) mus_init_bank D_800604F0=ipbank, MusStartSong(addr), restore D_800604F4; matches the macro's MusPtrBankSetSingle+MusStartSong semantics |
| 80014064 | `MusBankStartEffect` | `func_80014064` | libmus | libmus/src/player.c (+playerinc/player_api.inc.c) | modified | no 3.14 function (removed API); (ipbank,number): bank override + inlined MusStartEffect (0x80,0x80, priority table D_800604D8) -> __MusIntStartEffect, restores default bank; caller game func_8000327C |
| 80014140 | `MusBankStartEffect2` | `func_80014140` | libmus | libmus/src/player.c (+playerinc/player_api.inc.c) | modified | no 3.14 function (removed API); (ipbank,number,volume,pan,restartflag,priority): bank override + inlined MusStartEffect2; callers game func_800032A4/80003098/80004F80 |
| 80014268 | `MusHandleGetPtrBank` | `func_80014268` | libmus | libmus/src/player.c (+playerinc/player_api.inc.c) | exact | masked score 2 vs libmus 3.14; returns cp->sample_bank(+0x98) of first channel with handle(+0x60); diff only u32 counter; no callers in ROM (old API may have had another name) |
| 800142C4 | `MusHandlePause` | `func_800142C4` | libmus | libmus/src/player.c (+playerinc/player_api.inc.c) | exact | masked score 0 vs libmus 3.14; fifo cmd 0 = FIFOCMD_PAUSE (player_fifo.h enum order) -> __MusIntFifoAddCommand |
| 800142E8 | `MusHandleUnPause` | `func_800142E8` | libmus | libmus/src/player.c (+playerinc/player_api.inc.c) | exact | masked score 0 vs libmus 3.14; fifo cmd 1 = FIFOCMD_UNPAUSE; called by MusStartSong |
| 80014310 | `MusSetFxType` | `func_80014310` | libmus | libmus/src/player.c (+playerinc/player_api.inc.c) | exact | masked score 0 vs libmus 3.14; fifo cmd 2 = FIFOCMD_CHANGEFX, latches mus_last_fxtype D_800604FC |
| 80014340 | `MusSetSongFxChange` | `func_80014340` | libmus | libmus/src/player.c (+playerinc/player_api.inc.c) | exact | masked score 0 vs libmus 3.14; if off -> MusSetFxType(mus_last_fxtype); sets mus_songfxchange_flag D_800604F8 |
| 8001439C | `__MusIntFifoOpen` | `func_8001439C` | libmus | libmus/src/playerinc/player_fifo.inc.c | modified | masked score 13 vs libmus 3.14; clamp 0x40..0x400 commands, alloc 8*n, fifo_limit/start/current=0; old version calls alHeapDBAlloc directly instead of __MusIntMemMalloc |
| 80014418 | `__MusIntFifoProcessCommand` | `func_80014418` | libmus | libmus/src/playerinc/player_fifo.inc.c | modified | masked score 16 vs libmus 3.14; case 0 -> __MusIntHandleSetFlag(handle,~1,1) pause, case 1 -> (handle,~1,0) unpause, case 2 no-op (built without SUPPORT_FXCHANGE) |
| 8001446C | `__MusIntFifoAddCommand` | `func_8001446C` | libmus | libmus/src/playerinc/player_fifo.inc.c | modified | masked score 6 vs libmus 3.14 (only the swapped MemMove argument registers); index=(current+1)%limit, full->0, __MusIntMemMove(cmd, slot, 8) with old (src,dst) order, returns 1 |
| 80014500 | `__MusIntMain` | `updateAudioVoices` | libmus | libmus/src/player.c | modified | masked score 91 vs libmus 3.14; installed as plr_player handler in MusInitialize: inlined __MusIntFifoProcess, per-channel GetNewNote/ContinuousVolume/PitchBend/stop/Envelope/Sweep/Vibrato/Wobble/SetPitch/SetVolumeAndPan, returns mus_next_frame_time; extra D_80060500=0 at end (not in 3.14) |
| 8001488C | `__MusIntGetNewNote` | `func_8001488C` | libmus | libmus/src/player.c | modified | masked score 78 vs libmus 3.14; jumptable D_80036E80 dispatch for bytes>=0x80, note/length/velocity parse, n_alSynSetVol/SetFXMix/StopVoice calls; older channel_t |
| 80014D78 | `__MusIntFlushPending` | `func_80014D78` | libmus | libmus/src/player.c | exact | masked score 0 vs libmus 3.14; if playing n_alSynStopVoice, playing=1, n_alSynStartVoice(voice,pending wave) |
| 80014DF4 | `__MusIntSetVolumeAndPan` | `updateAudioVoiceVolume` | libmus | libmus/src/player.c | modified | masked score 13 vs libmus 3.14; volume=(vol*env*velocity*volscale)>>13, master vol by fx/song, stopping scale, n_alSynSetVol; pan -> n_alSynSetPan; extra: if D_80060500 pan forced 0x40 |
| 80014F5C | `__MusIntSetPitch` | `func_80014F5C` | libmus | libmus/src/player.c | exact | masked score 0 vs libmus 3.14; porta (+0xD8) interpolation, __MusIntPowerOf2, clamp 2.0, n_alSynSetPitch |
| 80015068 | `__MusIntInitEnvelope` | `func_80015068` | libmus | libmus/src/player.c | modified | masked score 37 vs libmus 3.14; env end time from cutoff/endit (+0xD2/+0xD4) or 0x7FFFFFFF for length 0x7FFF, env_phase=1; older u64 frame fields |
| 80015118 | `__MusIntProcessEnvelope` | `updateAudioVoiceEnvelope` | libmus | libmus/src/player.c | modified | masked score 144 vs libmus 3.14; ADSR phases 1..4 with env_speed counter (+0xE5/+0xDF), release at cutoff time; older field layout (u64 frames) |
| 80015468 | `__MusIntInitSweep` | `func_80015468` | libmus | libmus/src/player.c | exact | masked score 4 vs libmus 3.14: only difference is sweep_frame copied as two words (u64 frame field in the old channel_t); sweep_frame=note_start, sweep_timer=0, sweep_dir=pan&0x40; same statements |
| 8001548C | `__MusIntProcessSweep` | `func_8001548C` | libmus | libmus/src/player.c | modified | masked score 39 vs libmus 3.14; pan sweep 0..0x7F bouncing, 0x40 step accumulator (same algorithm as 3.14 player.c:749) |
| 80015574 | `__MusIntProcessWobble` | `func_80015574` | libmus | libmus/src/player.c | exact | masked score 0 vs libmus 3.14; wobble counter (+0xF0) toggles between on/off speeds, returns wobble amount |
| 800155CC | `__MusIntProcessVibrato` | `func_800155CC` | libmus | libmus/src/player.c | modified | masked score 5 vs libmus 3.14 (inverted branch, no early 0.0 return path, result stored and reloaded); sinf((count-vib_delay)*vib_precalc)*vib_amount (sinf 0x8001BF50) |
| 80015628 | `__MusIntProcessContinuousVolume` | `func_80015628` | libmus | libmus/src/player.c | modified | masked score 21 vs libmus 3.14; continuous volume stream (+0x4C) with repeat counts; older u64 frame |
| 80015718 | `__MusIntProcessContinuousPitchBend` | `func_80015718` | libmus | libmus/src/player.c | modified | masked score 40 vs libmus 3.14; pitchbend stream (+0x48), pitchbend(+0x90)=byte-64, precalc(+0x38)=pitchbend*bendrange(+0x8C) |
| 80015858 | `__MusIntPowerOf2` | `func_80015858` | libmus | libmus/src/player.c | exact | masked score 0 vs libmus 3.14 (98 insns); polynomial 2^x approximation (14 f64 consts D_8003B348..B3B0), x<0 -> 1/poly |
| 800159EC | `__MusIntRemapPtrBank` | `func_800159EC` | libmus | libmus/src/player.c | exact | masked score 2 vs libmus 3.14 (102 insns); sets remapped flag bit31 at +0x10, __MusIntRemapPtrs on tables, wave base +wbank, tune/detune float convert; diff only u32 counter |
| 80015B84 | `__MusIntRandom` | `func_80015B84` | libmus | libmus/src/player.c | exact | masked score 1 vs libmus 3.14 (sltiu vs slti only); mus_random_seed D_800604EC 8-step LFSR, returns range*seed/2^32 |
| 80015C18 | `__MusIntInitialiseChannel` | `func_80015C18` | libmus | libmus/src/player.c | modified | masked score 10 vs libmus 3.14; memset 0x158, defaults (old_reverb/old_pan 0xFF, velocity 127, pan 64, 99.9f, 0.03125f, tempo 0x6000/vsyncs), sample_bank=mus_init_bank |
| 80015D4C | `__MusIntFindChannel` | `selectAudioVoiceSlot` | libmus | libmus/src/player.c | modified | masked score 53 vs libmus 3.14; free channel, else lowest-priority effect, else song channel of other song, else same song/channel, else index%channels; older channel_t |
| 80015ECC | `__MusIntMemSet` | `func_80015ECC` | libmus | libmus/src/lib_memory.c | exact | masked and unmasked score 0 vs libmus 3.14 lib_memory.c; byte fill (dest,value,len); MusInitialize calls it (heap,0,len) |
| 80015EF8 | `__MusIntMemMove` | `func_80015EF8` | libmus | libmus/src/lib_memory.c | modified | forward byte copy *arg1=*arg0 i.e. (src,dst,len) order (3.14 is (dest,src) with overlap check) -> older lib_memory; sits inside the libmus block; used by __MusIntFifoAddCommand |
| 80015F2C | `__MusIntRemapPtrs` | `func_80015F2C` | libmus | libmus/src/player.c | exact | masked score 2 vs libmus 3.14; adds offset to each non-zero of count pointers; diff only u32 counter; callers MusStartSong, __MusIntRemapPtrBank |
| 80015F64 | `__MusIntStartEffect` | `func_80015F64` | libmus | libmus/src/player.c | modified | masked score 99 vs libmus 3.14; inlined InitialiseChannel + fx number(+0xC6)/volscale/panscale/priority/handle, data=fx table D_800604D4[number]; old API (no fx_header) |
| 800160E8 | `__MusIntHandleSetFlag` | `func_800160E8` | libmus | libmus/src/player.c | exact | masked score 2 vs libmus 3.14; channel_flag=(flag&clear)\|set for handle (called from __MusIntFifoProcessCommand with ~1); diff only u32 counter |
| 8001613C | `func_8001613C` |  | ? |  | unknown | 1-insn setter D_80060500=arg (libmus bss, next to fifo vars D_80060504..); flag forces pan 0x40 in __MusIntSetVolumeAndPan, cleared at end of __MusIntMain; no counterpart in libmus 3.14; only caller game func_8000333C passes (arg<<16)==0 -> mono switch, probably an AKI addition or an old-API call |
| 80016148 | `Fstop` | `func_80016148` | libmus | libmus/src/playerinc/player_commands.inc.c | exact | command 0x80 = jumptable D_80036E80[0] (ROM table re-dumped: same order as 3.14 jumptable[] 0x80..0xAA incl. 0x86 Fcutoff/0x87 Fendit); masked score 1 (sh vs sw field width) |
| 80016168 | `Fwave` | `func_80016168` | libmus | libmus/src/playerinc/player_commands.inc.c | exact | command 0x81 (D_80036E80[1]); masked score 0 vs libmus 3.14; 7/15-bit wave number into +0xCE |
| 80016198 | `Fport` | `func_80016198` | libmus | libmus/src/playerinc/player_commands.inc.c | exact | command 0x82 (D_80036E80[2]); masked score 0; porta byte +0xD8 |
| 800161B8 | `Fportoff` | `func_800161B8` | libmus | libmus/src/playerinc/player_commands.inc.c | exact | command 0x83 (D_80036E80[3]); masked score 0; porta=0 |
| 800161C4 | `Fdefa` | `func_800161C4` | libmus | libmus/src/playerinc/player_commands.inc.c | exact | command 0x84 (D_80036E80[4]); masked score 0 (74 insns); envelope definition parse |
| 800162EC | `Ftempo` | `func_800162EC` | libmus | libmus/src/playerinc/player_commands.inc.c | exact | command 0x85 (D_80036E80[5]); masked score 3 (types only); tempo byte*0x6000/120/vsyncs applied to all channels of the song handle |
| 800163D0 | `Fendit` | `func_800163D0` | libmus | libmus/src/playerinc/player_commands.inc.c | exact | command 0x87 (D_80036E80[7]); masked score 0; cutoff=0, endit=byte |
| 800163E4 | `Fcutoff` | `func_800163E4` | libmus | libmus/src/playerinc/player_commands.inc.c | exact | command 0x86 (D_80036E80[6]); masked score 0; endit=0, cutoff=16-bit |
| 80016408 | `Fvibup` | `func_80016408` | libmus | libmus/src/playerinc/player_commands.inc.c | exact | command 0x88 (D_80036E80[8]); masked score 0; vib delay/speed/amount |
| 80016478 | `Fvibdown` | `func_80016478` | libmus | libmus/src/playerinc/player_commands.inc.c | exact | command 0x89 (D_80036E80[9]); masked score 0; negative vib amount |
| 800164EC | `Fviboff` | `func_800164EC` | libmus | libmus/src/playerinc/player_commands.inc.c | exact | command 0x8A (D_80036E80[10]); masked score 0; vib_speed=0, vibrato=0 |
| 800164FC | `Flength` | `func_800164FC` | libmus | libmus/src/playerinc/player_commands.inc.c | modified | command 0x8B (D_80036E80[11]); masked score 15 vs 3.14; 7/14-bit fixed length into +0xCC (older form) |
| 8001653C | `Fignore` | `func_8001653C` | libmus | libmus/src/playerinc/player_commands.inc.c | exact | command 0x8C (D_80036E80[12]); masked score 0; ignore flag +0xD7=1 |
| 8001654C | `Ftrans` | `func_8001654C` | libmus | libmus/src/playerinc/player_commands.inc.c | exact | command 0x8D (D_80036E80[13]); masked score 0; transpose byte +0xD9 |
| 8001655C | `Fignore_trans` | `func_8001655C` | libmus | libmus/src/playerinc/player_commands.inc.c | exact | command 0x8E (D_80036E80[14]); masked score 0; ignore_transpose +0xDA=1 |
| 8001656C | `Fdistort` | `func_8001656C` | libmus | libmus/src/playerinc/player_commands.inc.c | exact | command 0x8F (D_80036E80[15]); masked score 0; distort(+0xAC), freqoffset adjusted |
| 800165C4 | `Fenvoff` | `func_800165C4` | libmus | libmus/src/playerinc/player_commands.inc.c | exact | command 0x91 (D_80036E80[17]); masked score 0; env off flag +0xF6=1 |
| 800165D4 | `Fenvon` | `func_800165D4` | libmus | libmus/src/playerinc/player_commands.inc.c | exact | command 0x92 (D_80036E80[18]); masked score 0; +0xF6=0 |
| 800165E0 | `Ftroff` | `func_800165E0` | libmus | libmus/src/playerinc/player_commands.inc.c | exact | command 0x93 (D_80036E80[19]); masked score 0; trigger off +0xF7=1 |
| 800165F0 | `Ftron` | `func_800165F0` | libmus | libmus/src/playerinc/player_commands.inc.c | exact | command 0x94 (D_80036E80[20]); masked score 0; +0xF7=0 |
| 800165FC | `Ffor` | `pushAudioSequenceLoopState` | libmus | libmus/src/playerinc/player_commands.inc.c | modified | command 0x95 (D_80036E80[21]); masked score 43 vs 3.14; pushes for_count/stack/stackvol/stackpb/volume/pitchbend/repeat counts at for_stack_count(+0xFB); older layout |
| 800166B0 | `Fwobble` | `func_800166B0` | libmus | libmus/src/playerinc/player_commands.inc.c | exact | command 0x97 (D_80036E80[23]); masked score 0; wobble amount/on/off speeds |
| 800166D8 | `Fwobbleoff` | `func_800166D8` | libmus | libmus/src/playerinc/player_commands.inc.c | exact | command 0x98 (D_80036E80[24]); masked score 0; wobble_on_speed=0 |
| 800166E4 | `Fvelon` | `func_800166E4` | libmus | libmus/src/playerinc/player_commands.inc.c | exact | command 0x99 (D_80036E80[25]); masked score 0; velocity_on +0xF2=1 |
| 800166F4 | `Fveloff` | `func_800166F4` | libmus | libmus/src/playerinc/player_commands.inc.c | exact | command 0x9A (D_80036E80[26]); masked score 0; +0xF2=0 |
| 80016700 | `Fvelocity` | `func_80016700` | libmus | libmus/src/playerinc/player_commands.inc.c | exact | command 0x9B (D_80036E80[27]); masked score 0; velocity_on=0, default_velocity(+0xF3)=byte |
| 80016714 | `Fpan` | `func_80016714` | libmus | libmus/src/playerinc/player_commands.inc.c | modified | command 0x9C (D_80036E80[28]); masked score 2 vs 3.14 (extra li 255/sb); pan=byte>>1 and also old_pan(+0xDE)=0xFF (3.14 does not) |
| 80016730 | `Fstereo` | `func_80016730` | libmus | libmus/src/playerinc/player_commands.inc.c | exact | command 0x9D (D_80036E80[29]); masked score 0; skips 2 bytes |
| 80016738 | `Fdrums` | `func_80016738` | libmus | libmus/src/playerinc/player_commands.inc.c | modified | command 0x9E (D_80036E80[30]); masked score 13 vs 3.14; 8-bit drum index into song-header table (3.14 parses 7/15-bit); older layout |
| 80016770 | `Fdrumsoff` | `func_80016770` | libmus | libmus/src/playerinc/player_commands.inc.c | exact | command 0x9F (D_80036E80[31]); masked score 0; pdrums=0 (sweep alSynDelete candidate wrong) |
| 8001677C | `Fprint` | `func_8001677C` | libmus | libmus/src/playerinc/player_commands.inc.c | exact | command 0xA0 (D_80036E80[32]); masked score 0; skips 1 byte (final ROM build) |
| 80016784 | `Fgoto` | `func_80016784` | libmus | libmus/src/playerinc/player_commands.inc.c | exact | command 0xA1 (D_80036E80[33]); masked score 0; song base(+0x9C)+offset, resets continuous vol/pb streams |
| 800167F4 | `Freverb` | `func_800167F4` | libmus | libmus/src/playerinc/player_commands.inc.c | exact | command 0xA2 (D_80036E80[34]); masked score 0; reverb byte +0xEA |
| 80016804 | `FrandNote` | `func_80016804` | libmus | libmus/src/playerinc/player_commands.inc.c | exact | command 0xA3 (D_80036E80[35]); masked score 0; transpose=__MusIntRandom(range)+base |
| 80016854 | `FrandVolume` | `func_80016854` | libmus | libmus/src/playerinc/player_commands.inc.c | exact | command 0xA4 (D_80036E80[36]); masked score 0; volume=__MusIntRandom(range)+base |
| 800168A4 | `FrandPan` | `func_800168A4` | libmus | libmus/src/playerinc/player_commands.inc.c | exact | command 0xA5 (D_80036E80[37]); masked score 0; pan=__MusIntRandom(range)+base |
| 800168F4 | `Fvolume` | `func_800168F4` | libmus | libmus/src/playerinc/player_commands.inc.c | exact | command 0xA6 (D_80036E80[38]); masked score 0; volume byte +0xDC |
| 80016904 | `Fstartfx` | `func_80016904` | libmus | libmus/src/playerinc/player_commands.inc.c | modified | command 0xA7 (D_80036E80[39]); masked score 17 vs 3.14; MusStartEffect2(id,volume,pan,0,priority) with temp priority bump, copies handle/sample_bank to new channels |
| 800169D4 | `Fbendrange` | `func_800169D4` | libmus | libmus/src/playerinc/player_commands.inc.c | modified | command 0xA8 (D_80036E80[40]); masked score 12 vs 3.14; bendrange(+0x8C)=byte*(100/4096) (3.14: 1/64) and pitchbend_precalc(+0x38)=pitchbend(+0x90)*pitchbend(+0x90): the old revision squares pitchbend instead of multiplying by bendrange (fields confirmed by __MusIntProcessContinuousPitchBend, which writes +0x90 and +0x38=+0x90*+0x8C) |
| 80016A10 | `Fsweep` | `func_80016A10` | libmus | libmus/src/playerinc/player_commands.inc.c | exact | command 0xA9 (D_80036E80[41]); masked score 0; sweep_speed +0xF4 |
| 80016A20 | `Fchangefx` | `func_80016A20` | libmus | libmus/src/playerinc/player_commands.inc.c | modified | command 0xAA (D_80036E80[42], last non-zero entry; 0xAB/0xAC slots are 0 = no Fmarker/Flength0); returns ptr+1 only: built without SUPPORT_FXCHANGE |
| 80016A30 | `amCreateAudioMgr` | `func_80016A30` | audio manager | demos/simple/src/main/audiomgr.c (adapted in old libmus aud manager) | modified | called only by MusInitialize with musConfig fields (sched, thread_priority, {output_rate, retraceCount, rsp_cmds}=amConfig, num_dma_bufs, dma_buf_size, vsyncs); statement-level match with demo amCreateAudioMgr (dmaproc=__amDmaNew, osAiSetFrequency, fsize=framesPerField*rate/vsyncs rounded to 184 for n_audio, n_alInit, DMA list via alLink, 2 ACMD lists, 4 AudioInfos, 3 queues, osCreateThread(__amMain)+osStartThread); libmus 3.14's aud_thread.c is a different design (__MusIntAudManInit + musSched), so the demo names fit better |
| 80016EDC | `__amMain` | `func_80016EDC` | audio manager | demos/simple/src/main/audiomgr.c (adapted in old libmus aud manager) | modified | statement-level match with audiomgr.c __amMain: osScAddClient, loop: 1 RETRACE -> __amHandleFrameMsg + wait reply, 4 PRE_NMI (no-op), 10 QUIT; __amHandleDoneMsg absent; then n_alClose |
| 80017018 | `__amHandleFrameMsg` | `createAudioTask` | audio manager | demos/simple/src/main/audiomgr.c (adapted in old libmus aud manager) | modified | audiomgr.c __amHandleFrameMsg plus libmus osAiGetStatus FIFO_FULL check; __clearAudioDMA, osAiGetLength>>2, osAiSetNextBuffer(last), n_alAudioFrame, cmdLen==0 -> 0, fills OSScTask, osSendMesg(osScGetCmdQ), curAcmdList^=1 |
| 800171B4 | `__amDMA` | `func_800171B4` | audio manager | demos/simple/src/main/audiomgr.c (adapted in old libmus aud manager) | modified | audiomgr.c __amDMA buffer search/alUnlink/alLink/osEPiStartDma plus libmus 3.14 __CallBackDmaProcess additions: 0xFF000000 -> 64DD handle +0x140000, control_flag&1 (MUSCONTROL_RAM) -> osVirtualToPhysical(addr) |
| 800173C0 | `__amDmaNew` | `func_800173C0` | audio manager | demos/simple/src/main/audiomgr.c (adapted in old libmus aud manager) | modified | audiomgr.c __amDmaNew (3.14 role: __CallBackDmaNew); init firstUsed/firstFree once, returns __amDMA; installed as dmaproc by amCreateAudioMgr |
| 80017408 | `__clearAudioDMA` | `func_80017408` | audio manager | demos/simple/src/main/audiomgr.c (adapted in old libmus aud manager) | modified | audiomgr.c __clearAudioDMA (3.14 role: __MusIntDmaProcess); recv nextDMA msgs NOBLOCK, frees buffers with lastFrame+1<audFrameCt via alUnlink/alLink, audFrameCt++ |
| 80017510 | `n_alInit` | `func_80017510` | n_audio | libnaudio/src/n_sl.c | exact | score 0 -O3; if(!alGlobals){alGlobals=g; if(!n_syn){n_syn=&g->drvr; n_alSynNew(c)}} with alGlobals D_80036F50, n_syn D_80036F54; called by amCreateAudioMgr |
| 80017554 | `n_alClose` | `func_80017554` | n_audio | libnaudio/src/n_sl.c | exact | score 0; n_alSynDelete + clears D_80036F50/D_80036F54; called by __amMain on quit |
| 80017590 | `n_alSynAddPlayer` | `func_80017590` | n_audio | libnaudio/src/n_synaddplayer.c | exact | score 0; interrupt-masked push onto n_syn->head, samplesLeft=curSamples; called by MusInitialize |
| 800175E0 | `n_alSynAllocVoice` | `func_800175E0` | n_audio | libnaudio/src/n_synallocvoice.c | exact | score 0 with older-revision steal constants (offset=512, moredata=offset-64; sdkmod 552/368 scores 7); calls _allocatePVoice/__n_allocParam/n_alEnvmixerParam |
| 80017700 | `_allocatePVoice` | `func_80017700` | n_audio | libnaudio/src/n_synallocvoice.c | exact | score 0; static of n_synallocvoice.c: pLameList/pFreeList/pAllocList scan by priority; libaudio alSynAllocVoice/_allocatePVoice not in ROM, so source name is free (Banjo-Kazooie decomp spells it _n_allocatePVoice) |
| 800177C0 | `n_alSynDelete` | `func_800177C0` | n_audio | libnaudio/src/n_syndelete.c | exact | score 0 after removing n_seqp1/n_seqp2/n_sndp stores (older N_ALSynth; sdkmod scores 3); body n_syn(D_80036F54)->head=0; called by n_alClose (sweep __osAiDeviceBusy wrong) |
| 800177D0 | `n_alSynSetFXMix` | `func_800177D0` | n_audio | libnaudio/src/n_synsetfxmix.c | exact | score 0 without the fxmix>127 clamp (older revision; sdkmod scores 21); update type 16 = AL_FILTER_SET_FXAMT |
| 80017860 | `n_alSynSetPan` | `func_80017860` | n_audio | libnaudio/src/n_synsetpan.c | exact | score 0; real operand: update type 0xC = AL_FILTER_SET_PAN (breaks tie with the other same-shape setters); paramSamples at n_syn+0x1C |
| 800178F0 | `n_alSynSetPitch` | `func_800178F0` | n_audio | libnaudio/src/n_synsetpitch.c | exact | score 0; update type 7 = AL_FILTER_SET_PITCH, f32 payload; called by __MusIntSetPitch |
| 80017980 | `n_alSynSetVol` | `func_80017980` | n_audio | libnaudio/src/n_synsetvol.c | exact | score 0; type 0xB = AL_FILTER_SET_VOLUME, moredata=_n_timeToSamples(t); called by __MusIntSetVolumeAndPan |
| 80017A30 | `n_alSynStartVoice` | `func_80017A30` | n_audio | libnaudio/src/n_synstartvoice.c | exact | score 0; type 0xE = AL_FILTER_START_VOICE with unityPitch (+0x1A); called by __MusIntFlushPending |
| 80017AC0 | `n_alSynStopVoice` | `func_80017AC0` | n_audio | libnaudio/src/n_synstopvoice.c | exact | score 0; type 0xF = AL_FILTER_STOP_VOICE; called by __MusIntMain/GetNewNote |
| 80017B40 | `n_alSynNew` | `initStatePools17B40` | n_audio | libnaudio/src/n_synthesizer.c | exact | score 0 with older revision (no n_seqp1/n_seqp2/n_sndp init; sdkmod scores 3); maxOutSamples=184, mainBus handler n_alFxPull/n_alAuxBusPull, alN_PVoiceNew per voice; called by n_alInit; libaudio alSynNew is 0x80020340 |
| 80017DB0 | `n_alAudioFrame` | `writeAudioStreamBuffer` | n_audio | libnaudio/src/n_synthesizer.c | exact | score 0 with older single-client loop (n_synthesizer_old3.c; sdkmod 3-client __n_nextSampleTime version scores 49); n_alSavePull, _n_collectPVoices; called by __amHandleFrameMsg; libaudio alAudioFrame is 0x8002060C |
| 80017F18 | `__n_allocParam` | `func_80017F18` | n_audio | libnaudio/src/n_synthesizer.c | exact | score 0; pops n_syn(D_80036F54)->paramList (+0x2C), no ALSynth* arg -> not libaudio __allocParam (0x800207BC) |
| 80017F44 | `_n_freeParam` | `func_80017F44` | n_audio | libnaudio/src/n_synthesizer.c | exact | score 0; pushes onto n_syn->paramList; sdkmod name _n_freeParam (Banjo-Kazooie decomp: __n_freeParam); sweep __freeParam tie broken by n_syn global (libaudio __freeParam is 0x800207E8) |
| 80017F5C | `_n_collectPVoices` | `func_80017F5C` | n_audio | libnaudio/src/n_synthesizer.c | exact | score 0; moves pLameList to pFreeList via alUnlink/alLink on n_syn; called by n_alAudioFrame |
| 80017FBC | `_n_freePVoice` | `func_80017FBC` | n_audio | libnaudio/src/n_synthesizer.c | exact | score 0; alUnlink + alLink to n_syn->pLameList; called by n_alEnvmixerPull |
| 80017FF4 | `_n_timeToSamplesNoRound` | `func_80017FF4` | n_audio | libnaudio/src/n_synthesizer.c | exact | score 0; micros*outputRate(+0x40)/1e6+0.5; called by n_alAudioFrame |
| 80018044 | `_n_timeToSamples` | `func_80018044` | n_audio | libnaudio/src/n_synthesizer.c | exact | score 0 at -O3, 19 at -O2 -> libnaudio built -O3; NoRound & ~0xF; called by n_alSynSetVol |
| 800180A0 | `n_alAuxBusPull` | `func_800180A0` | n_audio | libnaudio/src/n_auxbus.c | exact | score 0; aClearBuffer then n_alEnvmixerPull per source; mainBus handler when fxType==NONE |
| 80018140 | `n_alFxNew` | `func_80018140` | n_audio | libnaudio/src/n_drvrNew.c | exact | score 0 (251 insns, rechecked); reverb param tables, alHeapDBAlloc, init_lpfilter; sweep near-miss alFxNew(14) is libaudio's |
| 8001852C | `alN_PVoiceNew` | `func_8001852C` | n_audio | libnaudio/src/n_drvrNew.c | exact | score 0; source name confirmed in sdkmod n_drvrNew.c:171; allocates em/rs/ld state, dmaNew callback; called by n_alSynNew |
| 80018660 | `n_alEnvmixerPull` | `func_80018660` | n_audio | libnaudio/src/n_env.c | exact | older n_env.c revision: live __assert("EX","n_env.c",130/134), SAMPLE184(delta) then samples=this-last; patched source scores 13 (s6/s7 swap + one sltiu/slti, no logic difference) vs 63 for sdkmod; calls _n_pullSubFrame/_n_getVol/n_alLoadParam/_n_freePVoice/_n_freeParam |
| 80018C24 | `n_alEnvmixerParam` | `func_80018C24` | n_audio | libnaudio/src/n_env.c | exact | score 0 after removing em_segEnd=0 in RESET (older revision; sdkmod scores 1); called by all n_alSynSet* |
| 80018CC4 | `_n_pullSubFrame` | `func_80018CC4` | n_audio | libnaudio/src/n_env.c | exact | score 0; static _pullSubFrame of n_env.c; renamed because libaudio _pullSubFrame is 0x8001E960 (Banjo-Kazooie decomp spells it __n_pullSubFrame) |
| 80018EE4 | `_n_getRate` | `computeFixedPointStepRate` | n_audio | libnaudio/src/n_env.c | exact | score 0 with older count==0 else-branch returning 0; static _getRate of n_env.c; renamed because libaudio _getRate is 0x8001ED64 (Banjo-Kazooie decomp: __n_getRate) |
| 80019024 | `_n_getVol` | `func_80019024` | n_audio | libnaudio/src/n_env.c | exact | score 0; static _getVol of n_env.c; renamed because libaudio _getVol is 0x8001EFE4 (Banjo-Kazooie decomp: __n_getVol) |
| 80019070 | `n_alAdpcmPull` | `func_80019070` | n_audio | libnaudio/src/n_load.c | exact | score 0 (274 insns, rechecked); calls _n_decodeChunk; sweep near-miss alAdpcmPull(13) is libaudio's |
| 800194B8 | `n_alLoadParam` | `func_800194B8` | n_audio | libnaudio/src/n_load.c | exact | score 0; SET_WAVETABLE/RESET/START; sweep near-miss alLoadParam(11) is libaudio's |
| 80019644 | `_n_decodeChunk` | `buildAudioLoadBufferCommand` | n_audio | libnaudio/src/n_load.c | exact | score 0; static _decodeChunk of n_load.c; renamed because libaudio _decodeChunk is 0x8001E0AC; same name as the Banjo-Kazooie decomp uses |
| 80019790 | `n_alResamplePull` | `func_80019790` | n_audio | libnaudio/src/n_resample.c | exact | score 0; pitch clamp 1.99996, aResample, calls n_alAdpcmPull |
| 8001994C | `n_alResampleParam` | `func_8001994C` | n_audio | libnaudio/src/n_resample.c | exact | score 0 (8 insns, rechecked); real callee is n_alLoadParam 0x800194B8, returns 0 (sweep __d_to_ll wrong) |
| 80019970 | `n_alFxPull` | `func_80019970` | n_audio | libnaudio/src/n_reverb.c | exact | score 0; n_alAuxBusPull, _n_loadBuffer/_n_saveBuffer/_n_loadOutputBuffer/_n_filterBuffer; mainBus handler set in n_alSynNew |
| 80019C80 | `n_alFxParamHdl` | `setAudioRegionParameter` | n_audio | libnaudio/src/n_reverb.c | exact | score 0; uses n_syn->outputRate; tie with libaudio alFxParamHdl (0x8001F874) broken by n_syn global |
| 80019E70 | `_n_loadOutputBuffer` | `writeOscillatorSegment` | n_audio | libnaudio/src/n_reverb.c | exact | score 0; calls libaudio _doModFunc (0x8001FFF8, extern in n_reverb.c), aResample |
| 8001A080 | `_n_loadBuffer` | `func_8001A080` | n_audio | libnaudio/src/n_reverb.c | exact | score 0; circular-buffer aLoadBuffer split at end |
| 8001A1A8 | `_n_saveBuffer` | `func_8001A1A8` | n_audio | libnaudio/src/n_reverb.c | exact | score 0; circular-buffer aSaveBuffer |
| 8001A2C0 | `_n_filterBuffer` | `func_8001A2C0` | n_audio | libnaudio/src/n_reverb.c | exact | score 0; aLoadADPCM(32)+aPoleFilter |
| 8001A360 | `n_alSavePull` | `func_8001A360` | n_audio | libnaudio/src/n_save.c | exact | score 0; n_alMainBusPull then aInterleave and aSaveBuffer; called by n_alAudioFrame |
| 8001A3B0 | `n_alSynAllocFX` | `func_8001A3B0` | n_audio | libnaudio/src/n_synallocfx.c | exact | score 0; n_alFxNew(&n_syn->auxBus->fx[bus],c,hp); called by n_alSynNew |
| 8001A400 | `n_alMainBusPull` | `func_8001A400` | n_audio | libnaudio/src/n_mainbus.c | exact | score 0; aClearBuffer, mainBus filter handler, aMix 0x7FFF; called by n_alSavePull |
| 8001A480 | `nw2Sqrtf` |  | libultra (gu) | gu/sqrtf.s | exact | Same code as the SDK's hand-written LEAF(sqrtf): sqrt.s fv0,fa0; j ra (2 instructions). It is sqrtf.o, member 3 of base/I/libgultra_rom.txt, which sits just before align.o as in the ROM. build.json symbols already put 'sqrtf' at 0x8001A480. guAlign, guLookAt and guNormalize call it as the fallback after the inline sqrt.s. |
| 8001A490 | `guAlignF` | `func_8001A490` | libultra (gu) | gu/align.c | exact | Score 0 (113) at I/J/K/L, both -O2 and -O3. Calls guNormalize, sinf, cosf, sqrtf, guMtxIdentF. D_80037200 is the static dtor. |
| 8001A65C | `guAlign` | `func_8001A65C` | libultra (gu) | gu/align.c | exact | Score 0 (115) at -O3 on I/J/K/L; -O2 gives 112. Same callees as guAlignF plus guMtxF2L. |
| 8001A830 | `cosf` |  | libultra (gu) | gu/cosf.c | exact | Score 0 (79) against __cosf on every version. cosf.c has '#pragma weak cosf = __cosf', so the current name is already the SDK's public name. No rename needed. |
| 8001A980 | `guLookAtF` | `func_8001A980` | libultra (gu) | gu/lookat.c | exact | Score 0 (224) on every version. Calls guMtxIdentF and sqrtf, as in the source. |
| 8001AD00 | `guLookAt` | `func_8001AD00` | libultra (gu) | gu/lookat.c | exact | Score 0 (225) at -O3; -O2 gives 222. Same as guLookAtF plus guMtxF2L. |
| 8001B090 | `guMtxF2L` | `func_8001B090` | libultra (gu) | gu/mtxutil.c | exact | Score 0 (37). First function of mtxutil.c (F2L, L2F, IdentF, Ident). Every fixed-point gu builder in the region calls it. |
| 8001B128 | `guMtxL2F` | `func_8001B128` | libultra (gu) | gu/mtxutil.c | exact | Score 0 (41). Second function of mtxutil.c, in ROM order. Nothing in main calls it (dead code in mtxutil.o). |
| 8001B1D0 | `guMtxIdentF` | `initIdentityMatrix4x4` | libultra (gu) | gu/mtxutil.c | exact | Score 0 (19). The gu float builders (guOrthoF, guScaleF, guTranslateF ...) call it first. |
| 8001B220 | `guMtxIdent` | `func_8001B220` | libultra (gu) | gu/mtxutil.c | exact | Score 0 (59) at -O3 (-O2 gives 59 differences); IdentF and F2L are inlined into it. Fourth function of mtxutil.c. No callers. |
| 8001B310 | `guMtxCatF` | `nw2Mat4Mul` | libultra (gu) | gu/mtxcatf.c | exact | Score 0 (54). First function of mtxcatf.c, which defines guMtxCatF and then guMtxXFMF. |
| 8001B3EC | `guMtxXFMF` | `func_8001B3EC` | libultra (gu) | gu/mtxcatf.c | exact | Score 0 (43). It directly follows guMtxCatF, as in mtxcatf.c, and 2.0I libgultra_rom has no mgu objects, so this is the library copy. The score-0 copy at 80007F70 (game code) is the one that needs another name. |
| 8001B4A0 | `guNormalize` | `func_8001B4A0` | libultra (gu) | gu/normalize.c | exact | Score 0 (42) on every version. Inline sqrt.s with the jal sqrtf fallback; guAlignF and guAlign call it. Note: it is still an asm/nonmatchings .s file in build.json (no src .c). |
| 8001B550 | `guOrthoF` | `buildOrthoMatrixFloat` | libultra (gu) | gu/ortho.c | exact | Score 0 (76), against 55 for guFrustumF. Calls guMtxIdentF. |
| 8001B680 | `guOrtho` | `buildOrthoMatrixFixed` | libultra (gu) | gu/ortho.c | exact | Score 0 (83) at -O3; -O2 gives 80. Calls guMtxIdentF and guMtxF2L. |
| 8001B7D0 | `guPerspectiveF` | `buildPerspectiveMatrixFloat` | libultra (gu) | gu/perspective.c | exact | Score 0 (104). Calls guMtxIdentF, cosf, sinf. |
| 8001B980 | `guPerspective` | `func_8001B980` | libultra (gu) | gu/perspective.c | exact | Score 0 (110) at -O3; -O2 gives 107. Adds guMtxF2L. |
| 8001BB50 | `guRotateRPYF` | `func_8001BB50` | libultra (gu) | gu/rotaterpy.c | exact | Score 0 (98). Three sinf and three cosf calls, then guMtxIdentF. D_80037210 is the static dtor. |
| 8001BCD8 | `guRotateRPY` | `func_8001BCD8` | libultra (gu) | gu/rotaterpy.c | exact | Score 0 (99) at -O3; -O2 gives 96. Adds guMtxF2L. |
| 8001BE70 | `guScaleF` | `func_8001BE70` | libultra (gu) | gu/scale.c | exact | Score 0 (24), against 3 for guTranslateF. The operands decide it: x/y/z are stored at +0x0/+0x14/+0x28 (the diagonal) and 1.0 at +0x3C, after guMtxIdentF. |
| 8001BED0 | `guScale` | `buildScaleMatrixFixed` | libultra (gu) | gu/scale.c | exact | Score 0 (31) at -O3, against 6 for guTranslate. Calls guMtxIdentF and guMtxF2L. |
| 8001BF50 | `sinf` |  | libultra (gu) | gu/sinf.c | exact | Score 0 (103) against __sinf. sinf.c has '#pragma weak sinf = __sinf', so the current name is already the SDK's. No rename needed. |
| 8001C0F0 | `guTranslateF` | `func_8001C0F0` | libultra (gu) | gu/translate.c | exact | Score 0 (21), against 3 for guScaleF. The operands decide it: x/y/z go to row 3 (+0x30/+0x34/+0x38) after guMtxIdentF. |
| 8001C144 | `guTranslate` | `func_8001C144` | libultra (gu) | gu/translate.c | exact | Score 0 (28) at -O3 (-O2 gives 23), against 6 for guScale. Calls guMtxIdentF and guMtxF2L. |
| 8001C1C0 | `guPositionF` | `buildScaledRotationTranslationMatrix` | libultra (gu) | gu/position.c | exact | Score 0 (118). Three sinf and three cosf calls. D_80037220 is the static dtor. |
| 8001C398 | `guPosition` | `buildScaledRotationTranslationMatrixFixed` | libultra (gu) | gu/position.c | exact | Score 0 (120) at -O3; -O2 gives 117. Adds guMtxF2L. |
| 8001C580 | `guRandom` | `func_8001C580` | libultra (gu) | gu/random.c | exact | Score 0 (11). The operands confirm it: x = xseed<<2; xseed = ((x+2)*(x+3))>>2. In the ROM, D_80037230 holds 0x0A6B99CD = 174823885, the SDK's 'static unsigned int xseed = 174823885'. |
| 8001C5B0 | `osInvalDCache` | `func_8001C5B0` | libultra | os/invaldcache.s | asm-identified | Already settled: its header comment names osInvalDCache and says it is identical to the 2.0I .s file. |
| 8001C660 | `osInvalICache` | `func_8001C660` | libultra | os/invalicache.s | asm-identified | Already settled: header comment names osInvalICache. The zero words after it, up to 8001C740, are alignment padding, not a hidden function. |
| 8001C740 | `osSetIntMask` | `func_8001C740` | libultra | os/setintmask.s | asm-identified | Already settled: header comment names osSetIntMask. Uses __OSGlobalIntMask (D_80038810) and __osRcpImTable (D_8003B650). |
| 8001C7E0 | `osWritebackDCache` | `func_8001C7E0` | libultra | os/writebackdcache.s | asm-identified | Already settled: header comment names osWritebackDCache. |
| 8001C860 | `osWritebackDCacheAll` | `func_8001C860` | libultra | os/writebackdcacheall.s | asm-identified | Already settled: header comment names osWritebackDCacheAll. |
| 8001C890 | `osCreateMesgQueue` | `func_8001C890` | libultra | os/createmesgqueue.c | exact | Score 0 (9). Both wait lists are set to &D_80037240. The ROM data proves D_80037240 is __osThreadTail: it holds {NULL,-1}, and D_80037248 (__osRunQueue) and D_8003724C (__osActiveQueue) both point at it, exactly as thread.c initialises them. |
| 8001C8C0 | `osCreateThread` | `func_8001C8C0` | libultra | os/createthread.c | exact | Score 0 (52). Calls __osDisableInt and __osRestoreInt, and links into __osActiveQueue (D_8003724C). |
| 8001C990 | `osRecvMesg` | `func_8001C990` | libultra | os/recvmesg.c | exact | Score 0 (73), against 46 for osSendMesg. Calls __osEnqueueAndYield, then osStartThread(__osPopThread(&mq->fullqueue)). D_80037250 is __osRunningThread (initialised to NULL). |
| 8001CAC0 | `osSendMesg` | `func_8001CAC0` | libultra | os/sendmesg.c | exact | Score 0 (76), against 16 for osJamMesg. Same callees as osRecvMesg. |
| 8001CBF0 | `osSetEventMesg` | `func_8001CBF0` | libultra | os/seteventmesg.c | exact | Score 0 (23) on 2.0I (and on G/H). J, K and L give 32 at both -O2 and -O3, because their source is different (__osShutdown/PRENMI handling), not because of a flag. Writes __osEventStateTab (D_8007DF30). |
| 8001CC50 | `osSetThreadPri` | `func_8001CC50` | libultra | os/setthreadpri.c | exact | Score 0 (50). Calls __osDequeueThread (8001CE40), __osEnqueueThread and __osEnqueueAndYield, and uses __osRunQueue and __osRunningThread. |
| 8001CD20 | `osStartThread` | `startThread` | libultra | os/startthread.c | exact | Score 0 (70). Calls __osEnqueueThread, __osPopThread and __osDispatchThread. osRecvMesg and osSendMesg call it. |
| 8001CE40 | `__osDequeueThread` | `func_8001CE40` | libultra | os/thread.c | exact | Score 0 (12). Unlinks t from the ->next chain at offset 0. Called by osSetThreadPri and by osDestroyThread (which looks like osDestroyThread). thread.o comes after startthread.o in the 2.0I archive, as in the ROM. |
| 8001CE80 | `osVirtualToPhysical` | `func_8001CE80` | libultra | os/virtualtophysical.c | exact | Score 0 (21). KSEG0 and KSEG1 addresses are masked with 0x1FFFFFFF; anything else goes to __osProbeTLB. Callers include _pullSubFrame, alResamplePull, the reverb buffer functions, _filterBuffer and osAiSetNextBuffer. |
| 8001CEE0 | `__assert` | `func_8001CEE0` | libultra | debug/assert.c | exact | Empty function (jr ra; nop): with _FINALROM the body of __assert is compiled out. assert.o comes between virtualtophysical.o and drvrnew.o in 2.0I libgultra_rom, which is where this function sits. Called with (expr, file, line) by alEnvmixerPull, _pullSubFrame, alFxPull, alSavePull and __nextSampleTime, plus the second audio copy (n_alEnvmixerPull). |
| 8001CEF0 | `init_lpfilter` | `func_8001CEF0` | libaudio | audio/drvrnew.c | exact | Score 0 (40) on I. synthInternals.h line 338 '#define _init_lpfilter init_lpfilter' applies before J, and the J/K/L objects have no symbol of that name. Uses SCALE: D_8003B6D0 holds 16384.0. alFxParamHdl calls it. |
| 8001CF94 | `alFxNew` | `initAudioStream` | libaudio | audio/drvrnew.c | exact | Score 0 (294) at -O3 on all versions; -O2 gives 53 (at -O3 init_lpfilter is inlined). Passes alFxPull, alFxParam and alFxParamHdl, and calls alFilterNew and alHeapDBAlloc. |
| 8001D42C | `alEnvmixerNew` | `func_8001D42C` | libaudio | audio/drvrnew.c | exact | Score 0 (46). Calls alFilterNew(alEnvmixerPull, alEnvmixerParam), then alHeapDBAlloc. |
| 8001D4E4 | `alLoadNew` | `func_8001D4E4` | libaudio | audio/drvrnew.c | exact | Score 0 (44). Calls alFilterNew(alAdpcmPull, alLoadParam) and alHeapDBAlloc twice. |
| 8001D594 | `alResampleNew` | `func_8001D594` | libaudio | audio/drvrnew.c | exact | Score 0 (35). Calls alFilterNew(alResamplePull, alResampleParam). |
| 8001D620 | `alAuxBusNew` | `func_8001D620` | libaudio | audio/drvrnew.c | exact | Score 0 (23); the code is the same shape as alMainBusNew. Operands settle it: it calls alFilterNew(alAuxBusPull 8001E230, alAuxBusParam 8001E30C, type 6), and AL_AUXBUS = 6 in the synthInternals.h enum. alSynNew calls it with drvr->auxBus (+0x34). |
| 8001D67C | `alMainBusNew` | `func_8001D67C` | libaudio | audio/drvrnew.c | exact | Score 0 (23). Operands settle it: it calls alFilterNew(alMainBusPull 8001F090, alMainBusParam 8001F1D0, type 7), and AL_MAINBUS = 7. alSynNew calls it with drvr->mainBus (+0x30). |
| 8001D6D8 | `alSaveNew` | `func_8001D6D8` | libaudio | audio/drvrnew.c | exact | Score 0 (17). Calls alFilterNew(alSavePull, alSaveParam). Last function of drvrnew.c. |
| 8001D720 | `alAdpcmPull` | `func_8001D720` | libaudio | audio/load.c | exact | Score 0 (273). Calls _decodeChunk 3 times. alLoadNew and alLoadParam reference it. |
| 8001DB64 | `alRaw16Pull` | `func_8001DB64` | libaudio | audio/load.c | exact | Score 0 (231). alLoadParam uses it as the handler for 16-bit raw wavetables. |
| 8001DF00 | `alLoadParam` | `func_8001DF00` | libaudio | audio/load.c | exact | Score 0 (107). Calls alCopy and switches the handler between alAdpcmPull and alRaw16Pull. alSynNew calls it with (SET_SOURCE, 0). |
| 8001E0AC | `_decodeChunk` | `buildAudioLoadBufferCommands` | libaudio | audio/load.c | exact | Score 0 (94). Static function. alAdpcmPull calls it 3 times. |
| 8001E230 | `alAuxBusPull` | `pullAudioMixerChildren` | libaudio | audio/auxbus.c | exact | Score 0 (55). alAuxBusNew passes it as the handler. |
| 8001E30C | `alAuxBusParam` | `func_8001E30C` | libaudio | audio/auxbus.c | exact | Code identical to alMainBusParam (score 0, 12 instructions). The call graph settles it: alAuxBusNew passes it, it follows alAuxBusPull (auxbus.o), and alSynNew's voice loop calls it as alAuxBusParam(drvr->auxBus(+0x34), ADD_SOURCE 2, &pv->envmixer). |
| 8001E340 | `alEnvmixerPull` | `func_8001E340` | libaudio | audio/env.c | exact | Score 0 (339) on I (and G/H). Compiled with asserts, J/K/L give 2: only the __assert line arguments differ (li a2 104/105 against 105/106). With the -DNDEBUG that J+ libgultra_rom really uses, they give 55. Calls __assert x2, _pullSubFrame, _getVol, _freePVoice, __freeParam. |
| 8001E88C | `alEnvmixerParam` | `func_8001E88C` | libaudio | audio/env.c | exact | Score 0 (53). alEnvmixerNew passes it, and alSynNew calls it with (SET_SOURCE, &pv->resampler). |
| 8001E960 | `_pullSubFrame` | `func_8001E960` | libaudio | audio/env.c | exact | Score 0 (192) on I. With asserts, J/K/L differ by 1 (the assert line number); with NDEBUG they differ by 96. Static function. Calls __assert, _getRate x2, osVirtualToPhysical. |
| 8001EC60 | `_frexpf` | `func_8001EC60` | libaudio | audio/env.c | exact | Score 0 (49). Static function. It follows _pullSubFrame in env.c order; at -O3 it is inlined into _getRate, but the standalone copy is still emitted. |
| 8001ED40 | `_ldexpf` | `func_8001ED40` | libaudio | audio/env.c | exact | Score 0 (9). Operands: in * (double)(1<<ex), skipped when ex == 0. Directly follows _frexpf. Static function, no jal callers (inlined). |
| 8001ED64 | `_getRate` | `func_8001ED64` | libaudio | audio/env.c | exact | Score 0 (150) at -O3; -O2 gives 99. _pullSubFrame calls it twice. |
| 8001EFE4 | `_getVol` | `func_8001EFE4` | libaudio | audio/env.c | exact | Score 0 (32). alEnvmixerPull calls it. |
| 8001F070 | `alFilterNew` | `func_8001F070` | libaudio | audio/filter.c | exact | Score 0 (7). Operands: source=0, handler=a1, setParam=a2, inp=outp=0 (s16 at +0xC/+0xE), type=a3 at +0x10. Every al*New constructor calls it. |
| 8001F090 | `alMainBusPull` | `func_8001F090` | libaudio | audio/mainbus.c | exact | Score 0 (80). alMainBusNew passes it as the handler. |
| 8001F1D0 | `alMainBusParam` | `func_8001F1D0` | libaudio | audio/mainbus.c | exact | Code identical to alAuxBusParam. The call graph settles it: alMainBusNew passes it, it follows alMainBusPull (mainbus.o), alSynAllocFX calls it, and alSynNew's no-fx branch calls it as alMainBusParam(drvr->mainBus(+0x30), ADD_SOURCE 2, drvr->auxBus). |
| 8001F200 | `alResamplePull` | `func_8001F200` | libaudio | audio/resample.c | exact | Score 0 (123). Calls osVirtualToPhysical. alResampleNew passes it as the handler. |
| 8001F3EC | `alResampleParam` | `func_8001F3EC` | libaudio | audio/resample.c | exact | Score 0 (48). Has jump table jtbl_8003B818. alSynNew calls it with (SET_SOURCE, &pv->decoder). |
| 8001F4B0 | `alFxPull` | `func_8001F4B0` | libaudio | audio/reverb.c | exact | Score 0 (236) on I. With asserts, J/K/L differ by 1 (the assert line); with NDEBUG they differ by 133. Calls __assert, _saveBuffer, _loadBuffer, _loadOutputBuffer, _filterBuffer. |
| 8001F860 | `alFxParam` | `func_8001F860` | libaudio | audio/reverb.c | exact | Score 0 (5). Operands: if paramID == AL_FILTER_SET_SOURCE (1), f->source(+0) = param; return 0. Referenced only by alFxNew and alSynAllocFX. |
| 8001F874 | `alFxParamHdl` | `setAudioStreamRegionParameter` | libaudio | audio/reverb.c | exact | Score 0 (124). Calls init_lpfilter, uses jtbl_8003B850 and alGlobals (D_80037510). alFxNew references it. A second copy, n_alFxParamHdl at 80019C80, is the duplicate. |
| 8001FA64 | `_loadOutputBuffer` | `loadResampledAudioRingBuffer` | libaudio | audio/reverb.c | exact | Score 0 (134). Calls _doModFunc, _loadBuffer x2, osVirtualToPhysical. |
| 8001FC7C | `_loadBuffer` | `loadAudioRingBuffer` | libaudio | audio/reverb.c | exact | Score 0 (92), against 55 for _saveBuffer. Calls osVirtualToPhysical. |
| 8001FDEC | `_saveBuffer` | `saveAudioRingBuffer` | libaudio | audio/reverb.c | exact | Score 0 (92), against 59 for _loadBuffer. Calls osVirtualToPhysical. |
| 8001FF5C | `_filterBuffer` | `func_8001FF5C` | libaudio | audio/reverb.c | exact | Score 0 (39). Calls osVirtualToPhysical (aPoleFilter state), as in the source; alFxPull calls it. |
| 8001FFF8 | `_doModFunc` | `updateTriangleOscillator` | libaudio | audio/reverb.c | exact | Score 0 (33). _loadOutputBuffer calls it (the chorus triangle LFO). |
| 80020090 | `alSavePull` | `func_80020090` | libaudio | audio/save.c | exact | Score 0 (64) on I. Calls __assert with line 34 (0x22); with asserts on, J/K/L pass 35, so they differ by 1. alSaveNew passes it as the handler. |
| 80020190 | `alSaveParam` | `func_80020190` | libaudio | audio/save.c | exact | Score 0 (10). Operands: case 1 (SET_SOURCE) stores +0, case 6 (AL_FILTER_SET_DRAM is 6 in the synthInternals.h enum) stores dramout at +0x14. alSynNew calls it as (save, SET_SOURCE, drvr->mainBus). |
| 800201C0 | `alInit` | `func_800201C0` | libaudio | audio/sl.c | exact | Score 0 (11). If alGlobals (D_80037510) is null, it stores g there and calls alSynNew. No callers in the ROM: sl.o is linked because of alLink/alUnlink. |
| 800201EC | `alClose` | `func_800201EC` | libaudio | audio/sl.c | exact | Score 0 (12). If alGlobals is set, it calls alSynDelete and clears alGlobals. No callers. |
| 8002021C | `alLink` | `func_8002021C` | libaudio | audio/sl.c | exact | Score 0 (8). Inserts ln after to (next/prev at +0/+4). Called by _collectPVoices, _freePVoice and alSynNew. |
| 8002023C | `alUnlink` | `func_8002023C` | libaudio | audio/sl.c | exact | Score 0 (11). Called by _collectPVoices and _freePVoice. |
| 80020270 | `alHeapInit` | `func_80020270` | libaudio | audio/heapinit.c | exact | Score 0 (13). Operands: base aligned to 16, cur=base, len, count=0. MusInitialize calls it. |
| 800202B0 | `alHeapDBAlloc` | `func_800202B0` | libaudio | audio/heapalloc.c | exact | Score 0 (18). Five arguments, called as (0, 0, hp, num, size), which is the alHeapAlloc macro expansion. 16-aligned bump of hp->cur, bounded by base+len. |
| 80020300 | `alCopy` | `func_80020300` | libaudio | audio/copy.c | exact | Score 0 (12). Byte-copy loop. Called by alLoadParam and by the second audio copy's n_alLoadParam. |
| 80020340 | `alSynNew` | `initObjectNodeLists` | libaudio | audio/synthesizer.c | exact | Score 0 (179). Its call sequence matches the source exactly: alHeapDBAlloc, alSaveNew, alAuxBusNew, alMainBusNew, alSynAllocFX or alMainBusParam, then per voice alLink, alLoadNew, alLoadParam, alResampleNew, alResampleParam, alEnvmixerNew, alEnvmixerParam, alAuxBusParam, and finally alSaveParam. |
| 8002060C | `alAudioFrame` | `func_8002060C` | libaudio | audio/synthesizer.c | exact | Score 0 (108). Calls __nextSampleTime, _timeToSamplesNoRound and _collectPVoices, and uses alGlobals. |
| 800207BC | `__allocParam` | `func_800207BC` | libaudio | audio/synthesizer.c | exact | Score 0 (11). Pops alGlobals->drvr.paramList (ALSynth +0x2C). Its byte twin __n_allocParam belongs to the second audio copy. |
| 800207E8 | `__freeParam` | `func_800207E8` | libaudio | audio/synthesizer.c | exact | Score 0 (6). Pushes onto paramList (+0x2C). alEnvmixerPull calls it. Its byte twin _n_freeParam belongs to the second audio copy. |
| 80020800 | `_collectPVoices` | `func_80020800` | libaudio | audio/synthesizer.c | exact | Score 0 (21), against 9 for _freePVoice. Operands: while (pLameList.next at +0x14) it calls alUnlink, then alLink to &pFreeList (+4). alAudioFrame calls it. |
| 80020854 | `_freePVoice` | `func_80020854` | libaudio | audio/synthesizer.c | exact | Score 0 (16). Calls alUnlink(pv), then alLink(pv, &drvr->pLameList (+0x14)). alEnvmixerPull calls it. |
| 80020894 | `_timeToSamplesNoRound` | `func_80020894` | libaudio | audio/synthesizer.c | exact | Score 0 (17). Computes (s32)(micros * outputRate(+0x44) / 1e6 + 0.5) with no '& ~0xF'; alAudioFrame calls it. |
| 800208DC | `_timeToSamples` | `func_800208DC` | libaudio | audio/synthesizer.c | exact | Score 0 (19) at -O3 (-O2 gives 19 differences), with NoRound inlined. What separates it from NoRound is the trailing '& ~0xF' (both add 0.5). No callers in main. |
| 80020928 | `__nextSampleTime` | `func_80020928` | libaudio | audio/synthesizer.c | exact | Score 0 (42) on I. With asserts, J/K/L differ by 1 (the assert line); with NDEBUG they differ by 38. Static function; alAudioFrame calls it. |
| 800209D0 | `alSynDelete` | `func_800209D0` | libaudio | audio/syndelete.c | exact | 2 instructions: drvr->head(+0) = 0. The proof is the call graph: its only caller is alClose, and it sits after synthesizer.o, matching the archive order (syndelete.o follows synthesizer.o). |
| 800209E0 | `alSynAllocFX` | `func_800209E0` | libaudio | audio/synallocfx.c | exact | Score 0 (37). Calls alFxNew, alFxParam(SET_SOURCE) and alMainBusParam(ADD_SOURCE). alSynNew calls it. |
| 80020A80 | `osAiGetLength` | `func_80020A80` | libultra | io/aigetlen.c | exact | Score 0 (4). The operand decides it: it reads 0xA4500004 (AI_LEN_REG). __amHandleFrameMsg calls it. |
| 80020A90 | `osAiGetStatus` | `func_80020A90` | libultra | io/aigetstat.c | exact | Score 0 (4). The operand decides it: it reads 0xA450000C (AI_STATUS_REG). __amHandleFrameMsg calls it. |
| 80020AA0 | `osAiSetNextBuffer` | `func_80020AA0` | libultra | io/aisetnextbuf.c | exact | Score 0 (37) on I (and G/H). J, K and L give 21 at both -O2 and -O3, because the source changed. Calls __osAiDeviceBusy and osVirtualToPhysical; uses hdwrBugFlag (D_80037520) and AI_DRAM_ADDR_REG. |
| 80020B40 | `osSpTaskLoad` | `loadRspTask` | libultra | io/sptask.c | exact | ul.py 0 at -O3 in I/J/K/L (O2 gives 93), rerun by checker; static _VirtualToPhysicalTask inlined; callees bcopy, osVirtualToPhysical x7, osWritebackDCache, __osSpSetStatus(0x2B00), __osSpSetPc, __osSpRawStartDma x2, __osSpDeviceBusy (__osSpDeviceBusy = SP_STATUS&0x1C) |
| 80020D4C | `osSpTaskStartGo` | `func_80020D4C` | libultra | io/sptask.c | exact | 0 in all versions; loops on __osSpDeviceBusy (__osSpDeviceBusy reads 0xA4040010 & 0x1C), then __osSpSetStatus(0x125 = SP_SET_INTR_BREAK\|SP_CLR_SSTEP\|SP_CLR_BROKE\|SP_CLR_HALT); callers renderTaskThread/rspTaskThread |
| 80020D80 | `osSpTaskYield` | `func_80020D80` | libultra | io/sptaskyield.c | exact | 7 instructions, 0 in all versions; only call is __osSpSetStatus(__osSpSetStatus writes 0xA4040010) with 0x400 = SP_SET_YIELD; caller rspTaskThread |
| 80020DA0 | `osSpTaskYielded` | `func_80020DA0` | libultra | io/sptaskyielded.c | exact | 0 in all versions; __osSpGetStatus (__osSpGetStatus returns 0xA4040010), tests SP_STATUS_YIELD 0x80 / YIELDED 0x100, sets tp->flags(+4) \|= r and clears OS_TASK_DP_WAIT (2) |
| 80020DF0 | `osViGetCurrentFramebuffer` | `func_80020DF0` | libultra | io/vigetcurrframebuf.c | exact | 0, ties with osViGetNextFramebuffer; resolved by operand: asm loads __osViCurr (0x80038890, the pointer __osViSwapContext sets to the just-programmed context and __osViInit sets to vi[0])->framep(+4) |
| 80020E30 | `osViGetNextFramebuffer` | `func_80020E30` | libultra | io/vigetnextframebuf.c | exact | 0, tie with osViGetCurrentFramebuffer resolved by operand: asm loads __osViNext (0x80038894)->framep(+4) |
| 80020E70 | `osViSetEvent` | `func_80020E70` | libultra | io/visetevent.c | exact | 0 in all versions; stores __osViNext->msgq(+0x10), msg(+0x14), retraceCount(+2, s16) with interrupts disabled |
| 80020ED0 | `osViSetMode` | `func_80020ED0` | libultra | io/visetmode.c | exact | 0 in all versions; __osViNext->modep(+8)=mode, state=VI_STATE_MODE_UPDATED(1), control(+0xC)=modep->comRegs.ctrl(+4) |
| 80020F20 | `osViSetSpecialFeatures` | `setViSpecialFeatures` | libultra | io/visetspecial.c | exact | 89 instructions, 0 in I/J/K/L at O2 and O3; only global is __osViNext, between __osDisableInt/__osRestoreInt |
| 80021090 | `osViSetYScale` | `func_80021090` | libultra | io/visetyscale.c | exact | 0; f32 store to __osViNext->y.factor(+0x24), state \|= VI_STATE_YSCALE_UPDATED(4) |
| 800210E0 | `osViSwapBuffer` | `func_800210E0` | libultra | io/viswapbuf.c | exact | 0; __osViNext->framep(+4)=arg, state \|= VI_STATE_BUFFER_UPDATED(0x10) |
| 80021130 | `osViBlack` | `func_80021130` | libultra | io/viblack.c | exact | 0 (I/J), osViRepeatLine scores 2 even with masking: it toggles bit 0x20 (andi 0xFFDF) = VI_STATE_BLACK, which __osViSwapContext uses to zero hStart; 0x40 would be REPEATLINE |
| 80021190 | `osContStartQuery` | `func_80021190` | libultra | io/contquery.c | exact | 0; __osSiGetAccess, __osContLastCmd(D_8007BD30) check, __osPackRequestData(80021480), __osSiRawStartDma(W), osRecvMesg, __osSiRawStartDma(R), __osSiRelAccess on __osContPifRam(D_8006A260); osContStartReadData (7) would call __osPackReadData |
| 80021210 | `osContGetQuery` | `func_80021210` | libultra | io/contquery.c | exact | 8 instructions, 0; only call is __osContGetInitData(800213CC) with a stack bitpattern; caller func_80003E78 also calls osContStartQuery |
| 80021230 | `osContInit` | `initializeControllers` | libultra | io/controller.c | exact | 0 in all versions; osGetTime, osCreateMesgQueue, osSetTimer, osRecvMesg, __osPackRequestData, __osSiRawStartDma x2, __osContGetInitData, __osSiCreateAccessQueue(800276F0), osCreateMesgQueue; uses __osContinitialized(D_80037530), __osMaxControllers(D_80070A98) |
| 800213CC | `__osContGetInitData` | `func_800213CC` | libultra | io/controller.c | exact | 0, ties with __osPfsGetInitData; resolved by operand: reads __osContPifRam (D_8006A260, used by osContStartQuery/osContInit/osContGetReadData) and is called by osContInit/osContGetQuery |
| 80021480 | `__osPackRequestData` | `func_80021480` | libultra | io/controller.c | exact | 0 (the next candidate, __osPfsRequestData, scores 20); zeroes __osContPifRam ramarray, pifstatus D_8006A29C (=D_8006A260+0x3C)=1, rxsize 3 + cmd arg; called by osContInit/osContStartQuery |
| 80021540 | `osContSetCh` | `func_80021540` | libultra | io/contsetch.c | exact | 0; __osSiGetAccess, writes __osMaxControllers(D_80070A98) and __osContLastCmd(D_8007BD30)=0xFE, __osSiRelAccess |
| 800215A0 | `osPfsInit` | `func_800215A0` | libultra | io/pfsinit.c | exact | 0 in all versions; __osSiGetAccess, __osPfsGetStatus, __osSiRelAccess, __osGetId, osPfsChecker |
| 80021640 | `osPfsGetLabel` | `func_80021640` | libultra | io/pfsgetlabel.c | exact | 0; only call is __osCheckId, then copies pfs->label |
| 800216D0 | `osPfsIsPlug` | `resetControllers` | libultra | io/pfsisplug.c | exact | 0; __osSiGetAccess, __osPfsRequestData(8002184C), __osSiRawStartDma/osRecvMesg x2, __osPfsGetInitData(800218F0), __osSiRelAccess; uses __osPfsPifRam(D_8007DFD0) |
| 8002184C | `__osPfsRequestData` | `func_8002184C` | libultra | io/pfsisplug.c | exact | 0 (__osPackRequestData scores 20); fills __osPfsPifRam(D_8007DFD0) and pifstatus(D_8007E00C = +0x3C), sets __osContLastCmd; called only by osPfsIsPlug |
| 800218F0 | `__osPfsGetInitData` | `func_800218F0` | libultra | io/pfsisplug.c | exact | 0, tie with __osContGetInitData resolved by operand: reads __osPfsPifRam(D_8007DFD0) and is called only by osPfsIsPlug |
| 800219B0 | `osEPiStartDma` | `func_800219B0` | libultra | io/epidma.c | exact | 0 (osPiStartDma scores 21); checks __osPiDevMgr.active(D_80037600), then osPiGetCmdQueue + osJamMesg / osSendMesg |
| 80021A50 | `osEPiLinkHandle` | `func_80021A50` | libultra | io/epilinkhandle.c | exact | 17 instructions, 0 (I/J); handle->next=__osPiTable(D_8003761C, also linked by osCartRomInit/osDriveRomInit); __osPiTable=handle; between __osDisableInt/__osRestoreInt; returns 0 |
| 80021AA0 | `osCartRomInit` | `initControllerPakDescriptor` | libultra | io/cartrominit.c | exact | 0 for the 2.0I code only (J/K/L: 72, rerun by checker); pre-J body: returns early if baseAddress==0xB0000000, osPiRawReadIo, bzero, links into __osPiTable(D_8003761C); handle CartRomHandle=D_8007E198 |
| 80021B80 | `osDriveRomInit` | `func_80021B80` | libultra | io/driverominit.c | exact | 0 in I/J/K/L; bzero, links __DriveRomHandle(D_80065128) into __osPiTable(D_8003761C) with interrupts disabled |
| 80021C40 | `bcopy` | `func_80021C40` | libultra (libc) | libc/bcopy.s | asm-identified | hand-written asm; the file's explanation comment names libultra bcopy (src/libc/bcopy.s); 66 call sites |
| 80021F60 | `bzero` | `func_80021F60` | libultra (libc) | libc/bzero.s | asm-identified | hand-written asm; the file's explanation comment names libultra bzero (src/libc/bzero.s) |
| 80022000 | `osAiSetFrequency` | `func_80022000` | libultra | io/aisetfreq.c | exact | 0 for J/K/L (I: 19, because I also writes AI_CONTROL_REG); uses osViClock(D_80038808) |
| 80022120 | `__osSumcalc` | `func_80022120` | libultra | io/contpfs.c | exact | 13 instructions, 0 for J/K/L (I: 10, masks inside the loop); only caller is osPfsReFormat (twice, inode checksum), which matches J pfsreformat.c |
| 80022154 | `__osIdCheckSum` | `func_80022154` | libultra | io/contpfs.c | exact | 0 in all versions; only caller osPfsInitPak, right after reading PFS_ID_0AREA (inlined into __osCheckPackId at -O3) |
| 80022198 | `__osRepairPackId` | `func_80022198` | libultra | io/contpfs.c | modified | J/K/L -O3 score 1: only diff is li v0,10 vs 11, i.e. the pre-J '#else return PFS_ERR_ID_FATAL' branch at contpfs.c:135 instead of J's PFS_ERR_DEVICE. 2.0I_patch code, not a game change. Calls osGetCount, __osPfsSelectBank, __osContRamRead/Write; callers osPfsInitPak, __osGetId |
| 80022484 | `__osCheckPackId` | `func_80022484` | libultra | io/contpfs.c | exact | 0 for J/K/L at -O3 only (O2: 36, I: 15); __osPfsSelectBank, __osContRamRead, __osContRamWrite; callers osPfsInitPak, __osGetId |
| 800225E8 | `__osGetId` | `readControllerPakId` | libultra | io/contpfs.c | exact | 0 for J/K/L -O3 (I: 11); __osPfsSelectBank, __osContRamRead, __osCheckPackId, __osRepairPackId x2, bcopy; callers osPfsInit, osPfsRepairId, osPfsChecker, osPfsReFormat |
| 800227B4 | `__osCheckId` |  | libultra | io/contpfs.c | exact | 0 for J/K/L (I: 23); already correctly named; __osPfsSelectBank, __osContRamRead x2, bcmp |
| 8002286C | `__osPfsRWInode` | `readWriteControllerPakInode` | libultra | io/contpfs.c | exact | 0 for J/K/L -O3 (I: 139, rerun); J inode cache globals __osPfsInodeCacheChannel(D_800375E0)/Bank(D_800375E4)/__osPfsInodeCache(D_8007DDB8) |
| 80022BB0 | `__osContRamRead` |  | libultra | io/contramread.c | modified | J score 57; 0 at O2 and O3 once ptr=&__osPfsPifRam moves from the start of the retry loop to its declaration, i.e. the pre-J retry behaviour. 2.0I_patch code; already named; uses __osPfsPifRam D_8007DFD0 |
| 80022DB0 | `__osContRamWrite` |  | libultra | io/contramwrite.c | modified | J score 55; 0 at O2 and O3 with the same edit: ptr=__osPfsPifRam.ramarray in the declaration, not reset each retry. 2.0I_patch; already named |
| 80022FD0 | `osContStartReadData` | `func_80022FD0` | libultra | io/contreaddata.c | exact | 0 (osContStartQuery scores 7); __osSiGetAccess, __osPackReadData(800230F4), __osSiRawStartDma, osRecvMesg, __osSiRawStartDma, __osSiRelAccess |
| 80023058 | `osContGetReadData` | `func_80023058` | libultra | io/contreaddata.c | exact | 0 (next candidate scores 17); leaf that reads __osContPifRam(D_8006A260) for __osMaxControllers(D_80070A98) entries; caller func_80003E78 |
| 800230F4 | `__osPackReadData` | `packControllerReadCommands` | libultra | io/contreaddata.c | exact | 0 (__osPackRequestData scores 21); fills __osContPifRam with CONT_CMD_READ_BUTTON; only caller osContStartReadData |
| 800231B0 | `__osContAddressCrc` | `calculateControllerPakAddressCrc` | libultra | io/crc.c | exact | 0 for J/K/L (I: 27); called by __osContRamRead/Write on the address, and by osMotorInit |
| 8002321C | `__osContDataCrc` | `calculateControllerPakDataCrc` | libultra | io/crc.c | exact | 0 for J/K/L (I: 29); called only by __osContRamRead/Write on the 32-byte data block |
| 800232A0 | `__osMotorAccess` | `writeControllerPakBank` | libultra | io/motor.c | exact | 0 for J/K/L (I has osMotorStart/Stop instead); __osSiGetAccess, __osSiRawStartDma/osRecvMesg x2, __osSiRelAccess on __MotorDataBuf (gControllerPakBankBuffers) |
| 800233E4 | `osMotorInit` | `readWriteControllerPakBank` | libultra | io/motor.c | exact | 0 for J/K/L -O3 (O2: 103, I: 234, rerun); __osPfsSelectBank x3, __osContRamRead x2, __osContAddressCrc (inlined _MakeMotorData); builds __MotorDataBuf |
| 80023630 | `osPfsAllocateFile` |  | libultra | io/pfsallocatefile.c | exact | 0 for J/K/L (I: 141); already named; osPfsFindFile, osPfsFreeBlocks, __osPfsRWInode, __osPfsDeclearPage, bcopy, __osContRamWrite |
| 8002393C | `__osPfsDeclearPage` |  | libultra | io/pfsallocatefile.c | exact | 0 for J/K/L (I: 99); already named; only caller osPfsAllocateFile |
| 80023A60 | `osPfsChecker` |  | libultra | io/pfschecker.c | exact | 0 for J/K/L (I: 129); already named; __osCheckId, __osGetId, corrupted_init, __osPfsRWInode, corrupted, bzero, __osPfsSelectBank |
| 80023EC0 | `corrupted_init` |  | libultra | io/pfschecker.c | exact | 0 for the 2.0I code; J/K/L give 1 (andi 0xff in ROM vs J's andi 0x7f): the game lacks J's (page & 0x7F) mask. Static function, already named; calls __osPfsRWInode; only caller osPfsChecker |
| 80024018 | `corrupted` | `countControllerPakPageReferences` | libultra | io/pfschecker.c | exact | 0 in I/J/K/L; static corrupted() from pfschecker.c, keeps its source name; only caller osPfsChecker; calls __osPfsRWInode |
| 80024180 | `osPfsDeleteFile` | `deleteControllerPakFile` | libultra | io/pfsdeletefile.c | exact | 0 for J/K/L (I: 97); osPfsFindFile, __osPfsSelectBank, __osContRamRead, __osPfsRWInode, __osPfsReleasePages, bzero, __osContRamWrite |
| 8002432C | `__osPfsReleasePages` |  | libultra | io/pfsdeletefile.c | exact | 0 for J/K/L (I: 107, older 7-arg signature); already named; only caller osPfsDeleteFile |
| 800243A0 | `osPfsFileState` |  | libultra | io/pfsfilestate.c | modified | J score 4; 0 at O2/O3 once the J tail 'ret=__osPfsGetStatus(...);return ret;' is replaced by pre-J 'return 0;'. 2.0I_patch code; already named |
| 80024530 | `osPfsFreeBlocks` | `getControllerPakFreeBytes` | libultra | io/pfsfreeblocks.c | exact | 0 for J/K/L (I: 3); __osCheckId, __osPfsRWInode; called by osPfsAllocateFile |
| 80024640 | `__osPfsGetStatus` | `func_80024640` | libultra | io/pfsgetstatus.c | exact | 0 for J/K/L (I: 6); __osPfsRequestOneChannel, __osSiRawStartDma/osRecvMesg x2, __osPfsGetOneChannelData; resets __osPfsInodeCacheBank(D_800375E4); called by osPfsInit/InitPak/ReFormat/__osContRamRead/Write |
| 80024730 | `__osPfsRequestOneChannel` | `func_80024730` | libultra | io/pfsgetstatus.c | exact | 0 for J/K/L (I: 9); fills __osPfsPifRam pifstatus(D_8007E00C), sets __osContLastCmd(D_8007BD30); only caller __osPfsGetStatus |
| 800247C4 | `__osPfsGetOneChannelData` | `func_800247C4` | libultra | io/pfsgetstatus.c | exact | 0 in all versions; reads __osPfsPifRam(D_8007DFD0); only caller __osPfsGetStatus |
| 80024850 | `osPfsInitPak` | `func_80024850` | libultra | io/pfsinitpak.c | modified | J score 6; 0 at O2/O3 after deleting ERRCK(__osPfsCheckRamArea(pfs)) (a J addition). Otherwise J code (PFS_ID_BROKEN, bcopy). 2.0I_patch; callees __osSiGetAccess, __osPfsGetStatus, __osSiRelAccess, __osPfsSelectBank, __osContRamRead, __osIdCheckSum, __osCheckPackId, __osRepairPackId, bcopy, osPfsChecker |
| 80024A40 | `osPfsNumFiles` | `func_80024A40` | libultra | io/pfsnumfiles.c | modified | J score 21 (I: 31); 0 at O2/O3 once the J tail __osPfsGetStatus return is replaced by 'return 0;'. 2.0I_patch; __osCheckId, __osPfsSelectBank, __osContRamRead |
| 80024B40 | `osPfsReadWriteFile` | `readWriteControllerPakFile` | libultra | io/pfsreadwritefile.c | modified | J -O3 score 8; 0 at -O3 (O2 154) once the final 'ret=__osPfsGetStatus(...);return ret;' becomes pre-J 'return 0;'. 2.0I_patch |
| 80024F80 | `osPfsReFormat` |  | libultra | io/pfsreformat.c | exact | 0 for J/K/L (I: 29); already named; calls __osSiGetAccess/RelAccess, __osPfsGetStatus, __osGetId, __osPfsSelectBank, __osContRamWrite, __osSumcalc x2 |
| 80025280 | `osPfsRepairId` | `func_80025280` | libultra | io/pfsrepairid.c | exact | 22 instructions, 0 for J/K/L (I: 104); only call is __osGetId |
| 800252E0 | `osPfsFindFile` | `findControllerPakFile` | libultra | io/pfssearchfile.c | modified | J score 31 (I: 16); 0 at O2 and O3 once J's per-entry ERRCK(__osPfsGetStatus) after __osContRamRead is removed. 2.0I_patch; callees __osCheckId, __osContRamRead |
| 80025480 | `__osPfsSelectBank` | `func_80025480` | libultra | io/pfsselectbank.c | exact | 0 for J/K/L; J signature (pfs, bank) writes the bank byte with __osContRamWrite to 0x8000/32; called by every pfs function and osMotorInit |
| 800254F0 | `osPfsSetLabel` | `func_800254F0` | libultra | io/pfssetlabel.c | exact | 0 for J/K/L (I: 25); __osCheckId, __osPfsSelectBank, __osContRamWrite(PFS_LABEL_AREA) |
| 800255B0 | `osCreatePiManager` | `createPiManager` | libultra | io/pimgr.c | modified | I-O3 and J-O3 both score 23; an edited copy (one extra call createSpeedParam() after the active check) scores 0. Globals __osPiDevMgr D_80037600 (dma=osPiRawStartDma, edma=osEPiRawStartDma, acsQueue=D_80073E98). Callees osCreateMesgQueue, __osPiCreateAccessQueue (__osPiCreateAccessQueue when D_800389A0==0), osSetEventMesg, osGetThreadPri, osCreateThread(__osDevMgrMain) |
| 80025750 | `createSpeedParam` | `cachePiDomainTimings` | libultra | os/initialize.c | modified | J createSpeedParam scores 2. replacing its two stores __Dom1/2SpeedParam.type=7 with .domain=0/.domain=1 gives score 0. The real operands agree: DOM1/DOM2 LAT->+5 latency, PGS->+6 pageSize, RLS->+7 relDuration, PWD->+8 pulse, +9 domain, on the 2.0I handles D_8007DEB8/D_80070AA0, which are the initial data of __osCurrentHandle D_80037620 = {CartRomHandle, LeoDiskHandle}. Only caller is osCreatePiManager, not osInitialize |
| 80025810 | `__osSiRawStartDma` | `func_80025810` | libultra | io/sirawdma.c | exact | J score 0, I score 21 (the I version has an assert and calls __osSiDeviceBusy). Reads SI_STATUS 0xA4800018&3 directly; SI_DRAM_ADDR, PIF_RD64B/WR64B; osWritebackDCache/osVirtualToPhysical/osInvalDCache. Callers are controller/pak code |
| 800258C0 | `osCreateViManager` | `createViManager` | libultra | io/vimgr.c | exact | J score 0, I score 2. The difference is the J store __additional_scanline=0 (D_8003764C, which __osViSwapContext also reads). Calls __osTimerServicesInit __osTimerServicesInit, events VI/COUNTER, thread viMgrMain viMgrMain, __osViInit __osViInit |
| 80025A60 | `viMgrMain` | `func_80025A60` | libultra | io/vimgr.c | exact | Score 0 in every version. Static thread entry of osCreateViManager. Uses __osViSwapContext, __osViGetCurrentContext, __osTimerInterrupt, osGetCount, D_80070480/D_80070B20/D_80065120 |
| 80025C00 | `__osViSwapContext` |  | libultra | io/viswapcontext.c | exact | Score 0 for J/K, I scores 68: it uses the J vStart computation with __additional_scanline D_8003764C. Already named |
| 80025F10 | `osAfterPreNMI` | `func_80025F10` | libultra | os/afterprenmi.c | exact | Score 0 in every version, 7 instructions: returns __osSpSetPc(0) (__osSpSetPc writes SP_PC 0xA4080000 when HALT). Caller func_800032FC (pre-NMI handler) |
| 80025F30 | `__osExceptionPreamble` | `func_80025F30` | libultra | os/exceptasm.s | asm-identified | From the asm comment (2.0I _FINALROM exceptasm.s). The symbol at this address is __osExceptionPreamble, the 4-instruction lui/addiu k0,+0x10; jr k0 stub that osInitialize copies to 0x80000000/80/100/180 as *__osExceptionPreamble. __osException proper is the unlabelled body at +0x10 (80025F40). Uses __osThreadSave D_8006A0B0, __osRunningThread D_80037250, __OSGlobalIntMask D_80038810 |
| 800264BC | `send_mesg` | `func_800264BC` | libultra | os/exceptasm.s | asm-identified | From the asm comment: static LEAF(send_mesg) of exceptasm.s. Posts an event from __osEventStateTab D_8007DF30 and returns through $s2 |
| 80026578 | `handle_CpU` | `func_80026578` | libultra | os/exceptasm.s | asm-identified | From the asm comment: handle_CpU of exceptasm.s (lazy FPU enable for Cause code 11). ultralib defines it as its own LEAF(handle_CpU) between send_mesg and __osEnqueueAndYield, which is exactly where it sits here |
| 800265AC | `__osEnqueueAndYield` | `func_800265AC` | libultra | os/exceptasm.s | asm-identified | From the asm comment. Callers osRecvMesg/osSendMesg/osJamMesg/osStartThread/osSetThreadPri/osYieldThread |
| 800266B4 | `__osEnqueueThread` | `func_800266B4` | libultra | os/exceptasm.s | asm-identified | From the file comment: priority insert into __osRunQueue D_80037248. It is LEAF(__osEnqueueThread) in ultralib exceptasm.s, in the same order |
| 800266FC | `__osPopThread` | `func_800266FC` | libultra | os/exceptasm.s | asm-identified | Byte-for-byte the 4 instructions of exceptasm.s __osPopThread (lw v0; lw t9; jr; sw t9). The K-only __osNop correctly does not follow it |
| 8002670C | `__osDispatchThread` | `func_8002670C` | libultra | os/exceptasm.s | asm-identified | From the asm comment: __osDispatchThread, with __osCleanupThread (move a0,zero; jal osDestroyThread) folded in at +0x17C |
| 800268A0 | `osInitialize` | `initializePiAndRdram` | libultra | os/initialize.c | modified | I-O3 14, J 19. an edited copy (adds the J osUnmapTLBAll() before osMapTLBRdb and the J AI_CONTROL/DACRATE/BITRATE writes) scores 0. It has no __osGetCause wait and no createSpeedParam call. Uses osPiRawReadIo(4,&clock), osClockRate D_80038800*3/4 via __udivdi3, osViClock D_80038808 |
| 80026AF0 | `osGetCount` | `func_80026AF0` | libultra | os/getcount.s | asm-identified | From the asm comment: mfc0 Count |
| 80026B00 | `__osGetSR` | `func_80026B00` | libultra | os/getsr.s | asm-identified | From the asm comment: mfc0 Status. Caller osInitialize |
| 80026B10 | `__osDisableInt` | `nw2DisableInterrupts` | libultra | os/interrupt.s | asm-identified | From the asm comment: the 2.0I form, without __OSGlobalIntMask handling |
| 80026B30 | `__osRestoreInt` | `nw2RestoreInterrupts` | libultra | os/interrupt.s | asm-identified | From the asm comment |
| 80026B50 | `__osProbeTLB` | `func_80026B50` | libultra | os/probetlb.s | asm-identified | From the asm comment. Only caller osVirtualToPhysical osVirtualToPhysical |
| 80026C10 | `__osSetFpcCsr` | `func_80026C10` | libultra | os/setfpccsr.s | asm-identified | From the asm comment. osInitialize passes 0x01000800 |
| 80026C20 | `__osSetSR` | `func_80026C20` | libultra | os/setsr.s | asm-identified | From the asm comment |
| 80026C30 | `osUnmapTLBAll` | `func_80026C30` | libultra | os/unmaptlball.s | asm-identified | From the asm comment, identical to unmaptlball.s |
| 80026C80 | `osMapTLBRdb` | `func_80026C80` | libultra | os/maptlbrdb.s | asm-identified | From the asm comment, identical to maptlbrdb.s |
| 80026CE0 | `osDestroyThread` | `func_80026CE0` | libultra | os/destroythread.c | exact | I score 0, J score 10. Uses __osActiveQueue D_8003724C, __osRunningThread D_80037250, __osDequeueThread __osDequeueThread, __osDispatchThread. __osCleanupThread jals it |
| 80026DB0 | `osGetThreadPri` | `func_80026DB0` | libultra | os/getthreadpri.c | exact | Score 0, tied with osGetThreadId. Checked: it reads offset 4 = OSThread.priority (id is at 0x14); NULL means __osRunningThread D_80037250. Callers osCreatePiManager/osCreateViManager use it for myPri |
| 80026DD0 | `osGetTime` | `func_80026DD0` | libultra | os/gettime.c | exact | Score 0 in every version. Returns __osCurrentTime D_80070B20 + (osGetCount - __osBaseCounter D_80065120) under __osDisableInt. Caller osContInit |
| 80026E60 | `osJamMesg` | `func_80026E60` | libultra | os/jammesg.c | exact | Score 0 (osSendMesg 17). first=(first+msgCount-1)%msgCount, __osEnqueueAndYield when full, __osPopThread/osStartThread. Callers osPiStartDma/osEPiStartDma (osEPiStartDma/osPfsGetLabel) with osPiGetCmdQueue |
| 80026FA0 | `osSetTimer` | `func_80026FA0` | libultra | os/settimer.c | exact | Score 0 for I/J (not K). Uses __osTimerList g_80038820, __osInsertTimer, __osSetTimerIntr. Caller osContInit |
| 80027040 | `__osTimerServicesInit` | `func_80027040` | libultra | os/timerintr.c | exact | Score 0 in every version. Zeroes __osCurrentTime/__osBaseCounter/__osViIntrCount and the __osTimerList node. First call in osCreateViManager |
| 80027094 | `__osTimerInterrupt` | `handleTimerInterrupt` | libultra | os/timerintr.c | exact | Score 0 in every version. Uses __osTimerList, __osTimerCounter D_8007BD60, __osSetCompare(0), osSendMesg, __osInsertTimer. Called from viMgrMain |
| 800271D0 | `__osSetTimerIntr` | `programTimerCountdown` | libultra | os/timerintr.c | exact | Score 0 for I/J. __osTimerCounter=osGetCount(), then __osSetCompare(count+tim) |
| 80027230 | `__osInsertTimer` | `insertTimer` | libultra | os/timerintr.c | exact | Score 0 in every version. Sorted delta insert into __osTimerList |
| 80027340 | `__osAiDeviceBusy` | `ai_is_busy` | libultra | io/ai.c | exact | Score 0. Checked: it reads AI_STATUS 0xA450000C and tests the sign bit (AI_STATUS_FIFO_FULL). Callers are the audio DMA code |
| 80027360 | `__osSpDeviceBusy` | `func_80027360` | libultra | io/sp.c | exact | Score 0, tied with Pi/Dp. Checked operand SP_STATUS 0xA4040010 & 0x1C. Caller __osSpRawStartDma |
| 80027380 | `__osSpGetStatus` | `func_80027380` | libultra | io/spgetstat.c | exact | Score 0, tied with osPiGetStatus/osViGetCurrentLine. Checked: it returns *(SP_STATUS 0xA4040010) |
| 80027390 | `__osSpSetStatus` | `func_80027390` | libultra | io/spsetstat.c | exact | Score 0. Checked: it writes SP_STATUS 0xA4040010. Callers include osSpTaskLoad |
| 800273A0 | `__osSpSetPc` | `func_800273A0` | libultra | io/spsetpc.c | exact | Score 0. If SP_STATUS & HALT it writes SP_PC 0xA4080000, else returns -1. Called by osAfterPreNMI(0) |
| 800273D0 | `__osSpRawStartDma` | `func_800273D0` | libultra | io/sprawdma.c | exact | Score 0 for 2.0I only. Asserts at lines 0x3A/0x3B with "EX"/"sprawdma.c" (D_8003B970/D_8003B974, checked in ROM) and __assert __assert. Calls __osSpDeviceBusy. Caller osSpTaskLoad |
| 800274D0 | `__osViInit` | `func_800274D0` | libultra | io/vi.c | exact | Score 0 in every version. bzero of the vi contexts, sets __osViCurr/__osViNext, osTvType D_80000300 picks the mode, calls __osViSwapContext. Called from osCreateViManager |
| 800275E0 | `__osViGetCurrentContext` | `func_800275E0` | libultra | io/vigetcurrcontext.c | exact | Score 0, tied with __osGetActiveQueue/__osGetCurrFaultedThread. Checked: it returns __osViCurr. Caller viMgrMain |
| 800275F0 | `__osSiRawReadIo` | `func_800275F0` | libultra | io/sirawread.c | exact | Score 0 for 2.0I, tied with __osSpRawReadIo. Checked: the assert file string at D_8003B984 is "sirawread.c", and it calls __osSiDeviceBusy __osSiDeviceBusy. Caller osInitialize (PIF 0x1FC007FC) |
| 80027680 | `__osSiRawWriteIo` | `func_80027680` | libultra | io/sirawwrite.c | exact | Score 0 for 2.0I. Checked: the assert string at D_8003B994 is "sirawwrite.c". Calls __osSiDeviceBusy. Caller osInitialize (pifdata\|8) |
| 800276F0 | `__osSiCreateAccessQueue` | `func_800276F0` | libultra | io/siacs.c | exact | Score 0, tied with __osPiCreateAccessQueue. Globals D_800388A0/D_8007E210, used only by the SI/controller code. Caller osContInit. The PI copy is __osPiCreateAccessQueue, which osCreatePiManager calls |
| 80027744 | `__osSiGetAccess` | `func_80027744` | libultra | io/siacs.c | exact | Score 0 at O3, tied with __osPiGetAccess. SI globals D_800388A0/D_8007E210. Callers __osContRamRead/__osContRamWrite/osPfsReFormat/osPfsIsPlug and other controller code |
| 800277B0 | `__osSiRelAccess` | `func_800277B0` | libultra | io/siacs.c | exact | Score 0, tied with __osPiRelAccess. Does osSendMesg(&__osSiAccessQueue D_8007E210,0,NOBLOCK). Same controller callers as __osSiGetAccess |
| 800277E0 | `osPiRawReadIo` | `func_800277E0` | libultra | io/pirawread.c | exact | Score 0 for 2.0I only. Checked: assert line 0x3D with "pirawread.c" at D_8003B9A8. This is the 2.0I name (piint.h #define; J renamed it __osPiRawReadIo). Callers osInitialize, osCartRomInit |
| 80027880 | `osPiRawStartDma` | `startPiRawDma` | libultra | io/pirawdma.c | exact | Score 0 for I and J (same code). The 2.0I name osPiRawStartDma is used to agree with the I-only osPiRawReadIo/osEPiRaw* rows. osCreatePiManager stores it as __osPiDevMgr.dma |
| 80027950 | `osPiGetCmdQueue` | `func_80027950` | libultra | io/pigetcmdq.c | exact | Score 0. Checked: returns __osPiDevMgr.active ? cmdQueue (+8, D_80037608) : NULL. Callers osPiStartDma/osEPiStartDma (osEPiStartDma/osPfsGetLabel) |
| 80027970 | `osEPiRawStartDma` | `startPiDmaWithHandle` | libultra | io/epirawdma.c | exact | Score 0 for 2.0I (J __osEPiRawStartDma 22). Uses the I form of EPI_SYNC, which compares the __osCurrentHandle[domain] (D_80037620) pointer. osCreatePiManager stores it as __osPiDevMgr.edma |
| 80027B40 | `__osDevMgrMain` | `func_80027B40` | libultra | io/devmgr.c | exact | Score 0 in every version. Thread entry that osCreatePiManager starts with &__osPiDevMgr. Calls __osResetGlobalIntMask/__osSetGlobalIntMask/osYieldThread/osEPiRawReadIo/osEPiRawWriteIo |
| 80027F00 | `__osPiCreateAccessQueue` | `func_80027F00` | libultra | io/piacs.c | exact | Score 0. Checked: D_800389A0/D_80073E98, and osCreatePiManager installs D_80073E98 as __osPiDevMgr.acsQueue (D_80037610) and calls this when D_800389A0==0 |
| 80027F54 | `__osPiGetAccess` | `func_80027F54` | libultra | io/piacs.c | exact | Score 0 at O3. PI globals D_800389A0/D_80073E98. No callers in the ROM (linked but unused) |
| 80027FC0 | `__osPiRelAccess` | `func_80027FC0` | libultra | io/piacs.c | exact | Score 0. Does osSendMesg(&__osPiAccessQueue D_80073E98,0,NOBLOCK). No callers |
| 80027FF0 | `bcmp` |  | libultra (libc) | libc/bcmp.s | asm-identified | From the asm comment, src/libc/bcmp.s. Already named |
| 80028100 | `__osSetCompare` | `func_80028100` | libultra | os/setcompare.s | asm-identified | From the asm comment: mtc0 Compare |
| 80028110 | `__osResetGlobalIntMask` | `func_80028110` | libultra | os/resetglobalintmask.c | exact | Score 0. Does __OSGlobalIntMask D_80038810 &= ~(mask & ~0x401). Caller __osDevMgrMain |
| 80028160 | `__osSetGlobalIntMask` | `func_80028160` | libultra | os/setglobalintmask.c | exact | Score 0. __OSGlobalIntMask \|= mask. Caller __osDevMgrMain |
| 800281A0 | `osYieldThread` | `func_800281A0` | libultra | os/yieldthread.c | exact | Score 0. Sets __osRunningThread->state=2, then __osEnqueueAndYield(&__osRunQueue D_80037248) |
| 800281F0 | `__osSiDeviceBusy` | `func_800281F0` | libultra | io/si.c | exact | Score 0, tied with Pi/Dp. Checked operand SI_STATUS 0xA4800018 & 3. Callers __osSiRawReadIo/__osSiRawWriteIo |
| 80028210 | `osEPiRawReadIo` | `readPiHandleWord` | libultra | io/epirawread.c | exact | Score 0 for 2.0I (assert string "epirawread.c" at D_8003B9DC, checked; I form of EPI_SYNC: pointer compare and store into D_80037620[domain]). Caller __osDevMgrMain |
| 800283A0 | `osEPiRawWriteIo` | `writePiHandleWord` | libultra | io/epirawwrite.c | exact | Score 0 for 2.0I (J __osEPiRawWriteIo 24 because of EPI_SYNC). Caller __osDevMgrMain |
| 800284F4 | `unusedMuldi3` | `func_800284F4` | KMC | KMC GCC runtime | asm-identified | From the asm comment: 64x64 multiply in __muldi3 shape (odd word order), first routine of the KMC hand-written 64-bit runtime before __divdi3. Unreferenced dead code, so the name cannot be confirmed by a call site |
| 80028528 | `func_80028528` |  | KMC | KMC GCC runtime | unknown | From the asm comment: internal 64/64 shift-subtract divide helper of the KMC __udivdi3/__divdi3 family. It returns the remainder in a0:a1, outside the ABI. Real name unknown |
| 80028624 | `func_80028624` |  | KMC | KMC GCC runtime | unknown | From the asm comment: internal 64/32 divu divide helper (remainder in $t1, break 7 on zero). Real name unknown |
| 800286F0 | `__divdi3` |  | KMC | KMC GCC runtime | asm-identified | From the asm comment. Already named |
| 800287A0 | `__moddi3` |  | KMC | KMC GCC runtime | asm-identified | From the asm comment. Already named |
| 80028860 | `__udivdi3` | `func_80028860` | KMC | KMC GCC runtime | asm-identified | From the asm comment: unsigned 64-bit divide entry (j to the two helpers). osInitialize uses it for osClockRate*3/4, and __divdi3 tail-branches here |
| 80028880 | `__umoddi3` | `func_80028880` | KMC | KMC GCC runtime | asm-identified | From the asm comment: unsigned 64-bit remainder. __moddi3 tail-branches here |
| 800288C0 | `__fixsfdi` |  | KMC | KMC GCC runtime | asm-identified | From the asm comment. Already named |
| 800289B0 | `__floatdisf` | `signed64ToFloatTrunc` | KMC | KMC GCC runtime | asm-identified | From the asm comment: the (f32)s64 conversion, right after __fixsfdi in the same hand-written style. 12 call sites in calculateObjectVertexCentroid and func_800080A0 (the matched C calls it by name) |
| 8002BC40 | `rspbootTextStart` | `func_8002BC40` | RSP microcode | rsp/rspboot.s (SDK, not in the ultralib checkout) | asm-identified | From the asm comment: RSP code, not CPU code. Bytes 0-0xCF are rspboot (OSTask.ucode_boot, size D_8002BD10-rspbootTextStart=0xD0), then the audio microcode text starts at D_8002BD10 |

## Data

The SDK functions' global variables carry their SDK names too. They were found with `tools/uldata.py`: it compiles each
identified function's SDK source, lines its instructions up with the ROM function's, and every pair of aligned
instructions that refers to data on both sides says "SDK variable S is at address A" (statics are recovered from the
object's symbol table, offsets from the instruction immediates, since MIPS relocations keep the addend there). A name was
taken when an exact function voted for it or two votes agreed; where votes split, the majority won, and the few
single votes from changed functions were taken only with other evidence (osInitialize and osCreatePiManager are proven
by small edits, the libmus command table index by index, the boot variables sit at fixed addresses). The exception
handler's globals come from reading its assembly. Function-scope statics keep their source name without GCC's `.N`
suffix (`xseed`, `hdwrBugFlag`, `retrace`).

Only the start of each object is named. Code that reaches a field through its own symbol (for example `D_80037604`, a
field of `__osPiDevMgr`) still uses the automatic name; folding those into struct accesses would change the C.
Not named: `dtor` (guAlign's degrees-to-radians constant, three conflicting candidates), some libmus variables only the
changed MusInitialize touches, and the game's own data.

| VRAM | name | was | found through |
| :-- | :-- | :-- | :-- |
| 80000300 | `osTvType` | `D_80000300` | fixed boot variable 0x80000300 (MusInitialize, __osViInit, osInitialize) |
| 80000308 | `osRomBase` | `D_80000308` | fixed boot variable 0x80000308 (osPiRawReadIo, osPiRawStartDma) |
| 8000030C | `osResetType` | `D_8000030C` | fixed boot variable 0x8000030C (osInitialize) |
| 8000031C | `osAppNMIBuffer` | `D_8000031C` | fixed boot variable 0x8000031C (osInitialize) |
| 80036E80 | `jumptable` | `D_80036E80` | __MusIntGetNewNote; its 43 entries are the F* sequence commands in libmus 3.14 order |
| 80036F50 | `n_alGlobals` | `D_80036F50` | n_alClose, n_alInit |
| 80036F54 | `n_syn` | `D_80036F54` | __n_allocParam, _allocatePVoice, _n_collectPVoices, _n_freePVoice, _n_freeParam, _n_timeToSamples (+20 more) |
| 80036F60 | `SMALLROOM_PARAMS_N` | `D_80036F60` | n_alFxNew |
| 80036FC8 | `BIGROOM_PARAMS_N` | `D_80036FC8` | n_alFxNew |
| 80037050 | `ECHO_PARAMS_N` | `D_80037050` | n_alFxNew |
| 80037078 | `CHORUS_PARAMS_N` | `D_80037078` | n_alFxNew |
| 800370A0 | `FLANGE_PARAMS_N` | `D_800370A0` | n_alFxNew |
| 800370C8 | `NULL_PARAMS_N` | `D_800370C8` | n_alFxNew |
| 800370F0 | `n_eqpower` | `D_800370F0` | n_alEnvmixerPull |
| 80037230 | `xseed` | `D_80037230` | guRandom |
| 80037240 | `__osThreadTail` | `D_80037240` | osCreateMesgQueue |
| 80037248 | `__osRunQueue` | `D_80037248` | osSetThreadPri, osStartThread, osYieldThread |
| 8003724C | `__osActiveQueue` | `D_8003724C` | osCreateThread, osDestroyThread |
| 80037250 | `__osRunningThread` | `D_80037250` | osDestroyThread, osGetThreadPri, osJamMesg, osRecvMesg, osSendMesg, osSetThreadPri (+2 more) |
| 80037254 | `__osFaultedThread` | `D_80037254` | read from __osExceptionPreamble: set on a CPU fault before OS_EVENT_FAULT is posted |
| 80037260 | `SMALLROOM_PARAMS` | `D_80037260` | alFxNew |
| 800372C8 | `BIGROOM_PARAMS` | `D_800372C8` | alFxNew |
| 80037350 | `ECHO_PARAMS` | `D_80037350` | alFxNew |
| 80037378 | `CHORUS_PARAMS` | `D_80037378` | alFxNew |
| 800373A0 | `FLANGE_PARAMS` | `D_800373A0` | alFxNew |
| 800373C8 | `NULL_PARAMS` | `D_800373C8` | alFxNew |
| 800373F0 | `eqpower` | `D_800373F0` | _pullSubFrame, alEnvmixerPull |
| 80037510 | `alGlobals` | `D_80037510` | __allocParam, __freeParam, alAudioFrame, alClose, alEnvmixerPull, alFxParamHdl (+1 more) |
| 80037520 | `hdwrBugFlag` | `D_80037520` | osAiSetNextBuffer |
| 80037530 | `__osContinitialized` | `D_80037530` | osContInit |
| 800375E0 | `__osPfsInodeCacheChannel` | `D_800375E0` | __osPfsRWInode |
| 800375E4 | `__osPfsInodeCacheBank` | `D_800375E4` | __osPfsGetStatus, __osPfsRWInode |
| 800375F0 | `__osPfsLastChannel` | `D_800375F0` | __osContRamRead, __osContRamWrite |
| 80037600 | `__osPiDevMgr` | `D_80037600` | osCreatePiManager, osEPiStartDma, osPiGetCmdQueue |
| 8003761C | `__osPiTable` | `D_8003761C` | osCartRomInit, osDriveRomInit, osEPiLinkHandle |
| 80037620 | `__osCurrentHandle` | `D_80037620` | osEPiRawReadIo, osEPiRawStartDma, osEPiRawWriteIo |
| 80037630 | `__osViDevMgr` | `D_80037630` | osCreateViManager |
| 8003764C | `__additional_scanline` | `D_8003764C` | __osViSwapContext, osCreateViManager |
| 80037650 | `osViModeTable` | `D_80037650` | osCreateScheduler |
| 800387D0 | `__osHwIntTable` | `D_800387D0` | read from __osExceptionPreamble: entry 1 is the cart / 64DD interrupt hook |
| 800387F8 | `__osPiIntTable` | `D_800387F8` | read from __osExceptionPreamble: the hook called before a PI interrupt is posted (a 2.0J feature) |
| 80038800 | `osClockRate` | `D_80038800` | osInitialize |
| 80038808 | `osViClock` | `D_80038808` | osAiSetFrequency, osInitialize |
| 8003880C | `__osShutdown` | `D_8003880C` | read from __osExceptionPreamble: set at the first PreNMI |
| 80038810 | `__OSGlobalIntMask` | `D_80038810` | __osResetGlobalIntMask, __osSetGlobalIntMask |
| 80038820 | `__osTimerList` | `g_80038820` | __osInsertTimer, __osTimerInterrupt, __osTimerServicesInit, osSetTimer |
| 80038830 | `vi` | `D_80038830` | __osViInit |
| 800388A0 | `__osSiAccessQueueEnabled` | `D_800388A0` | __osSiCreateAccessQueue, __osSiGetAccess |
| 800388B0 | `osViModeNtscLan1` | `D_800388B0` | __osViInit |
| 80038900 | `osViModePalLan1` | `D_80038900` | __osViInit |
| 80038950 | `osViModeMpalLan1` | `D_80038950` | __osViInit |
| 800389A0 | `__osPiAccessQueueEnabled` | `D_800389A0` | __osPiCreateAccessQueue, __osPiGetAccess, osCreatePiManager |
| 8003B650 | `__osRcpImTable` | `D_8003B650` | read from osSetIntMask and __osDispatchThread: the MI_INTR_MASK_REG value for each 6-bit RCP mask |
| 8003B910 | `__osIntOffTable` | `D_8003B910` | read from __osExceptionPreamble: pending interrupt bits -> offset into its jump table |
| 800604C8 | `max_channels` | `D_800604C8` | Fstartfx, Ftempo, MusAsk, MusHandleAsk, MusHandleGetPtrBank, MusHandleSetFreqOffset (+11 more) |
| 800604CC | `mus_voices` | `D_800604CC` | MusInitialize, __MusIntFlushPending, __MusIntGetNewNote, __MusIntMain, __MusIntSetPitch, __MusIntSetVolumeAndPan |
| 800604D0 | `mus_channels` | `D_800604D0` | Fstartfx, Ftempo, MusAsk, MusHandleAsk, MusHandleGetPtrBank, MusHandleSetFreqOffset (+9 more) |
| 800604DC | `mus_vsyncs_per_second` | `D_800604DC` | Ftempo, MusInitialize, __MusIntInitialiseChannel |
| 800604E0 | `mus_next_frame_time` | `D_800604E0` | MusInitialize, __MusIntGetNewNote, __MusIntMain, __MusIntSetVolumeAndPan |
| 800604E4 | `mus_master_volume_effects` | `D_800604E4` | MusSetMasterVolume, __MusIntSetVolumeAndPan |
| 800604E6 | `mus_master_volume_songs` | `D_800604E6` | MusSetMasterVolume, __MusIntSetVolumeAndPan |
| 800604E8 | `mus_current_handle` | `D_800604E8` | MusInitialize, __MusIntStartEffect |
| 800604EC | `mus_random_seed` | `D_800604EC` | MusInitialize, __MusIntRandom |
| 800604F0 | `mus_init_bank` | `D_800604F0` | MusInitialize, __MusIntInitialiseChannel |
| 800604F8 | `mus_songfxchange_flag` | `D_800604F8` | MusSetSongFxChange |
| 800604FC | `mus_last_fxtype` | `D_800604FC` | MusSetFxType, MusSetSongFxChange |
| 80060504 | `fifo_start` | `D_80060504` | __MusIntFifoAddCommand, __MusIntFifoOpen, __MusIntMain |
| 80060508 | `fifo_current` | `D_80060508` | __MusIntFifoAddCommand, __MusIntFifoOpen, __MusIntMain |
| 8006050C | `fifo_limit` | `D_8006050C` | __MusIntFifoAddCommand, __MusIntFifoOpen, __MusIntMain |
| 80060510 | `fifo_addr` | `D_80060510` | __MusIntFifoAddCommand, __MusIntFifoOpen, __MusIntMain |
| 80062580 | `tmp_task` | `D_80062580` | osSpTaskLoad |
| 800625C0 | `__MotorDataBuf` | `gControllerPakBankBuffers` | __osMotorAccess, osMotorInit |
| 800626C0 | `piThread` | `D_800626C0` | osCreatePiManager |
| 80063870 | `piEventQueue` | `D_80063870` | osCreatePiManager |
| 80063888 | `piEventBuf` | `D_80063888` | osCreatePiManager |
| 80063890 | `retrace` | `D_80063890` | viMgrMain |
| 80063898 | `viThread` | `D_80063898` | osCreateViManager |
| 80064A50 | `viEventQueue` | `D_80064A50` | osCreateViManager |
| 80064A68 | `viEventBuf` | `D_80064A68` | osCreateViManager |
| 80064A80 | `viRetraceMsg` | `D_80064A80` | osCreateViManager |
| 80064A98 | `viCounterMsg` | `D_80064A98` | osCreateViManager |
| 80064AB0 | `siAccessBuf` | `D_80064AB0` | __osSiCreateAccessQueue, __osSiGetAccess |
| 80064AC0 | `piAccessBuf` | `D_80064AC0` | __osPiCreateAccessQueue, __osPiGetAccess |
| 80065120 | `__osBaseCounter` | `D_80065120` | __osTimerServicesInit, osGetTime, viMgrMain |
| 80065128 | `DriveRomHandle` | `D_80065128` | osDriveRomInit |
| 8006A0B0 | `__osThreadSave` | `D_8006A0B0` | read from __osExceptionPreamble: the scratch frame the handler spills $at, SR and $t0-$t2 into |
| 8006A260 | `__osContPifRam` | `D_8006A260` | __osContGetInitData, __osPackReadData, __osPackRequestData, osContGetReadData, osContInit, osContStartQuery (+1 more) |
| 80070480 | `__osViIntrCount` | `D_80070480` | __osTimerServicesInit, viMgrMain |
| 80070A98 | `__osMaxControllers` | `D_80070A98` | __osContGetInitData, __osPackReadData, __osPackRequestData, __osPfsGetInitData, __osPfsRequestData, osContGetReadData (+3 more) |
| 80070AA0 | `__Dom2SpeedParam` | `D_80070AA0` | createSpeedParam (as __Dom1SpeedParam); __osCurrentHandle[1] points here |
| 80070B20 | `__osCurrentTime` | `D_80070B20` | __osTimerServicesInit, osGetTime, viMgrMain |
| 80073E98 | `__osPiAccessQueue` | `D_80073E98` | __osPiCreateAccessQueue, __osPiGetAccess, __osPiRelAccess, osCreatePiManager |
| 8007BD30 | `__osContLastCmd` | `D_8007BD30` | __osContRamRead, __osContRamWrite, __osMotorAccess, __osPfsRequestData, __osPfsRequestOneChannel, osContInit (+3 more) |
| 8007BD34 | `__osEepromTimerMsg` | `D_8007BD34` | osContInit |
| 8007BD60 | `__osTimerCounter` | `D_8007BD60` | __osSetTimerIntr, __osTimerInterrupt |
| 8007DDB8 | `__osPfsInodeCache` | `D_8007DDB8` | __osPfsRWInode |
| 8007DEB8 | `__Dom1SpeedParam` | `D_8007DEB8` | createSpeedParam (stores to +0 and, changed by the game, +5); __osCurrentHandle[0] points here |
| 8007DF30 | `__osEventStateTab` | `D_8007DF30` | osSetEventMesg |
| 8007DFB8 | `__osFinalrom` | `D_8007DFB8` | osInitialize |
| 8007DFD0 | `__osPfsPifRam` | `D_8007DFD0` | __osContRamRead, __osContRamWrite, __osPfsGetInitData, __osPfsGetOneChannelData, __osPfsGetStatus, __osPfsRequestData (+2 more) |
| 8007E180 | `__osEepromTimerQ` | `D_8007E180` | osContInit |
| 8007E198 | `CartRomHandle` | `D_8007E198` | osCartRomInit |
| 8007E210 | `__osSiAccessQueue` | `D_8007E210` | __osSiCreateAccessQueue, __osSiGetAccess, __osSiRelAccess |
