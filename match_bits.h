#pragma once

#include <stdint.h>

typedef struct {
    uint64_t a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z;
} match_bits_t;

int match_bits(match_bits_t *m, const void* d, size_t l, const char* p);
