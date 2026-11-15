/* @header
 * func_800A2B5C
 * VRAM 0x800A2B5C | ROM 0x4F2CC | size 0x64
 * asm: asm/nonmatchings/code_80090000/func_800A2B5C.s
 */
#include "common.h"

#ifdef TARGET_PC
typedef Gfx G; /* PC: a command is port.h's 16-byte Gfx */
#else
typedef struct { u32 w0, w1; } G;
#endif
void func_800B6FE0(G **, s32);
#ifdef TARGET_PC
/* PC: D_8003A4FE is a label 6 bytes into D_8003A4F8, the 13 name tables (8 bytes each on the N64: the entries'
 * address, their count and an id), and D_8003A4FE[k * 4] is table k's id. On PC the tables hold a pointer, so they
 * are 16 bytes each (tools/port_data.py's TABLES) and the label has no PC symbol: the PC reads the id by name. */
typedef struct { void *entries; u16 count; u16 id; } Tbl2B5C;
extern Tbl2B5C D_8003A4F8[];
#else
extern u16 D_8003A4FE[];
#endif

void func_800A2B5C(G **dl, s32 unused, s32 k) {
    G *g;
    G *p;
    g = *dl;
#ifdef TARGET_PC
    func_800B6FE0(&g, D_8003A4F8[k].id); /* PC: the table's id by name, as above */
#else
    func_800B6FE0(&g, D_8003A4FE[k * 4]);
#endif
    p = g++;
    p->w0 = 0x7000206;
    p->w1 = 0x604;
    *dl = g;
}
