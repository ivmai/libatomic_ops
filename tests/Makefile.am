EXTRA_DIST=test_atomic_include.template list_atomic.template run_parallel.h \
	   test_atomic_include.h list_atomic.c
# We distribute test_atomic_include.h and list_atomic.c, since it is hard
# to regenerate them on Windows without sed.

BUILT_SOURCES = test_atomic_include.h list_atomic.i
CLEANFILES = list_atomic.i

AM_CPPFLAGS = \
	-I$(top_builddir)/src -I$(top_srcdir)/src \
	-I$(top_builddir)/tests -I$(top_srcdir)/tests

TESTS=test_atomic test_atomic_pthreads test_stack test_malloc

#create the test_atomic test program
check_PROGRAMS=test_atomic test_atomic_pthreads test_stack test_malloc

test_atomic_SOURCES=test_atomic.c
test_atomic_LDADD = $(THREADDLLIBS) $(top_builddir)/src/libatomic_ops.la

test_atomic_pthreads_SOURCES=test_atomic.c
test_atomic_pthreads_CPPFLAGS=-DAO_USE_PTHREAD_DEFS $(AM_CPPFLAGS)
test_atomic_pthreads_LDADD = $(THREADDLLIBS) $(top_builddir)/src/libatomic_ops.la

test_stack_SOURCES=test_stack.c
test_stack_LDADD = $(THREADDLLIBS) \
	$(top_builddir)/src/libatomic_ops_gpl.la \
	$(top_builddir)/src/libatomic_ops.la

test_malloc_SOURCES=test_malloc.c
test_malloc_LDADD = $(THREADDLLIBS) \
	$(top_builddir)/src/libatomic_ops_gpl.la \
	$(top_builddir)/src/libatomic_ops.la

test_atomic_include.h: test_atomic_include.template
	sed -e s/XX// $? > $@
	sed -e s/XX/_release/ $? >> $@
	sed -e s/XX/_acquire/ $? >> $@
	sed -e s/XX/_read/ $? >> $@
	sed -e s/XX/_write/ $? >> $@
	sed -e s/XX/_full/ $? >> $@
	sed -e s/XX/_release_write/ $? >> $@
	sed -e s/XX/_acquire_read/ $? >> $@

list_atomic.c: list_atomic.template
	echo "#include \"atomic_ops.h\" " > $@
	sed -e s/XX// $? >> $@
	sed -e s/XX/_release/ $? >> $@
	sed -e s/XX/_acquire/ $? >> $@
	sed -e s/XX/_read/ $? >> $@
	sed -e s/XX/_write/ $? >> $@
	sed -e s/XX/_full/ $? >> $@
	sed -e s/XX/_release_write/ $? >> $@
	sed -e s/XX/_acquire_read/ $? >> $@

list_atomic.i: list_atomic.c
	$(COMPILE) $? -E > list_atomic.i
