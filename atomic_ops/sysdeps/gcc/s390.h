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

/* FIXME.  Very incomplete.	*/

AO_INLINE AO_t AO_compare_and_swap_full(volatile AO_t *addr,
                                               AO_t old, AO_t new_val)
{
  int retval;
  __asm__ __volatile__ (
# ifndef __s390x__
    "     cs  %1,%2,0(%3)\n"
# else
    "     csg %1,%2,0(%3)\n"
# endif
  "     ipm %0\n"
  "     srl %0,28\n"
  : "=&d" (retval), "+d" (old)
  : "d" (new_val), "a" (addr)
  : "cc", "memory");
  return retval == 0;
}

#define AO_HAVE_compare_and_swap_full

