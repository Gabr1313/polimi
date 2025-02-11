#define NDEBUG                           // no asserts
#define CAP_EXP        2                 // >= 1 allocated once
#define CAP            4                 // >= 1 allocated once
#define WORD_LEN       256               // max word length
#define BUFF_LEN       (WORD_LEN * 257)  // > 2
#define CHECK_SHIFT    5                 // found empirically
#define PRE_FETCH_DIST 16                // found empirically
#define P1(x)          __builtin_expect(x, 1)
#define P0(x)          __builtin_expect(x, 0)
#define prefetch(x)    __builtin_prefetch(x)

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef uint32_t u32;
typedef uint64_t u64;

typedef struct _Heap {
    u32   size, cap, mem_size;
    u32   (*cmp)(void *x, void *y);
    void *inner;
} Heap;

typedef struct _Shelf {
    u32  sum, update_time;
    Heap hp;
} Shelf;

typedef struct _Ingredient {
    Shelf *shl_ptr;
    u32    weight;
} Ingredient;

typedef struct _Recipe {
    u32         cap_ref, size;  // .cap_ref meh... it would be nicer to have 2 structs
    char       *name;
    Ingredient *where_to_start;
    // Ingredient *circ_buff; // is hidden behind `recipe_ing_circ_buff()` -> avoid pointers deref
} Recipe;

typedef struct _Food {
    Recipe *rcp_ptr;
    u32     quantity, time, weight;
} Food;

typedef struct _ExpWeight {
    u32 expiration, weight;
} ExpWeight;

typedef struct _Order {
    Recipe *rcp_ptr;
    u32     quantity, time;  // .time +=0x80000000 if it is cooked
} Order;

typedef struct _VecQ {
    Order *inner;
    u32    size, cap, del;
} VecQ;

typedef struct _Bucket {
    u64             hash;
    void           *ptr;
    struct _Bucket *next;
} Bucket;

typedef struct _HashMap {
    u32     size, cap;  // .cap is a power of 2
    Bucket *buckets;
    void    (*free_inner)(void *inner);
} HashMap;

u32     tick;
HashMap warehouse, cookbook;
VecQ    wait_queue;
Heap    to_deliver, truck;
char    buffer[BUFF_LEN], *str_buffer;

HashMap hm_new(u32 cap_exp, void (*free_inner)(void *inner)) {
    HashMap hm = {
        .size       = 0,
        .cap        = 1 << cap_exp,
        .free_inner = free_inner,
        .buckets    = calloc(hm.cap, sizeof(*hm.buckets)),
    };
    assert(hm.buckets != NULL);
    return hm;
}

void hm_free(HashMap hm) {
    for (u32 i = 0; i < hm.cap; i++) {
        Bucket *buk = &hm.buckets[i], *next_bk;
        if (buk->hash == 0) continue;
        hm.free_inner(buk->ptr);
        for (buk = buk->next; buk != NULL; buk = next_bk) {
            next_bk = buk->next;
            hm.free_inner(buk->ptr);
            free(buk);
        }
    }
    free(hm.buckets);
}

void hm_insert_no_resize(HashMap *hm, u64 hash, void *ptr) {
    hm->size++;
    Bucket *buk = &hm->buckets[hash & (hm->cap - 1)];
    if (buk->hash != 0) {
        Bucket *buk_old = buk;
        buk             = malloc(sizeof(*hm->buckets));
        assert(buk != NULL);
        buk->next     = buk_old->next;
        buk_old->next = buk;
    }
    buk->hash = hash;
    buk->ptr  = ptr;
}

void hm_double(HashMap *hm) {
    Bucket *old_shelves   = hm->buckets;
    u32     old_cap       = hm->cap;
    hm->cap             <<= 1;
    hm->size              = 0;
    hm->buckets           = calloc(hm->cap, sizeof(*hm->buckets));
    assert(hm->buckets != NULL);
    for (u32 i = 0; i < old_cap; i++) {
        Bucket *buk = &old_shelves[i], *next_buk;
        if (buk->hash == 0) continue;
        hm_insert_no_resize(hm, buk->hash, buk->ptr);
        for (buk = buk->next; buk != NULL; buk = next_buk) {
            next_buk = buk->next;
            hm_insert_no_resize(hm, buk->hash, buk->ptr);
            free(buk);
        }
    }
    free(old_shelves);
}

void hm_insert(HashMap *hm, u64 hash, void *ptr) {
    if (hm->size >= hm->cap) hm_double(hm);  // @perf || @memory? cache_misses
    hm_insert_no_resize(hm, hash, ptr);
}

