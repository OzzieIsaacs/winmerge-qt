#include <stdio.h>
#include <cstdlib>
#include "xdiff.h"
#include "libxdiff_tools.h"

// We must set allocator / deallocator functions for libxdiff before
// we can use it.

void *wrap_malloc(void *priv, unsigned int size)
{
    return malloc(size);
}

void wrap_free(void *priv, void *ptr)
{
    free(ptr);
}

void *wrap_realloc(void *priv, void *ptr, unsigned int size)
{
    return realloc(ptr, size);
}

void libxdiff_tools_init(void)
{
    memallocator_t malt;

    malt.priv = NULL;
    malt.malloc = wrap_malloc;
    malt.free = wrap_free;
    malt.realloc = wrap_realloc;
    xdl_set_allocator(&malt);
}
