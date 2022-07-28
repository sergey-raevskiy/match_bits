#include <stdio.h>
#include "match_bits.h"

static void __ok(int ko, const char *_ko)
{
    if (!ko)
    {
        fprintf(stderr, "Assertion failed: %s\n", _ko);
        exit(1);
    }
}

#define ok(ko) __ok((ko), #ko)

int main()
{
    ok(match_bits(NULL, NULL, 0, ""));

    return 0;
}
