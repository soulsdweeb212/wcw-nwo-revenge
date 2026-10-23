/* context.h for WCW / nWo  REVENGE: shared by every function. Agents grow it with edit_context:
 * add a prototype or struct the moment you work one out, so the next function benefits. */

typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef signed long long s64;
typedef unsigned long long u64;
typedef float f32;
typedef double f64;
typedef volatile u8 vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;
typedef volatile s32 vs32;
typedef int s32_bool;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))

/* 0x3B0-stride entity/action record selected by s8 index into D_800F9D10
 * (see matched func_8009D8D0). Use a typed pointer for this record; raw u8*+offset
 * access changes register allocation/scheduling. Fields are at the named offsets. */
typedef struct {
    u8 pad0[0xA];
    s16 fA;
    u8 padC[0x14];
    u64 flags;
    u8 pad28[0xF];
    u8 f37;
    u8 f38;
    u8 pad39[3];
    s16 f3C;
    u8 pad3E[0xE];
    f32 f4C;
    u8 pad50[0x301];
    s8 f351;
    s8 f352;
    u8 pad353[2];
    s8 f355;
    u8 pad356[2];
    s32 f358;
    s32 f35C;
} Nw2Entity3B0;

/* s32 global at 0x800D6D30; linkable by this name (func_8009001C polls it) */
extern s32 D_800D6D30;

/* Sub-words of the D_8007E228 bss block. Declare these as PLAIN SCALARS:
 * KMC then emits a direct `lw/lhu sym` (expanded to lui+lw), which is what the
 * ROM does. Writing `*(u32*)(D_8007E228 + 0x620)` makes KMC LICM-hoist the
 * invariant address out of loops instead (see pickPresentControllerEntity). */
extern u32 D_8007E848; /* "present" bitmask word at D_8007E228+0x620 */
extern u16 D_8007E280; /* u16 flags word at D_8007E228+0x58 */

/* Display-list data blobs referenced by func_8009B66C (and D_C9620 elsewhere). */
extern u8 D_C9620[], D_C9788[], D_C9808[];

/* byte arrays at 0x800484F4/0x800484F8/0x800484FC (func_8000439C/43CC/440C use them indexed by s16) */
extern s8 D_800484F4[];
extern s8 D_800484F8[];
extern s8 D_800484FC[];

/* command-buffer state (func_800213CC/21480/21540):
 * D_8006A260 is an array of 8-byte entries; D_80070A98 is the entry count.
 * D_8006A260+0x38 = D_8006A298, D_8006A260+0x3C = D_8006A29C (flag).
 * D_8007BD30 is a byte status written 0xFE. */
extern u8 D_80070A98;
extern u8 D_8007BD30;
extern s32 D_8006A298;
extern s32 D_8006A29C;

/* Layout of the objects pointed to by the global pointers at 0x80038894 (->0x80038860)
 * and 0x80038890 (->0x80038830).  func_80020ED0/800210E0/80021130 and func_80020DF0 read them.
 * NOTE: those matched sources define their own local types of the same layout, so use these
 * distinct names in new code (__osViNext itself is declared locally as `extern void *`). */
typedef struct {
    volatile s16 f0;
    s32 f4;
    void *volatile f8;
    volatile s32 fC;
} Nw2Obj80038860;
typedef struct {
    s16 f0;
    s32 f4;
} Nw2Obj80038830;

/* object behind the global pointer D_800EB408 (func_8009F774/8009FC0C/800A3E54/800A5D64...):
 * f4 compared as s16 (lh), fC read/incremented as s16 (lh/lhu -> addiu -> sh).
 * NOTE: matched sources define this locally as `T_F408`, so use the Nw2F408 name in new code. */
typedef struct {
    s32 f0;
    s16 f4;
    s16 f6;
    s32 f8;
    s16 fC;
    s16 fE;
} Nw2F408;

/* globals of that group; all matched uses agree on these types (unlike D_800EB40C,
 * which is s32 in some and void* in others -- do NOT add it here). */
extern void *D_800EB408;
extern s16 D_800EB37A;
extern s32 D_800F99C0;
extern s32 *D_800F99D4;

/* xform/scene record built by initIdentityMatrix4x4 (12 f32 "matrix") and given 3 coords:
 * func_8001C0F0(obj, x,y,z) writes 0x30/0x34/0x38, func_8001C144 builds it on the stack (size 0x40).
 * func_8001B090(xform, out) converts 16 f32 pairs into 2x4 words. */
typedef struct {
    f32 m[12];
    f32 x, y, z;
} Nw2Xform;

/* setIndexedS16Pair stores a pair of s16 values; both indices are s16.
 * Declare locally while legacy callers use narrower index prototypes. */

void initIdentityMatrix4x4(void *);
/* func_8001C0F0(void *, f32, f32, f32) -- declared locally in the saved 0x800014xx file,
 * which uses (void *, s32, s32, f32); declare it yourself in new files. */
void func_800A6C48(void *, s32);
void func_800D93DC(void *);
/* func_800A83DC returns s8 (callers test `sll 24; bnez`, no sign-extension — like func_800B4C60). */
/* func_800D2B64 takes (void *, f32, u16, s32) and returns the boundary-core s32 result.
 * Declare locally because legacy callers use raw float bits. */
/* func_800D2BEC forwards entity pointers and a float scale to func_800D2CAC.
 * Declare locally: legacy callers use raw s32 float bits in their prototypes. */

/* Eight-byte PIF controller-read packet, verified by packControllerReadCommands.
 * Signed stick fields preserve the -1 initialization separately from dummy=0xFF. */
typedef struct {
    u8 dummy, txSize, rxSize, command;
    u16 buttons;
    s8 stickX, stickY;
} Nw2ControllerReadPacket;
/* updateTriangleOscillator updates float phase at +0x14 by rate(+0x10)*ticks,
 * wraps above 2 by subtracting 4, returns amplitude(+0x1C)*(abs(phase)-1). */
f32 updateTriangleOscillator(f32 *, s32);

/* Four-way XZ heading from a three-float vector; 4096 angle units per turn. */
s32 getXZDirectionQuadrant(f32 *);
/* Result storage used by func_800D3890 and func_800A712C:
 * three floats at +0/+4/+8, signed angle at +0xC. */
typedef struct {
    f32 x, y, z;
    s32 angle;
} Nw2DirectionResult;

/* Table of 0x3B0-byte records used by the 0x800BFxxx code: the address D_800F9D30 + i*0x3B0
 * IS the record's u64 flag word (D_800F9D34 is its second word, i.e. D_800F9D30+4);
 * the 16-byte vector handed to func_800D3890 lives at record+0x4C (D_800F9D7C).
 * NOTE: func_800D3890 returns f32 and takes (void*,void*,void*), but matched sources
 * declare it with conflicting types, so leave it file-local. */
extern u8 D_800F9D30[];
extern u8 D_800F9D34[];
extern u8 D_800F9D7C[];

/* decodeAnimationMetadata(void *slotRecord, s16 value) only writes the record;
 * return value is unused by D427C. Keep prototype local for legacy callers. */

/* func_800D26A0: semantic s8 result; declare locally (some callers retain raw s32 result). */
s32 func_800D3550(s32);
s32 func_800D3684(s32, s32);

/* Two-key 0x48-byte buffer/cache records used by func_80028D18.
 * D_8007FC3C points to 40 entries; key0==0 marks an unused record. */
typedef struct {
    u8 buffer[64];
    s32 key0, key1;
} Nw2KeyedBufferEntry;
/* Lookup in the zero-terminated two-byte Shift-JIS table at 0x80038BB8. */
u8 *findSjisCodeEntry(u8 *);
/* Wrapper reserves 256 s32 results and returns results[index]. */
/* func_80029C7C: s32 (u8 *str, u16 flags, s32 *out, s32 count) -- returns packed
 * (width<<16)|(sum&0xFFFF); the matched caller declares it locally as void. */
s32 func_80029C40(void *, u16, s32);

/* Boundary correction core: entity and two optional linked entities, float divisor,
 * optional attachment record, optional three-point buffer, optional position,
 * direction mask, body-part mask, and apply-correction flag. */
s32 func_800D2CAC(void *, void *, void *, f32, void *, void *, void *, u16, s32, u16);
s32 func_800D2C2C(void *, void *, void *, f32, void *, s32);
s32 func_800D2C68(void *, void *, f32, void *, s32);
s32 func_800D2BAC(void *, void *, f32, s32);
/* Recovered func_800D2BEC signature (local declarations for legacy callers):
 * s32 func_800D2BEC(void *, void *, void *, f32, u16, s32); */

/* func_8000FD34 initializes two float channels at half their targets, then
 * computes per-step increments. +0x10 and +0x1C are untouched. */
typedef struct {
    s16 mode, steps;
    s32 value;
    f32 current0, current1;
    f32 reserved10;
    f32 target0, target1;
    f32 reserved1C;
    f32 increment0, increment1;
} Nw2FloatPairRamp;
void func_8000FD34(void *, s16, s16, s32, f32, f32);

/* Lookup tables used by the 0x8002B6xx family (func_8002B5AC/8002B668/8002B6BC).
 * The table whose first record starts at 0x8003A4F8 (and whose count field starts at
 * 0x8003A4FC) is an array of these 8-byte records; index < 0xD is valid in the
 * element getters and index < 0xB in func_8002B5AC. 0x8003A59C is the fallback
 * record returned for a bad index (its +2 byte is 0).
 * NOTE: matched sources declare lookupSubTables/D_8003A59C locally with the same layout
 * under the Nw2Lookup* names, so declare those symbols locally in new code. */
typedef struct {
    u16 id;
    u8 value;
} Nw2IdTableEntry;
typedef struct {
    Nw2IdTableEntry **entries;
    u16 count;
    u16 pad;
} Nw2IdSubTable;
/* Matched signatures (local declarations avoid legacy caller conflicts):
 * void setIndexedS16Pair(s16, s16, s16, s16);
 * void func_8000EED8(s16);
 * void func_8000E8A0(s8, s32, s8, s8);
 * void func_8000F4FC(s16);
 * void func_800074A4(s32, void *, void *, s32);
 */

/* func_800C2B20 resets eight entries for an s8 entity index. Table stride is
 * 0x40 bytes per entity, 8 bytes per entry; field symbols are D_800FABE8,
 * D_800FABEC and D_800FABEE. Initial values: 150.0f, 15, 0. */
typedef struct {
    f32 value;
    s16 count;
    s16 state;
} Nw2EntityResetEntry;
/* Confirmed signatures, kept local to avoid legacy caller conflicts:
 * void func_800C278C(void *, f32);
 * s32 func_800C2830(void *);
 * void func_800C2B20(s8);
 * void updateEntityStatus43Timer(void *, s16);
 * void func_800D2638(void *, u16, f32);
 * func_800C278C temporarily ORs entity u64 flags at +0x20 with 0x40,
 * calls boundary correction, and restores the original flags.
 */

/* Confirmed by matching 800B09A4/800B10B8/800AFFE0/800B1634:
 * s8 func_800D4198(s16); -- callers test its low byte (sll 24).
 * f32 func_800B3AD8(void *);
 * s16 func_800B10B8(void);
 * s16 func_800B1634(void);
 * Keep these declarations local because legacy sources use s32 returns.
 * D_800FABD0 points to an action record: s16 fields +2,+4,+8,+12,+14,+22,
 * byte +C, u16 +2E, u32 flags +5C (low three bits reset on state change).
 * D_800F9B60 has u16 counter +6, s16 state +A and u8 limit +370.
 */

/* Confirmed by matched 800D2B64/800D2ACC/800D26A0/800D1EA8:
 * s32 func_800D2B64(void *, f32, u16, s32);
 * s32 func_800D2ACC(void *, s32, f32 *);
 * void translateEntityXZ(void *, void *);
 * f32 func_800D63F0(void *, void *, s32);
 * void *func_800D6610(void *, s16);
 * void func_800D37C0(void *, f32, void *);
 * Keep local declarations to accommodate legacy m2c signatures.
 * func_800D26A0's s32 second argument is actually an optional pointer to
 * a 16-byte Nw2DirectionResult-compatible record, copied by structure assignment.
 * translateEntityXZ reads only vector +0/+8, so temporary vectors in these
 * wrappers intentionally initialize only x and z.
 */

/* 0x30-byte record table at D_800F98E0, four entries, reset by matched func_800E1AD8.
 * +0 u8 id (set to -1 = unused), +1/+2 u8 (-1 when reset), +3 u8, then s32 fields at
 * +4/+8/+C/+10/+14/+18/+1C.  func_800E2090 stores an entity id at record+0.
 * NOTE: declare `extern u8 D_800F98E0[];` etc. locally (matched sources do). */
typedef struct {
    u8 id;
    u8 f1;
    u8 f2;
    u8 f3;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
} Nw2FieldRecord98E0;

/* Matched 800CCC64 (facing/step helper): entity f32 at +0x4C/+0x54, s32 heading +0x58.
 * f32 func_800D3564(f32); s32 func_800D35B0(s32, s32);
 * s32 func_800D3B24(void *, void *, s32, f32 *);
 * s32 func_800D3E40(void *, f32 *, s32, f32 *);
 * Keep declarations local to accommodate legacy caller prototypes.
 * A 4-way mode local should be s16 (not s32) to get KMC's v0-to-v1 copy before the switch. */

/* Confirmed by matched 800E2768/800E2090/800DEEE8 (segment code_800DE9C0):
 * D_800F99A0 is a byte table indexed by an s8 entity id (entity[0]);
 * D_800F98E2 is a byte table with 0x30-byte records, first byte = entity id.
 * s8 func_800D8DF0(void *); -- callers test its low byte (sll 24).
 * void applyEntityTextureMasks(s8, s8);
 * KMC quirk: for a u64 at +0x20 (big-endian: the word at +0x20 is the HIGH half),
 * a mask on the +0x20 word written as 0x30000 in a target listing needs the
 * DImode literal 0x3000000000000 in C (KMC materializes the high half first).
 */

