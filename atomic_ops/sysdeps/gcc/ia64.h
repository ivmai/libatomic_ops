/*
 * Copyright (c) 2003 by Hewlett-Packard Company.  All rights reserved.
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

#include "../atomic_load_store.h"

#include "../acquire_release_volatile.h"

AO_INLINE void
AO_nop_full()
{
  __asm__ __volatile__("mf" : : : "memory");
}
#define AO_HAVE_nop_full

AO_INLINE AO_t
AO_fetch_and_add1_acquire (volatile AO_t *p)
{
  AO_t result;

  __asm__ __volatile__ ("fetchadd8.acq %0=[%1],1":
			"=r" (result): "r"(p) :"memory");
  return result;
}
#define AO_HAVE_fetch_and_add1_acquire

AO_INLINE AO_t
AO_fetch_and_add1_release (volatile AO_t *p)
{
  AO_t result;

  __asm__ __volatile__ ("fetchadd8.rel %0=[%1],1":
			"=r" (result): "r"(p) :"memory");
  return result;
}

#define AO_HAVE_fetch_and_add1_release

AO_INLINE AO_t
AO_fetch_and_sub1_acquire (volatile AO_t *p)
{
  AO_t result;

  __asm__ __volatile__ ("fetchadd8.acq %0=[%1],-1":
			"=r" (result): "r"(p) :"memory");
  return result;
}

#define AO_HAVE_fetch_and_sub1_acquire

AO_INLINE AO_t
AO_fetch_and_sub1_release (volatile AO_t *p)
{
  AO_t result;

  __asm__ __volatile__ ("fetchadd8.rel %0=[%1],-1":
			"=r" (result): "r"(p) :"memory");
  return result;
}

#define AO_HAVE_fetch_and_sub1_release

AO_INLINE int
AO_compare_and_swap_acquire(volatile AO_t *addr,
		             AO_t old, AO_t new_val) 
{
  AO_t oldval;
  __asm__ __volatile__("mov ar.ccv=%3 ;; cmpxchg8.acq %0=%1,%2,ar.ccv"
		       : "=r"(oldval), "+S"(*addr)
		       : "r"(new_val), "r"(old) : "memory");
  return (oldval == old);
}

#define AO_HAVE_compare_and_swap_acquire

AO_INLINE int
AO_compare_and_swap_release(volatile AO_t *addr,
		             AO_t old, AO_t new_val) 
{
  AO_t oldval;
  __asm__ __volatile__("mov ar.ccv=%3 ;; cmpxchg8.rel %0=%1,%2,ar.ccv"
		       : "=r"(oldval), "+S"(*addr)
		       : "r"(new_val), "r"(old) : "memory");
  return (oldval == old);
}

#define AO_HAVE_compare_and_swap_release

