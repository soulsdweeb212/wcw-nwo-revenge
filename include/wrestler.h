/* wrestler.h: the per-wrestler match record (0x3B0 bytes) of WCW/nWo Revenge.
 *
 * D_800F9D10 holds four of these, one per player slot (0x800F9D10..0x800FABD0), in overlay 2's BSS. There is no
 * fifth record: every loop runs i < 4. docs/wrestler.md explains each field with its evidence. This header is a map
 * for reading and porting; the matched C does not use it yet (it still uses raw offsets), so a field name here
 * changes no build output.
 *
 * Coordinates: world units, Y up. Ring centre (0,0); ropes at |x|,|z| = 230; apron standing line 265; ring platform
 * edge 280; floor out to 528; entrance aisle on +Z out to z = 1250. Y = 90 on the mat and apron, 0 on the floor.
 * Angles: 0x1000 = 360 degrees; heading 0 faces +Z, 0x400 faces +X; forward = (sin, cos).
 * Time: one tick = 1/30 s (the match clock counts 30 ticks per second).
 *
 * Names with a "?" in the comment are only partly understood; unkXXX fields have no known meaning. */
#ifndef WRESTLER_H
#define WRESTLER_H

#include "common.h"

/* A cached world position of one skeleton joint (game coordinates, w unused). */
typedef struct {
    f32 x, y, z, w;
} WrJointPos;

/* Decoded metadata of the current animation (+0x368..+0x383). */
typedef struct {
    s32 headingDelta;   /* 0x368 turn built into the animation, added to heading when it ends */
    u8 frameCount;      /* 0x36C length in frames; animFramesLeft starts here */
    u8 loop;            /* 0x36D */
    u8 endZone;         /* 0x36E zone after the animation: 1 ring, 2 floor, 3 apron (4-bit value) */
    u8 endPose;         /* 0x36F pose the animation ends in, copied to pose (+0x42) */
    u8 hitStart;        /* 0x370 frame window in which the move can hit (also the ring->floor frame of falls) */
    u8 hitEnd;          /* 0x371 */
    u8 unk372[4];
    u8 busyStart;       /* 0x376 busy window */
    u8 busyEnd;         /* 0x377 */
    u8 reversalFrame;   /* 0x378 ? */
    u8 unk379;
    u8 activeStart;     /* 0x37A frame window in which a dive or paired move moves the body */
    u8 activeEnd;       /* 0x37B */
    u8 cancelFrame;     /* 0x37C after this frame the animation can be cancelled */
    u8 unk37D[7];
} WrAnimMeta;

/* The current move, unpacked from the move table of moveOwnerId (+0x38C..+0x3AF). */
typedef struct {
    u16 unk38C;             /* 0x38C 11-bit value */
    u16 nameId;             /* 0x38E 12-bit move id / name */
    s8 power;               /* 0x390 base damage */
    s8 spiritGainSelf;      /* 0x391 spirit added to the attacker on hit */
    s8 spiritDeltaTarget;   /* 0x392 spirit added (usually negative) to the target on hit */
    u8 stunBits;            /* 0x393 can stun / daze (state 0x2A) */
    u8 koBits;              /* 0x394 can knock out (state 0x29) */
    s8 attackPart;          /* 0x395 attacker body part used, 0..4 */
    s8 targetPart;          /* 0x396 target body part hit, 0..4 (4 = not a limb) */
    s8 activeJoint[3];      /* 0x397 striking or steered joints */
    s8 targetJoint;         /* 0x39A joint of the opponent aimed at */
    u8 unk39B;
    u8 partDamage[5];       /* 0x39C damage to each of the target's 5 body parts */
    u8 unk3A1;
    s8 spiritOnFinish;      /* 0x3A2 spirit added to self when certain moves (poses) end */
    u8 moveCode;            /* 0x3A3 */
    s8 unk3A4;              /* 0x3A4 copied to lastMoveTakenParam of the target */
    u8 unk3A5;
    u8 range;               /* 0x3A6 dive / jump range factor */
    u8 unk3A7;
    u8 unk3A8[2];           /* 0x3A8 change D_800F9B78 */
    u8 unk3AA[2];
    u32 flags;              /* 0x3AC move properties (0x80 pin-able, 0x200/0x1E00 paired-move kinds ...) */
} WrMove;

