cmake_minimum_required(VERSION 3.10)
project(foxc C)

set(CMAKE_CXX_STANDARD 99)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find LLVM package
find_package(LLVM REQUIRED CONFIG)

# Print LLVM version and configuration path for debugging
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# Set LLVM include directories
include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_executable(foxc 
    src/main.c 
    src/lexer.c 
    src/compiler.c 
    src/parser.c 
    src/lib/vector.c 
    src/lib/hex.c
)

target_link_libraries(foxc PRIVATE LLVM)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_link_libraries(foxc PRIVATE stdc++)
endif()

target_include_directories(foxc PRIVATE include)
