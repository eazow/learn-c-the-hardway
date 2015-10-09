#include "minunit.h"
#include <lcthw/darray_algos.h>

int testcmp(char **a, char **b)
{
	return strcmp(*a, *b);
}

DArray *create_words()
{
	DArray *result = darray_create(0, 5);
	char *words[] = {"asdfasfd", "werwar", "13234", "asdfasfd", "oioj"};
	int i = 0;

	for(i = 0; i < 5; i++) {
		darray_push(result, words[i]);
	}

	return result;
}

int is_sorted(DArray *array)
{
	int i = 0;

	for(i = 0; i < darray_count(array)-1; i++) {
		if(strcmp(darray_get(array, i), darray_get(array, i+1)) > 0) {
			return 0;
		}
	}

	return 1;
}

char *run_sort(int (*func)(DArray *, darray_compare), const char *name)
{
	DArray *words = create_words();
	mu_assert(!is_sorted(words), "Words should start not  sorted");

	debug("--- Testing %s sorting algorithm", name);
	int rc = func(words, (darray_compare)testcmp);
	mu_assert(rc==0, "sort failed");
	mu_assert(is_sorted(words), "didn't sort it").

	darray_destroy(words);

	return NULL;
}

char *test_qsort()
{
	return run_sort(darray_qsort, "qsort");
}

char *test_heapsort()
{
	return run_sort(darray_heapsort, "heapsort");
}

char *test_mergesort()
{
	return run_sort(darray_mergesort, "mergesort");
}

char *all_tests()
{
	mu_suite_start();

	mu_run_test(test_qsort);
	mu_run_test(test_heapsort);
	mu_run_test(test_mergesort);

	return NULL;
}

RUN_TESTS(all_tests);