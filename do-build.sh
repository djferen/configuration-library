#!/bin/bash
mkdir -p build
cd build && cmake ..
make all

VERSION=0.1.0
NAME=configuration-library
SPEC=$NAME.spec
SRC=$NAME-$VERSION.tar.gz

#pushd ..
#tar -czf $SRC $NAME/include/*.h $NAME/src/*.cpp $NAME/test/* $NAME/CMakeLists.txt
#cp $SRC ~/rpmbuild/SOURCES
#popd

#rpmbuild -bp $SPEC


# find -iname '*cmake*' -not -name CMakeLists.txt -exec rm -rf {} \+