/* Confirmed by matched 800B9148/800B8D04/800B8C94/800B83CC:
 * void func_800DA8B4(void *, s32, s32);
 * void func_800B9730(void *, void *, s32, s32);
 * void func_8009678C(void); void func_80096018(void);
 * Keep declarations local for legacy callers and overlay aliases.
 * D_800FAF60 has four 6-byte entries, reset by func_800B8D04.
 * func_800B8C94 passes the same four-byte {-1,-1,-1,-1} array twice.
 * func_800B83CC takes an s16 entity index; entity stride is 0x3B0.
 * It uses s16 state at +0xA, s8 linked index at +0x353,
 * linked entity's s8 +0x396 to index its own s8 array at +0x34C.
 * Its call to func_800BF2FC truncates the result to s16 before comparing.
 */

/* Confirmed by matched 800B60C8/800B3B24/800B1BB8/800AF1B8:
 * s8 func_800B4C60(void *, void *, s32, s32);
 * s8 func_800B5DC4(void *, s32);
 * s32 func_800B60C8(void *, void *);
 * Keep declarations local for compatibility with legacy drafts.
 * func_800B60C8 forwards BOTH incoming pointers to B4C60 with (0,1),
 * then tests B5DC4(first pointer,1) only if the first low-byte result is zero.
 * D_800FABD0 action record: +4 is the s16 substate; +6 is an s16 command.
 * D_800FAF58 has s16 state +A and f32 value +74 (B3B24 compares as f64).
 */

/* Controller Pak CRCs: address input is the 11-bit block address; data is 32 bytes. */
s32 calculateControllerPakAddressCrc(u16);
s32 calculateControllerPakDataCrc(u8 *);
/* func_8001F3EC dispatches messages to child pointer +0 via callback +8.
 * Messages 4/9 reset/set parent state and forward with third argument zero.
 * Message 1 sets child; 7 sets +0x18; 8 sets +0x1C to one. */

/* Audio command queue: 8-byte message records, read index D_80060504,
 * write index D_80060508, capacity D_8006050C, buffer pointer D_80060510.
 * Declare these locally where needed for legacy source compatibility.
 * s32 func_8001446C(void *message); copies eight bytes, returns success.
 * void func_80015EF8(void *source, void *destination, s32 bytes);
 * func_80014418 consumes {u8 type; padding[3]; s32 value;} messages:
 * types 0/1 call func_800160E8(value,-2,1/0); type2 is a no-op.
 */

/* Matched signatures (declare locally for legacy caller compatibility):
 * s32 readControllerPakId(void *);
 * s32 func_80025480(u8 *, s32); -- fill 32-byte Controller Pak bank select command
 * s32 func_800254F0(u8 *, u8 *); -- optional 32-byte name update
 * s32 __osContRamWrite(s32, s32, s32, void *, s32);
 * s32 func_8001446C(void *); -- enqueue 8-byte {u8 type; s32 value;} record
 * void func_80015EF8(void *source, void *destination, s32 size);
 */
void cachePiDomainTimings(void);

/* Matched CDEE4/C9AC0: entity+0x20 is u64 flags. Natural KMC literals
 * 0x80000 and 0x200000 test the word at +0x24 in these functions.
 * C9AC0 forwards incoming second argument into func_800D3684.
 * s32 func_800D35B0(s32 angle, s32 delta); -- used in CE2C8/CE6E4.
 */

/* Matched AD6D0/AD730/ADF40/AE6B4:
 * D_800EB420 and D_800F9B78 are s16 entity-indexed tables.
 * D_800FA074 is a pointer field table with entity stride 0x3B0;
 * D_800F9D1A is an s16 field table with the same entity stride.
 * AD730 returns D_800EB420[index] iff pointed-to u64 +0x38 has bit 0
 * (mask 1) and D_800F9D1A[index] == 75, otherwise -1.
 * s16 func_800ADF40(s16 *); walks threshold/value pairs, -1 sentinel,
 * returns value at first threshold >= (s16)func_800D4148(), else zero.
 * s32 func_800D4148(void); -- keep local for legacy callers.
 */

/* Matched D3A74: YZ-plane distance/heading, optional 16-byte output
 * { f32 distance, dy, dz; s32 angle; } copied with struct assignment.
 * f32 func_800D3A74(void *, void *, void *);
 * D4028 evaluates three quadratic spline weights from float t into f32[3].
 * void func_800D4028(f32, f32 *);
 */

/* Matched 13994: D_800604D8 is s32 *thresholds, D_800604D0 a
 * pointer to records of stride 0x158 (not an inline array in this routine).
 * func_80015F64(void *, s32, s32, s32, s32) takes FIVE arguments;
 * the fifth is the selected table threshold, passed at stack+0x10.
 * Matched 17700: func_8002023C(void *) takes only the list node;
 * func_8002021C(void *, void *) moves it to a list head.
 */

/* Confirmed by matched 800AE75C/800ABFF8/800ABCD8/800ABC40 (0x800AExxx action-record family):
 * D_800E4E30/D_800E4E38/D_800E4E40/D_800E4E68/D_800E4E70 are f64 thresholds compared against
 * the f32 at D_800FABD0+0x34 (load f32, cvt.d.s, c.lt.d). D_800E3658 is an s16 table.
 * D_800FAF58+0x364 points to a record whose byte +0x18 is a signed byte divided by 3 to index
 * D_800E3658: store the quotient in an `s8` local so KMC emits `sll 24 / sra 23` (2*(s8)q).
 * D_800E35F8 and D_800E35E0 are byte data whose addresses are passed to func_800ADA38.
 * s32 func_800ABFF8(void); void func_800ABCD8(void); void func_800ABC40(void);
 */

/* Confirmed by matched 800178F0/80017860/80017980 (same family as 800177D0/80017A30/80017AC0):
 * D_80036F54 is s32 *; func_80017F18 returns a fresh command packet (s32 *); the packet
 * layout is p[0]=0, p[1]=D_80036F54[7]+child[0x88], s16 command at byte +8, s32/f32 payload
 * at +0xC, p[3] extra at +0xC too (payload word), p[4] at +0x10. Send with
 * func_80018C24(child, 3, p). Commands: 7 (float payload, 178F0), 0xC (arg&0xFF, 17860),
 * 0xB (s16 payload + func_80018044(arg2, p[1]) -> p[4], 17980).
 * s32 *func_80017F18(void); s32 func_80018C24(s32 *, s32, s32 *); s32 func_80018044(s32, s32);
 */

/* Matched 1BED0 (buildScaleMatrixFixed): void (void *, f32, f32, f32);
 * uses f32 m[4][4], local pointer p=m, initializes with initIdentityMatrix4x4,
 * sets [0][0], [1][1], [2][2], [3][3]=1, converts via func_8001B090.
 * Matched 1D4E4/1D594: func_8001F070 takes FOUR arguments:
 * (object, callback0, callback1, mode). Object is incoming a0.
 */

/* Audio voice records used by func_80013B58: 0x158-byte stride.
 * A typed record pointer is important for alias analysis / hoisting voice count. */
typedef struct {
    s32 flags;
    s32 active;
    u8 pad8[16];
    s32 state;
    u8 pad1C[20];
    s32 value;
    u8 pad34[146];
    u16 kind;
    u8 padC8[144];
} Nw2AudioVoiceRecord;
/* D_800604D0: Nw2AudioVoiceRecord *; D_800604C8: u32 voice count.
 * Keep extern declarations local for compatibility with legacy sources. */

/* Matched CBD5C: s8 func_800B71F8(void *, s32, s32);
 * Keep local prototype for legacy caller compatibility. Entity u64 flags
 * at +0x20 use masks 0x80000 and 9; byte +0x36 bits 4/8 track its result. */

/* D_800FAF5C points to the action object driven by 800C17D8/800C9A34
 * (s16 state +0xC, u64 flags +0x20, s16 quadrant/angle +0x3E, f32 vec[3] +0x6C).
 * func_800A7240 takes FOUR args: (void *obj, s32 animId, s32 id, u64 arg).
 * The u64 4th arg goes entirely on the stack (a3 is untouched) -- declare it u64,
 * NOT six s32 params, or the a3 setup appears. D_800E3C90 is s32[] indexed by the
 * quadrant, D_800E3CD0 is u16[] indexed the same way; D_800F9B00 is a pointer arg
 * and D_800F9B0C a global f32 passed on the stack to func_800D6658.
 * Keep these declarations local (legacy callers disagree). */

/* Assert/warning printer stub used with the string pair D_8003B970 ("EX") and
 * D_8003B974 ("sprawdma.c"): func_8001CEE0 is EMPTY (jr ra; nop) and takes
 * (char *tag, char *file, s32 line). Call sites: PI DMA helpers 800273D0/275F0/
 * 27680/277E0/28210, 18660, 1E340, 1E960, 1F4B0, 20090, 20928.
 * void func_8001CEE0(char *, char *, s32);
 * Hardware PI registers must be written as literal volatile addresses
 * (`*(vu32 *)0xA4040000`), not extern symbols -- see note for 800273D0. */

/* Matched startPiRawDma: direction 0 writes PI_WR_LEN (cart->RAM),
 * direction 1 writes PI_RD_LEN (RAM->cart); returns 0 or -1.
 * s32 startPiRawDma(s32 direction, u32 devAddr, void *dramAddr, u32 size);
 * u32 func_8001CE80(void *); -- translates virtual address to physical.
 * Declare locally to avoid legacy caller conflicts. */

/* Matched 07BB8: all matrix-call numeric arguments are f32, including
 * register arguments a1/a2/a3. Local matrix is f32[4][4] (0x40 bytes).
 * void func_8001A490(void *, f32, f32, f32, f32);
 * void func_8001BB50(void *, f32, f32, f32);
 * void buildScaledRotationTranslationMatrix(void *, f32, f32, f32, f32, f32, f32, f32);
 * void func_8001BE70(void *, f32, f32, f32);
 * void buildOrthoMatrixFloat(void *, f32, f32, f32, f32, f32, f32, f32);
 * Keep prototypes local for legacy caller compatibility. */

/* Matched F620: two arrays of 0xDC-byte records at D_80056968 (8)
 * and D_80057048 (23). First byte bit 0x80 is cleared for nonzero
 * argument, set for zero. Confirmed local signatures:
 * void func_8000F620(s16); void func_800112BC(s16);
 * Keep declarations local for legacy caller compatibility. */

/* buildObjectDisplayListTail (800060A4) object layout:
 * signed bytes +2 count and +3 first vertex; +C enables optional
 * 0x03 cull command (only when count<9); +10 command-buffer pointer;
 * +14 next display list (0 -> end). Emits render/combine modes, then
 * branches to next list using its physical address or ends the list. */

/* f64 distance thresholds added to func_800D3EEC results in entity action checks. */
extern f64 D_800E76B0;
extern f64 D_800E76B8;

/* Matched A9028: s32 func_800A9028(s16 entityIndex). Returns state-derived
 * mask: state 0x58 ->4, state 0x3E ->2, state 0x49 ->1 iff
 * D_800F9D3C entity word bit2, state7 ->0x10 iff entity u64 flags
 * D_800F9D30 contain 0x10000000000ULL; otherwise zero. */

/* Matched BF62C: void addEntityHealthDelta(void *entity, s32 delta);
 * Adds delta to s16 +0x14 unless u64 flags +0x20 contain 0xE0000.
 * At >=100 clamps to 99 when flag1 set, otherwise 100 and sets 0x40000.
 * At <=0 clamps to zero and sets 0x20000. Keep prototype local. */

/* Matched func_80004BA8 (object init from a descriptor, sibling of matched 80007874):
 * the descriptor arg1 is the SAME record type that func_8000498C consumes:
 * s8 id at +2, s8 at +3, u8 at +6, s32 at +0xC, s32 at +0x10 (+0x14 fallback),
 * s32 work-buffer at +0x28 (stored before calling func_8000498C(src, s16 id)).
 * The destination's +0x14 points to a subrecord with s32 +0, s16 +0x2C/+0x2E,
 * s32 +0x30/+0x34. Typed access was required: with raw u8* casts the entry-block
 * schedule differed (stack params s2-s4 loaded before the saves; the src->f28
 * store sank into the first jal delay slot). With the structs the prologue matches. */
typedef struct {
    u8 pad0[2];
    s8 f2;
    s8 f3;
    u8 pad4[2];
    u8 f6;
    u8 pad7[5];
    s32 fC;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    s32 f20;
    s32 f24;
    s32 f28;
} Nw2Descr4BA8;
typedef struct {
    s32 f0;
    u8 pad0[0x28];
    s16 f2C;
    s16 f2E;
    s32 f30;
    s32 f34;
} Nw2Sub4BA8;

/* Matched func_800162EC (audio voice pitch/level update):
 * lo = (*arg1++ * 0x6000) / 120 / D_800604DC; then
 * t2 = (lo * s16[arg0+0xB8]) >> 7; if (u16[arg0+0xC6] != 0) s16[arg0+0xBC] = lo;
 * else walk D_800604D0 (D_800604C8 records, stride 0x158) and for records whose
 * s32 +0x94 equals arg0's +0x94: s16 +0xC8 = lo, s16 +0xBC = t2. return arg1.
 * D_800604C8 is u32 (hoisted out of the loop ONLY when the walker is a real
 * 0x158-byte struct pointer; with a raw u8 * it reloads every iteration).
 * D_800604DC is s32. The 8-byte stack frame is from the inline signed-division
 * sequence, not from a local. */
typedef struct {
    u8 pad0[0x94];
    s32 id;
    u8 pad98[0x24];
    s16 fBC;
    s16 padBE[5];
    s16 fC8;
    u8 padCA[0x8E];
} Nw2VoiceRecord162EC;

/* Matched 00E0C: event dispatcher waits via func_8001C990(queue,msg*,1)
 * at object+0x40. Event 0x29A increments +0x27C and sends object to
 * listener queues; event 0x29D sends object+0x20. Listener head +0x260,
 * each listener {next pointer, queue pointer}. func_8001CAC0(queue,msg,0)
 * sends. Both queue helpers return s32; keep prototypes local. */

/* Matched B630: void func_8000B630(u8 *out5, u32 id, s16 variant).
 * D_80036710 is a table of pointer tables (u16 **[]). ID bits8..12
 * select table, bits0..4 minus1 select entry; each variant is 4 bytes.
 * Variants >=4 fall back to zero. Decodes into five bytes; last three
 * are masked to nibbles. Keep declarations local for legacy compatibility. */

/* Matched 80001DC4: recursive transform node. +0 = source node (its 4x4 world matrix at
 * +0x5C; NULL means copy local->world), +4 child, +8 next sibling, +0x1C local 4x4,
 * +0x5C world 4x4. World = local * source->world (4x4 float multiply). */
