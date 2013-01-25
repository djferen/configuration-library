#!/bin/bash
VERSION=`cat version`

mkdir -p ~/rpmbuild/SOURCES
mkdir -p ~/rpmbuild/SRPMS
mkdir -p ~/rpmbuild/RPMS
mkdir -p ~/rpmbuild/SPECS
mkdir -p ~/rpmbuild/BUILDROOT
mkdir -p ~/rpmbuild/BUILD

pushd ..
cp -r configuration-library configuration-library-$VERSION
tar -czf configuration-library-$VERSION.tar.gz configuration-library-$VERSION
rm -fR configuration-library-$VERSION
mv configuration-library-$VERSION.tar.gz ~/rpmbuild/SOURCES
popd

rpmbuild -bb configuration-library.spec

