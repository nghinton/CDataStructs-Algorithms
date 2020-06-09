#undef NDEBUG
#include <stdint.h>
#include <stdlib.h>
#include "hashmap.h"
#include "dbg.h"
#include "bstrlib.h"

static int default_compare(void *a, void *b) 
{
    return bstrcmp((bstring) a, (bstring) b);
}

/**
 * Simple Bob Jenkin's hash algorithm taken from the 
 * Wikipedia description
 */
static uint32_t default_hash(void *a) 
{
    size_t len = blength((bstring) a);
    char *key = bdata((bstring) a);
    uint32_t hash = 0;
    uint32_t i = 0;

    for (hash = i = 0; i<len; i++) {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}

Hashmap *create_Hashmap(Hashmap_compare compare, Hashmap_hash hash) 
{
    Hashmap *map = calloc(1, sizeof(Hashmap));
    check_mem(map);

    map->compare = compare == NULL ? default_compare : compare;
    map->hash = hash == NULL ? default_hash : hash;
    check_mem(map->buckets);

    return map;

error:
    if (map) {
        destroy_Hashmap(map);
    }

    return NULL;
}

void destroy_Hashmap(Hashmap *map) 
{
    if (map) {
        if (map->buckets) {
            for (int i=0; i<DEFAULT_NUMBER_OF_BUCKETS; i++) {
                DA *bucket = map->buckets[i];
                if (bucket) {
                    freeDA(bucket);
                }
            }
           // freeDA(map->buckets);
        }
        free(map);
    }
}

static inline HashmapNode *Hashmap_node_create(int hash, void *key, void *data) 
{
    HashmapNode *node = calloc(1, sizeof(HashmapNode));
    check_mem(node);

    node->key = key;
    node->data = data;
    node->hash = hash;

    return node;

error:
    return NULL;
}

static inline DA *Hashmap_find_bucket(Hashmap *map, void *key, int create, uint32_t *hash_out) 
{
    uint32_t hash = map->hash(key);
    int bucket_n = hash % DEFAULT_NUMBER_OF_BUCKETS;
    check(bucket_n >= 0, "Invalid bucket found: %d", bucket_n);

    // store it for the return so the caller can use it
    *hash_out = hash;

    DA *bucket = map->buckets[bucket_n];

    if (!bucket && create) {
        // new bucket, set it up
        bucket = newDA();
        check_mem(bucket);
        map->buckets[bucket_n] = bucket;
    }
    
    return bucket;

error:
    return NULL;

}

int set_Hashmap(Hashmap *map, void *key, void *data) 
{
    uint32_t hash = 0;
    DA *bucket = Hashmap_find_bucket(map, key, 1, &hash);
    check(bucket, "Error cant find bucket");

    HashmapNode *node = Hashmap_node_create(hash, key, data);
    check_mem(node);

    insertDAback(bucket, node);

    return 0;

error:
    return -1;
}

static inline int Hashmap_get_node(Hashmap *map, uint32_t hash, DA *bucket, void *key) 
{
    for (int i=0; i<sizeDA(bucket); i++) {
        debug("TRY: %d", i);
        HashmapNode *node = getDA(bucket, i);
        if (node->hash == hash && map->compare(node->key, key) == 0) {
            return i;
        }
    }

    return -1;
}

void *get_Hashmap(Hashmap *map, void *key) 
{
    uint32_t hash = 0;
    DA *bucket = Hashmap_find_bucket(map, key, 0, &hash);
    if (!bucket) return NULL;

    int i = Hashmap_get_node(map, hash, bucket, key);
    if (i == -1) return NULL;

    HashmapNode *node = getDA(bucket, i);
    check(node != NULL, "Failed to get node from bucket when it should exist");
     
    return node->data;

error:
    return NULL;
}

int traverse_Hashmap(Hashmap *map, Hashmap_traverse_cb traverse_cb) 
{
    int rc = 0;

    for (int i=0; i<DEFAULT_NUMBER_OF_BUCKETS; i++) {
        DA *bucket = map->buckets[i];
        if (bucket) {
            for (int j=0; j<sizeDA(bucket); j++) {
                HashmapNode *node = getDA(bucket, j);
                rc = traverse_cb(node);
                if(rc != 0)
                    return rc;
            }
        }
    }

    return 0;
}

void *delete_Hashmap(Hashmap *map, void *key) 
{
    uint32_t hash = 0;
    DA *bucket = Hashmap_find_bucket(map, key, 0, &hash);
    if (!bucket) 
        return NULL;

    int i = Hashmap_get_node(map, hash, bucket, key);
    if (i == -1) 
        return NULL;

    HashmapNode *node = getDA(bucket, i);
    void *data = node->data;
    free(node);

    HashmapNode *ending = removeDAback(bucket);

    if (ending != node) {
        // alright looks like its not the last one, swap it
        setDA(bucket, i, ending);
    }

    return data;
}