#include <stdlib.h>
#include <stdio.h>

#include "../src/bigint.h"
#include "utils.h"

int main(void)
{
    fprintf(stdout, "[TEST]: Running byte-order.c\n");

    int64_t x = 1;
    bigint_t bi = bg_new64(x);

    if (bi.val[0] != 1)
    {
        fprintf(stderr, "[FAIL]: First byte should be equal to 1, got: %d\n", bi.val[0]);
        bg_free(&bi);
        exit(EXIT_FAILURE);
        return EXIT_FAILURE;
    }

    if (bi.sign != S_POSITIVE)
    {
        fprintf(stderr, "[FAIL]: Failed to identify positive number\n");
        bg_free(&bi);
        exit(EXIT_FAILURE);
        return EXIT_FAILURE;
    }

    bg_free(&bi);

    x = -40000000;
    bi = bg_new64(x);
    int64_t aux = utils_int64_from_bi(&bi);

    if (aux != x && bi.sign != S_NEGATIVE)
    {
        fprintf(stderr, "[FAIL]: Did not manage to store correctly negative number, expected: %lld, got: %lld\n", x, aux);
    }

    bg_free(&bi);

    fprintf(stdout, "[TEST]: byte-order.c... Ok\n");

    return 0;
}
