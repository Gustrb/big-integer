#include <stdlib.h>
#include <stdio.h>

#include "../src/bigint.h"
#include "utils.h"

static bigint_t CLEANUP[100] = {0};
static size_t num_of_clean = 0;

static void zero_addition_case(void)
{
    bigint_t zero = bg_new64(0);
    PUSH_TO_CLEANUP(&zero);
    bigint_t x = bg_new64(10);
    PUSH_TO_CLEANUP(&x);

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
}

static void simple_addition_case(void)
{
    bigint_t x = bg_new64(10);
    PUSH_TO_CLEANUP(&x);

    bigint_t res = bg_add(&x, &x);
    int64_t v = utils_int64_from_bi(&res);

    bg_free(&res);
    if (v != 20)
    {
        fprintf(stderr, "[FAIL]: Adding 10 to 10 shold equal 20, got: %lld\n", v);
        __FAIL;
    }


    bigint_t byte = bg_newu8(255);
    PUSH_TO_CLEANUP(&byte);
    bigint_t one = bg_new8(1);
    PUSH_TO_CLEANUP(&one);

    res = bg_add(&byte, &one);
    v = utils_int64_from_bi(&res);
    bg_free(&res);
    if (v != 256)
    {
        fprintf(stderr, "[FAIL]: Adding 1 to 255 shold equal 256, got: %lld\n", v);
        __FAIL;
    }
}

static void addition_with_negative_numbers(void)
{
    bigint_t x = bg_new64(2);
    PUSH_TO_CLEANUP(&x);
    bigint_t y = bg_new64(-1);
    PUSH_TO_CLEANUP(&y);

    bigint_t res = bg_add(&x, &y);
    int64_t v = utils_int64_from_bi(&res);
    bg_free(&res);
    if (v != 1)
    {
        fprintf(stderr, "[FAIL]: Adding -1 to 2 should equal 1, got: %lld\n", v);
        __FAIL;
    }

    x = bg_new64(-20);
    PUSH_TO_CLEANUP(&x);

    res = bg_add(&x, &y);
    v = utils_int64_from_bi(&res);
    bg_free(&res);
    if (v != -21)
    {
        fprintf(stderr, "[FAIL]: Adding -1 to -20 should equal -21, got: %lld\n", v);
        __FAIL;
    }

    x = bg_new64(0);
    PUSH_TO_CLEANUP(&x);
    y = bg_new64(-255);
    PUSH_TO_CLEANUP(&y);

    res = bg_add(&x, &y);
    v = utils_int64_from_bi(&res);
    bg_free(&res);
    if (v != -255)
    {
        fprintf(stderr, "[FAIL]: Adding -255 to 0 should equal -255, got: %lld\n", v);
        __FAIL;
    }
}

int main(void)
{
    fprintf(stdout, "[TEST]: Running sum.c\n");

    zero_addition_case();
    simple_addition_case();
    addition_with_negative_numbers();

    fprintf(stdout, "[TEST]: sum.c... Ok\n");
    DO_CLEANUP;
    return 0;
}
