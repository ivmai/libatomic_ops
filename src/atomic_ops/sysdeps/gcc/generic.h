/*
 * Copyright (c) 1991-1994 by Xerox Corporation.  All rights reserved.
 * Copyright (c) 1996-1999 by Silicon Graphics.  All rights reserved.
 * Copyright (c) 2003-2011 Hewlett-Packard Development Company, L.P.
 *
 *
 * THIS MATERIAL IS PROVIDED AS IS, WITH ABSOLUTELY NO WARRANTY EXPRESSED
 * OR IMPLIED.  ANY USE IS AT YOUR OWN RISK.
 *
 * Permission is hereby granted to use or copy this program
 * for any purpose, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

/* The following implementation assumes GCC 4.7 or later. */

#ifdef AO_UNIPROCESSOR
  /* If only a single processor (core) is used, AO_UNIPROCESSOR could   */
  /* be defined by the client to avoid unnecessary memory barrier.      */
  AO_INLINE void
  AO_nop_full(void)
  {
    AO_compiler_barrier();
  }
# define AO_HAVE_nop_full

#else
  AO_INLINE void
  AO_nop_full(void)
  {
    __sync_synchronize();
  }
# define AO_HAVE_nop_full

  /* TODO: Add AO_nop_write/read. */
#endif /* !AO_UNIPROCESSOR */

/* load */
AO_INLINE AO_t
AO_load(const volatile AO_t *addr)
{
  return __atomic_load_n(addr, __ATOMIC_RELAXED);
}
#define AO_HAVE_load

AO_INLINE AO_t
AO_load_acquire(const volatile AO_t *addr)
{
  return __atomic_load_n(addr, __ATOMIC_ACQUIRE);
}
#define AO_HAVE_load_acquire

/* store */
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

#ifndef AO_PREFER_GENERALIZED
  /* test_and_set */
  AO_INLINE AO_TS_VAL_t
  AO_test_and_set(volatile AO_TS_t *addr)
  {
    return (AO_TS_VAL_t)__atomic_test_and_set(addr, __ATOMIC_RELAXED);
  }
# define AO_HAVE_test_and_set

  AO_INLINE AO_TS_VAL_t
  AO_test_and_set_acquire(volatile AO_TS_t *addr)
  {
    return (AO_TS_VAL_t)__atomic_test_and_set(addr, __ATOMIC_ACQUIRE);
  }
# define AO_HAVE_test_and_set_acquire

  AO_INLINE AO_TS_VAL_t
  AO_test_and_set_release(volatile AO_TS_t *addr)
  {
    return (AO_TS_VAL_t)__atomic_test_and_set(addr, __ATOMIC_RELEASE);
  }
# define AO_HAVE_test_and_set_release

  AO_INLINE AO_TS_VAL_t
  AO_test_and_set_full(volatile AO_TS_t *addr)
  {
    return (AO_TS_VAL_t)__atomic_test_and_set(addr, __ATOMIC_SEQ_CST);
  }
# define AO_HAVE_test_and_set_full

  /* fetch_and_add */
  AO_INLINE AO_t
  AO_fetch_and_add(volatile AO_t *addr, AO_t incr)
  {
    return __atomic_fetch_add(addr, incr, __ATOMIC_RELAXED);
  }
# define AO_HAVE_fetch_and_add

  AO_INLINE AO_t
  AO_fetch_and_add_acquire(volatile AO_t *addr, AO_t incr)
  {
    return __atomic_fetch_add(addr, incr, __ATOMIC_ACQUIRE);
  }
# define AO_HAVE_fetch_and_add_acquire

  AO_INLINE AO_t
  AO_fetch_and_add_release(volatile AO_t *addr, AO_t incr)
  {
    return __atomic_fetch_add(addr, incr, __ATOMIC_RELEASE);
  }
# define AO_HAVE_fetch_and_add_release

  AO_INLINE AO_t
  AO_fetch_and_add_full(volatile AO_t *addr, AO_t incr)
  {
    return __atomic_fetch_add(addr, incr, __ATOMIC_SEQ_CST);
  }
# define AO_HAVE_fetch_and_add_full
#endif /* !AO_PREFER_GENERALIZED */

/* TODO: Add AO_and/or/xor primitives. */

/* CAS primitives */
AO_INLINE AO_t
AO_fetch_compare_and_swap(volatile AO_t *addr, AO_t old_val, AO_t new_val)
{
  return __sync_val_compare_and_swap(addr, old_val, new_val
                                     /* empty protection list */);
}
#define AO_HAVE_fetch_compare_and_swap

/* TODO: Add CAS _acquire/release/full primitives. */

#ifndef AO_GENERALIZE_ASM_BOOL_CAS
  AO_INLINE int
  AO_compare_and_swap(volatile AO_t *addr, AO_t old_val, AO_t new_val)
  {
    return __sync_bool_compare_and_swap(addr, old_val, new_val
                                        /* empty protection list */);
  }
# define AO_HAVE_compare_and_swap
#endif /* !AO_GENERALIZE_ASM_BOOL_CAS */

/* TODO: Add AO_int_ primitives. */
/* TODO: Include standard_ao_double_t.h, add double-wide primitives. */
