#
# Copyright (c) 2003 Hewlett-Packard Developlment Company, L.P.
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE. 
#  

# PREFIX should usually be set to the intended install directory, e.g. /usr/local
# It defaults to the installed subdirectory of the build directory.  This allows
# (somewhat inconvenient) use of the profiler without setting up or accessing
# a separate installation directory.
PREFIX=XXPWDXX/installed
CC= gcc
#Add -DHW_EVENT_SUPPORT if you have Itanium perfmon installed
CFLAGS= -g -O2
RANLIB=ranlib

VERSION=0.3
LIBDIR=$(PREFIX)/lib/ao-$(VERSION)
DOCDIR=$(PREFIX)/doc/ao-$(VERSION)
INCDIR=$(PREFIX)/include/ao-$(VERSION)

C_SOURCES= test_atomic.c atomic_ops.c
TOP_LEVEL_HEADERS= atomic_ops.h atomic_ops_generalize.h
DERIVED_HEADERS= test_atomic_include.h
DOC= doc/COPYING doc/LICENSING.txt doc/README_atomic_ops.txt
SYSDEP_GCC_HEADERS= ao_sysdeps/gcc/x86.h ao_sysdeps/gcc/ia64.h \
	ao_sysdeps/gcc/alpha.h ao_sysdeps/gcc/arm.h \
	ao_sysdeps/gcc/powerpc.h ao_sysdeps/gcc/sparc.h \
	ao_sysdeps/gcc/hppa.h ao_sysdeps/gcc/m68k.h ao_sysdeps/gcc/s390.h
SYSDEP_ECC_HEADERS= ao_sysdeps/ecc/ia64.h
SYSDEP_VENDORC_HEADERS= ao_sysdeps/vendorc/none_yet
SYSDEP_HEADERS= ao_sysdeps/generic_pthread.h ao_sysdeps/atomic_load_store.h \
	ao_sysdeps/aligned_atomic_load_store.h ao_sysdeps/ordered_except_wr.h \
	ao_sysdeps/acquire_release_volatile.h ao_sysdeps/ordered.h \
	ao_sysdeps/emul_cas.h
ALL_SYSDEP_HEADERS= $(SYSDEP_GCC_HEADERS) $(SYSDEP_ECC_HEADERS) \
$(SYSDEP_VENDORC_HEADERS) $(SYSDEP_HEADERS)
ATOMIC_OPS_HEADERS= atomic_ops.h atomic_ops_generalize.h $(ALL_SYSDEP_HEADERS)
HEADERS= $(TOP_LEVEL_HEADERS) $(SYSDEP_GCC_HEADERS) $(SYSDEP_HEADERS)
OTHER_FILES=Makefile README test_atomic.template list_atomic.template
ALL_DIST_FILES= $(DOC) $(C_SOURCES) $(HEADERS) $(OTHER_FILES) 

all: atomic_ops.a Makefile.expanded

Makefile.expanded: Makefile
	sed -e s:XXPWDXX:`pwd`: Makefile > Makefile.expanded

atomic_ops.o: atomic_ops.c $(ATOMIC_OPS_HEADERS)
	$(CC) $(CFLAGS) -c -fPIC atomic_ops.c

atomic_ops.a: atomic_ops.o
	$(AR) ruc atomic_ops.a atomic_ops.o
	$(RANLIB) atomic_ops.a

test_atomic: test_atomic.c atomic_ops.c test_atomic_include.h $(ATOMIC_OPS_HEADERS)
	$(CC) $(CFLAGS) test_atomic.c atomic_ops.c -o test_atomic -lpthread

test_atomic_pthreads: test_atomic.c atomic_ops.c test_atomic_include.h $(ATOMIC_OPS_HEADERS)
	$(CC) $(CFLAGS) -DAO_USE_PTHREAD_DEFS test_atomic.c atomic_ops.c -o test_atomic_pthreads -lpthread

