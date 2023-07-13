# Minimum version of cmake needed to run following commands
cmake_minimum_required(VERSION 3.20.0)


# Generate the compile commands in JSON format to help clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# Compiler variable (locally defined)
# set(CLANG_LINKER_FLAGS "-Llibglfw.3.3.dylib")
set(CLANG_COMPILE_FLAGS "-Wno-deprecated -Wall")


set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CLANG_COMPILE_FLAGS}")


# Name of the project 
project(lox VERSION 1.0.0)


# Generate the application executable
add_executable( lox 
src/main.cpp
src/lox.cpp
src/token.cpp
src/scanner.cpp )
