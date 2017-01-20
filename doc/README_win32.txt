Most of the atomic_ops functionality is available under Win32 with
the Microsoft tools, but the build process currently is considerably more
primitive than on Linux/Unix platforms.

To build:

1) Go to the src directory in the distribution.
2) Make sure the Microsoft command-line tools (e.g. nmake) are available.
3) Run "nmake -f Makefile.msft".  This should run some tests, which
may print warnings about the types of the "Interlocked" functions.
I haven't been able to make all versions of VC++ happy.  If you know
how to, please send a patch.
4) To compile applications, you will need to retain or copy the following
pieces from the resulting src directory contents:
        "atomic_ops.h" - Header file defining low-level primitives.  This
                         includes files from:
        "atomic_ops"- Subdirectory containing implementation header files.
        "atomic_ops_stack.h" - Header file describing almost lock-free stack.
        "atomic_ops_malloc.h" - Header file describing almost lock-free malloc.
        "libatomic_ops_gpl.lib" - Library containing implementation of the
                        above two (plus AO_pause() defined in atomic_ops.c).
                        The atomic_ops.h implementation is entirely in the
                        header files in Win32.

If the client defines AO_ASSUME_VISTA (before include atomic_ops.h), it should
make double_compare_and_swap_full available.
Please note that MS compiler for x86 does not align AO_double_t on an 8-byte
boundary, thus to avoid an undefined behavior, an AO_double_t (volatile)
variable should be declared with AO_DOUBLE_ALIGN attribute if the variable
reference is passed to an AO primitive (the attribute is not applicable to
arguments and pointers).

Note that the library is covered by the GNU General Public License, while
the top 2 of these pieces allow use in proprietary code.
