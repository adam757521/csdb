cmake_minimum_required(VERSION 3.16)
project(csdb VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include external/asio/asio/include)
file(GLOB_RECURSE SOURCES "src/*.cpp" "include/*.h")

add_library(asio INTERFACE)
target_compile_options(asio INTERFACE ASIO_STANDALONE)
target_include_directories(asio INTERFACE asio/asio/include)
# Using ASIO requires you link your final executable/library with your system's threading library (e.g. pthread on linux)
target_link_libraries(asio
INTERFACE pthread
)

add_executable(csdb ${SOURCES})
