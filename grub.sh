#!/bin/bash

set -euo pipefail

source ./common.sh
source ./logging.sh

wget ftp://ftp.gnu.org/gnu/grub/grub-2.02.tar.gz
zcat grub-2.02.tar.gz | tar xvf -
rm grub-2.02.tar.gz
mv grub-2.02 $GRUB_SRC
mkdir $GRUB_SRC/build && cd $GRUB_SRC/build
../configure --target="$TARGET" --prefix="$PREFIX" --disable-werror > ${log_dir}/grub-config.log 2>&1
make > ${log_dir}/grub-build.log 2>&1
make install > ${log_dir}/grub-install.log 2>&1