typedef struct {
    void *src;
    void *child;
    void *next;
    u8 pad[0x10];
    f32 local[4][4];
    f32 world[4][4];
} Nw2MatrixNode;

/* Matched 2BAB8: D_8003A594 is a byte-buffer pointer. Builds 80 groups
 * of 4 variants, each 0x2A bytes, via buildWrestlerNameRecord(u16 id,s32 variant,void *out).
 * Searches first 11 lookupSubTables for entry.value == group (fallback
 * D_8003A59C) then uses entry.id. Keep extern/prototype declarations local. */

/* Matched C778C: s16 func_800C778C(u8 *entity, s32 fallbackId).
 * Selects 0x1049..0x104E / 0x107B..0x1080 from entity word +0x30:
 * bit0x1000 selects one group, bits0x10000000/0x20000000/0x40000000
 * sequentially override the fallback. Without bit0x1000, bit0x10000000
 * uses signed-byte (attachment[0x1E]-1), attachment pointer at +0x364.
 * Keep prototype local for legacy callers. */

/* Matched BF548: D_800EB490 is an s16 entity-indexed tick table.
 * void func_800BF548(u8 *entity, s16 mode); mode0 resets, mode1 increments.
 * u64 entity+0x20 flag 0x400000000ULL chooses 90 ticks / attachment+2,
 * otherwise 60 ticks / attachment+1; attachment pointer at +0x364.
 * At threshold resets timer and calls func_800BF338(entity,(s8)amount,1).
 * void func_800BF338(void *, s8, s32); keep declarations local. */

/* func_800ADFB8 (95% matched): D_800FAF58 object layout confirmed here —
 * s8 kind at +0, s16 state at +0xA (==1 test), u64 flags +0x20, f32 +0x74,
 * s8 +0x353/+0x355 (copied when (f64)D_800FABD0->f3C exceeds f64 D_800E51B0).
 * D_800FAF80 has s16 state +0xA and u64 flags +0x20; D_800FADDC has u64 flags +0x20.
 * D_800FABD0 has s16 +2/+4, s8 +0xC (set 0x50), s16 +0x1E, s16 +0x2E,
 * f32 +0x3C, and u32 flags +0x5C (cleared low 3 bits). D_800F9B60 has u16 +0xA.
 * u64 flag masks here: &1 and &0x100 test the LOW word (+0x24); &0x1000000000000000ULL
 * (i.e. 0x10000000 in the HIGH word +0x20) — the high-half DImode literal. */

/* func_800BE908 (99.7%, score 35) — 5-case switch state machine on D_800FAF5C->f0xC (0..4,
 * jump table D_800E5840). D_800F9B00: u16 at +0x8 (animation id, read `(s16)(f8+1)` before
 * func_800D427C) and u16 at +0x360 (bit flags 1/2/4). func_800A7D1C takes (void *, s32):
 * called func_800A7D1C(D_800FAF5C, (fA==0xE) ? 0x27 : 0x28). Nw2F5C phase-timer f4 (+4),
 * s16 fA at +0xA, switch state fC (+0xC), s32 heading f58 (+0x58). */

/* Matched BF018: f64 thresholds compared against entity f32 +0x6C/+0x74;
 * func_800BED3C(entity, arg1, mask) returns a mask. */
extern f64 D_800E5868;
extern f64 D_800E5870;
extern f64 D_800E5878;
s32 func_800BED3C(u8 *, s32, u32);

/* Matched B46C: u16 func_8000B46C(s16 index) scans 23 buffers.
 * D_8007C438 is u16 *[][23], D_8007C318 is u16[][23] (buffer counts).
 * For nonnull buffers with count>=17, inspect u16 elements 16..31;
 * values>=2 fitting masks D_80030860[1]/[2] contribute result bits1/2.
 * D_80030860 is u16[4] = {0xF801,0x07C1,0x003F,0}. Declare locally. */

/* Matched 9F654: void func_800A7C40(void *, s8, s16);
 * void func_800A7F6C(void *, s32); void func_800A837C(void *);
 * void func_800D427C(void *, s16, s32); void func_800D4AD0(void *);
 * s16 func_800D5438(void *, s32); D_800FADB8 is s8.
 * Keep these prototypes local for legacy source compatibility. */

/* Matched E55C signatures (declare locally for legacy compatibility):
 * void func_8000E55C(s32 index, s16 duration, s8 enabled);
 * s16 func_800033F8(void); void func_800033C0(s16);
 * void func_8000337C(void *); void func_80003684(void *, s32, void *);
 * D_80030D0C is s16[22], D_80036748 is the current s16 index,
 * D_800487F0 is a 0x8000-byte buffer. E55C passes a 24-byte stack local
 * to 03684, then buffer to 0337C; busy path clears index and calls 033C0. */

/* Matched D9E1C: void func_800D9E1C(void *first, void *second, s16 setState);
 * Calls func_800A6BE0(void *, s32) with complementary IDs 0x7F/0x80
 * selected by first entity u64+0x20 flag 0x200. Sets first flags
 * 0x1000000000ULL and second flags 0x1020000000ULL; nonzero setState
 * writes s16 state +0xC = 2 on both. Keep prototypes local for legacy callers. */

/* Matched D238: void func_8000D238(s16 index, s8 value).
 * D_800651B8/D_800517E8 are byte fields in arrays of 23 records,
 * each record 0xDC bytes (outer stride 0x13C4). Declare locally as
 * struct {u8 value; u8 pad[0xDB];} table[][23] to preserve addressing.
 * D_80030894 is u8[20]; D_800662D0 is a word field and D_800662E8
 * a byte field with the same outer stride. */

/* Matched E07DC: s32 func_800E07DC(void *record) scans four entities
 * with s16 loop index, stride 0x3B0. Ignores entities whose s16 +2 is -1;
 * compares entity s16 +0x3E to record s16 +0x3E. Returns zero for
 * matching entity state(+0xA) 10/24, or state20 with substate(+0xC)<4;
 * returns one otherwise. D_800F9D12/1A/1C/4E are these field tables.
 * Keep prototype and extern declarations local for legacy compatibility. */

/* Matched 24640: s32 func_80024640(void *queue, s32 channel).
 * Uses func_80024730(s32,s32), func_80025810(s32,void *) -> s32,
 * func_8001C990(void *,void *,s32) -> s32, func_800247C4(s32,void *).
 * Local controller status: u16 type at +0, u8 status at +2, u8 error at +3;
 * tests status bits1/2/4 and big-endian u16 at +2 masked with 0x1FF.
 * D_800375E4 is command byte (set 0xFA); D_8007DFD0 is I/O buffer.
 * Keep signatures and globals local for legacy caller compatibility. */

/* Matched 15628 audio stream stepper: u64 target time +0x10,
 * u64 current time +0x20 (increments 0x100), u8 *cursor +0x4C,
 * u16 run countdown +0xC2, u8 decoded value +0xDC.
 * Byte <128 means value with run 1; high-bit value introduces run length
 * (next byte+2 or next two bytes, with high bit stripped, +2).
 * void func_80015628(void *); keep declaration local for legacy callers. */

/* Matched A63D8: s8 func_800CE6E4(void *, s32) (low-byte boolean);
 * void func_800CE388(void *, s32, void *); void beginEntityActionA8D8C(void *);
 * D_800F9B24 is indexed as s32[][4], D_800FADB8 is signed byte index.
 * Keep declarations local for legacy caller compatibility. */

/* Matched A297C additional signatures (local declarations for legacy compatibility):
 * void func_800D25D0(void *, f32);
 * void func_800D7B54(void *, u16, u16, s32);
 * D_800FABE6 and D_800FAF8A are u16 values. */

/* Matched 800A4D74: D_800EB408 action object (0x800EB408). Confirmed layout used there:
 * s32 +0, s16 +4 (==1 tests), s16 +6, s32 +8, s16 +0xC (switch state, `++` loads lhu),
 * s16 +0xE, u16 counter +0x16. `s32 func_800D2B64(void *, f32, u16, s32)` is called as
 * (D_800EB408, 1.0f, 0, 2); `void func_800D427C(void *, s32, s32)`; `void func_800D4AD0(void *)`.
 * Declare these locally; note `switch` on the s16 with cases 0..3 is a compare tree, and
 * case bodies should use direct global expressions so the pointer stays in a0.
 */

/* Matched 2AAFC: 128 resource entries behind D_8007FC34, stride0x18.
 * key -1 entries freed first; remaining keys may point into D_8007FC3C's
 * 0xB40-byte keyed-buffer pool. Clear key target +0x40/+0x44 and byte0
 * before freeing allocation. Keep globals/prototypes local for legacy types. */
typedef struct {
    u32 key;
    void *allocation;
    u8 reserved[0x10];
} Nw2ResourceEntryAAFC;

/* Heap allocation header: 16-byte units, circular free list, 64-bit magic. */
typedef struct Nw2HeapBlock {
    struct Nw2HeapBlock *next;
    u32 size;
    u64 magic;
} Nw2HeapBlock;
/* void *allocateHeap(u32 bytes); keep local for legacy prototypes. */

/* A7B38 receives four candidate records from A7418; only signed ID at +0 is
 * consumed there. Each candidate is 12 bytes: signed entity id, then the
 * distance (f32 +4) and heading angle (s32 +8) filled in by A7418. */
typedef struct {
    s8 id;
    u8 reserved[3];
    f32 dist;
    s32 angle;
} Nw2TargetCandidate;
/* Gameplay-overlay signatures (declare locally for legacy callers):
 * void collectLinkedTargets(void *entity, void *position, void *outCandidates, u64 flags);
 * void func_80096E2C(s32 entityId, s32 targetId);
 * s8 selectNewLinkedTarget(void *entity, s32 flags);
 */

/* insertTimer: delta-time timer queue; value is remaining relative delay. */
typedef struct Nw2TimerQueueEntry {
    struct Nw2TimerQueueEntry *next, *prev;
    u64 interval, value;
    void *queue;
    u32 message;
} Nw2TimerQueueEntry;
/* u64 insertTimer(Nw2TimerQueueEntry *); declare locally for legacy types. */

/* Matched 14F5C: audio voice float +40 interpolates from +68 using
 * byte duration +D8 and u16 elapsed +CA; +6C caches interpolation.
 * +38 is additive pitch, +3C cached total; byte +DB clears on ratio >2.
 * func_80015858(f32) approximates 2^x; takes only ONE argument.
 * void func_80014F5C(void *, s32 voiceIndex, f32 delta); keep local.
 */

/* getControllerPakFreeBytes: Controller Pak +60 s32 first usable page,
 * +64 u8 bank count. readWriteControllerPakInode(void *,u16 *,s32,s32) reads 128 inode
 * entries for a bank; entry 3 means free, page size 256 bytes.
 * s32 getControllerPakFreeBytes(void *,s32 *); keep local legacy declarations.
 */

/* Matched B678C: entity signed-byte +354 caches another entity's ID;
 * compares heading result from D3890 against entity s32 +58 via
 * D3684 then D3550, accepting differences <0x2AA. Returns 1 on new
 * accepted ID, 2 for already cached ID, 0 otherwise.
 * Requires incoming mask4, shared u64+20 bit0x40 OR bit0x100,
 * target u64+20 bit0x400000, and own u16+28 bit0x20 clear.
 */

/* Matched CBC4C: s32 func_800CBC4C(u8 *first, u8 *second).
 * first+36 bits1/2 choose animation C4/C6/C8/CA; bit10 and second
 * u64+20 flags9 select whose signed ID is used. first+386 is u16
 * animation ID; second+360 u16 bit10 or first+36 bit8 mirrors it+1.
 * Calls void func_800A7C40(void *,s8,s16), void func_800A7F6C(void *,s32).
 */

/* snapEntityToRingBoundary(u8 *entity): clears u64 flags10000000,
 * stores getXZDirectionQuadrant(position+6C) to s16+3C, copies X/Z
 * to +4C/+54 and table D_800E3CA0[quadrant] to s32+58, then snaps
 * quadrant-selected X/Z to +/-265. D_800E3CA0 is s32[4]. */
void snapEntityToRingBoundary(u8 *);

/* Matched 9903C/99148/99254/99364: 64 resource-cache entries at D_800E7CE0,
 * stride 20, key at +8, s16 parameters +C/+E, secondary key +10.
 * Keep globals and 98EEC prototype local for legacy type compatibility. */
typedef struct {
    s32 f0, f4, key;
    s16 parameter0, parameter1;
    s32 secondaryKey;
} Nw2ResourceCacheEntry;

/* Matched D23B4: s32 func_800D23B4(u8 *,u8 *,Nw2DirectionResult *);
 * s8 checkFacingProximity(void *,void *,s32); keep prototypes local for legacy callers.
 * D23B4 tests first entity u64+20 bit100 then second entity bit80;
 * result float+4 compared with D_800E6AF8 / D_800E6B00 (f64).
 */

/* startThread (8001CD20): OS thread header +0 next, +4 s32 priority,
 * +8 queue pointer, +C thread-list next, +10 u16 state.
 * State1 stopped,2 runnable,8 waiting. D_80037248 runnable queue,
 * D_80037250 current thread. 266B4 enqueue(queue**,thread*),
 * 266FC dequeue(queue**)->thread*, 2670C dispatch(),265AC yield(queue**).
 * Keep declarations local for legacy source compatibility. */

/* Matched C4610: void func_800C4610(u8 *source,u8 *target).
 * Computes heading halfway between source facing(+58) and source->target
 * direction; source animation s16+386 B6/DE/DF/E0/E7 reverses facing.
 * Clears target u64+20 bit08000000, sets it and target u32+30 bit1000
 * when target facing is within 0x400 of this halfway heading.
 * D35B0(angle,delta) wraps addition; D3684 gives signed angle delta.
 * Keep prototypes local for legacy caller compatibility. */

/* approximateAtan (80003920): eight-level continued-fraction arctangent,
 * f32 argument/result, double +/-pi/2 constants D_8003B0B0/B8.
 * Keep prototype local for legacy caller compatibility. */

/* Matched A64CC: func_800D2600(void *,s32,f32), called with
 * (D_800FAF5C,-1,2.0f) when nearby entity lacks u64 flag400000.
 * Third argument is float (raw bits40000000 in a2), required for exact
 * call argument scheduling. Keep prototype local for legacy callers. */

