/*
 * Copyright (c) 2011 Hewlett-Packard Development Company, L.P.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <atomic_ops.h>
#include <limits.h>

#ifndef AO_BIT
#  define AO_BIT LONG_BIT  /* CHECKME */
#endif

/* TODO */
/* #define ATOMIC_INTEGRAL_LOCK_FREE 1 */
/* #define ATOMIC_ADDRESS_LOCK_FREE 1 */


/* Memory Order and Fences
 * ======================= */

typedef enum {
    memory_order_relaxed,
    memory_order_acquire,
    memory_order_release,
    memory_order_acq_rel,
    memory_order_seq_cst
} memory_order;

#define atomic_thread_fence(order) \
    do { switch (order) { \
        case memory_order_relaxed: break; \
        case memory_order_acquire: AO_nop_acquire(); break; \
        case memory_order_release: AO_nop_release(); break; \
        case memory_order_acq_rel: \
        case memory_order_seq_cst: AO_nop_full(); break; \
    } } while (0)

#define atomic_signal_fence atomic_thread_fence


/* Atomic Integers, Bool, and Address
 * ==================================
 *
 * CHECKME: Is it appropriate to use AO_t if it is smaller than some of the
 * corresponding non-atomic types? */

typedef struct { AO_t __ao_val; } atomic_bool;
typedef struct { AO_t __ao_val; } atomic_address;

typedef struct { AO_t __ao_val; } atomic_char;
typedef struct { AO_t __ao_val; } atomic_schar;
typedef struct { AO_t __ao_val; } atomic_uchar;
typedef struct { AO_t __ao_val; } atomic_short;
typedef struct { AO_t __ao_val; } atomic_ushort;
typedef struct { AO_t __ao_val; } atomic_int;
typedef struct { AO_t __ao_val; } atomic_uint;
typedef struct { AO_t __ao_val; } atomic_long;
typedef struct { AO_t __ao_val; } atomic_ulong;
#if defined LLONG_BIT && AO_BIT >= LLONG_BIT
typedef struct { AO_t __ao_val; } atomic_llong;
typedef struct { AO_t __ao_val; } atomic_ullong;
#endif

typedef struct { AO_t __ao_val; } atomic_char16_t;
typedef struct { AO_t __ao_val; } atomic_char32_t;
typedef struct { AO_t __ao_val; } atomic_wchar_t;
typedef struct { AO_t __ao_val; } atomic_int_least8_t;
typedef struct { AO_t __ao_val; } atomic_uint_least8_t;
typedef struct { AO_t __ao_val; } atomic_int_fast8_t;
typedef struct { AO_t __ao_val; } atomic_uint_fast8_t;
typedef struct { AO_t __ao_val; } atomic_int_least16_t;
typedef struct { AO_t __ao_val; } atomic_uint_least16_t;
typedef struct { AO_t __ao_val; } atomic_int_fast16_t;
typedef struct { AO_t __ao_val; } atomic_uint_fast16_t;
typedef struct { AO_t __ao_val; } atomic_int_least32_t;
typedef struct { AO_t __ao_val; } atomic_uint_least32_t;
typedef struct { AO_t __ao_val; } atomic_int_fast32_t;
typedef struct { AO_t __ao_val; } atomic_uint_fast32_t;
#if AO_BIT >= 64
typedef struct { AO_t __ao_val; } atomic_int_least64_t;
typedef struct { AO_t __ao_val; } atomic_uint_least64_t;
typedef struct { AO_t __ao_val; } atomic_int_fast64_t;
typedef struct { AO_t __ao_val; } atomic_uint_fast64_t;
#endif
typedef struct { AO_t __ao_val; } atomic_intptr_t;
typedef struct { AO_t __ao_val; } atomic_uintptr_t;
typedef struct { AO_t __ao_val; } atomic_size_t;
typedef struct { AO_t __ao_val; } atomic_ptrdiff_t;
#if 0 /* FIXME */
typedef struct { AO_t __ao_val; } atomic_ssize_t;
typedef struct { AO_t __ao_val; } atomic_intmax_t;
typedef struct { AO_t __ao_val; } atomic_uintmax_t;
#endif

#define _AO_of(a) (&(a)->__ao_val)

#if defined(ATOMIC_INTEGRAL_IS_LOCK_FREE) && \
     defined(ATOMIC_ADDRESS_IS_LOCK_FREE)
#  define atomic_is_lock_free(a) 1
#else
#  define atomic_is_lock_free(a) 0
#endif

#define atomic_store(a, x) AO_store_full(_AO_of(a), (AO_t)(x))

#define atomic_store_explicit(a, x, order) \
  do { switch (order) { \
    case memory_order_relaxed: AO_store(_AO_of(a), (AO_t)(x)); break; \
    case memory_order_acquire: AO_store_acquire(_AO_of(a), (AO_t)(x)); break; \
    case memory_order_release: AO_store_release(_AO_of(a), (AO_t)(x)); break; \
    case memory_order_acq_rel: \
    case memory_order_seq_cst: AO_store_full(_AO_of(a), (AO_t)(x)); break; \
  } } while (0)

/* FIXME: The return type of the atomic load macros is unsuitable for
 * atomic_address. */

#define atomic_load(a) AO_load_full(_AO_of(a))

#define atomic_load_explicit(a, order) \
    (((order) == memory_order_relaxed)? AO_load(_AO_of(a)) : \
     ((order) == memory_order_acquire)? AO_load_acquire(_AO_of(a)) : \
     ((order) == memory_order_release)? AO_load_release(_AO_of(a)) : \
     AO_load_full(_AO_of(a)))

/* TODO: atomic_exchange, atomic_compare_exchange_<strength>,
 *       atomic_fetch_<op> */


/* Atomic Flag
 * =========== */

typedef struct { AO_TS_t __ao_flag; } atomic_flag;

#define _AO_TS_of(af) (&(af)->__ao_flag)

#define ATOMIC_FLAG_INIT {AO_TS_INITIALIZER}

#define atomic_flag_test_and_set(af) AO_test_and_set(_AO_TS_of(af))

/* CHECKME: AO_CLEAR has release-semantic whereas N1349 seems to permit
 * memory_order_seq_cst. */
#define atomic_flag_clear(af) AO_CLEAR(_AO_TS_of(af))
#define atomic_flag_clear_explicit(af, order) AO_CLEAR(_AO_TS_of(af))
