#include "minunit.h"
#include <lcthw/radixmap.h>
#include <time.h>

static int make_random(RadixMap *map)
{
    size_t i = 0;

    for(i = 0; i < map->max-1; i++) {
        uint32_t key = (uint32_t)(rand()|(rand()<<16));
        check(radix_map_add(map, key, i)==0, "Failed to add key %u.", key);
    }

    return i;

error:
    return 0;
}

//test for big number of elements
static char *test_operations()
{
    size_t N = 200;

    RadixMap *map = radix_map_create(N);
    mu_assert(map!=NULL, "Failed to make the map.");
    mu_assert(make_random(map), "Didn't make a random fake radix map.");

    radix_map_sort(map);
    mu_assert(check_order(map), "Failed to properly sort the RadixMap.");

    mu_assert(test_search(map), "Failed to search the test.");
    mu_assert(check_order(map), "RadixMap didn't stay sorted after search.");

    radix_map_destroy(map);

    return NULL;
}

char *all_tests()
{
    mu_suite_start();
    srand(time(NULL));

    mu_run_test(test_operations);

    return NULL;
}

RUN_TESTS(all_tests);
