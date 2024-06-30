cmake_minimum_required(VERSION 3.16)
project(csdb VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)
file(GLOB_RECURSE SOURCES "src/*.cpp" "include/*.h")

add_executable(csdb ${SOURCES})