#!/bin/sh
set -e

# This script creates (or regenerates) configure (as well as aclocal.m4,
# config.h.in, Makefile.in, etc.) missing in the source repository.

# Install libtool.m4 and ltmain.sh in the build tree.  This command is needed
# if autoreconf and libtoolize are available from the different directories.
# Note: libtoolize might be missing on some platforms.
if which libtoolize > /dev/null 2>&1; then
  libtoolize -i -c
else
  echo "libtoolize is not found, ignoring!"
fi

autoreconf -i

echo
echo "Ready to run './configure'."