void *hm_find(HashMap hm, u64 hash) {
    for (Bucket *buk = &hm.buckets[hash & (hm.cap - 1)]; buk != NULL; buk = buk->next)
        if (buk->hash == hash) return buk->ptr;
    return NULL;
}

void hm_remove(HashMap *hm, u64 hash) {  // *hm: the ptr is not necessary
    Bucket *prec = NULL, *buk;
    for (buk = &hm->buckets[hash & (hm->cap - 1)]; buk != NULL && buk->hash != hash;
         buk = buk->next)
        prec = buk;
    assert(buk != NULL);
    hm->free_inner(buk->ptr);
    if (prec == NULL) {
        if (buk->next == NULL) memset(buk, 0, sizeof(*hm->buckets));
        else {
            void *buk_next = buk->next;
            memcpy(buk, buk_next, sizeof(*hm->buckets));
            free(buk_next);
        }
    } else {
        prec->next = buk->next;
        free(buk);
    }
}

Heap heap_new(u32 cap, u32 mem_size, u32 (*cmp)(void *x, void *y)) {
    assert(cap != 0);
    Heap hp = {
        .size     = 0,
        .cap      = cap,
        .mem_size = mem_size,
        .inner    = malloc(mem_size * cap),
        .cmp      = cmp,
    };
    assert(hp.inner != NULL);
    return hp;
}

void heap_free(Heap hp) {
    free(hp.inner);
}

#define heap_ssa(hp, i) ((hp).inner + (i) * (hp).mem_size)  // subscript address

void heap_bubble_up(Heap hp) {
    memcpy(heap_ssa(hp, 0), heap_ssa(hp, hp.size), hp.mem_size);
    u32 i;
    for (i = hp.size; i > 1 && hp.cmp(heap_ssa(hp, 0), heap_ssa(hp, i / 2)); i /= 2)
        memcpy(heap_ssa(hp, i), heap_ssa(hp, i / 2), hp.mem_size);
    memcpy(heap_ssa(hp, i), heap_ssa(hp, 0), hp.mem_size);
}

void heap_bubble_down(Heap hp) {
    memcpy(heap_ssa(hp, 0), heap_ssa(hp, 1), hp.mem_size);
    u32 i, pos;
    for (i = 1, pos = 2; pos <= hp.size; i = pos, pos *= 2) {
        if (pos != hp.size && hp.cmp(heap_ssa(hp, pos + 1), heap_ssa(hp, pos))) pos++;
        if (hp.cmp(heap_ssa(hp, 0), heap_ssa(hp, pos))) break;
        memcpy(heap_ssa(hp, i), heap_ssa(hp, pos), hp.mem_size);
    }
    memcpy(heap_ssa(hp, i), heap_ssa(hp, 0), hp.mem_size);
}

void heap_insert(Heap *hp, void *node) {
    if (++hp->size >= hp->cap) {
        hp->cap   *= 2;
        hp->inner  = realloc(hp->inner, hp->cap * hp->mem_size);
    }
    assert(hp->inner != NULL);
    memcpy(heap_ssa(*hp, hp->size), node, hp->mem_size);
    heap_bubble_up(*hp);
}

void heap_remove_min(Heap *hp) {
    memcpy(heap_ssa(*hp, 1), heap_ssa(*hp, hp->size--), hp->mem_size);
    heap_bubble_down(*hp);
}

void *heap_min(Heap hp) {
    if (hp.size == 0) return NULL;
    return heap_ssa(hp, 1);
}

VecQ vecq_new(u32 cap) {
    VecQ v = {
        .size  = 0,
        .cap   = cap,
        .del   = 0,
        .inner = malloc(sizeof(*v.inner) * cap),
    };
    assert(v.inner != NULL);
    return v;
}

void vecq_free(VecQ v) {
    free(v.inner);
}

void vecq_push(VecQ *v, Order ord) {
    if (v->size == v->cap) {
        v->cap   *= 2;
        v->inner  = realloc(v->inner, sizeof(*v->inner) * v->cap);
        assert(v->inner != NULL);
    }
    v->inner[v->size++] = ord;
}

ExpWeight exp_weight_new(u32 weight, u32 expiration) {
    return (ExpWeight){
        .weight     = weight,
        .expiration = expiration,
    };
}

u32 exp_weight_less_expiration(void *x, void *y) {
    return (*(ExpWeight *)x).expiration < (*(ExpWeight *)y).expiration;
}

