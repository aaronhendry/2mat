cmake_minimum_required(VERSION 3.19)
project(2mat)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
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

set(HEADERS
        inc/2mat.hpp
        inc/container.hpp
        inc/date/leap.hpp
        inc/datenum.hpp
        inc/element.hpp
        inc/file.hpp
        inc/io/fwriter.hpp
        inc/matrix.hpp
        inc/mstruct.hpp
        inc/types.hpp
        inc/util.hpp)

add_library(2mat ${SOURCES} ${HEADERS})
target_include_directories(2mat PUBLIC ${CMAKE_SOURCE_DIR}/inc)