cmake_minimum_required(VERSION 3.5)
project(Delmesh VERSION 0.1)


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SOURCES src/*.cpp)



add_executable(Delmesh ${SOURCES})


