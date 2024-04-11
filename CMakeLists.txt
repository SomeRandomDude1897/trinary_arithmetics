cmake_minimum_required(VERSION 3.5)
set( CMAKE_CXX_COMPILER "C:/msys64/ucrt64/bin/g++.exe" )

project(main LANGUAGES CXX)

set(CMAKE_VERBOSE_MAKEFILE ON)

file(GLOB SOURCES CONFIGURE_DEPENDS
./src/bebra.cpp
./src/bebra.h
./src/main.cpp
)

add_executable(main ${SOURCES})