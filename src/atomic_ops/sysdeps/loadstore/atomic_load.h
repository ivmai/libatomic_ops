/*
 * Copyright (c) 2004 Hewlett-Packard Development Company, L.P.
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

#if !defined(AO_ATOMIC_OPS_H) || defined(AO_ATOMIC_OPS_INCLUDED)
# error This file should not be included directly.
#endif

/* Definitions for architectures on which loads of given type are       */
/* atomic (either for suitably aligned data only or for any legal       */
/* alignment).                                                          */

AO_INLINE AO_t
AO_load(const volatile AO_t *addr)
{
# ifdef AO_ACCESS_CHECK_ALIGNED
    AO_ASSERT_ADDR_ALIGNED(addr);
# endif
  /* Cast away the volatile for architectures like IA64 where   */
  /* volatile adds barrier (fence) semantics.                   */
  return *(const AO_t *)addr;
}
#define AO_HAVE_load