/* Matched 175E0: audio link node +8 pointer, +C s32, +14 s16,
 * +16/+18 u16 descriptor copies, +1A s16 byte-mode copy, +88 s32 time.
 * Descriptor is {u16 id,u16 value,u8 mode}. func_80017700(void **,s16)
 * returns a status and supplies a child pointer. Keep prototypes local.
 * Command packets are {s32 f0,f4; s16 command,pad; s32 fC,f10;}.
 */

/* Matched AE7C8: D_800FABEC and D_800FABF4 are s16 fields at +4/+C
 * within the 0x40-byte entity block of eight Nw2EntityResetEntry entries.
 * The handler compares those two signed counters, indexed by signed entity ID.
 * Local extern s16 D_800FABEC[][32], D_800FABF4[][32] preserves stride.
 */

/* Matched 055AC camera matrix wrapper: all eleven numeric arguments after
 * the destination ID are f32. D_80048500/540 are f32[4][4] projection/view
 * work matrices; D_80048580/584/588 cache eye X/Y/Z. Verified prototypes:
 * void buildPerspectiveMatrixFloat(void *,u16 *,f32,f32,f32,f32,f32);
 * void func_8001A980(void *,f32,f32,f32,f32,f32,f32,f32,f32,f32);
 * void func_800014AC(s32,void *,void *); void func_800014D0(s32,u16);
 * Keep declarations local to accommodate legacy sources.
 */

/* Matched AB43C: D_800E3498/D_800E34A0 are s16 tables indexed by
 * (s8)(attachment signed byte +0x18 / 3), attachment at entity+0x364.
 * Action record D_800FABD0+0x28 is s16, compared to D_800E34A0[index].
 * AB43C requests action 0x2F through void func_800AD958(s32), returns boolean.
 * Keep declarations local for legacy callers. */

/* Matched 0F4FC: D_80036CAC is s8[]; D_80036CB4/CCC/CE4 are pointer tables.
 * D_80058A10/D_80058FA0 are 1408-byte buffers; D_80058A0C/D_80058F90
 * hold their s32 counts, D_80059D82 is s16 selection index.
 * void freeResourceDescriptorArray(void *,s32,s8);
 * s32 func_80007020(void *,void *,void *,s8);
 * void func_80007818(void *,void *,s32,s32);
 * Keep declarations local to accommodate legacy callers. */

/* Matched B5CA0: s32 func_800B5CA0(u8 *,u8 *,s32,f32).
 * Requires mask4000, common entity u64+20 flag40 or100, target flag400000,
 * distance below D3EEC(target+4C,source+6C,target heading)+f64 D_800E54D8,
 * and source heading delta <0x200. Calls A6C48(source,0x56), E212C(source).
 * f32 func_800D3EEC(void *,void *,s32); void func_800E212C(void *);
 * Keep local declarations for legacy signatures. */

/* Matched 952CC: void accumulateColorChannels(s32,s32,s32) accumulates three
 * signed-16 channels D_800E74CC/CE/D0, clamps each at255, tracks their
 * historical maximum in s16 D_800E74D2. Negative first arg clears all four.
 * Explicit s16 *p=&D_800E74CC makes KMC retain the first global's address
 * while the later two globals use separate lui accesses. */

/* Matched 04450: Controller Pak API call wrapper has local pfs[0x68],
 * message queue[0x18], state[0x20] in that declaration order, at stack
 * +0x20,+0x88,+0xA0. func_80024850(queue,pfs,0) initializes the Pak,
 * osPfsFileState(pfs,0,state) reads file state. Wrapper then calls most
 * Pak APIs with null/zero arguments; preserve seven args to 23630,
 * six to 252E0 and 24B40, five to 24180. */

/* Matched 1CAC0 message send: queue +0 s32 *receiveWaitList, +4 s32 *sendWaitList,
 * +8 count, +C readIndex, +10 capacity, +14 s32 *entries. Both wait lists
 * are dereferenced before testing for a waiter. Send waits only when wait==1;
 * receive 1C990 waits for any nonzero wait. yield(&sendWaitList) on full,
 * startThread(dequeue(queue)) after enqueue. Local declarations avoid legacy types.
 * s32 func_8001CAC0(void *queue, s32 message, s32 wait); */

/* Matched CEAE0: s8 func_800D3B24(void *,void *,f32,s32) tests XZ proximity.
 * D_800FADE4 and D_800FADEC are f32 field tables at 0x5C-byte stride
 * (local extern f32 name[][23]); CEAE0 interpolates source +EC/F4 to
 * +16C/174 with f64 D_800E6A10, checks target +8C then +6C.
 * Keep function declaration local for legacy return-type compatibility. */

/* Matched E0590: void beginPairedEntityActions(void *source,s32 sourceAction,
 * void *target,s32 targetAction); invokes paired actions 0x30/0x31
 * after E212C when source is inside target's D3EEC boundary + margin.
 * Declare locally for legacy caller compatibility. */

/* Matched D49A0: copies six float coordinate fields for four entities,
 * parts 1..19. Source stride 0xB24/entity, 0x7C/part; destination
 * stride 0x3B0/entity, 0x10/part. Source fields D_80070C94/98/9C
 * and D_80070CAC/B0/B4 -> D_800F9D6C/70/74 and D_800F9EDC/E0/E4.
 * Accessed as volatile f32 in the matching implementation. */
void copyPartCoordinateFields(void);

/* Matched 1852C: initializer takes (void *object,s32 (*callback)(void *),s32).
 * func_800202B0(s32,s32,s32,s32,s32) returns s32; called with
 * (0,0,arg2,1,0x20) three times and (0,0,arg2,1,0x50) once.
 * callback(object+0x2C) returns the word stored at object+0x28.
 * Object fields are volatile, including intentional duplicate +0x64/+0x66 stores.
 * Keep prototypes local for compatibility with legacy sources. */

/* Matched BB40: void func_8000BB40(s16,s32 unused,s8,s8).
 * D_80032B44 is u8 ***[]: id high five bits choose table,
 * low five bits minus one choose pointer list; D_8007DFB0[s16 id]
 * chooses record within list, whose u16 +0x16 is copied to D_80075440.
 * D_80075440/42/44 form three halfwords per entity.
 * D_80073ECC is s32[][23][11]; D_8007C438 is void *[][23].
 * void func_8000B884(s32,s16,s16); keep declarations local for legacy types. */

/* Animation metadata decoded by 086A4: 36-byte packed source records,
 * destination s32 offset +0 followed by decoded bytes +4..+1A. */
typedef struct { u8 bytes[36]; } Nw2PackedAnimationMetadata;
typedef struct { s32 offset; u8 bytes[24]; } Nw2AnimationMetadata;

/* Matched D9568: s8 func_800D9814(void) (low-byte boolean).
 * D_8007E228+58 u16 bit200 enables action81; D_8007EF30+170
 * u16 bit40 inhibits it for entity state1. Keep prototype local. */

/* Timer interrupt core: count is a wrapping 32-bit hardware counter;
 * programTimerCountdown programs the timer from a 64-bit delay. Keep declarations
 * local for legacy drafts: u32 func_80026AF0(void);
 * void programTimerCountdown(u64); void func_80028100(u32);
 * D_8007BD60 is u32 last count; g_80038820 is Nw2TimerQueueEntry *.
 */

/* Verified by matched B06F0: action/entity common prefix accesses.
 * func_800D3650(void *,void *) returns an angle-table index (s32,
 * truncated to s16 by caller); func_800D4198(s16) returns s8.
 * Keep declarations local for legacy source compatibility.
 * stepEntityXZQuadraticSpline(void *entity,void *controlPoints) returns
 * s32 completion; controls are three records of four f32 values each.
 */

/* PI handle prefix used by writePiHandleWord: timings are bytes +5..+8,
 * domain byte +9 selects cached handle D_80037620[domain], base address +C. */
typedef struct {
    u32 f0;
    u8 f4, latency, pulse, page, release, domain;
    u16 pad;
    u32 base;
} Nw2PiHandle;
/* s32 writePiHandleWord(Nw2PiHandle *,u32 address,u32 value);
 * Keep declaration local for legacy callers. */

/* Matched DFC8C: quadrant-indexed u16 direction-mask tables D_800E3CD0
 * and D_800E3CD8 choose actions 0x1C and 0x1B. The helper takes
 * (entity, otherEntity, s32 directionMask, Nw2DirectionResult *direction).
 * Other entity flags 0x40/0x100 select those actions; flag0x80 selects
 * action0x1D with own u64 flag0x8000000000 set by heading delta <=0.
 * Declare table externs locally for legacy source compatibility. */

/* Matched 2A820 resource invalidation: extended 0x18-byte resource entry.
 * Key+0, allocation+4, u16 variant+0x12, u16 string length+0x14,
 * u16 rolling sum+0x16. Last two compare together as a u32.
 * Keys with bit0x40000000 bypass string hashing; other keys are u8* strings.
 * Hash sums byte[i] << (i&7), modulo65536. 2A820 marks existing key -1
 * and clears a referenced keyed-buffer slot's +0/+0x40/+0x44 if in pool.
 * Return -1 for invalidated existing entry, zero for empty/no entry.
 */
typedef struct {
    u32 key;
    void *allocation;
    u8 reserved[10];
    u16 variant;
    union { struct { u16 length, sum; } h; u32 word; } hash;
} Nw2ResourceEntryHashed;

/* Memory-region init descriptors passed BY VALUE to func_80000700 (and, by the
 * caller's declaration, func_8000082C) -- see matched func_80013108.
 * Nw2InitRect (16 bytes) goes in a0-a3; Nw2InitBig (20 bytes) goes entirely on
 * the caller's stack (sp+0x10..0x20).  Descriptor records are 36 bytes and
 * contiguous: record n begins at 0x80036E30 + n*0x24; the two records in the
 * init loop have their Big halves at D_80036E40 and D_80036E64.
 * IMPORTANT: passing the 9 words as separate s32 arguments compiles to a
 * different load schedule (the 5th-arg load is hoisted and arg9 lands in t2);
 * use struct-by-value calls.  Nw2InitRect = {srcStart,srcEnd,dstStart,icacheEnd};
 * Nw2InitBig = {icacheEnd,dcacheStart,dcacheEnd,bzeroStart,bzeroEnd}. */
typedef struct {
    s32 srcStart, srcEnd, dstStart, icacheEnd;
} Nw2InitRect;
typedef struct {
    s32 icacheEnd, dcacheStart, dcacheEnd, bzeroStart, bzeroEnd;
} Nw2InitBig;

/* Matched C2B8C: per-entity part motion extents. Source field tables
 * D_80070C70/D_80070C78 have 23 records/entity, 31 floats (0x7C)/part.
 * D_800FADE0 is f32[][23], D_800E3AC0 f32[], D_800E5920 f64.
 * f32 func_800D3564(f32); keep declaration local for legacy callers. */

/* Matched 98EEC: 96 priority/resource request entries behind D_800E7518.
 * key +0, signed accumulated amount +4 (saturates at255), u16 flags +6,
 * active +8. s32 func_80098EEC(s32 key,s32 flags); flags stays full-width
 * for first-loop equality, but is truncated on storage for new entries.
 * Keep extern/prototype declarations local for legacy compatibility. */
typedef struct {
    s32 key;
    s16 amount;
    u16 flags;
    s32 active;
} Nw2ResourceRequest;

/* Matched B728: copies arrays of eight-byte graphics unions, indexed (not
 * pointer-postincrement) loops; D_80070458/45C are pointer fields at stride8,
 * D_80073FA4/FA8 pointer fields at stride0x3F4, D_80073E90 s16 counts,
 * D_800706A4 signed-byte enables. convertRgba16ToGrayscale(void *,u16) called on
 * the variable-count destination when u16 D_800307A0 == 1.
 * Keep externs/prototypes local for legacy compatibility. */

/* Matched B5DC4: s8 func_800B5DC4(void *entity,s16 clampMode).
 * Quadrant s16+3E selects signed Z/X/-Z/-X from f32+74/+6C.
 * mode0 tests the oriented position in [D_800E54E0,D_800E54E8).
 * Nonzero mode clamps to f64 D_800E54F0 via translateEntityXZ and
 * returns1 iff position >= threshold. Local f32 vec[3] initializes only
 * X/Z; Y intentionally unused. Keep prototype local for legacy callers. */

/* setViSpecialFeatures (80020F20): nonvolatile VI context view required for
 * mask constant hoisting into branch delay slots. The volatile view above
 * is useful for other SDK entry points but changes this routine's schedule. */
typedef struct {
    u16 state, pad;
    s32 value;
    void *mode;
    s32 control;
} Nw2ViContext;

/* Matched 1009C: side/slot float-pair ramp uses same 0x28 layout as
 * Nw2FloatPairRamp, but +4 is f32 angle and target fields +14/+18 are
 * volatile: both stores must be followed by explicit reloads. */
typedef struct {
    s16 mode, steps;
    f32 angle, x, y, reserved10;
    volatile f32 targetX, targetY;
    f32 reserved1C, incrementX, incrementY;
} Nw2SideSlotRamp;
/* void setupSideSlotRamp(s16 side,s16 slot,s16 mode,s16 steps,f32 angle,f32 y,f32 x);
 * Keep prototype local for legacy callers. */

/* Packed-nibble grid used by 29E94 and 2A1C4; width is in pixels,
 * buffer has width/2 bytes per row. Signed width/height, not unsigned. */
typedef struct {
    u8 reserved0[4];
    u8 *buffer;
    u8 reserved8[4];
    s16 width, height;
} Nw2NibbleGrid;
/* s32 countNibblePixelNeighbors(void *,s32 x,s32 y,s32 level,s32 packedByte);
 * Keep declaration local for compatibility with legacy sources. */

/* Controller Pak inode unit: two-byte union passed BY VALUE in high half
 * of a1 by 24018. Replacing with u32 loses the exact entry schedule. */
typedef union {
    struct { u8 bank, page; } inode_t;
    u16 ipage;
} Nw2PakInodeUnit;
/* 24018 counts references to page, stops at two, propagates read errors
 * other than 3; inode cache has selected bank byte +100 and bitmap +101.
 * s32 countControllerPakPageReferences(u8 *pfs,Nw2PakInodeUnit page,u8 *inodeCache);
 * Keep declaration local for compatibility with legacy sources. */

