cmake_minimum_required(VERSION 3.19)
project(2mat)

set(CMAKE_CXX_STANDARD 17)

add_library(2mat
        src/container.cpp
        src/date/leap.cpp
        src/datenum.cpp
        src/element.cpp
        src/io/fwriter.cpp
        src/matrix.cpp
        src/mstruct.cpp
        src/util.cpp
        src/v6/write.cpp
        src/v7/write.cpp
        src/v7_3/write.cpp)

target_include_directories(2mat PUBLIC inc/)