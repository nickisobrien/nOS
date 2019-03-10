#!/bin/bash

PREFIX="$HOME/opt/cross"
TARGET=i686-elf
PATH="$PREFIX/bin:$PATH"

BINUTILS_SRC="$PREFIX/nOS-binutils-gdb"
GCC_SRC="$PREFIX/nOS-gcc"

function onexit {
    if [ $? -ne 0 ]; then
        echo "FAIL!"
    fi
}
trap onexit EXIT

