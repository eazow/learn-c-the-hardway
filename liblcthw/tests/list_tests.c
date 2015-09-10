#include "minunit.h"
#include <lcthw/list.h>
#include <assert.h>

static List *list = NULL;
char *test1 = "test1 data";
char *test2 = "test2 data";
char *test3 = "test3 data";

char *test_create()
{
	list = list_create();
	mu_assert(list!=NULL, "Failed to create list.");

	return NULL;
}

char *test_destroy()
{
	list_clear_destroy(list);

	return NULL;
}

char *test_push_pop()
{
	list_push(list, test1);
	mu_assert(list_last(list)==test1, "Wrong last value");

	list_push(list, test2);
	mu_assert(list_last(list)==test2, "Wrong last value");

	list_push(list, test3);
	mu_assert(list_last(list)==test3, "Wrong last value");
	mu_assert(list_count(list)==3, "Wrong count on push");

	char *value = list_pop(list);
	mu_assert(value==test3, "Wrong value on pop");

	value = list_pop(list);
	mu_assert(value==test2, "Wrong value on pop");

	value = list_pop(list);
	mu_assert(value==test1, "Wrong value on pop");
	mu_assert(list_count(list)==0, "Wrong count after pop");

	return NULL;
}

char *all_tests() {
	mu_suite_start();

	mu_run_test(test_create);
	mu_run_test(test_push_pop);
	mu_run_test(test_destroy);

	return NULL;
}

RUN_TESTS(all_tests);