Shelf *shelf_new(u32 capacity) {
    Shelf *shl = malloc(sizeof(Shelf));
    assert(shl != NULL);
    *shl = (Shelf){
        .hp          = heap_new(capacity, sizeof(ExpWeight), exp_weight_less_expiration),
        .sum         = 0,
        .update_time = 0,
    };
    return shl;
}

void shelf_free(void *shl) {
    heap_free(((Shelf *)shl)->hp);
    free(shl);
}

static inline u32 shelf_lazy_update(Shelf *shl) {  // @perf inline
    u32 retval = 0;
    if (shl->update_time != tick) {
        shl->update_time = tick;
        while (shl->hp.size > 0 && ((ExpWeight *)heap_min(shl->hp))->expiration <= tick) {
            retval    = 1;
            shl->sum -= ((ExpWeight *)heap_min(shl->hp))->weight;
            heap_remove_min(&shl->hp);
        }
    }
    return retval;
}

void shelf_decrease(Shelf *shl, u32 weight) {
    assert(weight <= shl->sum);
    shl->sum -= weight;
    while (weight != 0 && ((ExpWeight *)heap_min(shl->hp))->weight <= weight) {
        weight -= ((ExpWeight *)heap_min(shl->hp))->weight;
        heap_remove_min(&shl->hp);
    }
    if (weight) ((ExpWeight *)heap_min(shl->hp))->weight -= weight;
}

Ingredient *recipe_ing_circ_buff(Recipe *rcp) {
    return (Ingredient *)(rcp + 1);
}

char *strdup_custom(char *s) {
    u64 len;
    for (len = 0; s[len] != ' ' /* && s[len] != '\n' */; len++);
    return strndup(s, len);
}

Recipe *recipe_new(u32 capacity, char *s) {
    Recipe *rcp = malloc(sizeof(Recipe) + sizeof(Ingredient) * capacity);
    assert(rcp != NULL);
    *rcp = (Recipe){
        .name    = strdup_custom(s),
        .size    = 0,
        .cap_ref = capacity,
    };
    return rcp;
}

void recipe_free(void *rcp) {
    free(((Recipe *)rcp)->name);
    free((Recipe *)rcp);
}

Recipe *recipe_shrink(Recipe *rcp) {
    rcp = realloc(rcp, sizeof(Recipe) + sizeof(Ingredient) * rcp->size);
    assert(rcp != NULL);
    rcp->cap_ref        = 0;  // now cap becomes the ref
    rcp->where_to_start = &recipe_ing_circ_buff(rcp)[0];
    return rcp;
}

Recipe *recipe_push(Recipe *rcp, Ingredient ing) {
    if (rcp->size == rcp->cap_ref) {
        rcp->cap_ref *= 2;
        rcp           = realloc(rcp, sizeof(Recipe) + sizeof(Ingredient) * rcp->cap_ref);
        assert(rcp != NULL);
    }
    recipe_ing_circ_buff(rcp)[rcp->size++] = ing;
    return rcp;
}

Food food_from_order(Order ord, u32 weight) {
    return (Food){
        .rcp_ptr  = ord.rcp_ptr,
        .quantity = ord.quantity,
        .time     = ord.time,
        .weight   = weight,
    };
}

u32 food_less_time(void *x, void *y) {
    return ((*(Food *)x).time < (*(Food *)y).time) ||
           ((*(Food *)x).time == (*(Food *)y).time && (*(Food *)x).weight < (*(Food *)y).weight);
}

u32 food_more_weight(void *x, void *y) {
    return ((*(Food *)x).weight > (*(Food *)y).weight) ||
           ((*(Food *)x).weight == (*(Food *)y).weight && (*(Food *)x).time < (*(Food *)y).time);
}

Order order_new(Recipe *ptr, u32 quantity, u32 time) {
    return (Order){
        .rcp_ptr  = ptr,
        .quantity = quantity,
        .time     = time,
    };
}

void truck_load(Heap *hp, u32 weight) {
    if (heap_min(*hp) == NULL || ((Food *)heap_min(*hp))->weight > weight) {
        printf("camioncino vuoto\n");
        return;
    }
    while (heap_min(*hp) != NULL && ((Food *)heap_min(*hp))->weight <= weight) {
        Food fd = *(Food *)heap_min(*hp);
        heap_remove_min(hp);
        weight -= fd.weight;
        heap_insert(&truck, &fd);
    }
    while (heap_min(truck) != NULL) {
        Food fd = *(Food *)heap_min(truck);
        heap_remove_min(&truck);
        fd.rcp_ptr->cap_ref--;
        printf("%u %s %u\n", fd.time, fd.rcp_ptr->name, fd.quantity);
    }
}

