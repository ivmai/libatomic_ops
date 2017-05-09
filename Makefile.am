SUBDIRS = src doc tests

ACLOCAL_AMFLAGS = -I m4

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = pkgconfig/atomic_ops.pc
noinst_DATA = pkgconfig/atomic_ops-uninstalled.pc

dist_doc_DATA = COPYING README.md

EXTRA_DIST = autogen.sh

#distclean-local:
