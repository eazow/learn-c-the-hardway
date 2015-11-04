#include "minunit.h"
#include <lcthw/string_algos.h>
#include <lcthw/bstrlib.h>
#include <time.h>

struct tagbstring IN_STR = bsStatic("I have ALPHA beta ALPHA and oranges ALPHA");
struct tagbstring ALPHA = bsStatic("ALPHA");
const int TEST_TIME = 1;

char *test_find_and_scan()
{
    StringScanner *scan = string_scanner_create(&IN_STR);
    mu_assert(scan != NULL, "Failed to make the scanner.");

    int find_i = string_find(&IN_STR, &ALPHA);
    mu_assert(find_i > 0, "Failed to find 'ALPHA' in test string.");

    int scan_i = string_scanner_scan(scan, &ALPHA);
    mu_assert(scan_i > 0, "Failed to find 'ALPHA' with scan.");
    mu_assert(scan_i == find_i, "find and scan don't match");

    scan_i = string_scanner_scan(scan, &ALPHA);
    mu_assert(scan_i > find_i, "should find another ALPHA after the first");

    scan_i = string_scanner_scan(scan, &ALPHA);
    mu_assert(scan_i > find_i, "should find another ALPHA after the first");

    mu_assert(string_scanner_scan(scan, &ALPHA) == -1, "shouldn't find it");

    string_scanner_destroy(scan);

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_find_and_scan);

    return NULL;
}

RUN_TESTS(all_tests);