void cook(Order ord) {
    u32     total_weight = 0;
    Recipe *rcp          = ord.rcp_ptr;
    for (u32 i = 0; i < rcp->size; i++) {
        Ingredient ing  = recipe_ing_circ_buff(rcp)[i];
        u32        w    = ord.quantity * ing.weight;
        Shelf     *shl  = ing.shl_ptr;
        total_weight   += w;
        shelf_decrease(shl, w);
    }
    Food fd = food_from_order(ord, total_weight);
    heap_insert(&to_deliver, &fd);
}

static inline u32 __attribute__((always_inline)) can_cook(Order ord) {  // @perf inline
    Recipe    *rcp      = ord.rcp_ptr;
    u32        quantity = ord.quantity;
    Ingredient ing      = *rcp->where_to_start;
    u32        w        = quantity * ing.weight;
    Shelf     *shl      = ing.shl_ptr;
    if (P1(shl->sum < w || (shelf_lazy_update(shl) && shl->sum < w))) return 0;
    Ingredient *circ_buff = recipe_ing_circ_buff(rcp);
    for (u32 i = 0; i != rcp->size; i++) {
        ing = circ_buff[i];
        w   = quantity * ing.weight;
        shl = ing.shl_ptr;
        if (P1(shl->sum < w || (shelf_lazy_update(shl) && shl->sum < w))) {
            rcp->where_to_start = &circ_buff[i];
            return 0;
        }
    }
    return 1;
}

static inline u32 test_1(VecQ w, VecQ *v, u32 i, u32 j) {  // @perf inline
    if (P1(w.inner[i].time < 0x80000000)) {
        if (P0(can_cook(v->inner[i]))) {
            cook(w.inner[i]);
        } else w.inner[j++] = w.inner[i];
    }
    return j;
}

static inline void test_2(VecQ w, VecQ *v, u32 i) {  // @perf inline
    if (P0(P1(w.inner[i].time < 0x80000000) && P0(can_cook(w.inner[i])))) {
        cook(w.inner[i]);
        w.inner[i].time += 0x80000000;
        v->del++;
    }
}

void wq_check(VecQ *v) {
    VecQ w = *v;
    u32  i;
    u32  end_1 = (w.size > PRE_FETCH_DIST ? w.size - PRE_FETCH_DIST : 0);
    u32  end_2 = w.size;
    if (v->del << CHECK_SHIFT > v->size) {  // @perf: either of the 2 alternatives can be cut
        u32 j = 0;
        for (i = 0; i < end_1; i++) {
            prefetch(w.inner[i + PRE_FETCH_DIST].rcp_ptr);
            j = test_1(w, v, i, j);
        }
        for (; i < end_2; i++) j = test_1(w, v, i, j);
        v->size = j;
        v->del  = 0;
    } else {
        for (i = 0; i < end_1; i++) {
            prefetch(w.inner[i + PRE_FETCH_DIST].rcp_ptr);
            test_2(w, v, i);
        }
        for (; i < end_2; i++) test_2(w, v, i);
    }
}

// should be called before every read to str_buffer
void update_buffer() {
    static char *last_idx = buffer + BUFF_LEN;
    str_buffer++;
    if (P0(str_buffer >= buffer + BUFF_LEN - WORD_LEN && last_idx == buffer + BUFF_LEN)) {
        char *old   = str_buffer;
        str_buffer -= (BUFF_LEN - WORD_LEN);
        memcpy(str_buffer, old, WORD_LEN - (str_buffer - buffer));
        last_idx = buffer + WORD_LEN + fread(&buffer[WORD_LEN], 1, BUFF_LEN - WORD_LEN, stdin);
    }
    if (P0(str_buffer == last_idx)) *str_buffer = '\0';
}

void skip_string() {
    update_buffer();
    while (*str_buffer != ' ' && *str_buffer != '\n') str_buffer++;
}

u32 read_u32() {
    update_buffer();
    u32 retval = 0;
    while (*str_buffer != ' ' && *str_buffer != '\n') retval = retval * 10 + *str_buffer++ - '0';
    return retval;
}

