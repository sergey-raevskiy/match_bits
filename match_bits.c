#include "match_bits.h"

int match_bits(match_bits_t *m, const void *d, size_t l, const char *p)
{
    const unsigned char *pd = d;
    unsigned char mask = 0x80;
    int binmode = 0;

    while (*p && l)
    {
        if (*p == ' ')
        {
            /* skip */
        }
        else if (*p == '<')
        {
            binmode = 1;
        }
        else if (*p == '>')
        {
            binmode = 0;
        }
        else if (binmode && *p == '0')
        {
            if (*pd & mask)
                return 0;
            mask >>= 1;
        }
        else if (binmode && *p == '1')
        {
            if (!(*pd & mask))
                return 0;
            mask >>= 1;
        }
        else
        {
            return -1;
        }

        p++;
        if (!mask)
        {
            pd++;
            l--;
            mask = 0x80;
        }
    }

    return pd - (unsigned char*) d;
}
