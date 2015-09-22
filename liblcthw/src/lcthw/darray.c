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