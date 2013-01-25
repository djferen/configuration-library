cmake_minimum_required (VERSION 2.8)

configure_file(main.cnf .)

include_directories(../include/Configuration)
add_executable(main main.cpp)
target_link_libraries(main qpidclient json_linux-gcc-4.4.6_libmt configuration-library)

