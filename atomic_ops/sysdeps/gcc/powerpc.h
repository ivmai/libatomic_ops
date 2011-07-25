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

/* FIXME.  Very incomplete.  No support for 64 bits.	*/
/* I have also been told that the behavior of some of the barriers is model 	*/
/* dependent.  This will probably require help from IBM to fix up.		*/

#include "../atomic_load_store.h"

AO_INLINE void
AO_nop_full()
{
  __asm__ __volatile__("sync" : : : "memory");
}

AO_INLINE void
AO_nop_write()
{
  __asm__ __volatile__("eieio" : : : "memory");
}

#define AO_HAVE_NOP_FULL

AO_INLINE AO_TS_VAL_t
AO_test_and_set_full(volatile AO_TS_t *addr) {
  int oldval;
  int temp = 1; /* locked value */

  __asm__ __volatile__(
               "1:\tlwarx %0,0,%3\n"   /* load and reserve               */
               "\tcmpwi %0, 0\n"       /* if load is                     */
               "\tbne 2f\n"            /*   non-zero, return already set */
               "\tstwcx. %2,0,%1\n"    /* else store conditional         */
               "\tbne- 1b\n"           /* retry if lost reservation      */
               "2:\t\n"                /* oldval is zero if we set       */
              : "=&r"(oldval), "=p"(addr)
              : "r"(temp), "1"(addr)
              : "memory");

  return oldval;
}

#define AO_HAVE_test_and_set_full


