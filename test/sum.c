#include <stdlib.h>
#include <stdio.h>

#include "../src/bigint.h"
#include "utils.h"

bigint_t CLEANUP[10] = {0};
size_t num_of_clean = 0;

#define __FAIL \
         __cleanup(); \
        exit(EXIT_FAILURE); \
        return EXIT_FAILURE; \


static inline void __push_to_cleanup(bigint_t *b)
{
    CLEANUP[num_of_clean++] = *b;
}

static inline void __cleanup(void)
{
    for (size_t i = 0; i < num_of_clean; ++i)
    {
        bg_free(&CLEANUP[i]);
    }
}

int main(void)
{
    fprintf(stdout, "[TEST]: Running sum.c\n");

    bigint_t zero = bg_new64(0);
    __push_to_cleanup(&zero);
    bigint_t x = bg_new64(10);
    __push_to_cleanup(&x);

    bigint_t res;
    int64_t v;

    res = bg_add(&zero, &x);
    v = utils_int64_from_bi(&res);
    bg_free(&res);

    if (v != 10)
    {
        fprintf(stderr, "[FAIL]: Adding 0 to %d shold equal %d, got: %lld\n", 10, 10, v);
        __FAIL;
    }

    res = bg_add(&x, &zero);
    v = utils_int64_from_bi(&res);
    bg_free(&res);

    if (v != 10)
    {
        fprintf(stderr, "[FAIL]: Adding %d to 0 shold equal %d, got: %lld\n", 10, 10, v);
        __FAIL;
    }


    res = bg_add(&zero, &zero);
    v = utils_int64_from_bi(&res);
    bg_free(&res);
    if (res.special != M_ZERO)
    {
        fprintf(stderr, "[FAIL]: Adding 0 to 0 shold equal 0, got: %lld\n", v);
        __FAIL;
    }

    res = bg_add(&x, &x);
    v = utils_int64_from_bi(&res);
    bg_free(&res);
    if (v != 20)
    {
        fprintf(stderr, "[FAIL]: Adding 10 to 10 shold equal 20, got: %lld\n", v);
        __FAIL;
    }


    bigint_t byte = bg_newu8(255);
    __push_to_cleanup(&byte);
    bigint_t one = bg_new8(1);
    __push_to_cleanup(&one);

    res = bg_add(&byte, &one);
    v = utils_int64_from_bi(&res);
    bg_free(&res);
    if (v != 256)
    {
        fprintf(stderr, "[FAIL]: Adding 1 to 255 shold equal 256, got: %lld\n", v);
        __FAIL;
    }

    fprintf(stdout, "[TEST]: sum.c... Ok\n");
    __cleanup();
    return 0;
}

#undef __FAIL
