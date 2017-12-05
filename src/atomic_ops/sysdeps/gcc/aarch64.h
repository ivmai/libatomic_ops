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

#include "../standard_ao_double_t.h"

/* As of clang-5.0 (and gcc-5.4), __atomic_thread_fence is always       */
/* translated to DMB (which is inefficient for AO_nop_write).           */
/* TODO: Update it for newer Clang and GCC releases. */
#if !defined(AO_PREFER_BUILTIN_ATOMICS) && !defined(AO_THREAD_SANITIZER) \
    && !defined(AO_UNIPROCESSOR)
  AO_INLINE void
  AO_nop_write(void)
  {
    __asm__ __volatile__("dmb ishst" : : : "memory");
  }
# define AO_HAVE_nop_write
#endif

/* Atomics for loading double word in Clang were translated to an       */
/* incorrect code lacking STXP (see the note in AO_double_load below).  */
#if defined(AO_PREFER_BUILTIN_ATOMICS) \
    && defined(__clang__) && !AO_CLANG_PREREQ(3, 8)
# define AO_SKIPATOMIC_double_load
# define AO_SKIPATOMIC_double_load_acquire
#endif

/* As of gcc-5.4, all built-in load/store and CAS atomics for double    */
/* word require -latomic (and are not lock-free), so we use the         */
/* asm-based implementation by default.                                 */
/* TODO: Update it when GCC has lock-free double-word load/store/CAS.   */
#if !defined(AO_PREFER_BUILTIN_ATOMICS) && !defined(AO_THREAD_SANITIZER) \
    && (!defined(__clang__) || defined(AO_AARCH64_ASM_LOAD_STORE_CAS))

  AO_INLINE AO_double_t
  AO_double_load(const volatile AO_double_t *addr)
  {
    AO_double_t result;
    int status;

    /* Note that STXP cannot be discarded because LD[A]XP is not        */
    /* single-copy atomic (unlike LDREXD for 32-bit ARM).               */
    do {
      __asm__ __volatile__("//AO_double_load\n"
      "       ldxp  %0, %1, %3\n"
      "       stxp %w2, %0, %1, %3"
      : "=&r" (result.AO_val1), "=&r" (result.AO_val2), "=&r" (status)
      : "Q" (*addr));
    } while (AO_EXPECT_FALSE(status));
    return result;
  }
# define AO_HAVE_double_load

  AO_INLINE AO_double_t
  AO_double_load_acquire(const volatile AO_double_t *addr)
  {
    AO_double_t result;
    int status;

    do {
      __asm__ __volatile__("//AO_double_load_acquire\n"
      "       ldaxp  %0, %1, %3\n"
      "       stxp %w2, %0, %1, %3"
      : "=&r" (result.AO_val1), "=&r" (result.AO_val2), "=&r" (status)
      : "Q" (*addr));
    } while (AO_EXPECT_FALSE(status));
    return result;
  }
# define AO_HAVE_double_load_acquire

  AO_INLINE void
  AO_double_store(volatile AO_double_t *addr, AO_double_t value)
  {
    AO_double_t old_val;
    int status;

    do {
      __asm__ __volatile__("//AO_double_store\n"
      "       ldxp  %0, %1, %3\n"
      "       stxp %w2, %4, %5, %3"
      : "=&r" (old_val.AO_val1), "=&r" (old_val.AO_val2), "=&r" (status),
        "=Q" (*addr)
      : "r" (value.AO_val1), "r" (value.AO_val2));
      /* Compared to the arm.h implementation, the 'cc' (flags) are not */
      /* clobbered because A64 has no concept of conditional execution. */
    } while (AO_EXPECT_FALSE(status));
  }
# define AO_HAVE_double_store

  AO_INLINE void
  AO_double_store_release(volatile AO_double_t *addr, AO_double_t value)
  {
    AO_double_t old_val;
    int status;

    do {
      __asm__ __volatile__("//AO_double_store_release\n"
      "       ldxp  %0, %1, %3\n"
      "       stlxp %w2, %4, %5, %3"
      : "=&r" (old_val.AO_val1), "=&r" (old_val.AO_val2), "=&r" (status),
        "=Q" (*addr)
      : "r" (value.AO_val1), "r" (value.AO_val2));
    } while (AO_EXPECT_FALSE(status));
  }
