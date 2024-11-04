cmake_minimum_required(VERSION 3.28)
project(projectlize)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(projectlize
        globals.cpp
        globals.h
        lalr.cpp
        lalr.h
        main.cpp
        myalgor.cpp
        myalgor.h
        production.cpp
        production.h
        analyseRecord.cpp
        analyseRecord.h
        util.cpp
        util.h)
