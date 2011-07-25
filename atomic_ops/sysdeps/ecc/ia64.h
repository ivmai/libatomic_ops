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

/*
 * This file specifies Itanimum primitives for use with the Intel (ecc)
 * compiler.  We use intrinsics instead of the inline assembly code in the
 * gcc file.
 */

#include "../atomic_load_store.h"

#include "../acquire_release_volatile.h"

#include <ia64intrin.h>

AO_INLINE void
AO_nop_full()
{
  __mf();
}
#define AO_HAVE_nop_full

AO_INLINE AO_t
AO_fetch_and_add1_acquire (volatile AO_t *p)
{
  return __fetchadd8_acq((unsigned __int64 *)p, 1);
}
#define AO_HAVE_fetch_and_add1_acquire

AO_INLINE AO_t
AO_fetch_and_add1_release (volatile AO_t *p)
{
  return __fetchadd8_rel((unsigned __int64 *)p, 1);
}

#define AO_HAVE_fetch_and_add1_release

AO_INLINE AO_t
AO_fetch_and_sub1_acquire (volatile AO_t *p)
{
  return __fetchadd8_acq((unsigned __int64 *)p, -1);
}

#define AO_HAVE_fetch_and_sub1_acquire

AO_INLINE AO_t
AO_fetch_and_sub1_release (volatile AO_t *p)
{
  return __fetchadd8_rel((unsigned __int64 *)p, -1);
}

#define AO_HAVE_fetch_and_sub1_release

AO_INLINE int
AO_compare_and_swap_acquire(volatile AO_t *addr,
		             AO_t old, AO_t new_val) 
{
  AO_t oldval;
  oldval = _InterlockedCompareExchange64_acq(addr, new_val, old);
  return (oldval == old);
}

#define AO_HAVE_compare_and_swap_acquire

AO_INLINE int
AO_compare_and_swap_release(volatile AO_t *addr,
		             AO_t old, AO_t new_val) 
{
  AO_t oldval;
  oldval = _InterlockedCompareExchange64_rel(addr, new_val, old);
  return (oldval == old);
}

#define AO_HAVE_compare_and_swap_release

