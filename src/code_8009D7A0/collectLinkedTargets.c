/* @header
 * collectLinkedTargets  (originally func_800A7418)
 * VRAM 0x800A7418 | ROM 0x9A8B8 | size 0x2E4
 * asm: asm/nonmatchings/code_8009D7A0/collectLinkedTargets.s
 */
#include "common.h"

extern u8 D_800F9D12[];
extern u8 D_800F9D30[];
extern u8 D_800F9D34[];
extern u8 D_800F9D7C[];
void func_800D3890(void *, void *, void *);
/* Builds the list of valid nearby target candidates for `entity`:
 * clears the four output slots, then for each of the four 0x3B0-byte entity
 * records (s16 id at record+2) that is alive (id != -1), is not `entity`
 * itself, matches the u64 flag mask, and lacks flag 0x80000000000, computes
 * the direction from `position` to the record's vector and records
 * {id, distance, angle}.  Finally sorts the candidates by ascending distance. */
void collectLinkedTargets(void *entity, void *position, Nw2TargetCandidate *outCandidates, u64 flags)
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
    s32 off = i * 0x3B0;
    if ((*((s16 *) (D_800F9D12 + off))) != (-1))
    {
      if (i != (*((s8 *) entity)))
      {
        if ((flags == 0) || (((*((u64 *) (D_800F9D30 + (i * 0x3B0)))) & flags) != 0))
        {
          s32 off2 = i * 0x3B0;
          if (((*((u64 *) (D_800F9D30 + off2))) & 0x80000000000ULL) == 0)
          {
            func_800D3890(position, D_800F9D7C + off2, &res);
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
