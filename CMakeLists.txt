cmake_minimum_required(VERSION 3.5)

project(BytePair LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    bytepair.cpp
    main.cpp
)

set(HEADERS
    bytepair.h
)

add_executable(BytePair ${SOURCES} ${HEADERS})

install(TARGETS BytePair
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
