cmake_minimum_required(VERSION 3.14)
project(lab05)

SET (CMAKE_C_COMPILER_WORKS 1)
SET (CMAKE_CXX_COMPILER_WORKS 1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lab05
#        baselexer.cpp
#        baselexer.h
#        fsm.h
#        lexer.h
        testlex.cpp)
