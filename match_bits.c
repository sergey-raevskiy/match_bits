#include "match_bits.h"

static int match(unsigned char qq, unsigned char xx)
{

}

int match_bits(match_bits_t *m, const void *d, size_t l, const char *p)
{
    static const unsigned char *bmsk = "\x80\x40\x20\x10\x08\x04\x02\x01";
    const unsigned char *pd = d;
    int binmode = 0;
    int state = 0;

    while (*p && l)
    {
        if (*p == ' ')
        {
            /* skip */
        }
        else if (!binmode && state == 0 && *p == '<')
        {
            binmode = 1;
            state = 0;
        }
        else if (!binmode && state == 1 && *p == '<')
        {
            binmode = 1;
            state = 4;
        }
        else if (binmode && state == 0 && *p == '>')
        {
            binmode = 0;
            state = 0;
        }
        else if (binmode && state == 4 && *p == '>')
        {
            binmode = 0;
            state = 1;
        }
        else if (binmode && *p == '0')
        {
            if (*pd & bmsk[state])
                return 0;
            state++;
            if (state == 8)
                state = 0, pd++, l--;
        }
        else if (binmode && *p == '1')
        {
            if (!(*pd & bmsk[state]))
                return 0;
            state++;
            if (state == 8)
                state = 0, pd++, l--;
        }
        else if (!binmode && state == 0 && (*p >= '0' && *p <= '9'))
        {
            if ((*pd & 0xf0) != ((*p - '0') << 4))
                return 0;
            state = 1;
        }
        else if (!binmode && state == 1 && (*p >= '0' && *p <= '9'))
        {
            if ((*pd & 0x0f) != (*p - '0'))
                return 0;
            state = 0, pd++, l--;
        }
        else if (!binmode && state == 0 && (*p >= 'A' && *p <= 'F'))
        {
            if ((*pd & 0xf0) != ((*p - 'A' + 10) << 4))
                return 0;
            state = 1;
        }
        else if (!binmode && state == 1 && (*p >= 'A' && *p <= 'F'))
        {
            if ((*pd & 0x0f) != (*p - 'A' + 10))
                return 0;
            state = 0, pd++, l--;
        }
        else
        {
            return -1;
        }

        p++;
    }

    if (state != 0)
        return -1;

    return pd - (unsigned char*) d;
}
