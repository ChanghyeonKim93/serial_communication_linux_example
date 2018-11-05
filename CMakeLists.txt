cmake_minimum_required(VERSION 2.8.3)
project(serial_test)
find_package(cmake_modules)

set(includeDirs ${includeDirs} ${CMAKE_CURRENT_BINARY_DIR})
set(includeDirs ${includeDirs} include)

set(SRC ${SRC} src/main.cpp)

include_directories( ${includeDirs} )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(DCMAKE_build_type debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg -g3 -O2 -m64 -Ofast -flto -msse2 -msse3 -march=native  -mfpmath=sse")

add_executable (serial_test_rx src/main_rx.cpp )
add_executable (serial_test_tx src/main_tx.cpp )
