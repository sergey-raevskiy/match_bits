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
    match_bits_t m;

    ok(match_bits(&m, data("\xff"), "") == 0);
    ok(match_bits(&m, data("\xff"), "<>") == 0);
    ok(match_bits(&m, data("\xff"), "<") == 0);
    ok(match_bits(&m, data("\xff"), "<<>") == -1);
    ok(match_bits(&m, data("\xff"), "<11>") == -1);
    ok(match_bits(&m, data("\xff"), "F") == -1);
    ok(match_bits(&m, data("\xfe\x11\x84"), "<1111 1110 0001 0001 1000 0100>") == 3);
    ok(match_bits(&m, data("\xfe\x11\x84"), "FE 1 <0001 1000> 4") == 3);
    ok(match_bits(&m, data("\xfe\x11\x84"), "xx xx xx") == 3);
    ok(m.x == 0xfe1184);
    ok(match_bits(&m, data("\xfe\x11\x84"), "xx <yyyy zzzz> xx") == 3);
    ok(m.x == 0xfe84);
    ok(m.y == 1);
    ok(m.z == 1);

    return 0;
}
