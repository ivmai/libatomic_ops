Usage:
1) type make check; make install in the directory containing unpacked
source.  The install directory defaults to the "installed" subdirectory
of the build directory.  The can be adjusted with the definition of PREFIX
in Makefile.

2) Applications should include atomic_ops.h.  Nearly all operations
are implemented by header files included from it.  It is sometimes
necessary, and always recommended to also link against atomic_ops.a.

Description:
Atomic_ops.h defines a large collection of operations, each one of which is a
combination of an (optional) atomic memory operation, and a memory barrier.
Also defines associated feature-test macros to determine whether a particular
operation is available on the current target hardware (either directly or
by synthesis).  This is an attempt to replace various existing files with
similar goals, since they usually do not handle differences in memory
barrier styles with sufficient generality.

If this is included after defining AO_REQUIRE_CAS, then the package
will make an attempt to emulate compare-and-swap in a way that (at least
on Linux) should still be async-signal-safe.  As a result, most other
atomic operations will then be defined using the compare-and-swap
emulation.  This emulation is slow, since it needs to disable signals.
And it needs to block in case of contention.  If you care about performance on
a platform that can't directly provide compare-and-swap, there are
probably better alternatives.  But this allows easy ports to some such
platforms (e.g. PA_RISC).  The option is ignored if compare-and-swap
can be implemented directly.

If atomic_ops.h is included after defining AO_USE_PTHREAD_DEFS, then all
atomic operations will be emulated with pthread locking.  This is NOT
async-signal-safe.  And it is slow.  It is intended primarily for debugging
of the atomic_ops package itself.

Note that the implementation reflects our understanding of real processor
behavior.  This occasionally diverges from the documented behavior.  (E.g.
the documented X86 behavior seems to be weak enough that it is impractical
to use.  Current real implementations appear to be much better behaved.)
We of course are in no position to guarantee that future processors
(even HPs) will continue to behave this way, though we hope they will.

This is a work in progress.  Corrections/additions for other platforms are
greatly appreciated.  It passes rudimentary tests on X86, Itanium, and
Alpha.

The defined operations are all of the form AO_<op><barrier>(<args>).
Most operations operate on values of type AO_t, which are unsigned integers
whose size matches that of pointers on the given architecture.  We may
provide more flexibility in operand types in the future, but this seems
to cover 90+% of common usage.

The <op> component specifies an atomic memory operation.  It may be
one of the following, where the corresponding argument and result types
are also specified:

void nop()
	No atomic operation.  The barrier may still be useful.
AO_t load(volatile AO_t * addr)
	Atomic load of *addr.
void store(volatile AO_t * addr, AO_t new_val)
	Atomically store new_val to *addr.
AO_t fetch_and_add(volatile AO_t *addr, AO_t incr)
	Atomically add incr to *addr, and return the original value of *addr.
AO_t fetch_and_add1(volatile AO_t *addr)
	Equivalent to AO_fetch_and_add(addr, 1).
AO_t fetch_and_sub1(volatile AO_t *addr)
	Equivalent to AO_fetch_and_add(addr, (AO_t)(-1)).
void or(volatile AO_t *addr, AO_t incr)
	Atomically or incr into *addr.
int compare_and_swap(volatile AO_t * addr, AO_t old_val, AO_t new_val)
	Atomically compare *addr to old_val, and replace *addr by new_val
	if the first comparison succeeds.  Returns nonzero if the comparison
	succeeded and *addr was updated.
AO_TS_VAL_t test_and_set(volatile AO_TS_T * addr)
	Atomically read the binary value at *addr, and set it.  AO_TS_VAL_t
	is an enumeration type which includes the two values AO_TS_SET and
	and AO_TS_CLEAR.  An AO_TS_T location is capable of holding an
	AO_TS_VAL_t, but may be much larger, as dictated by hardware
	constraints.  Test_and_set logically sets the value to AO_TS_SET.
	It may be reset to AO_TS_CLEAR with the AO_CLEAR(AO_TS_T *) macro.
	AO_TS_T locations should be initialized to AO_TS_INITIALIZER.
	The values of AO_TS_SET and AO_TS_CLEAR are hardware dependent.
	(On PA-RISC, AO_TS_SET is zero!)

Test_and_set is a more limited version of compare_and_swap.  Its only
advantage is that it is more easily implementable on some hardware.  It
should thus be used if only binary test-and-set functionality is needed.

Each operation name also includes a suffix that specifies the associated
memory barrier.  It is one of the following:

<none>: No memory barrier.  A plain AO_nop() really does nothing.
_release: Earlier operations must become visible to other threads
	  before the atomic operation.
_acquire: Later operations must become visible after this operation.
_read: Subsequent reads must become visible after reads included in
       the atomic operation or preceding it.
_write: Earlier writes become visible before writes during or after
        the atomic operation.
_full: Ordered with respect to both earlier and later memops.
_release_write: Ordered with respect to earlier writes.  This is
	        normally implemented as either a _write or _release
		barrier.
_acquire_read: Ordered with respect to later reads.  Usually implemented
	       as either a _read or _acquire barrier.

It is possible to test whether AO_<op><barrier> is available on the
current platform by checking whether AO_HAVE_<op>_<barrier> is defined
as a macro.

Note that we generally don't implement operations that are either
meaningless (e.g. AO_nop_acquire, AO_nop_release) or which appear to
have no clear use (e.g. AO_load_release, AO_store_acquire, AO_load_write,
AO_store_read).  On some platforms (e.g. PA-RISC) many operations
will remain undefined unless AO_REQUIRE_CAS is defined before including
the package.

When typed in the package build directory, the following command
will print operations that are unimplemented on the platform:

make test_atomic; ./test_atomic

The following command generates a file "list_atomic.i" containing the
macro expansions of all implemented operations on the platform:

make list_atomic.i

Future directions:

We expect the list of memory barrier types to remain more or less fixed.
However, it is likely that the list of underlying atomic operations will
grow.  It would also be useful to support double-wide and narrower operations
when available.

Example:

If you want to initialize an object, and then "publish" a pointer to it
in a global location p, such that other threads reading the new value of
p are guaranteed to see an initialized object, it suffices to use
AO_release_write(p, ...) to write the pointer to the object, and to
retrieve it in other threads with AO_acquire_read(p).

Platform notes:

All X86: We quietly assume 486 or better.

Windows:
Currently AO_REQUIRE_CAS is not supported.

Microsoft compilers:
Define AO_ASSUME_WINDOWS98 to get access to hardware compare-and-swap
functionality.  This relies on the InterlockedCompareExchange() function
which was apparently not supported in Windows95.  (There may be a better
way to get access to this.)  Currently only X86(32 bit) is supported for
Windows.

Gcc on x86:
Define AO_USE_PNETIUM4_INSTRS to use the Pentium 4 mfence instruction.
Currently this is appears to be of marginal benefit.
