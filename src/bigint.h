#ifndef BIGINT_H
#define BIGINT_H

#include <stdint.h>
#include <stddef.h>

typedef struct {
    uint8_t *val;
    size_t val_len;

    enum {
        M_ZERO = 1
    } special;
} bigint_t;

bigint_t bg_new64(int64_t x);
bigint_t bg_new32(int32_t x);
bigint_t bg_new16(int16_t x);
bigint_t bg_new8(int8_t x);

bigint_t bg_newu64(uint64_t x);
bigint_t bg_newu32(uint32_t x);
bigint_t bg_newu16(uint16_t x);
bigint_t bg_newu8(uint8_t x);

/**
 * Creates a new big integer containing the sum of a and b
 * The returned value is not owned, therefore it must be freed by the caller
*/
bigint_t bg_add(bigint_t *a, bigint_t *b);

void bg_free(bigint_t *);

#endif
