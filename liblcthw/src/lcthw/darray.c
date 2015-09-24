#include <lcthw/darray.h>
#include <assert.h>

DArray *darray_create(size_t element_size, size_t initial_max)
{
	DArray *array = malloc(sizeof(DArray));
	check_mem(array);
	array->max = initial_max;
	check(array->max > 0, "You must set an initial_max > 0.");

	array->contents = calloc(initial_max, sizeof(void *));
	check_mem(array->contents);

	array->end = 0;
	array->element_size = element_size;
	array->expand_rate = DEFAULT_EXPAND_RATE;

	return array;

error:
	if(array) {
		free(array);
	}
	return NULL;
}

void darray_destroy(DArray *array)
{
	if(array) {
		if(array->contents) {
			free(array->contents);
		}
		free(array);
	}
}

int darray_push(DArray *array, void *el)
{
	array->contents[array->end] = el;
	array->end++;

	if(darray_end(array) >= darray_max(array)) {
		return darray_expand(array);
	}
	else {
		return 0;
	}
}

static inline int darray_resize(DArray *array, size_t newsize)
{
	array->max = newsize;
	check(array->max>0, "The newsize must be > 0.");

	void *contents = realloc(array->contents, array->max*sizeof(void *));

	check_mem(contents);

	array->contents = contents;

	return 0;

error:
	return -1;

}

int darray_expand(DArray *array)
{
	size_t old_max = array->max;
	check(darray_resize(array, array->max+array->expand_rate)==0,
		"Failed to expand array to new size: %d",
		array->max+(int)array->expand_rate);

	memset(array->contents+old_max, 0, array->expand_rate);
	return 0;

error:
	return -1;
}