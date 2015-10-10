#ifndef _radixmap_h

#include <stdint.h>

typedef struct RMElement {
	uint64_t raw;
	struct {
		uint32_t key;
		uint32_t value;
	} data;
} RMElement;

typedef struct RadixMap {
	size_t max;
	size_t end;
	uint32_t counter;
	RMElement *contents;
	RMElement *temp;
} RadixMap;

RadixMap *radix_map_create(size_t max);

void radix_map_destroy(RadixMap *map);

void radix_map_sort(RadixMap *map);

RMElement*radix_map_find(RadixMap *map, uint32_t key);

int radix_map_add(RadixMap *map, uint32_t key, uint32_t value);

int radix_map_delete(RadixMap *map, RMElement *element);

#endif