/*
 * Copyright (c) 2008 Hewlett-Packard Development Company, L.P.
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
 *
 */ 
???? needs work

#include "../all_atomic_load_store.h"

??? What is mips memory ordering anyway???

#define AO_TS_t int

#    ifdef LINUX
#      include <sys/tas.h>
#      define GC_test_and_set(addr) _test_and_set((int *) addr,1)
#      define GC_TEST_AND_SET_DEFINED
#    elif __mips < 3 || !(defined (_ABIN32) || defined(_ABI64)) \
	|| !defined(_COMPILER_VERSION) || _COMPILER_VERSION < 700
#	 ifdef __GNUC__
#          define GC_test_and_set(addr) _test_and_set((void *)addr,1)
#	 else
#          define GC_test_and_set(addr) test_and_set((void *)addr,1)
#	 endif
#    else
#	 include <sgidefs.h>
#	 include <mutex.h>
#	 define GC_test_and_set(addr) __test_and_set32((void *)addr,1)
#	 define GC_clear(addr) __lock_release(addr);
#	 define GC_CLEAR_DEFINED
#    endif


#define AO_HAVE_test_and_set_full

