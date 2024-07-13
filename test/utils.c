#include "utils.h"

int64_t utils_int64_from_bi(bigint_t *bi)
{
    int64_t x = 0;

    for (size_t i = 0; i < bi->val_len; ++i)
    {
        x |= ((int64_t)bi->val[i] & 0xFF) << (i * 8);
    }

    return x;
}
