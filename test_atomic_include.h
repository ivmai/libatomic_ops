/*
 * Copyright (c) 2003 by Hewlett-Packard Company.  All rights reserved.
 *
 * This file is covered by the GNU general public license, version 2.
 * see doc/COPYING for details.
 */

/* Some basic sanity tests.  These do not test the barrier semantics. */

#undef TA_assert
#define TA_assert(e) \
  if (!(e)) { fprintf(stderr, "Assertion failed %s:%d (barrier: )\n", \
		    __FILE__, __LINE__), exit(1); }

#undef MISSING
#define MISSING(name) \
  fprintf(stderr, "Missing: %s\n", #name "")

void test_atomic(void)
{
  AO_T x;
# if defined(AO_HAVE_test_and_set)
    AO_TS_T z = AO_TS_INITIALIZER;
# endif

# if defined(AO_HAVE_nop)
    AO_nop();
# else
    MISSING(AO_nop);
# endif
# if defined(AO_HAVE_store)
    AO_store(&x, 13);
    TA_assert (x == 13);
# else
    MISSING(AO_store);
    x = 13;
# endif
# if defined(AO_HAVE_load)
    TA_assert(AO_load(&x) == 13);
# else
    MISSING(AO_load);
# endif
# if defined(AO_HAVE_test_and_set)
    assert(AO_test_and_set(&z) == AO_TS_CLEAR);
    assert(AO_test_and_set(&z) == AO_TS_SET);
    assert(AO_test_and_set(&z) == AO_TS_SET);
    AO_CLEAR(&z);
# else
    MISSING(AO_test_and_set);
# endif
# if defined(AO_HAVE_fetch_and_add)
    TA_assert(AO_fetch_and_add(&x, 42) == 13);
    TA_assert(AO_fetch_and_add(&x, -42) == 55);
# else
    MISSING(AO_fetch_and_add);
# endif
# if defined(AO_HAVE_fetch_and_add1)
    TA_assert(AO_fetch_and_add1(&x) == 13);
# else
    MISSING(AO_fetch_and_add1);
    ++x;
# endif
# if defined(AO_HAVE_fetch_and_sub1)
    TA_assert(AO_fetch_and_sub1(&x) == 14);
# else
    MISSING(AO_fetch_and_sub1);
    --x;
# endif
# if defined(AO_HAVE_compare_and_swap)
    TA_assert(!AO_compare_and_swap(&x, 14, 42));
    TA_assert(x == 13);
    TA_assert(AO_compare_and_swap(&x, 13, 42));
    TA_assert(x == 42);
# else
    MISSING(AO_compare_and_swap);
# endif
# if defined(AO_HAVE_or)
    AO_or(&x, 66);
    TA_assert(x == 106);
# else
    MISSING(AO_or);
    x |= 34;
# endif
}


    
/*
 * Copyright (c) 2003 by Hewlett-Packard Company.  All rights reserved.
 *
 * This file is covered by the GNU general public license, version 2.
 * see doc/COPYING for details.
 */

/* Some basic sanity tests.  These do not test the barrier semantics. */

#undef TA_assert
#define TA_assert(e) \
  if (!(e)) { fprintf(stderr, "Assertion failed %s:%d (barrier: _release)\n", \
		    __FILE__, __LINE__), exit(1); }

#undef MISSING
#define MISSING(name) \
  fprintf(stderr, "Missing: %s\n", #name "_release")

void test_atomic_release(void)
{
  AO_T x;
# if defined(AO_HAVE_test_and_set_release)
    AO_TS_T z = AO_TS_INITIALIZER;
# endif

# if defined(AO_HAVE_nop_release)
    AO_nop_release();
# else
    MISSING(AO_nop);
# endif
# if defined(AO_HAVE_store_release)
    AO_store_release(&x, 13);
    TA_assert (x == 13);
# else
    MISSING(AO_store);
    x = 13;
# endif
# if defined(AO_HAVE_load_release)
    TA_assert(AO_load_release(&x) == 13);
# else
    MISSING(AO_load);
# endif
# if defined(AO_HAVE_test_and_set_release)
    assert(AO_test_and_set_release(&z) == AO_TS_CLEAR);
    assert(AO_test_and_set_release(&z) == AO_TS_SET);
    assert(AO_test_and_set_release(&z) == AO_TS_SET);
    AO_CLEAR(&z);
# else
    MISSING(AO_test_and_set);
# endif
# if defined(AO_HAVE_fetch_and_add_release)
    TA_assert(AO_fetch_and_add_release(&x, 42) == 13);
    TA_assert(AO_fetch_and_add_release(&x, -42) == 55);
# else
    MISSING(AO_fetch_and_add);
# endif
# if defined(AO_HAVE_fetch_and_add1_release)
    TA_assert(AO_fetch_and_add1_release(&x) == 13);
# else
    MISSING(AO_fetch_and_add1);
    ++x;
# endif
# if defined(AO_HAVE_fetch_and_sub1_release)
    TA_assert(AO_fetch_and_sub1_release(&x) == 14);
# else
    MISSING(AO_fetch_and_sub1);
    --x;
# endif
# if defined(AO_HAVE_compare_and_swap_release)
    TA_assert(!AO_compare_and_swap_release(&x, 14, 42));
    TA_assert(x == 13);
    TA_assert(AO_compare_and_swap_release(&x, 13, 42));
    TA_assert(x == 42);
# else
    MISSING(AO_compare_and_swap);
# endif
# if defined(AO_HAVE_or_release)
    AO_or_release(&x, 66);
    TA_assert(x == 106);
# else
    MISSING(AO_or);
    x |= 34;
# endif
}


    
/*
 * Copyright (c) 2003 by Hewlett-Packard Company.  All rights reserved.
 *
 * This file is covered by the GNU general public license, version 2.
 * see doc/COPYING for details.
 */

/* Some basic sanity tests.  These do not test the barrier semantics. */

#undef TA_assert
#define TA_assert(e) \
  if (!(e)) { fprintf(stderr, "Assertion failed %s:%d (barrier: _acquire)\n", \
		    __FILE__, __LINE__), exit(1); }

#undef MISSING
#define MISSING(name) \
  fprintf(stderr, "Missing: %s\n", #name "_acquire")

void test_atomic_acquire(void)
{
  AO_T x;
# if defined(AO_HAVE_test_and_set_acquire)
    AO_TS_T z = AO_TS_INITIALIZER;
# endif

# if defined(AO_HAVE_nop_acquire)
    AO_nop_acquire();
# else
    MISSING(AO_nop);
# endif
# if defined(AO_HAVE_store_acquire)
    AO_store_acquire(&x, 13);
    TA_assert (x == 13);
# else
    MISSING(AO_store);
    x = 13;
# endif
# if defined(AO_HAVE_load_acquire)
    TA_assert(AO_load_acquire(&x) == 13);
# else
    MISSING(AO_load);
# endif
# if defined(AO_HAVE_test_and_set_acquire)
    assert(AO_test_and_set_acquire(&z) == AO_TS_CLEAR);
    assert(AO_test_and_set_acquire(&z) == AO_TS_SET);
    assert(AO_test_and_set_acquire(&z) == AO_TS_SET);
    AO_CLEAR(&z);
# else
    MISSING(AO_test_and_set);
# endif
# if defined(AO_HAVE_fetch_and_add_acquire)
    TA_assert(AO_fetch_and_add_acquire(&x, 42) == 13);
    TA_assert(AO_fetch_and_add_acquire(&x, -42) == 55);
# else
    MISSING(AO_fetch_and_add);
# endif
# if defined(AO_HAVE_fetch_and_add1_acquire)
    TA_assert(AO_fetch_and_add1_acquire(&x) == 13);
# else
    MISSING(AO_fetch_and_add1);
    ++x;
# endif
# if defined(AO_HAVE_fetch_and_sub1_acquire)
    TA_assert(AO_fetch_and_sub1_acquire(&x) == 14);
# else
    MISSING(AO_fetch_and_sub1);
    --x;
# endif
# if defined(AO_HAVE_compare_and_swap_acquire)
    TA_assert(!AO_compare_and_swap_acquire(&x, 14, 42));
    TA_assert(x == 13);
    TA_assert(AO_compare_and_swap_acquire(&x, 13, 42));
    TA_assert(x == 42);
# else
    MISSING(AO_compare_and_swap);
# endif
# if defined(AO_HAVE_or_acquire)
    AO_or_acquire(&x, 66);
    TA_assert(x == 106);
# else
    MISSING(AO_or);
    x |= 34;
# endif
}


    
/*
 * Copyright (c) 2003 by Hewlett-Packard Company.  All rights reserved.
 *
 * This file is covered by the GNU general public license, version 2.
 * see doc/COPYING for details.
 */

/* Some basic sanity tests.  These do not test the barrier semantics. */

#undef TA_assert
#define TA_assert(e) \
  if (!(e)) { fprintf(stderr, "Assertion failed %s:%d (barrier: _read)\n", \
		    __FILE__, __LINE__), exit(1); }

#undef MISSING
#define MISSING(name) \
  fprintf(stderr, "Missing: %s\n", #name "_read")

void test_atomic_read(void)
{
  AO_T x;
# if defined(AO_HAVE_test_and_set_read)
    AO_TS_T z = AO_TS_INITIALIZER;
# endif

# if defined(AO_HAVE_nop_read)
    AO_nop_read();
# else
    MISSING(AO_nop);
# endif
# if defined(AO_HAVE_store_read)
    AO_store_read(&x, 13);
    TA_assert (x == 13);
# else
    MISSING(AO_store);
    x = 13;
# endif
# if defined(AO_HAVE_load_read)
    TA_assert(AO_load_read(&x) == 13);
# else
    MISSING(AO_load);
# endif
# if defined(AO_HAVE_test_and_set_read)
    assert(AO_test_and_set_read(&z) == AO_TS_CLEAR);
    assert(AO_test_and_set_read(&z) == AO_TS_SET);
    assert(AO_test_and_set_read(&z) == AO_TS_SET);
    AO_CLEAR(&z);
# else
    MISSING(AO_test_and_set);
# endif
# if defined(AO_HAVE_fetch_and_add_read)
    TA_assert(AO_fetch_and_add_read(&x, 42) == 13);
    TA_assert(AO_fetch_and_add_read(&x, -42) == 55);
# else
    MISSING(AO_fetch_and_add);
# endif
# if defined(AO_HAVE_fetch_and_add1_read)
    TA_assert(AO_fetch_and_add1_read(&x) == 13);
# else
    MISSING(AO_fetch_and_add1);
    ++x;
# endif
# if defined(AO_HAVE_fetch_and_sub1_read)
    TA_assert(AO_fetch_and_sub1_read(&x) == 14);
# else
    MISSING(AO_fetch_and_sub1);
    --x;
# endif
# if defined(AO_HAVE_compare_and_swap_read)
    TA_assert(!AO_compare_and_swap_read(&x, 14, 42));
    TA_assert(x == 13);
    TA_assert(AO_compare_and_swap_read(&x, 13, 42));
    TA_assert(x == 42);
# else
    MISSING(AO_compare_and_swap);
# endif
# if defined(AO_HAVE_or_read)
    AO_or_read(&x, 66);
    TA_assert(x == 106);
# else
    MISSING(AO_or);
    x |= 34;
# endif
}


    
/*
 * Copyright (c) 2003 by Hewlett-Packard Company.  All rights reserved.
 *
 * This file is covered by the GNU general public license, version 2.
 * see doc/COPYING for details.
 */

/* Some basic sanity tests.  These do not test the barrier semantics. */

#undef TA_assert
#define TA_assert(e) \
  if (!(e)) { fprintf(stderr, "Assertion failed %s:%d (barrier: _write)\n", \
		    __FILE__, __LINE__), exit(1); }

#undef MISSING
#define MISSING(name) \
  fprintf(stderr, "Missing: %s\n", #name "_write")

void test_atomic_write(void)
{
  AO_T x;
# if defined(AO_HAVE_test_and_set_write)
    AO_TS_T z = AO_TS_INITIALIZER;
# endif

# if defined(AO_HAVE_nop_write)
    AO_nop_write();
# else
    MISSING(AO_nop);
# endif
# if defined(AO_HAVE_store_write)
    AO_store_write(&x, 13);
    TA_assert (x == 13);
# else
    MISSING(AO_store);
    x = 13;
# endif
# if defined(AO_HAVE_load_write)
    TA_assert(AO_load_write(&x) == 13);
# else
    MISSING(AO_load);
# endif
# if defined(AO_HAVE_test_and_set_write)
    assert(AO_test_and_set_write(&z) == AO_TS_CLEAR);
    assert(AO_test_and_set_write(&z) == AO_TS_SET);
    assert(AO_test_and_set_write(&z) == AO_TS_SET);
    AO_CLEAR(&z);
# else
    MISSING(AO_test_and_set);
# endif
# if defined(AO_HAVE_fetch_and_add_write)
    TA_assert(AO_fetch_and_add_write(&x, 42) == 13);
    TA_assert(AO_fetch_and_add_write(&x, -42) == 55);
# else
    MISSING(AO_fetch_and_add);
# endif
# if defined(AO_HAVE_fetch_and_add1_write)
    TA_assert(AO_fetch_and_add1_write(&x) == 13);
# else
    MISSING(AO_fetch_and_add1);
    ++x;
# endif
# if defined(AO_HAVE_fetch_and_sub1_write)
    TA_assert(AO_fetch_and_sub1_write(&x) == 14);
# else
    MISSING(AO_fetch_and_sub1);
    --x;
# endif
# if defined(AO_HAVE_compare_and_swap_write)
    TA_assert(!AO_compare_and_swap_write(&x, 14, 42));
    TA_assert(x == 13);
    TA_assert(AO_compare_and_swap_write(&x, 13, 42));
    TA_assert(x == 42);
# else
    MISSING(AO_compare_and_swap);
# endif
# if defined(AO_HAVE_or_write)
    AO_or_write(&x, 66);
    TA_assert(x == 106);
# else
    MISSING(AO_or);
    x |= 34;
# endif
}


    
/*
 * Copyright (c) 2003 by Hewlett-Packard Company.  All rights reserved.
 *
 * This file is covered by the GNU general public license, version 2.
 * see doc/COPYING for details.
 */

/* Some basic sanity tests.  These do not test the barrier semantics. */

#undef TA_assert
#define TA_assert(e) \
  if (!(e)) { fprintf(stderr, "Assertion failed %s:%d (barrier: _full)\n", \
		    __FILE__, __LINE__), exit(1); }

#undef MISSING
#define MISSING(name) \
  fprintf(stderr, "Missing: %s\n", #name "_full")

void test_atomic_full(void)
{
  AO_T x;
# if defined(AO_HAVE_test_and_set_full)
    AO_TS_T z = AO_TS_INITIALIZER;
# endif

# if defined(AO_HAVE_nop_full)
    AO_nop_full();
# else
    MISSING(AO_nop);
# endif
# if defined(AO_HAVE_store_full)
    AO_store_full(&x, 13);
    TA_assert (x == 13);
# else
    MISSING(AO_store);
    x = 13;
# endif
# if defined(AO_HAVE_load_full)
    TA_assert(AO_load_full(&x) == 13);
# else
    MISSING(AO_load);
# endif
# if defined(AO_HAVE_test_and_set_full)
    assert(AO_test_and_set_full(&z) == AO_TS_CLEAR);
    assert(AO_test_and_set_full(&z) == AO_TS_SET);
    assert(AO_test_and_set_full(&z) == AO_TS_SET);
    AO_CLEAR(&z);
# else
    MISSING(AO_test_and_set);
# endif
# if defined(AO_HAVE_fetch_and_add_full)
    TA_assert(AO_fetch_and_add_full(&x, 42) == 13);
    TA_assert(AO_fetch_and_add_full(&x, -42) == 55);
# else
    MISSING(AO_fetch_and_add);
# endif
# if defined(AO_HAVE_fetch_and_add1_full)
    TA_assert(AO_fetch_and_add1_full(&x) == 13);
# else
    MISSING(AO_fetch_and_add1);
    ++x;
# endif
# if defined(AO_HAVE_fetch_and_sub1_full)
    TA_assert(AO_fetch_and_sub1_full(&x) == 14);
# else
    MISSING(AO_fetch_and_sub1);
    --x;
# endif
# if defined(AO_HAVE_compare_and_swap_full)
    TA_assert(!AO_compare_and_swap_full(&x, 14, 42));
    TA_assert(x == 13);
    TA_assert(AO_compare_and_swap_full(&x, 13, 42));
    TA_assert(x == 42);
# else
    MISSING(AO_compare_and_swap);
# endif
# if defined(AO_HAVE_or_full)
    AO_or_full(&x, 66);
    TA_assert(x == 106);
# else
    MISSING(AO_or);
    x |= 34;
# endif
}


    
/*
 * Copyright (c) 2003 by Hewlett-Packard Company.  All rights reserved.
 *
 * This file is covered by the GNU general public license, version 2.
 * see doc/COPYING for details.
 */

/* Some basic sanity tests.  These do not test the barrier semantics. */

#undef TA_assert
#define TA_assert(e) \
  if (!(e)) { fprintf(stderr, "Assertion failed %s:%d (barrier: _release_write)\n", \
		    __FILE__, __LINE__), exit(1); }

#undef MISSING
#define MISSING(name) \
  fprintf(stderr, "Missing: %s\n", #name "_release_write")

void test_atomic_release_write(void)
{
  AO_T x;
# if defined(AO_HAVE_test_and_set_release_write)
    AO_TS_T z = AO_TS_INITIALIZER;
# endif

# if defined(AO_HAVE_nop_release_write)
    AO_nop_release_write();
# else
    MISSING(AO_nop);
# endif
# if defined(AO_HAVE_store_release_write)
    AO_store_release_write(&x, 13);
    TA_assert (x == 13);
# else
    MISSING(AO_store);
    x = 13;
# endif
# if defined(AO_HAVE_load_release_write)
    TA_assert(AO_load_release_write(&x) == 13);
# else
    MISSING(AO_load);
# endif
# if defined(AO_HAVE_test_and_set_release_write)
    assert(AO_test_and_set_release_write(&z) == AO_TS_CLEAR);
    assert(AO_test_and_set_release_write(&z) == AO_TS_SET);
    assert(AO_test_and_set_release_write(&z) == AO_TS_SET);
    AO_CLEAR(&z);
# else
    MISSING(AO_test_and_set);
# endif
# if defined(AO_HAVE_fetch_and_add_release_write)
    TA_assert(AO_fetch_and_add_release_write(&x, 42) == 13);
    TA_assert(AO_fetch_and_add_release_write(&x, -42) == 55);
# else
    MISSING(AO_fetch_and_add);
# endif
# if defined(AO_HAVE_fetch_and_add1_release_write)
    TA_assert(AO_fetch_and_add1_release_write(&x) == 13);
# else
    MISSING(AO_fetch_and_add1);
    ++x;
# endif
# if defined(AO_HAVE_fetch_and_sub1_release_write)
    TA_assert(AO_fetch_and_sub1_release_write(&x) == 14);
# else
    MISSING(AO_fetch_and_sub1);
    --x;
# endif
# if defined(AO_HAVE_compare_and_swap_release_write)
    TA_assert(!AO_compare_and_swap_release_write(&x, 14, 42));
    TA_assert(x == 13);
    TA_assert(AO_compare_and_swap_release_write(&x, 13, 42));
    TA_assert(x == 42);
# else
    MISSING(AO_compare_and_swap);
# endif
# if defined(AO_HAVE_or_release_write)
    AO_or_release_write(&x, 66);
    TA_assert(x == 106);
# else
    MISSING(AO_or);
    x |= 34;
# endif
}


    
/*
 * Copyright (c) 2003 by Hewlett-Packard Company.  All rights reserved.
 *
 * This file is covered by the GNU general public license, version 2.
 * see doc/COPYING for details.
 */

/* Some basic sanity tests.  These do not test the barrier semantics. */

#undef TA_assert
#define TA_assert(e) \
  if (!(e)) { fprintf(stderr, "Assertion failed %s:%d (barrier: _acquire_read)\n", \
		    __FILE__, __LINE__), exit(1); }

#undef MISSING
#define MISSING(name) \
  fprintf(stderr, "Missing: %s\n", #name "_acquire_read")

void test_atomic_acquire_read(void)
{
  AO_T x;
# if defined(AO_HAVE_test_and_set_acquire_read)
    AO_TS_T z = AO_TS_INITIALIZER;
# endif

# if defined(AO_HAVE_nop_acquire_read)
    AO_nop_acquire_read();
# else
    MISSING(AO_nop);
# endif
# if defined(AO_HAVE_store_acquire_read)
    AO_store_acquire_read(&x, 13);
    TA_assert (x == 13);
# else
    MISSING(AO_store);
    x = 13;
# endif
# if defined(AO_HAVE_load_acquire_read)
    TA_assert(AO_load_acquire_read(&x) == 13);
# else
    MISSING(AO_load);
# endif
# if defined(AO_HAVE_test_and_set_acquire_read)
    assert(AO_test_and_set_acquire_read(&z) == AO_TS_CLEAR);
    assert(AO_test_and_set_acquire_read(&z) == AO_TS_SET);
    assert(AO_test_and_set_acquire_read(&z) == AO_TS_SET);
    AO_CLEAR(&z);
# else
    MISSING(AO_test_and_set);
# endif
# if defined(AO_HAVE_fetch_and_add_acquire_read)
    TA_assert(AO_fetch_and_add_acquire_read(&x, 42) == 13);
    TA_assert(AO_fetch_and_add_acquire_read(&x, -42) == 55);
# else
    MISSING(AO_fetch_and_add);
# endif
# if defined(AO_HAVE_fetch_and_add1_acquire_read)
    TA_assert(AO_fetch_and_add1_acquire_read(&x) == 13);
# else
    MISSING(AO_fetch_and_add1);
    ++x;
# endif
# if defined(AO_HAVE_fetch_and_sub1_acquire_read)
    TA_assert(AO_fetch_and_sub1_acquire_read(&x) == 14);
# else
    MISSING(AO_fetch_and_sub1);
    --x;
# endif
# if defined(AO_HAVE_compare_and_swap_acquire_read)
    TA_assert(!AO_compare_and_swap_acquire_read(&x, 14, 42));
    TA_assert(x == 13);
    TA_assert(AO_compare_and_swap_acquire_read(&x, 13, 42));
    TA_assert(x == 42);
# else
    MISSING(AO_compare_and_swap);
# endif
# if defined(AO_HAVE_or_acquire_read)
    AO_or_acquire_read(&x, 66);
    TA_assert(x == 106);
# else
    MISSING(AO_or);
    x |= 34;
# endif
}


    
