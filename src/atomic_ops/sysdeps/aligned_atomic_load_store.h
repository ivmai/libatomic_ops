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

/* Definitions for architectures on which loads and stores of AO_t are  */
/* atomic fo all legal alignments.                                      */

AO_INLINE AO_t
AO_load(const volatile AO_t *addr)
{
#if defined(__m68k__)
  /* Even though AO_t is redefined in m68k.h, some clients use AO       */
  /* pointer size primitives to access variables not declared as AO_t.  */
  /* Such variables may have 2-byte alignment, while their sizeof is 4. */
#else
  assert(((size_t)addr & (sizeof(AO_t) - 1)) == 0);
#endif
  /* Cast away the volatile for architectures where             */
  /* volatile adds barrier semantics.                           */
  return *(AO_t *)addr;
}
#define AO_HAVE_load

AO_INLINE void
AO_store(volatile AO_t *addr, AO_t new_val)
{
#if !defined(__m68k__)
  assert(((size_t)addr & (sizeof(AO_t) - 1)) == 0);
#endif
  (*(AO_t *)addr) = new_val;
}
#define AO_HAVE_store