/* Matched 0498C: void func_8000498C(Nw2Descr4BA8 *,u16 resourceId).
 * Stack metadata and read-work buffers are s32[4], in that order.
 * lookupResourceDescriptor(void *,u16) supplies allocation size at metadata+8;
 * func_80003684(void *,u16,void *) loads the packed resource bytes.
 * Byte1 bit80 becomes descriptor+6, low7 become signed count+2;
 * byte2 becomes signed count+1, byte3 high/low nibbles -> +4/+5.
 * func_80007B50(s32 pool,u8 count) and func_80007B84(s32 pool,u16 count)
 * allocate records in optional pool at descriptor+28. Keep prototypes local.
 */

/* Matched loadAudioRingBuffer (8001FC7C): builds RSP SETBUFF/LOADBUFF
 * commands for s16 ring samples, wrapping when requested span exceeds end.
 * Buffer prefix +14=s16 *base, +1C=s32 sampleCount. Arguments:
 * (buffer, s16 *start, s32 dmemByteOffset, s32 sampleCount, command *out),
 * returns next eight-byte command. Keep prototype local for legacy callers.
 */

/* Matched saveAudioRingBuffer (8001FDEC): same buffer/arguments/return as
 * loadAudioRingBuffer. SETBUFF word1 packs output DMEM offset<<16 with
 * byte count; SAVEBUFF opcode06000000. Split spans reset SETBUFF after
 * saving the wrapped second span; contiguous spans emit just two commands.
 */

/* WORKED OUT by (near-matched) func_800CFA50, the D_800FAF5C + D_800F9B00 paired
 * action state machine (cases 0..10 via jtbl_800E6A80). Both globals are the SAME
 * struct type: s8 f0; s16 f4 (timer, ==1 test); u16 f8 (anim); s16 fA; s16 fC
 * (state); s16 fE; s16 f16; u64 flags +0x20; u32 f2C; s32 f58 (heading);
 * f32 vec[3] +0x33C; s32 f348; u8 f351; u16 f360 (input bits 1/2/4/8); s8 f362;
 * pointer +0x364 to a record whose u64 flags are at +0x38; u32 f3AC.
 * Helpers: void selectTurnAnimationCDC04(void*,void*); void func_800D0700(void*,void*,u16);
 * s16 func_800D5438(void*,s32); void func_800A6BE0(void*,s32);
 * void beginPairedEntityActions(void*,s32,void*,s32);
 * s32 func_800D2BEC(void*,void*,void*,f32,u16,s32) - passing 1.0f (f32 prototype)
 * makes KMC emit lui a3,0x3f80 before the a0 load (matches the ROM; raw 0x3F800000
 * as s32 schedules a3 one slot later).
 * KMC quirks: a flag variable of a narrow type (u16/s16/s8/u8) produces the
 * `move v0,v1; beqz v0` test for `if (res = flag)` (s32/u32 coalesce and give
 * `beqz v1`), so use u16 in such if/else flag patterns.
 * A condition whose then and else bodies are identical calls is cross-jumped but
 * KMC keeps the mask computation: e.g. `if (x->flags & MASK) f(a); else f(a);`
 * leaves `lw hi/lw lo/andi...` with no branch, then f(a) runs unconditionally.
 * func_800CFA50 cases: 0 falls into 1; 3 falls into 4 (fC++ only); 5 falls into 6. */

/* WORKED OUT by matched func_8009EDBC (D_800EB408 action state machine, cases 0..7
 * via jtbl_800E44E0): like the D_800FAF5C action object, plus u16 f28 at +0x28
 * (also read as a u32 word there for a flag test), s16 quadrant f3E at +0x3E,
 * s32 heading f58, f32 vec[3] at +0x33C, s32 f348, s8 f354.
 * case0 falls through into case1; case5 falls through into case6 (no break).
 * D_800E3C90/D_800E3CA0 are s32[quadrant] heading tables, D_800E3CD0 u16[] mask table,
 * D_800FADC6 s16[] indexed by (s8)D_800FADB8, D_800FAF8A u16.
 * func_800C38FC signature is (void *entity, u64 mask, s32 value): the u64 forces the
 * o32 ABI to pass mask in a2/a3 (a1 skipped) and value on the stack at sp+0x10, which
 * matches every call site (e.g. (o, 0x40001000000000ULL, 0x1000000)).
 * translateEntityByActionQuadrant(void *) = func_800A7968; translateEntityXZ(void*,void*).
 * f32 func_800D63F0(void *, void *, s16) (2nd arg 0), void func_800D37C0(s32 heading,
 * f32 distance, f32 *outXYZ); func_800D3684(s32,s32)/6 uses magic 0x2AAAAAAB.
 * KMC quirk: `(v & A) && !(v & B)` is folded to one `(v & (A|B)) == A` test; write
 * nested ifs instead to keep the separate `andi` tests. Declare helpers locally. */

/* WORKED OUT by matched func_800E0D60 (D_800FAF5C state machine, cases 0..5 via
 * jtbl_800E7700, prologue D25D0(4.0f) + D2B64(2.0f,0,0xFFFFE)):
 * action object: s32 +0; s16 timer +4; s16 +6; s32 +8; s16 state +C; s16 +E;
 * s16 +0x16 countdown; u64 flags +0x20 (hi word at +0x20); s32 heading +0x58;
 * s32 turn step +0x348. D_800FABE6 u16 input bits (0x10/0x20/0x4000/0x8000),
 * D_800FADB8 s8 entity index, D_800FADBE/D_800F9B70 s16[], D_800FAF8E u16[],
 * D_800F9B14 s32 animation id, D_800FAF78 s8, D_800FAF8A u16.
 * s16 updateEntityHealthLevel(void *); void func_800E1560(void *,s32);
 * s8 func_800A93C0(void); s8 selectNewLinkedTarget(void *,s32);
 * void func_800A7240(void *,s32,s32,u64). Declare these locally.
 * Struct layout can be copied from the matched source (not added here to avoid
 * typedef conflicts with that source).
 * TIP: case0 falls through into case1. Write conditions positively with the
 * big true block first and an `else { o->fC++; break; }` at the end: KMC then
 * places the cold else block after the whole case (matches this function).
 * Case2's A7240 call needs a temp for D_800F9B14 to load a1 before a0. */

/* Matched BFB20: s32 readEntityStunState(s8 entityId,s16 *level,s16 *extra).
 * Reads signed level at D_800F9D24 (entity+14), clamps ordinary levels
 * to 1..99 unless zero flag20000; flag80000 gives100 and BF700(entity,0,4).
 * Returns whether high-word flag400 (u64 mask40000000000) is set.
 * s16 updateEntityStunTimer(void *,s32,s32); keep prototype local for legacy callers. */

/* Matched E0420: s32 tryBeginPairedActionOnContact(u8 *source,u8 *target,f32 distance).
 * Global D_8007EF30+170 bit100 OR source flag40 permits paired actions36/37;
 * requires common flag140, target flag400000, target high-word10 clear,
 * and source flags3 clear. Clears source high-word02000000 on success.
 * D_800E76D0 is an f64 boundary margin. Keep declarations local. */

/* Matched 07C90: row-major 4x4 float rotation matrix, three angles in degrees.
 * D_800307B0 is f32 pi/180. sinf(f32) returns sine.
 * Keep trig prototypes local for legacy compatibility. */
void buildEulerRotationMatrixDegrees(f32 [4][4],f32,f32,f32);

/* D3CCC: bits1/2 classify first entity facing toward/away from second,
 * bits4/8 classify second facing toward/away from first (inclusive 90deg).
 * Uses X/Z at +6C/+74 and signed heading at +58. */
/* getEntityPairFacingFlags(u8 *,u8 *): facing mask, declare locally; some callers use s32 return. */

/* E1F1C packs four 0x30-byte records into four 12-byte records.
 * Input +4/+8/+C are f32, +10/+14/+18/+1C are s32 (cvt.d.w).
 * Scale constants D_800E7770 and D_800E7778 are const f64.
 * Matched source uses its local PackedFieldRecord typedef; use this name in new code. */
typedef struct {
 u8 id,mode;
 s16 x,y,z;
 s8 a,b,c,d;
} Nw2PackedFieldRecord;
/* void packFieldRecords(Nw2PackedFieldRecord *); local prototype for legacy type. */

/* Matched 1E0AC: audio ADPCM voice prefix: +14 compressed buffer physical
 * source, +18 decoder state pointer, +30 s32 (*dma)(s32,s32,s32),
 * +34 callback context, +40 reset to zero, +44 callback source.
 * Builder takes (8-byte commands*,voice*,s32 sampleCount,s32 loadBytes,
 * u16 outputDmem,s32 inputDmem,s32 flags) and returns next command.
 * Keep signature local for legacy caller compatibility. */

/* convertRgba16ToGrayscale(u16 *pixels,u16 count) converts RGBA5551 in place.
 * u16 channels; unsigned double-to-integer casts emit 2^31 correction paths.
 * gray = (red + (u16)(u32)(green*0.7) + (u16)(u32)(blue*0.4))/3;
 * all RGB channels become gray, original alpha bit preserved.
 * Scale globals 8003B0F0/8003B100/8003B108 are const f64.
 * Keep prototype local to accommodate legacy void* declarations. */

/* Matched 046F0 (buildVertexDisplayList): 8-byte display-list command written as
 * two u32 words. The original used the GBI-macro shape
 *   { Nw2GfxCommand *q = g++; q->w0 = ...; q->w1 = ...; }
 * (block-scoped q per command = temp copy of g). The descriptor is
 * Nw2Descr4BA8: +1 s8 vertex count, +2 s8 vertex-data offset (in 8-byte units),
 * +0x14 display-list buffer pointer. Vertex bytes are packed RGBA16-ish:
 * w = ((r*2 & 0xFF) << 16) | ((g << 9) & 0xFE00) | (b*2 & 0xFF) [| opcode]. */
typedef struct {
    u32 w0, w1;
} Nw2GfxCommand;

/* Matched 800DA158 (sibling of 800A627C/800A63D8): the action object at
 * D_800FAF5C. +0 s32, +4 s16 phase timer (tested `<= 0` -> bgtz skip),
 * +0xC s16 switch state, +0x16 s16, +0x3C s16 index into s32 D_800E3CA0,
 * +0x3E s16 index into s32 D_800E3CC0, +0x58 s32 heading.
 * `o->fC++` on the s16 field is emitted as lhu/addiu/sh (KMC quirk). */
typedef struct {
    s32 f0;
    s16 f4, f6;
    s32 f8;
    s16 fC, fE;
    u8 pad10[4];
    s16 f14;
    s16 f16;
    u8 pad18[0x24];
    s16 f3C;
    s16 f3E;
    u8 pad40[0x18];
    s32 f58;
} Nw2F5CAction;

/* Matched resetControllers (216D0): s32 (void *queue,u8 *connectedMask).
 * Status records are {u16 type;u8 status,error;}[4], stack +10, followed
 * by s32 message at +20 and u8 temporary mask at +24.
 * 2184C(s32 command),218F0(u8 *mask,status*),27744(void),277B0(void).
 * Keep declarations local for legacy types. */

/* selectAudioVoiceSlot(void *owner,s32 index) returns a voice index.
 * Audio voice +64 s32 priority, +94 owner pointer, +9C sample word,
 * +C6 u16 kind. Owner +4 is s32 *sample table. The third scan intentionally
 * tests only the first voice repeatedly (no pointer increment).
 * Keep prototype local for legacy owner-struct declarations. */

/* Matched B242C: D_800E3CF0 is a u16 direction-command table indexed
 * by (s16)func_800D3650(source+6C,target+6C). D_800E5290 is f64;
 * compared to action f32 array +48 indexed by source s16 quadrant +3E.
 * Keep table/threshold extern declarations local for legacy compatibility. */

/* Matched A3A74: entity +378 is u8 animation/frame value, compared
 * to Nw2F408.f6. Calls s16 func_800D5438(void *,s32) then
 * void func_800D427C(void *,s16,s32); A83DC is an s8 predicate.
 * Entity u64 flags800000 and1000000 are tested/set in this paired handler. */

/* Matched B09E8: D_800E3CF0 direction command table and D_800E5240
 * f64 distance threshold are const ROM data. Declare locally as const
 * to permit threshold-load / command-store scheduling across each other. */

/* readPiHandleWord (80028210): checks output pointer with EX/epirawread.c line43,
 * waits for PI idle, updates cached domain timings, reads uncached base|address.
 * s32 readPiHandleWord(Nw2PiHandle *,u32,u32 *); declare locally for legacy types. */

/* Matched AC208: s8 requestAttachmentAction(void); maps attachment halfword IDs
 * (+24 if action s16+24>=65, else +26), minus1, into actions36..3C/2F/30.
 * Keep declaration local for legacy callers. */

/* buildColorOverlayDisplayList (06B84): (u8 *object,u8 red,u8 green,u8 blue,u8 alpha).
 * Object +10 display-list allocation (0x300 bytes); +14 transform pointer,
 * +19 enable byte. Sets transform float+24=-15000 on first allocation.
 * Keep prototype local for legacy compatibility. */

/* Vertex-centroid calculation at 016F4: signed coordinates stored in u16 fields,
 * 16-byte vertex stride. Mesh +C vertices, +1B signed count; object +4 mesh,
 * +C/+10/+14 float centroid. */
typedef struct { u16 x,y,z; u8 reserved[10]; } Nw2CentroidVertex;
typedef struct { u8 reserved0[12]; Nw2CentroidVertex *vertices; u8 reserved10[11]; s8 count; } Nw2CentroidMesh;
typedef struct { s32 f0; Nw2CentroidMesh *mesh; s32 f8; f32 x,y,z; } Nw2CentroidObject;

/* Matched 12B38: D_8005A730 is four 0xDC-byte object records;
 * +0 link, +14 points to part {u32 flags@0; f32 z@24}. D_8005B110
 * holds six 0x2C-byte Nw2Descr4BA8 descriptors, D_8005B0F8 s32[6].
 * D_800651A0 object records have [side][23] dimensions; D_80070478
 * and D_80070479 are signed-byte selected descriptor/slot at stride2.
 * void func_80012B38(s16 side,s16 descriptor,s16 slot); local declaration.
 */

