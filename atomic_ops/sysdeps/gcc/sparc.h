/* 
 * Copyright (c) 1991-1994 by Xerox Corporation.  All rights reserved.
 * Copyright (c) 1996-1999 by Silicon Graphics.  All rights reserved.
 * Copyright (c) 1999-2003 by Hewlett-Packard Company. All rights reserved.
 *
 *
 * THIS MATERIAL IS PROVIDED AS IS, WITH ABSOLUTELY NO WARRANTY EXPRESSED
 * OR IMPLIED.  ANY USE IS AT YOUR OWN RISK.
 *
 * Permission is hereby granted to use or copy this program
 * for any purpose,  provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

/* FIXME.  Very incomplete.  No support for sparc64.	*/
/* Non-ancient SPARCs provide compare-and-swap (casa).	*/
/* We should make that available.			*/

#include "../atomic_load_store.h"

/* Real SPARC code uses TSO:				*/
#include "../ordered_except_wr.h"

AO_INLINE AO_TS_VAL_t
AO_test_and_set_full(volatile AO_TS_t *addr) {
  int oldval;

   __asm__ __volatile__("ldstub %1,%0"
	                : "=r"(oldval), "=m"(*addr)
	                : "m"(*addr) : "memory");
   return oldval;
}

#define AO_HAVE_test_and_set_full


