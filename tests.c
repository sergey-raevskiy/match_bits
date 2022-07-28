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

#define data(s) s, (sizeof(""s)-1)

int main()
{
    ok(match_bits(NULL, data("\xff"), "<>") == 0);
    ok(match_bits(NULL, data("\xff"), "<<>") == -1);
    ok(match_bits(NULL, data("\xfe\x11\x84"), "<1111 1110 0001 0001 1000 0100>") == 3);
    ok(match_bits(NULL, data("\xfe\x11\x84"), "FE 1 <0001 1000> 4") == 3);

    return 0;
}