/* findControllerPakFile (252E0): s32 (void *pfs,u16 company,u32 game,
 * u8 *optionalName16,u8 *optionalExtension4,s32 *outIndex).
 * Directory entry: u32 game@0, u16 company@4, extension[4]@C,
 * name[16]@10, total32 bytes. pfs +50 directory count, +5C start block.
 * __osContRamRead(s32 queue,s32 channel,u16 block,void *out32) reads a block.
 * Local prototypes retain compatibility with legacy callers.
 */

/* The 0x800A34xx/0x800A36xx/0x800A3Axx action-handler family
 * (800A3428/800A3610/800A3A74): A = D_800EB408 is the action object,
 * B = D_800EB40C the entity.  Layout shared by both pointers:
 * s32 f0; s16 f4; s16 f6; s16 f8; u64 flags at +0x20 (big-endian: +0x20 is the
 * HIGH word, +0x24 the low word, so KMC emits `and hi,0` + `and lo,mask` for a
 * u64 literal with zero high half); s32 f2C; s8 f362.
 * The first statement of these handlers is the guard
 *   if (!(B->f2C & 0x380)) func_800D2BEC(A, B, 0, 4.0f, 0, 0xFFFFE);
 * (D2BEC signature: s32(void*,void*,void*,f32,u16,s32); 0xFFFFE, not -2).
 * Flags clear uses `flags &= ~0x40000000ULL`, set uses `flags |= 0x40000000ULL`.
 * Keep this typedef local in a file if a same-named type appears there. */
typedef struct {
    s32 f0;
    s16 f4;
    s16 f6;
    s16 f8;
    u8 padA[0x16];
    u64 flags;
    u8 pad28[4];
    s32 f2C;
    u8 pad30[0x332];
    s8 f362;
} Nw2ActionEB408;

/* Matched D5B74: void func_800D5B74(s8 entityId,s8 otherId,u32 mode).
 * D_800F97D8 is an s16 wrapping coordinate/angle with period600;
 * D_800F97DC receives its normalized copy. D_800F9D14 is u16 per-entity
 * field at stride0x3B0 (local extern u16 D_800F9D14[][0x1D8]).
 * Use an explicit s16 *p=&D_800F97D8 for final normalization to retain
 * its address across both conditional corrections and the last load.
 */

/* Matched deleteControllerPakFile (80024180):
 * s32 deleteControllerPakFile(void *pfs,u16 company,u32 game,u8 *name,u8 *extension);
 * PFS prefix: queue s32+4, channel s32+8, directoryBase s32+5C,
 * bankCount u8+64, activeBank u8+65. Directory record is32 bytes,
 * starting inode {bank,page} at bytes6/7. Locals declared inode u16[128],
 * directory u8[32], fileNo s32, next Nw2PakInodeUnit produce target stack.
 * Keep prototype local for compatibility with legacy caller declarations.
 */

/* Matched 927B0: graphics descriptor +4 vertex pointer, +8 u16 count.
 * The display-list writer takes (Nw2GfxCommand **,s32,descriptor*).
 * Local declarations retained for legacy signatures. */
typedef struct { s32 reserved0; u32 vertices; u16 count; } Nw2VertexDescriptor927;

/* Synthesizer command builder family (func_8002060C/80020800/80020894/80020928,
 * segment main). D_80037510 points to a state record:
 *  +0x00 head of pending list (nodes: +0 next, +8 fn(node)->s32, +0x10 s32 time)
 *  +0x14 deferred free-list consumed by func_80020800
 *  +0x1C current time (s32), +0x20 play position in samples (s32)
 *  +0x38 sink record {void *f0; Gfx*(*f4)(void*,s16*,s32,s32,Gfx*); void (*f8)(void*,s32,s32*);}
 *  +0x48 max chunk size (s32)
 * func_80020928(st,&node) returns the pending node with minimal (node+0x10 - st+0x20)
 * and writes it through the out pointer (NULL when list empty); 80020894(st,x) advances
 * a node; 80020800(st) frees the deferred list via func_8002023C/2021C.
 * Emitted graphics command is 8 bytes {u32 w0; u32 w1;}, w0=0x07000000.
 * NOTE: declare the prototypes locally with void* so legacy sources stay compatible:
 *   s32 func_80020928(void *, void **); s32 func_80020894(void *, s32);
 *   void func_80020800(void *);
 * Matching quirk (unresolved in 8002060C): KMC hoists the 0x07000000 word into a
 * callee-saved register ($s6) out of the second loop; writing it as a plain literal
 * rematerializes `lui` in-loop instead and every callee-saved colour shifts.
 */

/* Matched beginPairedEntityActions (A6E44): both action parameters are s16.
 * Resets states +C/+E/+360, bytes +362/+363 to signed -1; establishes
 * reciprocal IDs at +353 and target +351. Flag reset uses u64 mask
 * ~0x10810000000ULL then OR 0x1000000000ULL. */
void func_800DECAC(void *, s32, s32, s32);
void func_800A700C(void *);
/* void beginPairedEntityActions(void *,s16,void *,s16); local for legacy callers. */

/* Matched DCFBC: both DB4FC and D4CC4 return low-byte booleans;
 * BF62C takes an s32 delta even when the source field is signed byte +3A2.
 * Keep declarations local for legacy callers:
 * s8 func_800DB4FC(void *,void *); s8 func_800D4CC4(void *);
 * void addEntityHealthDelta(void *,s32);
 */

/* 90738: 48 transform/effect records at D_800D6D50, stride 0x178.
 * world matrix +0x5C, visibility flags +0x18 (bit80 hidden),
 * signed active count +0x160, signed amount +0x164, float scale +0x174.
 * Local prototypes: void func_8001B3EC(void *,f32,f32,f32,f32 *,f32 *,f32 *);
 * void func_800B82B8(f32 *,f32 *,f32 *,s32 *,s32 *,s32 *);
 */
typedef struct {
 u8 head[0x18]; u8 flags; u8 reserved19[0x147];
 s16 active, reserved162, amount; u8 reserved166[14]; f32 scale;
} Nw2EffectRecord;

/* Matched 2B8E4: builds a 0x2A-byte wrestler name/appearance record.
 * Input id/variant are s32; only the call to B630 truncates both to s16.
 * Lookup entries have a name string pointer at +8. Output has long name
 * +0 (25 bytes), short name +0x19 (11 bytes), appearance bytes +0x24..28.
 * ID404 variants1/3 use "<Mortis>"; ID601 variants1/3 use "<THQ man>".
 * Local prototypes: void func_8000B630(u8 *,s16,s16);
 * void func_80021F60(void *,s32); void func_80028C44(void *,void *);
 * void func_80028BB8(void *,void *);
 */

/* Matched ABE20: action record +0 is s16 mode (sets4), +12 s16
 * animation ID passed to s8 func_800D4198(s16), +48 f32[4] indexed
 * by D_800F9B60's signed quadrant +3E. Thresholds E4E50/58/60 are f64.
 * Declare symbols locally for legacy caller compatibility. */

/* Matched 98C40: draw-list descriptor {entry *entries; u32 count;}.
 * Each entry is 12 bytes: s32 id; s16 x,y; s32 extra.
 * Bit10000000 is cleared from id before dispatch; negative IDs and
 * 122..134 use 985CC, 01xx use 97E1C with u16 overlay table,
 * 51xx use 98804 with wrestler-name resource from 2B528.
 * Local declarations retain legacy source compatibility. */

/* Matched D63F0: f32 func_800D63F0(void *entity,void *optionalXZ,s16 mode).
 * Entity attachment pointer +364 has s8 tier +4; selects s16 threshold
 * tables E3F50/54/5C. s16 func_800BF1E0(void *,s32) is queried with3.
 * E3F64/E3F68 are interleaved f32 fields, stride8. Optional output gets
 * X at+0 and Z at+8 before flag/mode-specific return-value overrides.
 * Keep prototypes local for legacy call-site compatibility. */

/* Matched DF3E4: s32 func_800DF3E4(u8 *source,u8 *target,s32 mask,f32 distance).
 * mask10 permits action9 for source flag80, paired actions32/33 for
 * target flag400000 and shared flag140 within boundary+margin,
 * paired actions34/35 for target byte37 bit1 and shared flag40 in range,
 * otherwise action40. Calls E212C before all but action9. */

/* buildScaledRotationTranslationMatrixFixed(void *out,f32 x,f32 y,f32 z,
 * f32 scale,f32 tx,f32 ty,f32 tz) builds a local float Euler matrix then
 * converts through func_8001B090(floatMatrix,out). Declare locally. */

/* entity flag word at D_800F9D30 (u64): D_800F9D30 is the HIGH u32, D_800F9D34 the LOW u32.
 * Access per-entity with *(u64 *)(D_800F9D30 + i*0x3B0) (stride 0x3B0). func_800B955C clears
 * a u64 mask from it and passes two 4-byte {u8 id; s8 -1; s8 -1; s8 -1;} buffers to func_800B9730.
 * D_800FA061 is a byte field at entity+0x131 (same 0x3B0 stride). */
extern u8 D_800FA061[];
extern s16 D_800EB474;
extern s16 D_800EB478;

/* Matched DD188: void func_800DD188(void), action-state handler analogous
 * to DCFBC. Case0 gated by low-byte B60C8 result; starts animation E7,
 * D427C mode1, calls DACE4 ignoring result, increments state. Cases1/2
 * share DCFBC completion logic. Its B60C8 call tests an s8 result (sll24),
 * unlike other callers that declare B60C8 s32; keep prototype local. */

/* Matched AB780: D_800FAF50 is an s16 entity-indexed table. Its /3
 * quotient is truncated to s16 before (+1)*40 is passed to D4198.
 * AC208, AC0B4 and AB43C are low-byte booleans (s8 return), despite
 * older drafts using s32. Keep prototypes local for legacy compatibility. */

/* Matched 9F468: C778C is also called with only the entity argument
 * when entity +0x30 already selects a definite animation (0x10000000).
 * Use a local one-argument declaration for this caller; the fallback
 * second parameter is unused on that selected path. */

/* Matched 19C80: audio object+0x20 points to 0x28-byte regions.
 * Parameter IDs encode (id-2)/8 region and (id-2)%8 field. */
typedef struct {
    u32 start, end;
    s16 f8, fA, fC, padE;
    f32 rate;
    s32 f14, f18;
    f32 f1C;
    s16 *f20;
    s32 f24;
} Nw2AudioRegion;
/* Region field5: rate = ((f32)value/1000.0f)*2.0 / D_80036F54[16].
 * Field6: fractional offset = ((f32)value/D_8003B510)*(u32)(end-start).
 * Field7 writes through f20 and calls 1CEF0 if nonnull. */

/* Matched D7128: constructs three 16-byte control points from two entity
 * positions (+4C) and a third position, and sets per-entity interpolation
 * state D_800F97F0 (s32[]) / D_800F9800 (f32[]). Returns s16 duration.
 * s16 func_800D7128(u8 *,u8 *,void *,u8 *); keep local for legacy callers.
 * D_800E3E20 is f32[], indexed by (s16)(absolute angle delta / 113).
 */

/* Matched D7690 input-counter helper: s16 func_800D7690(u8 *entity,s32 buttons,s16 mode).
 * Mode0 resets s16 D_800F9810/9818/9820 entity-indexed counters (0,0,2).
 * Mode1 debounces mask C030 with D_800F9820, counts accepted input in 9810;
 * returns 2 below state-dependent threshold, 1 on threshold, 4 for threshold0.
 * Mode2 counts masked inputs in 9818; mode3 retrieves that counter.
 * D_800FAF62/FAF64 are s16 field tables with 6-byte entity stride.
 * Keep declarations local for legacy source compatibility. */

/* OSTask prefix copied and physicalized by loadRspTask (osSpTaskLoad). */
typedef struct {
    u32 type, flags;
    void *boot; u32 bootSize;
    void *ucode; u32 ucodeSize;
    void *data; u32 dataSize;
    void *stack; u32 stackSize;
    void *output, *outputSize;
    void *input; u32 inputSize;
    u32 *yield; u32 yieldSize;
} Nw2RspTask;
/* void loadRspTask(Nw2RspTask *); declare locally for legacy sources. */

/* Matched E27B4: s16 func_800D4D44(void *entity,s32 mode,f32 value);
 * s8 func_800D8D74(void *entity,s32 mode); void func_800D7E80(void *,s32);
 * void func_800E1920(void *,s32). Keep declarations local for legacy callers.
 * E27B4 uses signed-byte D_800F99A0[D_800FADB8] to index 0x30-byte
 * records and copies record byte+0 to byte+1 (D_800F98E0 -> D_800F98E1).
 */

/* updateFieldRecordMotion (E1B9C): four 0x30-byte records, s16 loop index.
 * Byte+3 flags: bit1 lowers Y(+8), bit8 selects floor90 (else0),
 * bits2/4 enable motion. X/Z +4/+C; heading +1C; f32 speed +20,
 * speed delta +24, Y velocity +28, Y velocity delta +2C.
 * func_800D37C0(s32 heading,f32 distance,f32 *outXYZ) -- confirmed
 * here; keep prototype local for older callers with pointer signatures.
 */

/* Matched isEntityActionEligible (800A94B4): s32 (u8 *source,u8 *target,s16 action).
 * Keep declaration local for legacy caller compatibility. Source attachment
 * pointer+0x364 has u64 capabilities+0x38; entity u64 status flags+0x20. */

/* Matched submitGraphicsTask (800028B4): input {s32 id;u32 framebuffer;u16 pad,clear;},
 * display-list cursor, s16 flags, s16 microcode selector. Four task buffers at
 * D_80044590[], index s16 D_8002EEBC. Task header at buffer+4000; OSTask at+4010.
 * D_800445A0/A4/A8 are pointers: DRAM stack, yield buffer, output buffer.
 * Keep declarations local to avoid legacy types. */

/* Matched 9F8D0: D_800EB408 s16 counter+16 increments with signed comparison<6;
 * s32 +348 is heading delta /5, used for five-frame turn toward quadrant(+3E)&3.
 * u16 +E bits1/2 track input attempted / B71F8 success. Signature local:
 * s8 func_800B71F8(void *,s32,s32); u16 func_800B6DEC(void *,s32,s32). */

