#include <stdlib.h>
#include <stdio.h>

#include "../src/bigint.h"
#include "utils.h"

static bigint_t CLEANUP[100] = {0};
static size_t num_of_clean = 0;

static void simple_subtraction_case(void)
{
    bigint_t x = bg_new64(10);
    PUSH_TO_CLEANUP(&x);
    bigint_t y = bg_new64(20);
    PUSH_TO_CLEANUP(&y);

    bigint_t res = bg_sub(&y, &x);
    int64_t v = utils_int64_from_bi(&res);
    bg_free(&res);
    if (v != 10)
    {
        fprintf(stderr, "[FAIL]: 20 minus 10 is 10, got: %lld\n", v);
        __FAIL;
    }

    res = bg_sub(&x, &y);
    v = utils_int64_from_bi(&res);
    bg_free(&res);
    if (v != -10)
    {
        fprintf(stderr, "[FAIL]: 10 minus 20 is -10, got: %lld\n", v);
        __FAIL;
    }
}

static void subtraction_with_zero_case(void)
{
    bigint_t x = bg_new64(0);
    PUSH_TO_CLEANUP(&x);
    bigint_t y = bg_new64(20);
    PUSH_TO_CLEANUP(&y);

    bigint_t res = bg_sub(&y, &x);
    int64_t v = utils_int64_from_bi(&res);
    bg_free(&res);
    if (v != 20)
    {
        fprintf(stderr, "[FAIL]: 20 minus 0 is 20, got: %lld\n", v);
        __FAIL;
    }

    res = bg_sub(&x, &y);
    v = utils_int64_from_bi(&res);
    bg_free(&res);
    if (v != -20)
    {
        fprintf(stderr, "[FAIL]: 0 minus 20 is -20, got: %lld\n", v);
        __FAIL;
    }

    res = bg_sub(&x, &x);
    v = utils_int64_from_bi(&res);
    bg_free(&res);
    if (v != 0)
    {
        fprintf(stderr, "[FAIL]: 0 minus 0 is 0, got: %lld\n", v);
        __FAIL;
    }

    res = bg_sub(&y, &y);
    v = utils_int64_from_bi(&res);
    if (v != 0 || res.special != M_ZERO)
    {
        fprintf(stderr, "[FAIL]: 20 minus 20 is zero, got: %lld\n", v);
        bg_free(&res);
        __FAIL;
    }
    bg_free(&res);
}

int main(void)
{
    fprintf(stdout, "[TEST]: Running sub.c\n");
    simple_subtraction_case();
    subtraction_with_zero_case();
    fprintf(stdout, "[TEST]: sub.c... Ok\n");
    DO_CLEANUP;
    return 0;
}
