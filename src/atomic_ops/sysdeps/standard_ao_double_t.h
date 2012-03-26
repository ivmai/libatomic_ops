/*
 * Copyright (c) 2004-2011 Hewlett-Packard Development Company, L.P.
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
 * NEC LE-IT: For 64-bit OS we extend the double type to hold two int64's
 *
 *  x86-64: __m128 serves as placeholder which also requires the compiler
 *          to align it on 16 byte boundary (as required by cmpxchg16).
 * Similar things could be done for PowerPC 64-bit using a VMX data type...
 */

#if (defined(__x86_64__) && __GNUC__ >= 4) || defined(_WIN64)
# include <xmmintrin.h>
  typedef __m128 double_ptr_storage;
#elif defined(_WIN32) && !defined(__GNUC__)
  typedef unsigned __int64 double_ptr_storage;
#else
  typedef unsigned long long double_ptr_storage;
#endif

# define AO_HAVE_DOUBLE_PTR_STORAGE

typedef union {
    double_ptr_storage AO_whole;
    struct {AO_t AO_v1; AO_t AO_v2;} AO_parts;
} AO_double_t;

#define AO_HAVE_double_t
#define AO_val1 AO_parts.AO_v1
#define AO_val2 AO_parts.AO_v2
