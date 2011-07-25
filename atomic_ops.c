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
 * Initialized data and out-of-line functions to support atomic_ops.h
 * go here.  Currently this is needed only for pthread-based atomics
 * emulation, or for compare-and-swap emulation.
 * Pthreads emulation isn't useful on a native Windows platform, and
 * cas emulation is not needed.  Thus we skip this on Windows.
 */

#if !defined(_MSC_VER) && !defined(__MINGW32__) && !defined(__BORLANDC__)

#undef AO_FORCE_CAS

#include <pthread.h>
#include <signal.h>
#ifdef _HPUX_SOURCE
# include <sys/time.h>
#else
# include <sys/select.h>
#endif
#include "atomic_ops.h"  /* Without cas emulation! */

/*
 * Lock for pthreads-based implementation.
 */

pthread_mutex_t AO_pt_lock = PTHREAD_MUTEX_INITIALIZER;

/*
 * Out of line compare-and-swap emulation based on test and set.
 * 
 * We use a small table of locks for different compare_and_swap locations.
 * Before we update perform a compare-and-swap, we grap the corresponding
 * lock.  Different locations may hash to the same lock, but since we
 * never acquire more than one lock at a time, this can't deadlock.
 * We explicitly disable signals while we perform this operation.
 *
 * FIXME: We should probably also suppport emulation based on Lamport
 * locks, since we may not have test_and_set either.
 */
#define AO_HASH_SIZE 16

#define AO_HASH(x) (((unsigned long)(x) >> 12) & (AO_HASH_SIZE-1))

AO_TS_T AO_locks[AO_HASH_SIZE] = {
	AO_TS_INITIALIZER, AO_TS_INITIALIZER,
	AO_TS_INITIALIZER, AO_TS_INITIALIZER,
	AO_TS_INITIALIZER, AO_TS_INITIALIZER,
	AO_TS_INITIALIZER, AO_TS_INITIALIZER,
	AO_TS_INITIALIZER, AO_TS_INITIALIZER,
	AO_TS_INITIALIZER, AO_TS_INITIALIZER,
	AO_TS_INITIALIZER, AO_TS_INITIALIZER,
	AO_TS_INITIALIZER, AO_TS_INITIALIZER,
};

static AO_T dummy = 1;

/* Spin for 2**n units. */
static void spin(int n)
{
  int i;
  AO_T j = AO_load(&dummy);

  for (i = 0; i < (2 << n); ++i)
    {
       j *= 5;
       j -= 4;
    }
  AO_store(&dummy, j);
}

static void lock_ool(volatile AO_TS_T *l)
{
  int i = 0;
  struct timeval tv;

  while (AO_test_and_set_acquire(l) == AO_TS_SET) {
    if (++i < 12)
      spin(i);
    else
      {
	/* Short async-signal-safe sleep. */
	tv.tv_sec = 0;
	tv.tv_usec = (i > 28? 100000 : (1 << (i - 12)));
	select(0, 0, 0, 0, &tv);
      }
  }
}

AO_INLINE void lock(volatile AO_TS_T *l)
{
  if (AO_test_and_set_acquire(l) == AO_TS_SET)
    lock_ool(l);
}

AO_INLINE void unlock(volatile AO_TS_T *l)
{
  AO_CLEAR(l);
}

static sigset_t all_sigs;

static volatile AO_T initialized = 0;

static volatile AO_TS_T init_lock = AO_TS_INITIALIZER;

int AO_compare_and_swap_emulation(volatile AO_T *addr, AO_T old,
				   AO_T new_val)
{
  AO_TS_T *my_lock = AO_locks + AO_HASH(addr);
  sigset_t old_sigs;
  int result;

  if (!AO_load_acquire(&initialized))
    {
      lock(&init_lock);
      if (!initialized) sigfillset(&all_sigs);
      unlock(&init_lock);
      AO_store_release(&initialized, 1);
    }
  sigprocmask(SIG_BLOCK, &all_sigs, &old_sigs);
  	/* Neither sigprocmask nor pthread_sigmask is 100%	*/
  	/* guaranteed to work here.  Sigprocmask is not 	*/
  	/* guaranteed be thread safe, and pthread_sigmask	*/
  	/* is not async-signal-safe.  Under linuxthreads,	*/
  	/* sigprocmask may block some pthreads-internal		*/
  	/* signals.  So long as we do that for short periods,	*/
  	/* we should be OK.					*/
  lock(my_lock);
  if (*addr == old)
    {
      *addr = new_val;
      result = 1;
    }
  else
    result = 0;
  unlock(my_lock);
  sigprocmask(SIG_SETMASK, &old_sigs, NULL);
  return result;
}

void AO_store_full_emulation(volatile AO_T *addr, AO_T val)
{
  AO_TS_T *my_lock = AO_locks + AO_HASH(addr);
  lock(my_lock);
  *addr = val;
  unlock(my_lock);
}

#else /* Non-posix platform */

int AO_non_posix_implementation_is_entirely_in_headers;

#endif
