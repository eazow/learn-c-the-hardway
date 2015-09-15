#ifndef lcthw_list_algos_h
#define lcthw_list_algos_h

#include <lcthw/list.h>

typedef int (*list_compare)(const void *a, const void *b);

int list_bubble_sort(List *list, list_compare cmp);

List *list_merge_sort(List *list, list_compare cmp);

#endif