#include <stdlib.h>
#include <stdio.h>

#include "../src/bigint.h"
#include "utils.h"

static bigint_t CLEANUP[100] = {0};
static size_t num_of_clean = 0;

int main(void)
{
    fprintf(stdout, "[TEST]: Running sub.c\n");


    fprintf(stdout, "[TEST]: sub.c... Ok\n");
    DO_CLEANUP;

    return 0;
}
