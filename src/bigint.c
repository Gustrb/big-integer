#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "bigint.h"

#define __IMPL_BG(type, v) \
    bigint_t b = {0}; \
    if (v == 0) { \
        b.special = M_ZERO; \
        return b; \
    } \
    b.val_len = sizeof(type); \
    b.val = malloc(b.val_len * sizeof(uint8_t)); \
    for (size_t i = 0; i < b.val_len; ++i) b.val[i] = (v >> (i * 8)) & 0xFF; \
    if (v < 0) b.sign = S_NEGATIVE; \
    return b;

bigint_t bg_new64(int64_t x) { __IMPL_BG(int64_t, x); }
bigint_t bg_new32(int32_t x) { __IMPL_BG(int32_t, x); }
bigint_t bg_new16(int16_t x) { __IMPL_BG(int16_t, x); }
bigint_t bg_new8(int8_t x) { __IMPL_BG(int8_t, x); }

bigint_t bg_newu64(uint64_t x) { __IMPL_BG(uint64_t, x); }
bigint_t bg_newu32(uint32_t x) { __IMPL_BG(uint32_t, x); }
bigint_t bg_newu16(uint16_t x) { __IMPL_BG(uint16_t, x); }
bigint_t bg_newu8(uint8_t x) { __IMPL_BG(uint8_t, x); }

static void __bg_copy(bigint_t *src, bigint_t *dst);

#undef __IMPL_BG

void bg_free(bigint_t *b)
{
    if (b->special) return;

    b->val_len = 0;
    free(b->val);

    b->val = NULL;
}

bigint_t bg_add(bigint_t *a, bigint_t *b)
{
    bigint_t res = {0};

    // 0 + 0 = 0
    if (a->special == M_ZERO && b->special == M_ZERO)
    {
        res.special = M_ZERO;
        return res;
    }
    // 0 + b = b
    else if (a->special == M_ZERO)
    {
        res.val_len = sizeof(uint8_t) * b->val_len;
        res.val = malloc(res.val_len);
        __bg_copy(b, &res);
        return res;
    }
    // a + 0 = a
    else if (b->special == M_ZERO)
    {
        res.val_len = sizeof(uint8_t) * a->val_len;
        res.val = malloc(res.val_len);
        __bg_copy(a, &res);
        return res;
    }

    bigint_t *largest = a->val_len > b->val_len ? a : b;

    // Since we are adding, we know that the resulting number will have
    // - largest->val_len if no carry
    // - largest->val_len + 1 if carry
    // so we can start allocating largest->val_len + 1 and just decrement val_len
    // if we are not going to use the last byte
    res.val_len = sizeof(uint8_t) * largest->val_len + sizeof(uint8_t);
    res.val = malloc(res.val_len);
    memset(res.val, 0, res.val_len);

    uint8_t carry = 0;
    for (size_t i = 0; i < res.val_len - 1; ++i)
    {
        uint8_t a_val = i < a->val_len ? a->val[i] : 0;
        uint8_t b_val = i < b->val_len ? b->val[i] : 0;
        uint16_t sum = a_val + b_val + carry;
        res.val[i] = sum & 0xFF; // Store the lower 8 bits
        carry = (sum >> 8) & 0xFF; // Carry is the upper 8 bits
    }

    // Handle the last carry
    if (carry) res.val[res.val_len - 1] = carry;
    // No carry, so we don't need the extra byte
    else res.val_len -= 1;

    return res;
}

static void __bg_copy(bigint_t *src, bigint_t *dst)
{
    memcpy(dst->val, src->val, src->val_len);
}
