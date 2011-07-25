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
CC= cc
#Add -DHW_EVENT_SUPPORT if you have Itanium perfmon installed
CFLAGS= -g -O2
RANLIB=ranlib

VERSION=0.5
DOCDIR=$(PREFIX)/doc/atomic_ops-$(VERSION)
INCDIR=$(PREFIX)/include/atomic_ops-$(VERSION)

C_SOURCES= test_atomic.c atomic_ops.c
TOP_LEVEL_HEADERS= atomic_ops.h
DERIVED_HEADERS= test_atomic_include.h
AO_SD_DIR=atomic_ops/sysdeps
DOC= doc/COPYING doc/LICENSING.txt doc/README_atomic_ops.txt $(AO_SD_DIR)/README
SYSDEP_GCC_HEADERS= $(AO_SD_DIR)/gcc/x86.h $(AO_SD_DIR)/gcc/ia64.h \
	$(AO_SD_DIR)/gcc/alpha.h $(AO_SD_DIR)/gcc/arm.h \
	$(AO_SD_DIR)/gcc/powerpc.h $(AO_SD_DIR)/gcc/sparc.h \
	$(AO_SD_DIR)/gcc/hppa.h $(AO_SD_DIR)/gcc/m68k.h $(AO_SD_DIR)/gcc/s390.h
SYSDEP_ECC_HEADERS= $(AO_SD_DIR)/ecc/ia64.h
SYSDEP_MSFTC_HEADERS= $(AO_SD_DIR)/msftc/x86.h
SYSDEP_HPC_HEADERS= $(AO_SD_DIR)/hpc/ia64.h $(AO_SD_DIR)/hpc/hppa.h
SYSDEP_HEADERS= $(AO_SD_DIR)/generic_pthread.h \
		$(AO_SD_DIR)/atomic_load_store.h \
		$(AO_SD_DIR)/aligned_atomic_load_store.h \
		$(AO_SD_DIR)/ordered_except_wr.h \
		$(AO_SD_DIR)/acquire_release_volatile.h \
		$(AO_SD_DIR)/ordered.h \
		$(AO_SD_DIR)/emul_cas.h
ALL_SYSDEP_HEADERS= $(SYSDEP_GCC_HEADERS) $(SYSDEP_ECC_HEADERS) \
$(SYSDEP_MSFTC_HEADERS) $(SYSDEP_HEADERS)
ATOMIC_OPS_PRIV_HEADERS=atomic_ops/generalize.h
ATOMIC_OPS_HEADERS= atomic_ops.h $(ATOMIC_OPS_PRIV_HEADERS) \
		    $(ALL_SYSDEP_HEADERS)
HEADERS= $(TOP_LEVEL_HEADERS) $(SYSDEP_GCC_HEADERS) $(SYSDEP_HEADERS) \
	 $(ATOMIC_OPS_PRIV_HEADERS) $(SYSDEP_ECC_HEADERS)
OTHER_FILES=Makefile README test_atomic.template list_atomic.template \
	    Makefile.msft
ALL_DIST_FILES= $(DOC) $(C_SOURCES) $(HEADERS) $(OTHER_FILES) 

all: libatomic_ops.a Makefile.expanded

Makefile.expanded: Makefile
	sed -e s:XXPWDXX:`pwd`: Makefile > Makefile.expanded

atomic_ops.o: atomic_ops.c $(ATOMIC_OPS_HEADERS)
	$(CC) $(CFLAGS) -c -fPIC atomic_ops.c

libatomic_ops.a: atomic_ops.o
	$(AR) ruc libatomic_ops.a atomic_ops.o
	$(RANLIB) libatomic_ops.a

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

list_atomic.i: list_atomic.c atomic_ops.h $(ATOMIC_OPS_PRIV_HEADERS) \
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
	# The same thing again for the atomic_ops distribution.
	mkdir atomic_ops-$(VERSION)
	ln Makefile atomic_ops.h $(ATOMIC_OPS_PRIV_HEADERS) atomic_ops.c \
	   Makefile.msft test_atomic_include.h atomic_ops-$(VERSION)
	ln test_atomic.c test_atomic.template list_atomic.template \
	   atomic_ops-$(VERSION)
	mkdir atomic_ops-$(VERSION)/atomic_ops
	ln $(ATOMIC_OPS_PRIV_HEADERS) atomic_ops-$(VERSION)/atomic_ops
	mkdir atomic_ops-$(VERSION)/$(AO_SD_DIR)
	ln $(SYSDEP_HEADERS) README atomic_ops-$(VERSION)/$(AO_SD_DIR)
	mkdir atomic_ops-$(VERSION)/$(AO_SD_DIR)/gcc
	ln $(SYSDEP_GCC_HEADERS)  atomic_ops-$(VERSION)/$(AO_SD_DIR)/gcc
	mkdir atomic_ops-$(VERSION)/$(AO_SD_DIR)/ecc
	ln $(SYSDEP_ECC_HEADERS)  atomic_ops-$(VERSION)/$(AO_SD_DIR)/ecc
	mkdir atomic_ops-$(VERSION)/$(AO_SD_DIR)/msftc
	ln $(SYSDEP_MSFTC_HEADERS)  atomic_ops-$(VERSION)/$(AO_SD_DIR)/msftc
	mkdir atomic_ops-$(VERSION)/$(AO_SD_DIR)/hpc
	ln $(SYSDEP_HPC_HEADERS)  atomic_ops-$(VERSION)/$(AO_SD_DIR)/hpc
	mkdir atomic_ops-$(VERSION)/doc
	ln doc/COPYING doc/README_atomic_ops.txt doc/LICENSING.txt atomic_ops-$(VERSION)/doc
	tar cvfzh atomic_ops-$(VERSION).tar.gz atomic_ops-$(VERSION)
	rm -rf atomic_ops-$(VERSION)

install: all
	make -f Makefile.expanded real_install

# The following target should only be used in the derived
# Makefile.expanded, since they must see the correct default value
# of PREFIX.

real_install:
	install -d $(INCDIR)
	install -d $(DOCDIR)
	install -d $(PREFIX)/include
	install -d $(PREFIX)/lib
	/usr/bin/install -m 644 $(DOC) $(DOCDIR)
	/usr/bin/install -m 644 libatomic_ops.a $(PREFIX)/lib/libatomic_ops-$(VERSION).a
	/usr/bin/install -m 644 $(TOP_LEVEL_HEADERS) $(PREFIX)/include
	cp -r atomic_ops atomic_ops.h $(INCDIR)
	ln -s -f $(PREFIX)/lib/libatomic_ops-$(VERSION).a $(PREFIX)/lib/libatomic_ops.a
	ln -s -f $(INCDIR)/atomic_ops $(PREFIX)/include/atomic_ops
	ln -s -f $(INCDIR)/atomic_ops.h $(PREFIX)/include/atomic_ops.h