typedef struct Wrestler {
    s8 id;                  /* 0x000 own slot 0..3 */
    u8 unk001;
    s16 characterId;        /* 0x002 wrestler id (0xBNN: bank in bits 8..11, index+1 low byte); -1 = slot empty */
    s16 animFramesLeft;     /* 0x004 counts down; <= 0 = animation finished */
    s16 animFrame;          /* 0x006 counts up from 0 */
    s16 animId;             /* 0x008 animation index; -1 forces a restart */
    s16 state;              /* 0x00A action state 0x00..0x91, index into the handler table D_800E2FF0 */
    s16 step;               /* 0x00C step inside the state; 0 on every state change */
    u16 stepFlags;          /* 0x00E per-state scratch bits */
    s16 health;             /* 0x010 hidden health 0..255; not shown on the HUD */
    s16 healthMax;          /* 0x012 recoverable ceiling: -total/4 per hit, never below 128 */
    s16 spirit;             /* 0x014 spirit meter 0..100 (50 neutral, 100 = SPECIAL ready); the HUD bar */
    s16 stateTimer;         /* 0x016 per-state timer */
    s16 escapeTimer;        /* 0x018 kick-out / submission escape / stay-down countdown; < 0 = escaped */
    u8 unk01A[6];
    u64 flags;              /* 0x020 WR_FLAG_* */
    u16 moveMode;           /* 0x028 ? locomotion / whip bits (0x20 running, 0x2 whipped, 0x8 rope run) */
    u16 unk02A;
    u32 grappleCtx;         /* 0x02C grapple context, copied to the partner without bit 2 */
    u32 hitInfo;            /* 0x030 incoming-hit descriptor that picks the reaction; sub-mode of state 0x28 */
    u8 unk034;
    u8 koFlags;             /* 0x035 1 KO, 2 stun, 4 was running off the ropes, 8 knocked flat ... */
    u8 unk036;
    u8 frameStatus;         /* 0x037 bit 0 = rebounding off the ropes (state 0x14); cleared every tick */
    u8 frameBits;           /* 0x038 low two bits cleared every tick */
    u8 unk039;
    s16 counterKind;        /* 0x03A ? kind of opponent strike being countered / move variant */
    s16 ringSide;           /* 0x03C side of the ring the root is on: 0 +Z, 1 +X, 2 -Z, 3 -X (every tick) */
    s16 dirIndex;           /* 0x03E side or corner index for the current action; meaning depends on the state */
    s16 knockdowns;         /* 0x040 knockdowns since last standing free; each shortens down time by 80 */
    u8 pose;                /* 0x042 end pose of the last animation: 0 standing ... 7..32 down */
    u8 comboHits;           /* 0x043 consecutive hits taken, capped at 4 */
    u16 lastMoveTakenId;    /* 0x044 move id of the last move received (the finisher at match end) */
    s16 lastMoveTakenParam; /* 0x046 */
    u16 nextCharacterId;    /* 0x048 next entrant for this slot (battle royal) */
    u8 unk04A[2];
    f32 x, y, z;            /* 0x04C root position */
    s32 heading;            /* 0x058 facing, -0x800..0x7FF */
    WrJointPos jointA[23];  /* 0x05C joint positions (1..19 filled); jointA[1] (+0x6C) = pelvis, body centre */
    WrJointPos jointB[23];  /* 0x1CC second point of each bone (its far end), same frame */
    f32 moveDelta[3];       /* 0x33C per-tick displacement for scripted movement (y used by dives) */
    s32 turnPerTick;        /* 0x348 heading change per tick */
    s8 bodyPart[5];         /* 0x34C condition of each body part, starts 50, <= 0 = injured */
    s8 heldById;            /* 0x351 who holds / attacks me, also the last attacker; -1 when I lead */
    s8 secondAttackerId;    /* 0x352 the second attacker of a double team */
    s8 opponentId;          /* 0x353 current opponent / focus (who I face and attack) */
    s8 steppedOverId;       /* 0x354 last downed wrestler stepped over (states 0x89/0x8A); -1 = none */
    s8 partnerId;           /* 0x355 tag partner; own id when there is none */
    u8 unk356[2];
    u64 partnerFlags;       /* 0x358 the partner's flags, copied at the start of each tick */
    u16 pairSignals;        /* 0x360 handshake bits between the two sides of a paired move or hold */
    s8 attached[2];         /* 0x362 records driven by my current move (3-man: [0] helper, [1] victim) */
    u8 *profile;            /* 0x364 64-byte character profile */
    WrAnimMeta anim;        /* 0x368 */
    s8 moveOwnerId;         /* 0x384 whose move table the current move is from */
    u8 unk385;
    s16 moveId;             /* 0x386 index into that table */
    u8 unk388[4];
    WrMove move;            /* 0x38C */
} Wrestler;                 /* 0x3B0 */

/* Bits of Wrestler.flags. Only bits whose meaning was checked in the code are listed; docs/wrestler.md has the rest. */
#define WR_FLAG_CPU             0x4ULL                  /* controlled by the AI */
#define WR_FLAG_IN_RING         0x40ULL                 /* zone: inside the ropes (Y 90) */
#define WR_FLAG_ON_APRON        0x80ULL                 /* zone: on the apron (Y 90) */
#define WR_FLAG_ON_FLOOR        0x100ULL                /* zone: arena floor or aisle (Y 0) */
#define WR_FLAG_ZONE_MASK       0x1C0ULL                /* usually one bit; 0xC0 / 0x180 while moving between zones */
#define WR_FLAG_LEGAL           0x200ULL                /* legal man / active participant */
#define WR_FLAG_SPIRIT_EMPTY    0x20000ULL
#define WR_FLAG_SPIRIT_FULL     0x40000ULL              /* taunt now to get SPECIAL */
#define WR_FLAG_SPECIAL         0x80000ULL              /* SPECIAL active (GameShark +0x25 = 8 writes this byte) */
#define WR_FLAG_RERUN           0x10000000ULL           /* state changed: run the handler again this tick */
#define WR_FLAG_UPDATED         0x20000000ULL           /* updated this tick */
#define WR_FLAG_PAIR_LEADER     0x40000000ULL           /* leads a paired move; attached[] follow it */
#define WR_FLAG_AUTO_FACE       0x100000000ULL          /* turn toward the opponent automatically */
#define WR_FLAG_TEAM_B          0x200000000ULL          /* team / side bit */

/* The four records, and the pointers set before each wrestler's update. */
extern Wrestler D_800F9D10[4];

#endif
