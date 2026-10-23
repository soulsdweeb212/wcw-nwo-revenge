#include "common.h"

extern Nw2IdSubTable lookupSubTables[];
extern u16 D_8003A4FC[][4];

/* Search the id sub-tables for an entry with the given id. Ids with bit 0x1000
 * set search the upper 13 tables from the top down, others the lower 11 from the
 * bottom up. The packed (table << 8 | entry) index is truncated to its low byte;
 * -1 if the id is absent. */
s32 findIdSubTableEntryIndex(s32 id) {
    s32 table, entry, result;
    if (id & 0x1000) {
        id &= 0xFFF;
        for (table = 12; table >= 0; table--) {
            for (entry = 0; entry < D_8003A4FC[table][0]; entry++) {
                if (lookupSubTables[table].entries[entry]->id == id) { result = (table << 8) + entry; goto done; }
            }
        }
    } else {
        for (table = 0; table < 11; table++) {
            for (entry = 0; entry < D_8003A4FC[table][0]; entry++) {
                if (lookupSubTables[table].entries[entry]->id == id) { result = (table << 8) + entry; goto done; }
            }
        }
    }
    result = -1;
done:
    return result & 0xFF;
}
