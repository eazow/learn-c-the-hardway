#include "minunit.h"
#include <lcthw/darray.h>

static DArray *array = NULL;
static int *val1 = NULL;
static int *val2 = NULL;

char *test_create()
{
	array = darray_create(sizeof(int), 100);
	mu_assert(array!=NULL, "darray create failed.");
	mu_assert(array->contents!=NULL, "contents are wrong in darray");
	mu_assert(array->end==0, "end isn't at the right spot");
	mu_assert(array->element_size==sizeof(int), "element size is wrong.");
	mu_assert(array->max==100, "wrong max length on initial size");

	return NULL;
}

char *test_destroy()
{
	darray_destroy(array);

	return NULL;
}

char *test_new()
{
	val1 = darray_new(array);
	mu_assert(val1!=NULL, "failed to make a new element");

	val2 = darray_new(array);
	mu_assert(val2!=NULL, "failed to make a new element");

	return NULL;
}

char *test_set()
{
	darray_set(array, 0, val1);
	darray_set(array, 1, val2);

	return NULL;
}

char *test_get()
{
	mu_assert(darray_get(array, 0)==val1, "Wrong first value");
	mu_assert(darray_get(array, 1)==val2, "Wrong second value");

	return NULL;
}

char *test_push()
{
	int i = 0;
	for(i=0;, i<1000; i++) {
		int *val = darray_new(array);
		*val = i*333;
		darray_push(array, val);
	}
	mu_assert(array->max==1200, "Wrong max size");

	return NULL;
}

char *all_tests() {
	mu_suite_start();

	mu_run_test(test_create);
	mu_run_test(test_new);
	mu_run_test(test_set);
	mu_run_test(test_get);

	mu_run_test(test_push);
	mu_run_test(test_destroy);

	return NULL;
}

RUN_TESTS(all_tests);