/* Matched updateAudioVoices (80014500): s32(void). Voice stride0x158:
 * u64 clock+10 incremented by u16+BC; event times u64+20/+28/+50;
 * countdown s32+18 (-1 disabled), stream flags s32+48/+4C;
 * u64 prior clock+58 -> u16 elapsed+CA = (clock-prior)>>8.
 * Active s32+4, state s32+8, flags+0 bit1 skips voice.
 * D_800604CC has 0x1C-byte per-voice handles, D_800604D0 voice pool.
 * Keep signature local for legacy callers. */

/* Matched AE8E8: s16 func_800AEBF0(void); returns direction index or -1.
 * D_800E3CF0 is a u16 direction-command table. D_800FABF8/FAC00 are
 * f32 field tables, FABFC/FAC04 s16 field tables, all entity stride0x40.
 * Keep symbol declarations local for legacy compatibility. */

/* Matched C5A28: entity byte+3A3 is a saved animation selector;
 * substate1 loads it via A7C40 before falling into substates2/3/4.
 * D_800FAF8E is u16[] indexed by signed D_800FADB8, bitsF00 select
 * animations5/6 for high flag01000000, or9D/9F otherwise. */

/* Matched C6D54: A837C(entity) before selected-target command updates;
 * target high-word flag2000 (u64 mask200000000000) directs updates to
 * target itself; otherwise signed link byte D_800FA063 (entity+353)
 * redirects flags D_800FA070 (entity+360). FA061 is entity+351. */

/* updateAudioVoiceEnvelope (80015118) verified field view. Other voice
 * routines may use different local views of the same 0x158-byte record. */
typedef struct {
    u8 reserved0[0x10];
    u64 clock;
    u8 reserved18[0x40];
    u64 envelopeStart;
    u8 reserved60[0x10];
    u64 releaseStart;
    f32 attackSlope, decaySlope, releaseSlope;
    s32 envelopeRate;
    u8 reserved88[0x57];
    u8 envelopePeriod;
    u8 initialLevel, peakLevel, sustainLevel;
    u8 envelopePhase, envelopeLevel, envelopeCountdown;
    u8 attackDuration, decayDuration, releaseDuration;
    u8 reservedE9[4];
    u8 releaseLevel;
} Nw2AudioEnvelopeView;

/* Recovered by 11764 (99.1%): 16-byte animated CI4 display-list state
 * at D_8005AAA0, three command-buffer pointers followed by slot/type/frame
 * and signed countdown. D_8005AAAC/AD/AE/AF are its field tables.
 * Declare externs locally for compatibility with existing sources. */
typedef struct {
    void *buffers[3];
    u8 slot, type, frame;
    s8 countdown;
} Nw2AnimatedCi4State;
/* 11764 calls buildCi4TextureDisplayList(void *texture,void *commands,u16 type),
 * returning the next command pointer, and func_800015AC(void *,s32).
 * Its descriptor stride is 0xDC; subrecord +30/+34 are deliberately zeroed
 * before receiving the vertex and command pointers. */

/* Matched 0082C: 16-byte struct by value causes the four incoming home-area saves.
 * This is NOT a varargs thunk. Both descriptor types come from caller 13108. */
/* void func_8000082C(Nw2InitRect rect, Nw2InitBig regions); declare locally for legacy sources. */
/* Matched readRomSynchronousChunks: void(s32 romAddress,s32 destination,s32 size),
 * transfers in <=512-byte chunks and waits on a temporary message queue. */

/* initializeTransformNode (800014D8), matched: void(void *node,u8 kind,f32 x,f32 y,f32 z).
 * Six link/state words +0..+14 cleared, bytes+19/+1A cleared, kind at+18.
 * Local transform +1C, identity matrices +5C/+9C. Keep declaration local for legacy callers.
 * func_80004B34 matched signature: void(void *node,u8 *descriptor,s8 kind,f32 x,f32 y,f32 z).
 * 014D8/04B34 required `f32 value=*(volatile f32 *)&stackFloatParam;` snapshots
 * to preserve the original lwc1+mfc1 instead of KMC's combined lw.
 */

/* Audio voice prefix used by matched countAudioVoicesByKey/80013DB0:
 * 0x158-byte records, s32 key at +0x60 and s16 value at +0xBE.
 * 13DB0 returns number of matching nonzero-key voices whose +BE it sets.
 * Use typed record pointer when storing fields so KMC hoists D_800604C8.
 */
typedef struct { u8 reserved0[0x60]; s32 key; u8 reserved64[0x5A]; s16 valueBE; u8 reservedC0[0x98]; } Nw2AudioVoiceKeyRecord;

/* Matched audio-voice setters 13E80/13EF0 also use typed 0x158-byte records:
 * +44 f32 = supplied float + f32(+AC) for matching s32 key(+60).
 * +B8 s16 = supplied integer clamped1..256; +BC s16 = (u16(+C8)*integer)>>7.
 * Direct global loop bound D_800604C8 with typed pointer preserves the target
 * hoisted count's extra v0-to-a3/t0 move; a cached count local removes it.
 */

/* Matched B4690: s32 resolveEntityMoveHeading(void *entity,u16 inputMask,s32 *outHeading).
 * Clears u16 +28, entity high-word flag80 and low-word flag01000000;
 * sets quadrant s16+3E and output heading using direction-mask helpers.
 * Local signatures (legacy callers differ): s16 func_800D7B08(u16);
 * s16 func_800D7A2C(u16); s16 func_800D65D0(void *,u16);
 * s8 func_800B4B3C(void *); s8 func_800D26A0(void *,void *,s32).
 */

/* Matched C9014: D_800FAF5C->+4 is read as s16 timer in this action;
 * +C s16 state, +360 u16 phase flags, +362 s8 target ID (-1 on finish).
 * D_800EB550 is an s8 target-ID table indexed by D_800FADB8;
 * D_800F9D10 + targetID*0x3B0 is passed as target entity.
 * s8 func_800A93C0(void); void func_800B68A0(void *,void *,void *);
 * void applyMovementToEntityPair(void *,void *,u16); keep prototypes local.
 */

/* Matched 11BB4: vertex initializer func_80007920 takes nine arguments:
 * (void *vtx,s32 x,s32 y,s32 s,s32 t,s32 r,s32 g,s32 b,s32 alpha).
 * Allocates four 16-byte vertices at D_8005B218. Data pairs built by
 * func_8000670C(void *,s16,s16) have eight-byte stride at D_8005B220.
 * D_8005AAA0 is void *[4][4] (three allocated buffers + separate byte at+C).
 * D_8007E010..28 field arrays have 0x5C-byte stride.
 * Keep extern/prototype declarations local for legacy type compatibility.
 */

/* Matched BD45C: void func_800C472C(void *,void *,s32), passed same
 * entity twice and mode2 after paired-action completion. Entity +2C is u32
 * action flags (bits80/800000/1000000); +8 is s16 animation ID.
 * D_800FADC6 is an s16 table indexed by signed-byte D_800FADB8.
 * Keep helper prototype local for legacy callers.
 */

/* Matched A164C: D_800EB408 action object +35 is u8 state/control flags,
 * +42 is signed-byte index into s16 D_800E3262; +14/+16 signed-16 counters.
 * D_800F9B68 is s16[] indexed by D_800FADB8. ++signed16 counter >60
 * produces lhu/addiu/sh/sll16/sra16/slti61. State switch cases0..7.
 */

/* WORKED OUT by func_800D54A0 (best 195, 436/437 insns; only one regalloc swap left):
 * Per-frame table D_800EB6D0 is s16 [4][0x258][6]: fields 0..3 = x (entity+0x4C),
 * z (+0x54), y (+0x50), s16 heading (+0x58); field 4 = u16 anim id (entity+0x8);
 * field 5 = ((entity+6)-1 clamped at 0) & 0x3FF, ORed with 0x8000 when
 * D_800EB6B8[i] is 2 or 3, 0x4000 when 6 (default 0) -- a jump table needs every
 * in-range case listed (case 0: case 1: case 4: case 5: break;), otherwise KMC
 * emits a compare chain instead of the 7-entry table.
 * Entity table D_800F9D10 stride 0x3B0: +2 s16 state (-1 = empty), +6 s16 f6,
 * +8 u16 f8, +0x20 u64 flags, +0x4C/+0x50/+0x54 f32 x/y/z, +0x58 s32 heading,
 * +0x353 s8 linked id, +0x382 u8. Frame cursor record D_800F97D0 (f2 aliases
 * D_800F97D2) has two gaps: +0 s8, +1 u8, +2 s16 f2, +4/+6/+8 s16, +0xA pad,
 * +0xC s16 fC, +0xE pad, +0x10 s16 f10. D_800F97D8/D6/D8 are u16 for the
 * frame/step math (lhu) but read as s16 through a pointer for the index (lh).
 * KMC tricks used here: `#define REC ((Nw2FrameRec *)&D_800F97D0)` (cast the
 * struct address at each use, not a named pointer) makes GCC keep the record
 * address in a2 across the search loop and yields the target's bnel+loop-init
 * delay preheader; `extern u8 D_800E3F30[]` + `*(u16 *)(D_800E3F30 + (s8)
 * D_800F97D0.f0 * 2)` stops hoisting that load above the following stores;
 * inline `(s32)D_800F97D0.f0` in the subscript (no cached id local) makes the
 * loop load the id before the frame.
 * REMAINING: in the D_800FABD8&0x100 tail loop the ROM keeps the frame pointer in
 * a1 and the id*0x1C20 base in a2 (with a `move a1,a2`), while the best source
 * has them swapped (p in a2, base in a1). All other instructions match.
 */

/* WORKED OUT by matched func_800CA758: D_800FAF5C and D_800F9B00 are the SAME
 * object type (a local `Nw2F5C` in that file; NOTE this is NOT the same layout as
 * the context Nw2F5CAction above -- here f8 is u16, not s32, and the record
 * extends to +0x360/+0x3AC). Offsets: s8 f0; s16 f4 (phase timer); u16 f8 (anim);
 * s16 fA; s16 fC (switch state); s16 fE; s16 f14; s16 f16; s16 f18 (countdown);
 * u64 flags at +0x20 (BE: +0x20 = HIGH word, +0x24 = LOW); s16 f44; s32 f58
 * (heading); u16 f360 (bits 1/2/4/8/0x10/0x20/0x40); u32 f3AC.
 * Flag literals: `flags |= 0x400000000000ULL` (hi|=0x4000), `flags |= 0x80000000000000ULL`
 * (hi|=0x800000 -- the case-2 "0x800000" mask lives in the HIGH word),
 * `flags |= 0x10000000` (low), `flags &= ~0x400ULL` (low). */

/* Matched A3610: uses Nw2ActionEB408 for both D_800EB408 and D_800EB40C.
 * Guard checks SECOND object's u32 +2C mask380 before D2BEC(first,second,
 * NULL,4.0f,0,0xFFFFE). Second flag800000 transfers low-word flag40000000,
 * signed byte362 and word2C to first; requests action49. Verified local
 * signatures: s16 func_800D5438(void *,s32);
 * void func_800D427C(void *,s16,s32); s8 func_800C472C(void *,void *,s32).
 * Keep local declarations for legacy caller compatibility.
 */

/* Matched 21230 (controller init): func_80026DD0 returns native u64 time;
 * func_80026FA0 takes (void *timer,u64 delay,u64 interval,void *queue,void *message).
 * ABI leaves a1 unused; first u64 occupies a2/a3, next occupies stack10/14.
 * Keep declarations local for legacy callers. Threshold is 23437500 ticks.
 */

/* Matched createViManager(s32 priority), formerly 258C0:
 * D_80037630 manager is 0x1C bytes: s32 active, thread*, queue*, eventQueue*,
 * three callback/access pointers. D_8003764C is a separate counter, NOT a field.
 * Thread D_80063898, aligned stack D_80063A50[0x1000], queue D_80064A50.
 * Stack end and queue share an address but need distinct source expressions.
 * Keep prototype and extern declarations local for legacy compatibility. */

/* Matched B93B0: standalone signed byte at D_8007E228+0x92.
 * Using its scalar symbol avoids KMC caching the array-offset address across calls. */
extern s8 D_8007E2BA;

/* freeResourceDescriptorArray (800072E8): (void *base, void *allocation, s16 count).
 * 0x2C descriptor stride: active u8+0, owned buffers+C/+10/+14,
 * cached shared buffer+18, owned buffer+1C, pool marker+28.
 * Nonzero pool marker suppresses freeing the first three buffers.
 * Cache node: next+0, data+4, key u16+8, refcount u16+A.
 * Signature kept local for older callers using s8 count/s32 allocation. */

extern u8 D_C5B90[];

/* func_800900C0 scene-node setup: absolute display-list constant D_C5B90=0xC5B90. */

/* slantNibbleBitmapRows (80029FFC) uses the Nw2NibbleGrid layout:
 * width+0xC and height+0xE are signed16. Flag0x8000 selects a 24-row
 * slant pattern; otherwise14 rows. Shift=(period-1-y%period)/4 pixels.
 * void slantNibbleBitmapRows(void *,s32 flags); keep prototype local. */

/* Matched applyMovementToEntityPair (wrestler body-part XZ delta application): the entity
 * passed as first/second argument (D_800FAF5C for the source, D_800F9D10 +
 * targetID*0x3B0 for the target) has: s8 id at +0, quad x/y/z at +0x4C/+0x50/
 * +0x54 and s32 heading +0x58, then 20 16-byte body parts at +0x5C (partA,
 * x@+0, z@+8) and 20 more at +0x1CC (partB). Use:
 *   typedef struct { f32 x,y,z,pad; } Nw2Part;
 *   typedef struct { f32 x,y,z; s32 heading; } Nw2Quad;
 *   typedef struct { s8 id; u8 pad1[0x4B]; Nw2Quad q; Nw2Part partA[20];
 *                    u8 pad2[0x30]; Nw2Part partB[20]; } Nw2BodyEntity;
 * D_800E6D78 is an f64 scale. func_800D63F0(void*,void*,s16)->f32;
 * s32 func_800D7A68(s32); void func_800D2600(void*,s32,f32);
 * s32 func_800D2B64(void*,f32,u16,s32); s32 func_800D2BAC(void*,void*,f32,s32);
 * s32 func_800D35B0(s32,s32). Keep local (legacy callers differ). */

