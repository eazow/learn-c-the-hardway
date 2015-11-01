#ifndef _lcthw_hashmap_h
#define _lcthw_hashmap_h

#include <stdint.h>
#include <lcthw/darray.h>

#define DEFAULT_NUMBER_OF_BUCKETS 100

typedef int (*hashmap_compare)(void *a, void *b);
typedef uint32_t (*hashmap_hash)(void *key);

typedef struct Hashmap {
	DArray *buckets;
	hashmap_compare compare;
	hashmap_hash hash;
} Hashmap;

typedef struct HashmapNode {
	void *key;
	void *data;
	uint32_t hash;
} HashmapNode;

typedef int (*hashmap_traverse_cb)(HashmapNode *node);

Hashmap *hashmap_create(hashmap_compare compare, hashmap_hash);

void hashmap_destroy(Hashmap *map);

int hashmap_set(Hashmap *map, void *key, void *data);

void * hashmap_get(Hashmap *map, void *key);

int hashmap_traverse(Hashmap *map, hashmap_traverse_cb traverse_cb);

void * hashmap_delete(Hashmap *map, void *key);

#endif
