#!/bin/bash
find -iname 'main' -exec rm -rf {} \;
find -iname '*cmake*' -not -name "CMakeLi*.txt" -exec rm -rf {} \+
find -iname 'Makefile' -exec rm -rf {} \+
rm -fR build