/* Matched __osViSwapContext is libultra's __osViSwapContext (older SDK, KMC 2.7.2):
 * programs the VI from the "next" osViContext and swaps __osViCurr/__osViNext.
 * __osViNext = __osViNext, __osViCurr = __osViCurr (pointers; the two context
 * objects at 0x80038860 / 0x80038830 are exactly Nw2OsViContext, size 0x30).
 * field = *(vu32*)0xA4400010 & 1 (odd/even field). func_8001CE80 = osVirtualToPhysical.
 * VI state bits: 2 = XSCALE_FACTOR_SET, 4 = YSCALE_FACTOR_SET, 0x20 = BLACK,
 * 0x40 = REPEATLINE, 0x80 = FADE. __additional_scanline = D_8003764C. (distinct name
 * from the SDK's Nw2ViContext so legacy sources keep compiling). */
typedef struct {
    s32 origin;      /* fldRegs.origin, added to physical framebuffer */
    s32 yScale;      /* fldRegs.yScale */
    s32 vStart;      /* fldRegs.vStart */
    u32 vBurst;      /* fldRegs.vBurst -> VI_V_BURST */
    u32 vIntr;       /* fldRegs.vIntr  -> VI_V_INTR  */
} Nw2OsViFldRegs;    /* stride 0x14 per field */

typedef struct {
    u8 pad0[8];
    u32 width;       /* +0x08 -> VI_WIDTH   */
    u32 burst;       /* +0x0C -> VI_BURST   */
    u32 vSync;       /* +0x10 -> VI_V_SYNC  */
    u32 hSync;       /* +0x14 -> VI_H_SYNC  */
    u32 leap;        /* +0x18 -> VI_LEAP    */
    u32 hStart;      /* +0x1C -> VI_H_START */
    u32 xScale;      /* +0x20 -> VI_X_SCALE */
    u8 pad24[4];
    Nw2OsViFldRegs fldRegs[2];  /* +0x28, stride 0x14 */
} Nw2OsViMode;

typedef struct {
    u16 state;       /* +0x00 VI_STATE_* bits */
    u16 pad2;
    void *framep;    /* +0x04 osVirtualToPhysical(framep) gives the base */
    Nw2OsViMode *modep; /* +0x08 */
    u32 features;    /* +0x0C -> VI_CONTROL */
    u8 pad10[0x10];
    u32 xScale;      /* +0x20 x.scale  */
    f32 yFactor;     /* +0x24 y.factor */
    u16 yOffset;     /* +0x28 y.offset */
    u16 pad2A;
    u32 yScale;      /* +0x2C y.scale  */
} Nw2OsViContext;    /* size 0x30 (copied whole by __osViSwapContext) */

/* Audio voice record used by func_8001488C (state machine, ~0xF8 bytes).
 * Other audio sources declare their own conflicting prototypes for
 * func_80014D78/15068/15468/177D0/17980/17AC0 and D_800604CC/E0/G80036E80,
 * so keep those declarations local. */
typedef struct {
    u8 pad0[4];
    u8 *unk4;            /* +0x04 stream cursor */
    s32 unk8;            /* +0x08 */
    u8 padC[4];
    s32 unk10;           /* +0x10 */
    s32 unk14;           /* +0x14 */
    u8 pad18[0x28];
    f32 unk40;           /* +0x40 */
    u8 pad44[0xC];
    u32 unk50;           /* +0x50 */
    u32 unk54;           /* +0x54 */
    u32 unk58;           /* +0x58 */
    u32 unk5C;           /* +0x5C */
    u8 pad60[8];
    f32 unk68;           /* +0x68 */
    f32 unk6C;           /* +0x6C */
    s32 unk70;           /* +0x70 */
    s32 unk74;           /* +0x74 */
    f32 unk78;           /* +0x78 */
    f32 unk7C;           /* +0x7C */
    f32 unk80;           /* +0x80 */
    s32 unk84;           /* +0x84 */
    u8 pad88[0xC];
    u8 *unk94;           /* +0x94 -> +0x10 table base */
    u8 *unk98;           /* +0x98 -> +0x28/+0x2C tables */
    u8 pad9C[4];
    u8 *unkA0;           /* +0xA0 4-byte entry array */
    u8 padA4[0x16];
    u16 unkBA;           /* +0xBA */
    u8 padBC[4];
    u16 unkC0;           /* +0xC0 */
    u8 padC2[8];
    u16 unkCA;           /* +0xCA */
    u16 unkCC;           /* +0xCC */
    u16 unkCE;           /* +0xCE */
    u8 padD0[7];
    u8 unkD7;
    u8 padD8;
    u8 unkD9;
    u8 unkDA;
    u8 unkDB;
    u8 padDC;
    u8 unkDD;
    u8 padDE;
    u8 unkDF;
    u8 unkE0, unkE1, unkE2, unkE3, unkE4, unkE5, unkE6, unkE7, unkE8;
    u8 unkE9, unkEA, unkEB, unkEC, unkED;
    u8 padEE;
    u8 unkEF, unkF0, unkF1, unkF2, unkF3, unkF4;
    u8 padF5;
    u8 unkF6, unkF7;
} Nw2Voice1488C;

/* Matched D5D1C recorded-frame playback: 600-frame circular recording.
 * Entity records have stride7200/entity,12/frame; frame pointer D_800F97DA
 * MUST be reloaded after func_8000DB90 before reading animation metadata.
 * Four auxiliary records/frame have stride12/entity,48/frame.
 * D_800F97E2 is s16 tick counter (not u16); D_800E6D48/50/58 are const f64
 * scale factors. Declare these globals locally for legacy compatibility.
 * func_80010200(s16,s16,s32), func_8000DB90(s32,s32),
 * func_8000946C(s32,s16,s16), func_80008CE8(s32,s16,s16,f32*,s32,s8),
 * func_80012364(s16,s8,s8,f32*) are the matched local signatures.
 */

/* Matched D4604: s32 (s8 entityId, Nw2TargetLookAngles *out).
 * Tracks linked entity (signed byte D_800FA063 at 0x3B0 stride).
 * Outputs pitch/yaw; inactive path also clears roll. Pitch steps by4,
 * clamp +/-30; yaw steps by8, clamp +/-67.5. Keep signature local.
 * D_800F9D6C is Nw2DirectionResult[][59]; inline row accessor then +5
 * is necessary to preserve target's distinct base and +0x50 additions. */
typedef struct { f32 pitch, yaw, roll; } Nw2TargetLookAngles;

/* Matched A2050: D_800EB408 action object includes u16 counter+0x40,
 * u8 selection+0x42 (read as s8 for animation table), u8+0x43,
 * s16 timer+4, state+C, flags+E, saved result+0x18, u64 flags+0x20.
 * States0->1 and7->8 FALL THROUGH. s32 func_800D2B64(void*,f32,u16,s32)
 * uses float4.0/2.0 here; legacy raw-bit prototypes are not authoritative.
 * s16 func_800B6DEC(void*,s32,s32); void func_800D7690(void*,s32,s32).
 * Keep prototypes local for legacy source compatibility. */

/* readWriteControllerPakInode (2286C): (pak, u8 *inode256, s32 rw, u8 bank)
 * rw low byte0 reads,1 writes. Cache keyed channel+bank; verifies byte-sum
 * of inode[first*2..255] against inode[1], tries mirror on mismatch,
 * repairs primary if mirror is valid. Returns3 for both copies corrupt.
 * Pak prefix: queue+4, channel+8, primary base+54, mirror base+58,
 * first usable inode+60, bank count byte64, selected bank byte65.
 * Keep prototype local for legacy callers. */

/* Matched DEF84: s32 tryEntityAttackDEF84(u8 *entity,u16 input,u16 triggers,u16 directionMask).
 * All three masks MUST be u16 for exact incoming/saved-register copies.
 * Local helper signatures: s16 func_800D7A68(u16), func_800D7A2C(u16);
 * s8 checkEntityAttackHit(void *,u16); s16 func_800A76FC(void *,u16).
 * Keep prototypes local for compatibility with legacy callers. */

/* Confirmed CC158/CCC64: void func_800CCC64(void *entity,void *target,u32 input)
 * has THREE arguments. a3 at the call is a temporary, not a fourth argument.
 * Keep declaration local for legacy source compatibility. */

/* Matched CDF40 input gate: s32 func_800CDF40(u8 *entity,u16 held,u16 pressed,s16 mode,s16 *out).
 * Return codes: 0 no selection, 1 selection/eligible flag, 2 timeout animation, 3 alternate input.
 * Signature kept local for legacy callers. */

/* Matched B7CF4/B955C: s8 func_800B955C(u64 mask) takes ONE 64-bit mask,
 * passed in a0:a1. Callers use 0x2000ULL/0x1000ULL/0x800ULL.
 * Two s32 parameters yield incorrect zero-immediate and call scheduling.
 * Keep prototype local for legacy source compatibility. */

/* Verified by near-matched 01930 (all instructions exact apart from frame size):
 * Scene node: child+4, next+8, light/mesh list+14, enabled u8+1A, matrix+5C.
 * List entry: model pointer+4, next+8, f32 position+C/+10/+14,
 * s16 vertex count+2C, vertex pointer+30.
 * Vertex record stride16: s8 normal X/Y/Z at+C/+D/+E, u8 intensity at+F.
 * Use typed node/list/vertex structs to preserve pointer hoisting and register allocation.
 * Intensity assignment is naturally (u32)float, which generates the unsigned conversion bias path.
 */

/* Matched loadResampledAudioRingBuffer (8001FA64):
 * (buffer, oscillator, s32 dmemOffset, s32 sampleCount, void *commands)->void *.
 * Oscillator +0 start,+4 end,+18 position,+24 resample pointer;
 * resample +14 state pointer,+20 f32 fraction,+24 u32 flags (byte+27).
 * Keep prototype local for legacy caller compatibility. */

/* Matched pushAudioSequenceLoopState (800165FC): voice arrays +100/+110/+120
 * are four u8* each; +130/+138 are four u16 each; +140/+144/+148 are four u8
 * each. +FB u8 depth; +DC u8 stream value; +90 f32 saved as unsigned byte;
 * +48/+4C cursors; +C2/+C4 u16 countdowns. Direct typed arrays are crucial
 * for initial parameter-copy register allocation. Returns input cursor+1. */

/* Matched pullAudioMixerChildren (8001E230):
 * (mixer, void *context, s32 sampleCount, void *arg3, commands)->commands.
 * Mixer +14 s32 childCount,+1C child-pointer array; child +4 is callback
 * commands *pull(child,context,sampleCount,arg3,commands).
 * Commands are {u32 w0,w1}. Emits CLEARBUFF at DMEM 6C0 and 800 before
 * iterating children. Keep prototypes local for legacy caller types. */

/* D_800FAF5C / D_800F9B00 action record, offsets verified in func_800AC3A0:
 * f2C is at 0x2C (u32, 4-byte pad after the u64 flags at +0x20), vec [3] at 0x33C,
 * f348 at 0x348, f360 u16, f362 s8, f36C u8, f371 u8, f3A3 u8.
 * Declare the two globals locally as `extern ... *D_800FAF5C;` (matched sources disagree). */
typedef struct {
    s8 f0;
    u8 pad1[3];
    s16 f4;
    s16 f6;
    u16 f8;
    s16 fA;
    s16 fC;
    s16 fE;
    u8 pad10[6];
    s16 f16;
    u8 pad18[8];
    u64 flags;
    u8 pad28[4];
    u32 f2C;
    u8 pad30[0x28];
    s32 f58;
    u8 pad5C[0x2E0];
    f32 vec[3];
    s32 f348;
    u8 pad34C[0x14];
    u16 f360;
    s8 f362;
    u8 pad363[9];
    u8 f36C;
    u8 pad36D[4];
    u8 f371;
    u8 pad372[0x31];
    u8 f3A3;
} Nw2ActF5C_AC3A0;

/* Step playback of a recorded pose animation (matched stepRecordedFramePlayback,
 * 0x800D5D1C).  Four player slots; each slot owns a 600-frame stream of 12-byte
 * pose samples.  The stream fields are SEPARATE linkable byte symbols 2 bytes
 * apart (D_800EB6D0..D_800EB6DA), so address each with its own symbol + byte
 * offset: a struct/array base would change the %hi/%lo relocations and break the
 * match.  Per-frame layout (stride 12): +0 s16 x, +2 s16 z, +4 s16 y, +6 s16 w,
 * +8 s16 clip, +0xA u16 poseFlags (bit0 reverse, bit0x3FF clip length,
 * bit0x4000/0x8000 orientation flags).  Player stride is 0x1C20 (600*12).
 * The output transform (D_800F2750..) is likewise parallel byte symbols with an
 * s8 attribute pair + s16 xyz + four s8 attributes. */
typedef struct { f32 x, y, z; s32 w; } Nw2PlaybackVec;
typedef struct { f32 x, y, z; s32 a, b, c, d; } Nw2PlaybackOut;

/* buildCiTextureDisplayList (matched 0x80005704): emits the RDP display list
 * for a color-index (CI) texture object.  colorPtr nonzero enables an optional
 * 0x03 cull command when count<9; dl is the write pointer, next ends the list. */
typedef struct { u32 w0, w1; } Nw2RdpCmd;
typedef struct {
    u8 pad[2];
    u8 mode;          /* 1 = 8-bit CI, otherwise 4-bit */
    u8 pad3;
    u8 clampS, clampT, maskS, maskT;
} Nw2TextureFormat;
typedef struct {
    u8 pad0[2];
    s8 count, first;
    u8 pad4[4];
    u16 width, height;
    void *colorPtr;
    Nw2RdpCmd *dl;
    void *next;
    Nw2TextureFormat *tex;
    u32 palette;
} Nw2TextureDisplayObj;

/* Entity records shared by the 0x800A/0x800C action code:
 * D_800F9D10 is an array of 0x3B0-byte records. Offsets used by many matched
 * update functions: +0x00 entity id (s8), +0x0A action type (s16), +0x0C
 * state-machine case selector (s16), +0x20 status/flag word (u64), +0x28
 * sub-flags (u16), +0x35 action flags (u8), +0x351 slot index (u8), +0x33C
 * trajectory vector (f32[4]), +0x355 target entity id (s8).
 * D_800FAF5C is the current entity pointer and D_800F9B00 its paired partner;
 * animations are started with func_800D427C(ent, animId, mode). Most paired
 * action updates are `void f(void){ switch(D_800FAF5C->[0x0C]) { ... } }` and
 * rely on case fallthrough (case 0 into case 1): keep case order intact. */


