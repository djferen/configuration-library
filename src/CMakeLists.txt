cmake_minimum_required (VERSION 2.8)

project (configuration-library)
include_directories(../include/Configuration)
file(GLOB_RECURSE SRC *.cpp)
add_library(configuration-library SHARED ${SRC})

