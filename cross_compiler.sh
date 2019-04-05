#!/bin/bash

set -euo pipefail

source ./common.sh
source ./logging.sh

# BINUTILS
echo "Binutils!"
git clone git://sourceware.org/git/binutils-gdb.git $BINUTILS_SRC
mkdir $BINUTILS_SRC/build && cd $BINUTILS_SRC/build
../configure \
	--target="$TARGET" \
	--prefix="$PREFIX" \
	--with-sysroot \
	--disable-nls \
	--disable-werror \
	> ${log_dir}/binutils-configure.log 2>&1
make > ${log_dir}/binutils-build.log 2>&1
make install > ${log_dir}/binutils-install.log 2>&1

# GCC
echo "GCC!"
svn checkout svn://gcc.gnu.org/svn/gcc/trunk $GCC_SRC \
	> ${log_dir}/gcc-checkout.log 2>&1
mkdir $GCC_SRC/build && cd $GCC_SRC/build
../configure \
	--target="$TARGET" \
	--prefix="$PREFIX" \
	--disable-nls \
	--enable-languages=c,c++ \
	--without-headers \
	> ${log_dir}/gcc-configure.log 2>&1
make all-gcc > ${log_dir}/gcc-build.log 2>&1
make all-target-libgcc >> ${log_dir}/gcc-build.log 2>&1
make install-gcc >> ${log_dir}/gcc-build.log 2>&1
make install-target-libgcc >> ${log_dir}/gcc-build.log 2>&1
