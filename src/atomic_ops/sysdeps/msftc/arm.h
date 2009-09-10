/*
 * Copyright (c) 2003 Hewlett-Packard Development Company, L.P.
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

#include "../read_ordered.h"

#ifndef AO_ASSUME_WINDOWS98
  /* CAS is always available */
# define AO_ASSUME_WINDOWS98
#endif
#include "common32_defs.h"

#ifdef AO_ASSUME_ARM_ARCH6
/* ARMv6 is the first architecture providing support for simple LL/SC.	*/

#include "../standard_ao_double_t.h"

/* If only a single processor is used, we can define AO_UNIPROCESSOR	*/
/* and do not need to access CP15 for ensuring a DMB at all.		*/
#ifdef AO_UNIPROCESSOR
  AO_INLINE void AO_nop_full(void) {}
# define AO_HAVE_nop_full
#else
/* FIXME: implement AO_nop_full() */
#endif

AO_INLINE AO_t
AO_load(const volatile AO_t *addr)
{
  /* Cast away the volatile in case it adds fence semantics */
  return (*(const AO_t *)addr);
}

#define AO_HAVE_load

/* FIXME: implement AO_store() */

/* #include "../test_and_set_t_is_ao_t.h" */
/* FIXME: implement AO_test_and_set() */

/* FIXME: implement AO_compare_double_and_swap_double() */

#endif /* AO_ASSUME_ARM_ARCH6 */
