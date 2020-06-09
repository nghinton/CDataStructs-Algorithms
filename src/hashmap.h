#ifndef _Hashmap_h
#define _Hashmap_h

#include <stdint.h>
#include "da.h"

#define DEFAULT_NUMBER_OF_BUCKETS 100

typedef int (*Hashmap_compare)(void *a, void *b);
typedef uint32_t (*Hashmap_hash)(void *key);

typedef struct Hashmap {
    DA *buckets[DEFAULT_NUMBER_OF_BUCKETS];
    Hashmap_compare compare;
    Hashmap_hash hash;
} Hashmap;

typedef struct HashmapNode {
    void *key;
    void *data;
    uint32_t hash;
} HashmapNode;

typedef int (*Hashmap_traverse_cb) (HashmapNode *node);

extern Hashmap *create_Hashmap(Hashmap_compare compare, Hashmap_hash hash);
extern void destroy_Hashmap(Hashmap *map);

extern int set_Hashmap(Hashmap *map, void *key, void *data);
extern void *get_Hashmap(Hashmap *map, void *key);

extern int traverse_Hashmap(Hashmap *map, Hashmap_traverse_cb traverse_cb);

extern void *delete_Hashmap(Hashmap *map, void *key);

#endif