test_atomic_include.h: test_atomic.template
	sed -e s/XX// test_atomic.template > test_atomic_include.h
	sed -e s/XX/_release/ test_atomic.template >> test_atomic_include.h
	sed -e s/XX/_acquire/ test_atomic.template >> test_atomic_include.h
	sed -e s/XX/_read/ test_atomic.template >> test_atomic_include.h
	sed -e s/XX/_write/ test_atomic.template >> test_atomic_include.h
	sed -e s/XX/_full/ test_atomic.template >> test_atomic_include.h
	sed -e s/XX/_release_write/ test_atomic.template \
					>> test_atomic_include.h
	sed -e s/XX/_acquire_read/ test_atomic.template \
					>> test_atomic_include.h

list_atomic.c: list_atomic.template
	echo "#include \"atomic_ops.h\" " > list_atomic.c
	sed -e s/XX// list_atomic.template >> list_atomic.c
	sed -e s/XX/_release/ list_atomic.template >> list_atomic.c
	sed -e s/XX/_acquire/ list_atomic.template >> list_atomic.c
	sed -e s/XX/_read/ list_atomic.template >> list_atomic.c
	sed -e s/XX/_write/ list_atomic.template >> list_atomic.c
	sed -e s/XX/_full/ list_atomic.template >> list_atomic.c
	sed -e s/XX/_release_write/ list_atomic.template \
					>> list_atomic.c
	sed -e s/XX/_acquire_read/ list_atomic.template \
					>> list_atomic.c

list_atomic.i: list_atomic.c atomic_ops.h atomic_ops_generalize.h \
	       $(SYSDEP_HEADERS) $(SYSDEP_GCC_HEADERS)
	cc -E list_atomic.c > list_atomic.i

check:  test_atomic_pthreads test_atomic
	echo The following will usually print some \"Missing ...\" messages.
	./test_atomic_pthreads
	./test_atomic

clean:
	rm -f *.so *.o *.a core test_atomic test_atomic_pthreads \
	list_atomic.c list_atomic.i \
	test_atomic_include.h Makefile.expanded
	rm -rf installed
	

dist:	$(ALL_DIST_FILES)
	# The same thing again for the ao distribution.
	mkdir ao-$(VERSION)
	ln atomic_ops.h atomic_ops_generalize.h atomic_ops.c ao-$(VERSION)
	mkdir ao-$(VERSION)/ao_sysdeps
	ln $(SYSDEP_HEADERS)  ao-$(VERSION)/ao_sysdeps
	mkdir ao-$(VERSION)/ao_sysdeps/gcc
	ln $(SYSDEP_GCC_HEADERS)  ao-$(VERSION)/ao_sysdeps/gcc
	mkdir ao-$(VERSION)/ao_sysdeps/ecc
	ln $(SYSDEP_ECC_HEADERS)  ao-$(VERSION)/ao_sysdeps/ecc
	mkdir ao-$(VERSION)/ao_sysdeps/vendorc
	ln $(SYSDEP_VENDORC_HEADERS)  ao-$(VERSION)/ao_sysdeps/vendorc
	mkdir ao-$(VERSION)/doc
	ln doc/README_atomic_ops.txt doc/LICENSING.txt ao-$(VERSION)/doc
	tar cvfzh ao-$(VERSION).tar.gz ao-$(VERSION)
	rm -rf ao-$(VERSION)

install: all
	make -f Makefile.expanded real_install

# The following target should only be used in the derived
# Makefile.expanded, since they must see the correct default value
# of PREFIX.

real_install:
	install -d $(LIBDIR)
	install -d $(INCDIR)
	install -d $(DOCDIR)
	ln -s -f $(LIBDIR) $(PREFIX)/lib/ao
	ln -s -f $(DOCDIR) $(PREFIX)/doc/ao
	ln -s -f $(INCDIR) $(PREFIX)/include/ao
	/usr/bin/install -c -m 644 $(DOC) $(DOCDIR)
	/usr/bin/install -c -m 644 atomic_ops.a $(LIBDIR)
	/usr/bin/install -c -m 644 $(TOP_LEVEL_HEADERS) $(INCDIR)
	cp -r ao_sysdeps $(INCDIR)

