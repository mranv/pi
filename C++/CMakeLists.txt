INCLUDE (CheckIncludeFiles)

cmake_minimum_required(VERSION 3.10)

# set the project name
project(Pi VERSION 1.1)

set(CMAKE_CXX_STANDARD 14)
find_library(MPFR_LIB libmpfr.so REQUIRED)

file(GLOB SOURCES "src/*.cpp")
include_directories(include)

# add the executable
add_executable(pi ${SOURCES})

target_link_libraries(pi -lmpfr)
