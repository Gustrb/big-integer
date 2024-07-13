#include <stdlib.h>
#include <stdio.h>

#include "../src/bigint.h"

bigint_t fib(int n)
{
    bigint_t previousprevious;
    bigint_t previous = bg_new8(0);
    bigint_t current = bg_new8(1);

    for (size_t i = 1; i < n; ++i)
    {
        previousprevious = previous;
        previous = current;
        current = bg_add(&previousprevious, &previous);
        bg_free(&previousprevious);
    }

    bg_free(&previous);

    return current;
}

int main(void)
{
    return EXIT_SUCCESS;
}