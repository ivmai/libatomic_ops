/*
 * Copyright (C) 2009 Bradley Smith <brad@brad-smith.co.uk>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include "../all_atomic_load_store.h"

#include "../ordered.h" /* There are no multiprocessor implementations. */

#include "../test_and_set_t_is_ao_t.h"

AO_INLINE AO_TS_VAL_t
AO_test_and_set(volatile AO_TS_t *addr)
{
        int ret;

        __asm__ __volatile__(
                "xchg %[old], %[mem], %[newv]"
                : [old] "=&r"(ret)
                : [mem] "r"(addr), [newv] "r"(1)
                : "memory");

        return ret;
}
#define AO_HAVE_test_and_set
