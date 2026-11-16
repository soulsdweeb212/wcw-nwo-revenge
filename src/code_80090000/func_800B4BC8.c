/* @header
 * func_800B4BC8
 * VRAM 0x800B4BC8 | ROM 0x61338 | size 0x2C
 * asm: asm/nonmatchings/code_80090000/func_800B4BC8.s
 */
#include "common.h"

typedef struct { u8 x[16]; } S;
#ifdef TARGET_PC
/* PC: the score ranking's default table, 9 tables of 10 records, by the record's fields (func_800BA940 reads them
 * from the save buffer, where func_800B8C4C copies them): an s32 score, a u16 at +4, 3 bytes at +6, a u16 at +0xA,
 * 3 bytes at +0xC. The PC starts game variables in its own byte order by the widths their declarations give
 * (port/game_vars.tsv), so the score and the two u16 must be declared as such; as plain bytes they stay in the ROM's
 * order, and the copies the game makes of them read as other numbers. The table is followed by 16 bytes that are not a
 * record (the variable's last bytes before D_800CD820), declared as bytes so that nothing turns them around. */
typedef struct { s32 score; u16 b; u8 c[4]; u16 d; u8 e[4]; } RankRec;
typedef struct { RankRec rec[9][10]; u8 tail[0x10]; } RankTable;
extern RankTable D_800CD270;

S *func_800B4BC8(s32 a) {
    /* as the N64: record a & 0xF of table a >> 4, ten records to a table */
    return (S *)(&D_800CD270.rec[0][0] + (a >> 4) * 10 + (a & 0xF));
}
#else
extern S D_800CD270[][10];

S *func_800B4BC8(s32 a) {
    return &D_800CD270[a >> 4][a & 0xF];
}
#endif
