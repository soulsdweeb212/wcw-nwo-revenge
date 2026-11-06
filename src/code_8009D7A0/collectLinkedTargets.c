/* @header
 * collectLinkedTargets  (originally func_800A7418)
 * VRAM 0x800A7418 | ROM 0x9A8B8 | size 0x2E4
 * asm: asm/nonmatchings/code_8009D7A0/collectLinkedTargets.s
 */
#include "common.h"

void func_800D3890(void *, void *, void *);
/* Builds the list of valid nearby target candidates for `entity`:
 * clears the four output slots, then for each of the four wrestler records
 * that is in use (characterId != -1), is not `entity` itself, matches the u64
 * flag mask, and lacks flag 0x80000000000, computes the direction from
 * `position` to the record's pelvis (jointA[1]) and records
 * {id, distance, angle}.  Finally sorts the candidates by ascending distance. */
void collectLinkedTargets(Wrestler *entity, void *position, Nw2TargetCandidate *outCandidates, u64 flags)
{
    Nw2TargetCandidate *out = outCandidates;
    s16 i;
    s16 count;
    s16 j;
    Nw2DirectionResult res;
    Nw2TargetCandidate tmp;
    i = 0;
    do
    {
        out[i].id = -1;
        i++;
    }
    while (i < 4);
    count = 0;
    for (i = 0; i < 4; i++)
    {
        if (D_800F9D10[i].characterId != (-1))
        {
            if (i != entity->id)
            {
                if ((flags == 0) || ((D_800F9D10[i].flags & flags) != 0))
                {
                    if ((D_800F9D10[i].flags & 0x80000000000ULL) == 0)
                    {
                        func_800D3890(position, &D_800F9D10[i].jointA[1], &res);
                        out[count].id = i;
                        out[count].dist = res.y;
                        out[count].angle = res.angle;
                        count++;
                    }
                }
            }
        }
    }
    for (i = 0; i < (count - 1); i++)
    {
        for (j = i + 1; j < count; j++)
        {
            if (out[i].dist > out[j].dist)
            {
                tmp = out[i];
                out[i] = out[j];
                out[j] = tmp;
            }
        }

    }

}
