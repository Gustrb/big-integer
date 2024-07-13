#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <stdint.h>
#include "../src/bigint.h"

#define PUSH_TO_CLEANUP(x) \
        CLEANUP[num_of_clean++] = *x;

#define DO_CLEANUP \
    for (size_t i = 0; i < num_of_clean; ++i) \
        bg_free(&CLEANUP[i]);

#define __FAIL \
         DO_CLEANUP; \
        exit(EXIT_FAILURE); \
        return;

int64_t utils_int64_from_bi(bigint_t *bi);

#endif
