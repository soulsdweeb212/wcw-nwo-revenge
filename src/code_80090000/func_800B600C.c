/* @header
 * func_800B600C
 * VRAM 0x800B600C | ROM 0x6277C | size 0x1C4
 * asm: asm/nonmatchings/code_80090000/func_800B600C.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: the table of loaded pictures is D_800E6BA0_ovl1 (port_decls.h), of common.h's Nw2MenuResSlot, and the key is a
 * MenuKey (port.h), as wide as a pointer: a resource id (1 to 0x1DE9), -1 for none, or a key of the resource-name
 * cache, which the N64 tells apart by its sign and the PC by MENU_KEY_IS_RES. For such a key the entry's key and data
 * are both the address of the resource-name cache's entry that func_8002A2FC returns (port_decls.h: a ResKey in, a
 * pointer out; func_8002A5F4 takes the entry back), as on the N64, where that address is negative too. MENU_KEY_NAME
 * keeps it a key of the cache on PC: it stops the program on an address that MENU_KEY_IS_RES would take for a
 * number. The function hands back the entry's data, a pointer. */
void func_8002A5F4(void *entry);
static inline Nw2MenuResSlot *find(MenuKey key) {
    s32 i = 0;
    Nw2MenuResSlot *p = D_800E6BA0_ovl1;
    for (; i < 0x80; i++) {
        if (p->key == key) {
            break;
        }
        p++;
    }
    return i != 0x80 ? p : NULL;
}

static inline Nw2MenuResSlot *get(MenuKey key, u16 t) {
    Nw2MenuResSlot *e;
    void *entry;

    if (MENU_KEY_IS_RES(key)) {
        entry = func_8002A2FC((ResKey)key, t);
        if (entry == NULL) {
            return NULL;
        }
        key = MENU_KEY_NAME(entry);
        e = find(key);
        if (e) {
            return e;
        }
        e = find((MenuKey)-1);
        if (e == NULL) {
            func_8002A5F4(entry);
            return NULL;
        }
        e->key = key;
        e->data = entry;
        e->refs = 2;
        e->flags |= 2;
        return e;
    }
    if (key == 0 || key >= 0x1DEA) {
        return NULL;
    }
    e = find(key);
    if (e) {
        return e;
    }
    e = find((MenuKey)-1);
    if (e == NULL) {
        return NULL;
    }
    e->key = key;
    e->refs = 2;
    e->flags |= 1;
    return e;
}

void *func_800B600C(MenuKey key, u16 t) {
    Nw2MenuResSlot *e;

    if (key == (MenuKey)-1) {
        return NULL;
    }
    e = get(key, t);
    if (e == NULL) {
        return NULL;
    }
    if (e->flags & 1) {
        return NULL;
    }
    e->refs++;
    return e->data;
}
#else
typedef struct { s32 a; s32 b; s32 c; s32 d; } N;
extern N D_800E6BA0[];
s32 func_8002A2FC(s32, s32);
void func_8002A5F4(s32);

static inline N *find(s32 id) {
    s32 i = 0;
    N *p = D_800E6BA0;
    for (; i < 0x80; i++) {
        if (p->a == id) {
            break;
        }
        p++;
    }
    return i != 0x80 ? p : 0;
}

static inline N *get(s32 id, u16 t) {
    N *e;

    if (id < 0) {
        id = func_8002A2FC(id, t);
        if (id == 0) {
            return 0;
        }
        e = find(id);
        if (e) {
            return e;
        }
        e = find(-1);
        if (e == 0) {
            func_8002A5F4(id);
            return 0;
        }
        e->a = id;
        e->b = id;
        e->c = 2;
        e->d |= 2;
        return e;
    }
    if (id == 0 || (u32)id >= 0x1DEA) {
        return 0;
    }
    e = find(id);
    if (e) {
        return e;
    }
    e = find(-1);
    if (e == 0) {
        return 0;
    }
    e->a = id;
    e->c = 2;
    e->d |= 1;
    return e;
}

s32 func_800B600C(s32 id, u16 t) {
    N *e;

    if (id == -1) {
        return 0;
    }
    e = get(id, t);
    if (e == 0) {
        return 0;
    }
    if (e->d & 1) {
        return 0;
    }
    e->c++;
    return e->b;
}
#endif
