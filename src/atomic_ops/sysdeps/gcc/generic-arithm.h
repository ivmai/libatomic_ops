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

AO_INLINE AO_t
AO_fetch_and_add(volatile AO_t *addr, AO_t incr)
{
  return __atomic_fetch_add(addr, incr, __ATOMIC_RELAXED);
}
#define AO_HAVE_fetch_and_add

AO_INLINE AO_t
AO_fetch_and_add_acquire(volatile AO_t *addr, AO_t incr)
{
  return __atomic_fetch_add(addr, incr, __ATOMIC_ACQUIRE);
}
#define AO_HAVE_fetch_and_add_acquire

AO_INLINE AO_t
AO_fetch_and_add_release(volatile AO_t *addr, AO_t incr)
{
  return __atomic_fetch_add(addr, incr, __ATOMIC_RELEASE);
}
#define AO_HAVE_fetch_and_add_release

AO_INLINE AO_t
AO_fetch_and_add_full(volatile AO_t *addr, AO_t incr)
{
  return __atomic_fetch_add(addr, incr, __ATOMIC_SEQ_CST);
}
#define AO_HAVE_fetch_and_add_full

AO_INLINE void
AO_and(volatile AO_t *addr, AO_t value)
{
  (void)__atomic_and_fetch(addr, value, __ATOMIC_RELAXED);
}
#define AO_HAVE_and

AO_INLINE void
AO_and_acquire(volatile AO_t *addr, AO_t value)
{
  (void)__atomic_and_fetch(addr, value, __ATOMIC_ACQUIRE);
}
#define AO_HAVE_and_acquire

AO_INLINE void
AO_and_release(volatile AO_t *addr, AO_t value)
{
  (void)__atomic_and_fetch(addr, value, __ATOMIC_RELEASE);
}
#define AO_HAVE_and_release

AO_INLINE void
AO_and_full(volatile AO_t *addr, AO_t value)
{
  (void)__atomic_and_fetch(addr, value, __ATOMIC_SEQ_CST);
}
#define AO_HAVE_and_full

AO_INLINE void
AO_or(volatile AO_t *addr, AO_t value)
{
  (void)__atomic_or_fetch(addr, value, __ATOMIC_RELAXED);
}
#define AO_HAVE_or

AO_INLINE void
AO_or_acquire(volatile AO_t *addr, AO_t value)
{
  (void)__atomic_or_fetch(addr, value, __ATOMIC_ACQUIRE);
}
#define AO_HAVE_or_acquire

AO_INLINE void
AO_or_release(volatile AO_t *addr, AO_t value)
{
  (void)__atomic_or_fetch(addr, value, __ATOMIC_RELEASE);
}
#define AO_HAVE_or_release

AO_INLINE void
AO_or_full(volatile AO_t *addr, AO_t value)
{
  (void)__atomic_or_fetch(addr, value, __ATOMIC_SEQ_CST);
}
#define AO_HAVE_or_full

AO_INLINE void
AO_xor(volatile AO_t *addr, AO_t value)
{
  (void)__atomic_xor_fetch(addr, value, __ATOMIC_RELAXED);
}
#define AO_HAVE_xor

AO_INLINE void
AO_xor_acquire(volatile AO_t *addr, AO_t value)
{
  (void)__atomic_xor_fetch(addr, value, __ATOMIC_ACQUIRE);
}
#define AO_HAVE_xor_acquire

AO_INLINE void
AO_xor_release(volatile AO_t *addr, AO_t value)
{
  (void)__atomic_xor_fetch(addr, value, __ATOMIC_RELEASE);
}
#define AO_HAVE_xor_release

AO_INLINE void
AO_xor_full(volatile AO_t *addr, AO_t value)
{
  (void)__atomic_xor_fetch(addr, value, __ATOMIC_SEQ_CST);
}
#define AO_HAVE_xor_full

/* TODO: Add AO_char/short/int_ primitives (via template header). */