# define AO_HAVE_double_store_release

  AO_INLINE int
  AO_double_compare_and_swap(volatile AO_double_t *addr,
                             AO_double_t old_val, AO_double_t new_val)
  {
    AO_double_t tmp;
    int result = 1;

    do {
      __asm__ __volatile__("//AO_double_compare_and_swap\n"
        "       ldxp  %0, %1, %2\n"
        : "=&r" (tmp.AO_val1), "=&r" (tmp.AO_val2)
        : "Q" (*addr));
      if (tmp.AO_val1 != old_val.AO_val1 || tmp.AO_val2 != old_val.AO_val2)
        break;
      __asm__ __volatile__(
        "       stxp %w0, %2, %3, %1\n"
        : "=&r" (result), "=Q" (*addr)
        : "r" (new_val.AO_val1), "r" (new_val.AO_val2));
    } while (AO_EXPECT_FALSE(result));
    return !result;
  }
# define AO_HAVE_double_compare_and_swap

  AO_INLINE int
  AO_double_compare_and_swap_acquire(volatile AO_double_t *addr,
                                     AO_double_t old_val, AO_double_t new_val)
  {
    AO_double_t tmp;
    int result = 1;

    do {
      __asm__ __volatile__("//AO_double_compare_and_swap_acquire\n"
        "       ldaxp  %0, %1, %2\n"
        : "=&r" (tmp.AO_val1), "=&r" (tmp.AO_val2)
        : "Q" (*addr));
      if (tmp.AO_val1 != old_val.AO_val1 || tmp.AO_val2 != old_val.AO_val2)
        break;
      __asm__ __volatile__(
        "       stxp %w0, %2, %3, %1\n"
        : "=&r" (result), "=Q" (*addr)
        : "r" (new_val.AO_val1), "r" (new_val.AO_val2));
    } while (AO_EXPECT_FALSE(result));
    return !result;
  }
# define AO_HAVE_double_compare_and_swap_acquire

  AO_INLINE int
  AO_double_compare_and_swap_release(volatile AO_double_t *addr,
                                     AO_double_t old_val, AO_double_t new_val)
  {
    AO_double_t tmp;
    int result = 1;

    do {
      __asm__ __volatile__("//AO_double_compare_and_swap_release\n"
        "       ldxp  %0, %1, %2\n"
        : "=&r" (tmp.AO_val1), "=&r" (tmp.AO_val2)
        : "Q" (*addr));
      if (tmp.AO_val1 != old_val.AO_val1 || tmp.AO_val2 != old_val.AO_val2)
        break;
      __asm__ __volatile__(
        "       stlxp %w0, %2, %3, %1\n"
        : "=&r" (result), "=Q" (*addr)
        : "r" (new_val.AO_val1), "r" (new_val.AO_val2));
    } while (AO_EXPECT_FALSE(result));
    return !result;
  }
# define AO_HAVE_double_compare_and_swap_release

  AO_INLINE int
  AO_double_compare_and_swap_full(volatile AO_double_t *addr,
                                  AO_double_t old_val, AO_double_t new_val)
  {
    AO_double_t tmp;
    int result = 1;

    do {
      __asm__ __volatile__("//AO_double_compare_and_swap_full\n"
        "       ldaxp  %0, %1, %2\n"
        : "=&r" (tmp.AO_val1), "=&r" (tmp.AO_val2)
        : "Q" (*addr));
      if (tmp.AO_val1 != old_val.AO_val1 || tmp.AO_val2 != old_val.AO_val2)
        break;
      __asm__ __volatile__(
        "       stlxp %w0, %2, %3, %1\n"
        : "=&r" (result), "=Q" (*addr)
        : "r" (new_val.AO_val1), "r" (new_val.AO_val2));
    } while (AO_EXPECT_FALSE(result));
    return !result;
  }
# define AO_HAVE_double_compare_and_swap_full

#endif /* !AO_PREFER_BUILTIN_ATOMICS && !__clang__ */

#if (defined(__clang__) && !AO_CLANG_PREREQ(3, 8)) || defined(__APPLE_CC__)
  /* __GCC_HAVE_SYNC_COMPARE_AND_SWAP_n macros are missing.     */
# define AO_GCC_FORCE_HAVE_CAS
# define AO_GCC_HAVE_double_SYNC_CAS
#endif

#include "generic.h"

#undef AO_GCC_FORCE_HAVE_CAS
#undef AO_GCC_HAVE_double_SYNC_CAS
#undef AO_SKIPATOMIC_double_load
#undef AO_SKIPATOMIC_double_load_acquire
