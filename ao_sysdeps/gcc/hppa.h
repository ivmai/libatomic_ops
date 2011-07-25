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

/* Some architecture set descriptions include special "ordered" memory	*/
/* operations.  As far as we can tell, no existing processors actually	*/
/* require those.  Nor does it appear likely that future processors 	*/
/* will.								*/
#include "../ordered.h"

/* It's not clear this should really be used from user mode.  But we 	*/
/* include it here to demonstrate that it could be handled.		*/
union AO_pa_clearable_loc {
  int data;
  double align_16[2];	/* Make the size 16 bytes */
} __attribute__ ((aligned (16)));

#undef AO_TS_T
#undef AO_TS_INITIALIZER
#define AO_TS_T union AO_pa_clearable_loc
#define AO_TS_INITIALIZER { 1 }
/* Switch meaning of set and clear, since we only have an atomic clear	*/
/* instruction.								*/
#undef AO_TS_VAL
#undef AO_TS_CLEAR
#undef AO_TS_SET
typedef enum {AO_PA_TS_set = 0, AO_PA_TS_clear = 1} AO_PA_TS_val;
#define AO_TS_VAL AO_PA_TS_val
#define AO_TS_CLEAR AO_PA_TS_clear
#define AO_TS_SET AO_PA_TS_set

AO_INLINE AO_TS_VAL
AO_test_and_set_full(volatile AO_TS_T * addr)
{
  int result;

  __asm__ __volatile__("ldcw 0(%1),%0"
		       : "=r"(result) : "r"(addr) : "memory");
  return result;
} 

#define AO_HAVE_test_and_set_full