u64 P = 79;  // don't touch (prime > 75)
// u64 M = 233503089540627143;  // don't touch (prime < 2^64 / P - P)
u64 read_string_and_hash(char **prev) {  // @hope no collision (Las Vegas would be a good fix)
    update_buffer();
    if (prev) *prev = str_buffer;
    u64 hash = 0;
    for (u64 c = *str_buffer; c != ' ' && c != '\n'; c = *++str_buffer)
        hash = ((hash * P) + c - 47);  // hash_map.cap is a power of 2, but `%M` is useless
    assert(hash != 0);                 // @hope otherwise hash_map is bugged
    return hash;
}

void parse_supply() {
    while (*str_buffer != '\n') {
        u64       hash       = read_string_and_hash(NULL);
        u32       weight     = read_u32();
        u32       expiration = read_u32();
        ExpWeight ew         = exp_weight_new(weight, expiration);
        Shelf    *shl_ptr    = hm_find(warehouse, hash);
        if (shl_ptr == NULL) {
            shl_ptr = shelf_new(CAP);
            hm_insert(&warehouse, hash, shl_ptr);
        }
        shl_ptr->sum += weight;
        heap_insert(&shl_ptr->hp, &ew);
    }
    printf("rifornito\n");
    wq_check(&wait_queue);
}

void parse_remove() {
    u64     hash    = read_string_and_hash(NULL);
    Recipe *rcp_ptr = hm_find(cookbook, hash);
    if (rcp_ptr == NULL) printf("non presente\n");
    else if (rcp_ptr->cap_ref == 0) {
        printf("rimossa\n");
        hm_remove(&cookbook, hash);
    } else printf("ordini in sospeso\n");
}

void parse_order() {
    u64     hash     = read_string_and_hash(NULL);
    u32     quantity = read_u32();
    Recipe *rcp_ptr  = hm_find(cookbook, hash);
    if (rcp_ptr == NULL) printf("rifiutato\n");
    else {
        printf("accettato\n");
        Recipe *rcp = rcp_ptr;
        rcp->cap_ref++;
        Order ord = order_new(rcp, quantity, tick);
        if (can_cook(ord)) cook(ord);
        else vecq_push(&wait_queue, ord);
    }
}

void parse_recipe() {
    char *prev;
    u64   hash = read_string_and_hash(&prev);
    if (hm_find(cookbook, hash) != NULL) {
        while (*str_buffer != '\n') {
            skip_string();
            skip_string();
        }
        printf("ignorato\n");
        return;
    }
    Recipe *rcp = recipe_new(CAP, prev);
    while (*str_buffer != '\n') {
        u64    hash_ing = read_string_and_hash(NULL);
        Shelf *shl_ptr  = hm_find(warehouse, hash_ing);
        if (shl_ptr == NULL) {
            shl_ptr = shelf_new(CAP);
            hm_insert(&warehouse, hash_ing, shl_ptr);
        }
        Ingredient ing = {
            .shl_ptr = shl_ptr,
            .weight  = read_u32(),
        };
        rcp = recipe_push(rcp, ing);
    }
    rcp = recipe_shrink(rcp);
    hm_insert(&cookbook, hash, rcp);
    assert(hm_find(cookbook, hash) != NULL);
    printf("aggiunta\n");
}

void parse_input_and_calc() {
    update_buffer();
    if (!*str_buffer) return;
    if (str_buffer[2] == 'g') {
        str_buffer += 16;
        parse_recipe();
    } else if (str_buffer[2] == 'd') {
        str_buffer += 6;
        parse_order();
    } else if (str_buffer[2] == 'm') {
        str_buffer += 15;
        parse_remove();
    } else if (str_buffer[2] == 'f') {
        str_buffer += 12;
        parse_supply();
    } else assert(0);
}

int main(void) {
    warehouse      = hm_new(CAP_EXP, shelf_free);
    cookbook       = hm_new(CAP_EXP, recipe_free);
    wait_queue     = vecq_new(CAP);
    to_deliver     = heap_new(CAP, sizeof(Food), food_less_time);
    truck          = heap_new(CAP, sizeof(Food), food_more_weight);
    str_buffer     = &buffer[BUFF_LEN] - 1;
    u32 truck_tick = read_u32();
    u32 truck_cap  = read_u32();
    u32 time_left  = truck_tick;
    for (tick = 0; *str_buffer; tick++, time_left--) {
        if (time_left == 0) {
            time_left = truck_tick;
            truck_load(&to_deliver, truck_cap);
        }
        parse_input_and_calc();
    }
    hm_free(warehouse);
    hm_free(cookbook);
    vecq_free(wait_queue);
    heap_free(to_deliver);
    heap_free(truck);
    return 0;
}
