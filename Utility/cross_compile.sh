#!/bin/bash

# Ask for the sudo password at the beginning so that you can go drinking coffee
sudo echo "This script needs to be run as root."

### BINUTILS

wget http://ftp.gnu.org/gnu/binutils/binutils-2.20.1.tar.bz2
tar xvf binutils-2.20.1.tar.bz2
cd binutils-2.20.1

./configure --target=arm-linux
make all
sudo make install

cd ..

### MPFR
wget http://ftp.gnu.org/gnu/mpfr/mpfr-2.4.2.tar.bz2
tar xvf mpfr-2.4.2.tar.bz2
cd mpfr-2.4.2

./configure --target=arm-linux
make all
sudo make install

cd ..

### GCC 4.4
wget http://ftp.gnu.org/gnu/gcc/gcc-4.4.3/gcc-4.4.3.tar.bz2
tar xvf gcc-4.4.3.tar.bz2 
cd gcc-4.4.3

./configure --enable-languages=c,c++ --disable-threads --disable-shared --disable-checking --prefix=/usr --mandir=/usr/share/man --infodir=/usr/share/info --target=arm-linux

make all-gcc
sudo make install-gcc

cd ..

### Clean

rm -rf binutils-2.20
rm -rf gcc-4.4.3
rm -rf mpfr-2.4.2
rm -f binutils-2.20.tar.bz2
rm -f gcc-4.4.3.tar.bz2
rm -f mpfr-2.4.2.tar.bz2
