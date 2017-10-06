cmake_minimum_required(VERSION 2.8.9)
project(chimp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
set(CMAKE_C_FLAGS_DEBUG "-O0")
set(CMAKE_BUILD_TYPE Debug)

include_directories(include)

file(GLOB SOURCES "*.cpp" "lib/Basic/*.cpp" "lib/ADT/*.cpp" "lib/Parse/*.cpp"
    "lib/Support/*.cpp")

add_executable(metal ${SOURCES})
