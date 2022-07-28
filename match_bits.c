#include "match_bits.h"

int match_bits(match_bits_t *m, const void *d, size_t l, const char *p)
{
    const unsigned char *pd = d;
    unsigned char mask = 0x80;

    while (*p && l)
    {
        if (*p == ' ')
        {
            /* skip */
        }
        else if (*p == '0')
        {
            if (*pd & mask)
                return 0;
        }
        else if (*p == '1')
        {
            if (!(*pd & mask))
                return 0;
        }
        else
        {
            return -1;
        }

        p++;
        if (!(mask >>= 1))
        {
            pd++;
            l--;
        }
    }

    return pd - (unsigned char*) d;
}
