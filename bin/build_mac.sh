#!/bin/sh

cd ../bin
rm -rf CMakeCache.txt
rm -rf CMakeFiles
rm cmake_install.cmake
rm Makefile
rm x
rm ../src/x
cmake ../src -G "Unix Makefiles"
make
ln -s ../bin/x ../src/x
