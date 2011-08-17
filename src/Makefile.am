AM_CFLAGS=@PICFLAG@
AM_CPPFLAGS = -I$(top_builddir)/src -I$(top_srcdir)/src

include_HEADERS=atomic_ops.h atomic_ops_stack.h atomic_ops_malloc.h
lib_LTLIBRARIES = libatomic_ops.la libatomic_ops_gpl.la
if NEED_ASM
libatomic_ops_la_SOURCES = atomic_ops.c atomic_ops_sysdeps.S
else
libatomic_ops_la_SOURCES = atomic_ops.c
endif
libatomic_ops_la_LDFLAGS = -version-info 1:3:0 -no-undefined

libatomic_ops_gpl_la_SOURCES = atomic_ops_stack.c atomic_ops_malloc.c
libatomic_ops_gpl_la_LDFLAGS = -version-info 1:3:0 -no-undefined

EXTRA_DIST=Makefile.msft atomic_ops/sysdeps/README \
        atomic_ops/generalize-small.template atomic_ops/sysdeps/sunc/sparc.S

#Private Headers
privatedir=${includedir}/
nobase_private_HEADERS=atomic_ops/generalize.h atomic_ops/generalize-small.h \
        \
          atomic_ops/sysdeps/acquire_release_volatile.h \
          atomic_ops/sysdeps/aligned_atomic_load_store.h \
          atomic_ops/sysdeps/all_acquire_release_volatile.h \
          atomic_ops/sysdeps/all_aligned_atomic_load_store.h \
          atomic_ops/sysdeps/all_atomic_load_store.h \
          atomic_ops/sysdeps/ao_t_is_int.h \
          atomic_ops/sysdeps/atomic_load_store.h \
          atomic_ops/sysdeps/char_acquire_release_volatile.h \
          atomic_ops/sysdeps/char_atomic_load_store.h \
          atomic_ops/sysdeps/emul_cas.h \
          atomic_ops/sysdeps/generic_pthread.h \
          atomic_ops/sysdeps/int_acquire_release_volatile.h \
          atomic_ops/sysdeps/int_aligned_atomic_load_store.h \
          atomic_ops/sysdeps/int_atomic_load_store.h \
          atomic_ops/sysdeps/ordered.h \
          atomic_ops/sysdeps/ordered_except_wr.h \
          atomic_ops/sysdeps/read_ordered.h \
          atomic_ops/sysdeps/short_acquire_release_volatile.h \
          atomic_ops/sysdeps/short_aligned_atomic_load_store.h \
          atomic_ops/sysdeps/short_atomic_load_store.h \
          atomic_ops/sysdeps/standard_ao_double_t.h \
          atomic_ops/sysdeps/test_and_set_t_is_ao_t.h \
          atomic_ops/sysdeps/test_and_set_t_is_char.h \
        \
          atomic_ops/sysdeps/armcc/arm_v6.h \
        \
          atomic_ops/sysdeps/gcc/alpha.h \
          atomic_ops/sysdeps/gcc/arm.h \
          atomic_ops/sysdeps/gcc/avr32.h \
          atomic_ops/sysdeps/gcc/cris.h \
          atomic_ops/sysdeps/gcc/hppa.h \
          atomic_ops/sysdeps/gcc/ia64.h \
          atomic_ops/sysdeps/gcc/m68k.h \
          atomic_ops/sysdeps/gcc/mips.h \
          atomic_ops/sysdeps/gcc/powerpc.h \
          atomic_ops/sysdeps/gcc/s390.h \
          atomic_ops/sysdeps/gcc/sh.h \
          atomic_ops/sysdeps/gcc/sparc.h \
          atomic_ops/sysdeps/gcc/x86.h \
          atomic_ops/sysdeps/gcc/x86_64.h \
        \
          atomic_ops/sysdeps/hpc/hppa.h \
          atomic_ops/sysdeps/hpc/ia64.h \
        \
          atomic_ops/sysdeps/ibmc/powerpc.h \
        \
          atomic_ops/sysdeps/icc/ia64.h \
        \
          atomic_ops/sysdeps/msftc/arm.h \
          atomic_ops/sysdeps/msftc/common32_defs.h \
          atomic_ops/sysdeps/msftc/x86.h \
          atomic_ops/sysdeps/msftc/x86_64.h \
        \
          atomic_ops/sysdeps/sunc/sparc.h \
          atomic_ops/sysdeps/sunc/x86.h \
          atomic_ops/sysdeps/sunc/x86_64.h

atomic_ops/generalize-small.h: atomic_ops/generalize-small.template
	sed -e s:XSIZE:char:g -e s:XCTYPE:char:g $? > $@
	sed -e s:XSIZE:short:g -e s:XCTYPE:short:g $? >> $@
	sed -e s:XSIZE:int:g -e s:XCTYPE:int:g $? >> $@
