#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <lcthw/radixmap.h>
#include <lcthw/dbg.h>

RadixMap *radix_map_create(size_t max)
{
	RadixMap *map = calloc(sizeof(RadixMap), 1);
	check_mem(map);

	map->contents = calloc(sizeof(RMElement), max+1);
	check_mem(map->contents);

	map->temp = calloc(sizeof(RMElement), max+1);
	check_mem(map->temp);

	map->max = max;
	map->end = 0;

	return map;

error:
	return NULL;
}

void radix_map_destroy(RadixMap *map)
{
	if(map) {
		free(map->contents);
		free(map->temp);
		free(map);
	}
}

static inline void radix_sort()
{
}

void radix_map_sort(RadixMap *map)
{
    
}

RMElement *radix_map_find()
{
    return NULL;
}

int radix_map_add(RadixMap *map, uint32_t key, uint32_t value)
{
    check(key < UINT32_MAX, "Key can't be equal to UINT32_MAX.");

    RMElement element = {.data={.key=key, .value=value}};
    check(map->end+1<map->max, "RadixMap is full.");

    map->contents[map->end++] = element;

    radix_map_sort(map);
    
    return 0;
}

int radix_map_delete()
{
    return 0;
}
