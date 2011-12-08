# Process this file with autoconf to produce a configure script.
AC_INIT([libatomic_ops],[7.3alpha1])

AC_PREREQ(2.64)
AC_CANONICAL_TARGET([])
AC_CONFIG_SRCDIR(src/atomic_ops.c)
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([foreign dist-bzip2 nostdinc])
AM_MAINTAINER_MODE

AM_CONFIG_HEADER(src/config.h)

# Checks for programs.
AM_PROG_CC_C_O
AM_PROG_AS
LT_INIT([disable-shared])

# Checks for functions.
AC_FUNC_MMAP

# Determine PIC flag, adjust default CFLAGS
need_asm=false
PICFLAG=
AC_MSG_CHECKING(Determining PIC compiler flag)
if test "$GCC" = yes; then
  case "$host" in
    *-*-solaris*)
      AC_MSG_RESULT(-fPIC)
      PICFLAG=-fPIC
      # Workaround: at least GCC 3.4.6 does not define this macro.
      CFLAGS="-D__PIC__=1 $CFLAGS"
      ;;
    *-*-cygwin* | *-*-mingw*)
      # Cygwin and Mingw[-w32/64] do not need -fPIC.
      ;;
    *)
      AC_MSG_RESULT(-fPIC)
      PICFLAG=-fPIC
      ;;
  esac
  # Output all warnings.
  CFLAGS="-Wall -Wextra $CFLAGS"
else
  case "$host" in
    *-*-hpux*)
      AC_MSG_RESULT("+Z")
      PICFLAG="+Z"
      CFLAGS="+O2 -mt $CFLAGS"
      ;;
    *-*-solaris*)
      AC_MSG_RESULT(-Kpic)
      PICFLAG=-Kpic
      CFLAGS="-O $CFLAGS"
      need_asm=true
      ;;
    *-*-linux*)
      AC_MSG_RESULT(-fPIC)
      PICFLAG=-fPIC
      # Any Linux compiler had better be gcc compatible.
      ;;
    *)
      AC_MSG_RESULT("<none>")
      ;;
  esac
fi
CFLAGS="-DNDEBUG $CFLAGS"
AC_SUBST(PICFLAG)
AC_SUBST(DEFS)

AH_TEMPLATE([_PTHREADS], [Indicates the use of pthreads (NetBSD).])

AH_TEMPLATE([AO_USE_NANOSLEEP],
        [Use nanosleep() instead of select() (only if atomic operations \
         are emulated)])
AH_TEMPLATE([AO_USE_NO_SIGNALS],
        [Do not block signals in compare_and_swap (only if atomic operations \
         are emulated)])
AH_TEMPLATE([AO_USE_WIN32_PTHREADS],
        [Use Win32 Sleep() instead of select() (only if atomic operations \
         are emulated)])
AH_TEMPLATE([AO_TRACE_MALLOC], [Trace AO_malloc/free calls (for debug only)])

# These macros are tested in public headers
AH_TEMPLATE([AO_GENERALIZE_ASM_BOOL_CAS],
        [Force compare_and_swap definition via fetch_compare_and_swap])
AH_TEMPLATE([AO_PREFER_GENERALIZED],
        [Prefer generalized definitions to direct assembly-based ones])
AH_TEMPLATE([AO_USE_PTHREAD_DEFS],
        [Emulate atomic operations via slow and async-signal-unsafe \
         pthread locking])
AH_TEMPLATE([AO_ASM_X64_AVAILABLE],
        [Inline assembly avalable (only VC/x86_64)])
AH_TEMPLATE([AO_ASSUME_VISTA],
        [Assume Windows Server 2003, Vista or later target (only VC/x86)])
AH_TEMPLATE([AO_ASSUME_WINDOWS98],
        [Assume hardware compare-and-swap functionality available \
         on target (only VC/x86)])
AH_TEMPLATE([AO_CMPXCHG16B_AVAILABLE],
        [Assume target is not old AMD Opteron chip (only x86_64)])
AH_TEMPLATE([AO_FORCE_USE_SWP],
        [Force test_and_set to use SWP instruction instead of LDREX/STREX \
         (only arm v6+)])
AH_TEMPLATE([AO_NO_SPARC_V9], [Assume target is not sparc v9+ (only sparc)])
AH_TEMPLATE([AO_OLD_STYLE_INTERLOCKED_COMPARE_EXCHANGE],
        [Assume ancient MS VS Win32 headers (only VC/arm v6+, VC/x86)])
AH_TEMPLATE([AO_UNIPROCESSOR], [Assume single-core target (only arm v6+)])
AH_TEMPLATE([AO_USE_INTERLOCKED_INTRINSICS],
        [Assume Win32 _Interlocked primitives available as intrinsics \
         (only VC/arm)])
AH_TEMPLATE([AO_USE_PENTIUM4_INSTRS],
        [Use Pentium 4 'mfence' instruction (only x86)])
AH_TEMPLATE([AO_USE_SYNC_CAS_BUILTIN],
        [Prefer GCC built-in CAS intrinsics in favor of inline assembly \
         (only gcc/x86, gcc/x86_64)])
AH_TEMPLATE([AO_WEAK_DOUBLE_CAS_EMULATION],
        [Emulate double-width CAS via pthread locking in case of no hardware \
         support (only gcc/x86_64, sunc/x86_64)])

THREADDLLIBS=
have_pthreads=true
## Libraries needed to support threads.
AC_CHECK_LIB(pthread, pthread_self, THREADDLLIBS="-lpthread",,)
AC_DEFINE(_REENTRANT, 1, [Required define if using POSIX threads.])
case "$host" in
    *-*-netbsd*)
      AC_DEFINE(_PTHREADS)
      ;;
    *-*-openbsd* | *-*-kfreebsd*-gnu | *-*-dgux*)
      THREADDLLIBS=-pthread
      ;;
    *-*-cygwin* | *-*-darwin*)
      THREADDLLIBS=
      ;;
    *-*-mingw*)
      THREADDLLIBS=
      have_pthreads=false
      ;;
esac
AC_SUBST(THREADDLLIBS)

AM_CONDITIONAL(HAVE_PTHREAD_H, test x$have_pthreads = xtrue)
AM_CONDITIONAL(NEED_ASM, test x$need_asm = xtrue)

AC_CONFIG_FILES([
        Makefile
        doc/Makefile
        src/Makefile
        tests/Makefile
        pkgconfig/atomic_ops.pc
        pkgconfig/atomic_ops-uninstalled.pc ])

AC_CONFIG_COMMANDS([default],[[]],[[
PICFLAG="${PICFLAG}"
CC="${CC}"
DEFS="${DEFS}"
]])
AC_OUTPUT
