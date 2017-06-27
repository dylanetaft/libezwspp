cmake_minimum_required (VERSION 3.2)
project (libezwspp)
set(CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(PkgConfig REQUIRED)
add_executable(myprog test.cpp)

pkg_search_module(LIBUV REQUIRED libuv)
include_directories(${LIBUV_INCLUDE_DIRS})

target_link_libraries(myprog ${LIBUV_LIBRARIES})

