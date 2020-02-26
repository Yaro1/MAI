cmake_minimum_required(VERSION 3.14)
project(lab08)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lab08
        #[[base-compiler.cpp
        base-compiler.h
        basegramma.cpp
        basegramma.h
        baselexer.cpp
        baselexer.h
        code-gen.cpp
        code-gen.h
        fsm.h
        kngramma.cpp
        kngramma.h
        lexer.h
        ]]
        mlispgen.cpp
        #[[pred.cpp
        slr.cpp
        slr.h]])
