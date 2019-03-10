#!/bin/bash

set -euo pipefail

source ./common.sh

git clone git://sourceware.org/git/binutils-gdb.git $BINUTILS_SRC
mkdir $BINUTILS_SRC/build
cd $BINUTILS_SRC/build
../configure --target="$TARGET" --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make
make install
