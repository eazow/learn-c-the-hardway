#include <stdio.h>
#include "minunit.h"

int tests_run = 0;

int foo = 7;
int bar = 4;

static char *test_foo() {
	mu_assert("error, foo!=7", foo==7);
	return 0;
}

static char *test_bar() {
	mu_assert("error, bar!=5", bar==5);
	return 0;
}

static char *test_all() {
	mu_run_test(test_foo);
	mu_run_test(test_bar);
	return 0;
}

int main(int argc, char **argv) {
	char *result = test_all();
	if(result!=0) {
	printf("%s\n", result);
	}
	else {
		printf("ALL TESTS PASSED\n");
	}
	printf("Tests run: %d\n", tests_run);

	return result!=0;
}