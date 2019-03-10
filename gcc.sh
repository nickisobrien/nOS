#!/bin/bash

set -euo pipefail

source ./common.sh

# GCC
svn checkout svn://gcc.gnu.org/svn/gcc/trunk $GCC_SRC
mkdir $GCC_SRC/build && cd $GCC_SRC/build
../configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc
