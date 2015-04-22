cmake_minimum_required(VERSION 3.1)
project(binary_translation)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(binary_translation ${SOURCE_FILES} errors.h errors.cpp binary_file.h binary_file.cpp map.h map.cpp assembler.h assembler.cpp source_file.h source_file.cpp translator.cpp)