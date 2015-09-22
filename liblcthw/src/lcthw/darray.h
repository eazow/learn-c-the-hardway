#ifndef _DArray_h
#define _DArray_h

#include <stdlib.h>
#include <assert.h>
#include <lcthw/dbg.h>

typedef struct DArray {
	int end;
	int max;
	size_t element_size;
	size_t expand_size;
	void **contents;
} DArray;

DArray *darray_create(size_t element_size, size_t initial_max);

void darray_destroy(DArray *array);

void darray_clear(DArray *array);

int darray_expand(DArray *array);

int darray_contract(DArray *array);

int darray_push(DArray *array, void *element);

void *darray_pop(DArray *array);

void darray_clear_destroy(DArray *array);

#define DEFAULT_EXPAND_RATE 300

static inline void darray_set(DArray *array, int i, void *el)
{
	check(i<array->max, "darray attempt to set past max");
	if(i > array->end) array->end = i;
	array->contents[i] = el;
error:
	return;
}