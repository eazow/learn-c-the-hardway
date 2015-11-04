#ifndef string_algos_h
#define string_algos_h

#include <lcthw/bstrlib.h>
#include <lcthw/darray.h>

typedef struct StringScanner {
    bstring in;
    const unsigned char *haystack;
    ssize_t hlen;
    const unsigned char *needle;
    ssize_t nlen;
    size_t skip_chars[UCHAR_MAX+1];
} StringScanner;

int string_find(bstring in, bstring what);

StringScanner *string_scanner_create(bstring in);

int string_scanner_scan(StringScanner *scan, bstring tofind);

void string_scanner_destroy(StringScanner *scan);

#endif
