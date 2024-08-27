cmake_minimum_required(VERSION 3.10)

project(foxc C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

add_executable(foxc src/main.c src/lexer.c src/compiler.c src/parser.c src/lib/vector.c src/lib/hex.c)

target_include_directories(foxc PRIVATE include)
add_compile_options(-g)
