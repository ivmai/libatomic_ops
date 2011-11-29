/*
 * Copyright (c) 2005,2007  Thiemo Seufer <ths@networkno.de>
 *
 * THIS MATERIAL IS PROVIDED AS IS, WITH ABSOLUTELY NO WARRANTY EXPRESSED
 * OR IMPLIED.  ANY USE IS AT YOUR OWN RISK.
 *
 * Permission is hereby granted to use or copy this program
 * for any purpose,  provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 */

/*
 * FIXME:  This should probably make finer distinctions.  SGI MIPS is
 * much more strongly ordered, and in fact closer to sequentially
 * consistent.  This is really aimed at modern embedded implementations.
 * It looks to me like this assumes a 32-bit ABI.  -HB
 */

#include "../all_aligned_atomic_load_store.h"
#include "../acquire_release_volatile.h"
#include "../test_and_set_t_is_ao_t.h"
#include "../standard_ao_double_t.h"

/* Data dependence does not imply read ordering.  */
#define AO_NO_DD_ORDERING

AO_INLINE void
AO_nop_full(void)
{
  __asm__ __volatile__(
      "       .set push           \n"
      "       .set mips2          \n"
      "       .set noreorder      \n"
      "       .set nomacro        \n"
      "       sync                \n"
      "       .set pop              "
      : : : "memory");
}
#define AO_HAVE_nop_full

AO_INLINE int
AO_compare_and_swap(volatile AO_t *addr, AO_t old, AO_t new_val)
{
  register int was_equal = 0;
  register int temp;

  __asm__ __volatile__(
      "       .set push           \n"
      "       .set mips2          \n"
      "       .set noreorder      \n"
      "       .set nomacro        \n"
      "1:     ll      %0, %1      \n"
      "       bne     %0, %4, 2f  \n"
      "        move   %0, %3      \n"
      "       sc      %0, %1      \n"
      "       .set pop            \n"
      "       beqz    %0, 1b      \n"
      "       li      %2, 1       \n"
      "2:                           "
      : "=&r" (temp), "+R" (*addr), "+r" (was_equal)
      : "r" (new_val), "r" (old)
      : "memory");
  return was_equal;
}
#define AO_HAVE_compare_and_swap

/* CAS primitives with acquire, release and full semantics are  */
/* generated automatically (and AO_int_... primitives are       */
/* defined properly after the first generalization pass).       */

/*
 * FIXME: We should also implement fetch_and_add and or primitives
 * directly.
 */

#define AO_T_IS_INT
