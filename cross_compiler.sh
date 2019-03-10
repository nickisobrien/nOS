#!/bin/bash

set -euo pipefail

source ./common.sh

function onexit {
	if [ $? -ne 0 ]; then
		echo "FAIL!"
	fi
}
trap onexit EXIT

# BINUTILS
git clone git://sourceware.org/git/binutils-gdb.git $BINUTILS_SRC
mkdir $BINUTILS_SRC/build && cd $BINUTILS_SRC/build
../configure --target="$TARGET" --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make
make install

# GCC
svn checkout svn://gcc.gnu.org/svn/gcc/trunk $GCC_SRC
mkdir $GCC_SRC/build && cd $GCC_SRC/build
../configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc
