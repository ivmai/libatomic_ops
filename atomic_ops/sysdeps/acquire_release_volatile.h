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
 * This file adds definitions appropriate for environments in which a
 * volatile load has acquire semantics, and a volatile store has release
 * semantics.  This is true with the standard Itanium ABI.
 */
AO_INLINE AO_t
AO_load_acquire(volatile AO_t *p)
{
  /* A normal volatile load generates an ld.acq		*/
  return *p;
}
#define AO_HAVE_load_acquire

AO_INLINE void
AO_store_release(volatile AO_t *p, AO_t val)
{
# if defined(__GNUC_MINOR__) && \
     (__GNUC__ < 3 || __GNUC__ == 3 && __GNUC_MINOR__ < 4)
    AO_compiler_barrier();	/* Empirically necessary for older gcc versions */
# endif
  /* A normal volatile store generates an st.rel	*/
  *p = val;
}
#define AO_HAVE_store_release


