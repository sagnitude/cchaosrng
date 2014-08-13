#!/bin/sh

cd ../bin
cmake ../src -G "Unix Makefiles"
make
ln -s ../bin/x ../src/x
