#include <lcthw/darray_algos.h>
#include <stdlib.h>

int darray_qsort(DArray *array, darray_compare cmp)
{
	qsort(array->contents, darray_count(array), sizeof(void *), cmp);
	return 0;
}

int darray_heapsort(DArray *array, darray_compare cmp)
{
	return heapsort(array->contents, darray_count(array), sizeof(void *), cmp);
}

int darray_mergesort(DArray *array, darray_compare cmp)
{
	return mergesort(array->contents, darray_count(array), sizeof(void *), cmp);
}