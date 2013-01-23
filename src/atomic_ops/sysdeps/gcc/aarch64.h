/*
 * Copyright (c) 1991-1994 by Xerox Corporation.  All rights reserved.
 * Copyright (c) 1996-1999 by Silicon Graphics.  All rights reserved.
 * Copyright (c) 1999-2003 by Hewlett-Packard Company. All rights reserved.
 *
 *
 * THIS MATERIAL IS PROVIDED AS IS, WITH ABSOLUTELY NO WARRANTY EXPRESSED
 * OR IMPLIED.  ANY USE IS AT YOUR OWN RISK.
 *
 * Permission is hereby granted to use or copy this program
 * for any purpose,  provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

#include "../read_ordered.h"

#include "../test_and_set_t_is_ao_t.h"

AO_INLINE void
AO_nop_full(void)
{
# ifndef AO_UNIPROCESSOR
__sync_synchronize ();
# endif
}
#define AO_HAVE_nop_full

AO_INLINE AO_t
AO_load(const volatile AO_t *addr)
{
  return  __atomic_load_n (addr, __ATOMIC_RELAXED);
}
#define AO_HAVE_load

AO_INLINE AO_t
AO_load_acquire(const volatile AO_t *addr)
{
  return __atomic_load_n (addr, __ATOMIC_ACQUIRE);
}
#define AO_HAVE_load_acquire

AO_INLINE void
 AO_store(volatile AO_t *addr, AO_t value)
{
  __atomic_store_n(addr, value, __ATOMIC_RELAXED);
}
#define AO_HAVE_store

AO_INLINE void
 AO_store_release(volatile AO_t *addr, AO_t value)
{
  __atomic_store_n(addr, value, __ATOMIC_RELEASE);
}
#define AO_HAVE_store_release

AO_INLINE AO_TS_VAL_t
AO_test_and_set(volatile AO_TS_t *addr)
{
    return __atomic_test_and_set(addr, __ATOMIC_RELAXED);
}
# define AO_HAVE_test_and_set

AO_INLINE AO_TS_VAL_t
AO_test_and_set_acquire(volatile AO_TS_t *addr)
{
    return __atomic_test_and_set(addr, __ATOMIC_ACQUIRE);
}
# define AO_HAVE_test_and_set_acquire

AO_INLINE AO_TS_VAL_t
AO_test_and_set_release(volatile AO_TS_t *addr)
{
    return __atomic_test_and_set(addr, __ATOMIC_RELEASE);
}
# define AO_HAVE_test_and_set_release

AO_INLINE AO_TS_VAL_t
AO_test_and_set_full(volatile AO_TS_t *addr)
{
    return __atomic_test_and_set(addr, __ATOMIC_SEQ_CST);
}
# define AO_HAVE_test_and_set_full

AO_INLINE AO_t
AO_fetch_and_add(volatile AO_t *p, AO_t incr)
{
  return __atomic_fetch_add(p, incr, __ATOMIC_RELAXED);
}
#define AO_HAVE_fetch_and_add

AO_INLINE AO_t
AO_fetch_and_add_acquire(volatile AO_t *p, AO_t incr)
{
  return __atomic_fetch_add(p, incr, __ATOMIC_ACQUIRE);
}
#define AO_HAVE_fetch_and_add_acquire

AO_INLINE AO_t
AO_fetch_and_add_release(volatile AO_t *p, AO_t incr)
{
  return __atomic_fetch_add(p, incr, __ATOMIC_RELEASE);
}
#define AO_HAVE_fetch_and_add_release

AO_INLINE AO_t
AO_fetch_and_add_full(volatile AO_t *p, AO_t incr)
{
  return __atomic_fetch_add(p, incr, __ATOMIC_SEQ_CST);
}
#define AO_HAVE_fetch_and_add_full

AO_INLINE AO_t
AO_fetch_and_add1(volatile AO_t *p)
{
  return __atomic_fetch_add(p, 1, __ATOMIC_RELAXED);
}
#define AO_HAVE_fetch_and_add1

AO_INLINE AO_t
AO_fetch_and_add1_acquire(volatile AO_t *p)
{
  return __atomic_fetch_add(p, 1, __ATOMIC_ACQUIRE);
}
#define AO_HAVE_fetch_and_add1_acquire

AO_INLINE AO_t
AO_fetch_and_add1_release(volatile AO_t *p)
{
  return __atomic_fetch_add(p, 1, __ATOMIC_RELEASE);
}
#define AO_HAVE_fetch_and_add1_release

AO_INLINE AO_t
AO_fetch_and_add1_full(volatile AO_t *p)
{
  return __atomic_fetch_add(p, 1, __ATOMIC_SEQ_CST);
}
#define AO_HAVE_fetch_and_add1_full

AO_INLINE AO_t
AO_fetch_and_sub1(volatile AO_t *p)
{
  return __atomic_fetch_sub(p, 1, __ATOMIC_RELAXED);
}
#define AO_HAVE_fetch_and_sub1

AO_INLINE AO_t
AO_fetch_and_sub1_acquire(volatile AO_t *p)
{
  return __atomic_fetch_sub(p, 1, __ATOMIC_ACQUIRE);
}
#define AO_HAVE_fetch_and_sub1_acquire

AO_INLINE AO_t
AO_fetch_and_sub1_release(volatile AO_t *p)
{
  return __atomic_fetch_sub(p, 1, __ATOMIC_RELEASE);
}
#define AO_HAVE_fetch_and_sub1_release

AO_INLINE AO_t
AO_fetch_and_sub1_full(volatile AO_t *p)
{
  return __atomic_fetch_sub(p, 1, __ATOMIC_SEQ_CST);
}
#define AO_HAVE_fetch_and_sub1_full

/* Returns nonzero if the comparison succeeded.  */
AO_INLINE int
AO_compare_and_swap(volatile AO_t *addr, AO_t old_val, AO_t new_val)
{
    return __sync_bool_compare_and_swap(addr, old_val, new_val);
}
# define AO_HAVE_compare_and_swap

AO_INLINE AO_t
AO_fetch_compare_and_swap(volatile AO_t *addr, AO_t old_val, AO_t new_val)
{
    return __sync_val_compare_and_swap(addr, old_val, new_val);
}
# define AO_HAVE_fetch_compare_and_swap
