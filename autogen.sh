#!/bin/sh
set -e

# This script creates (or regenerates) configure (as well as aclocal.m4,
# config.h.in, Makefile.in, etc.) missing in the source repository.

# Install libtool.m4 and ltmain.sh in the build tree.  This command is needed
# if autoreconf and libtoolize are available from the different directories.
libtoolize -i -c

autoreconf -i

echo
echo "Ready to run './configure'."
