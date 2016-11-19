CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(CALCULATOR)

SET(CMAKE_VERBOSE_MAKEFILE OFF)
SET(CMAKE_CXX_FLAGS "-g -std=c++11")

SET(test_matrix test_matrix.cpp)

INCLUDE_DIRECTORIES(
    "../include"
    "/usr/local/include"
)

LINK_DIRECTORIES(
    "/usr/local/lib"
)

ADD_EXECUTABLE(test_matrix ${test_matrix})

ADD_CUSTOM_COMMAND(
    TARGET test_matrix 
    POST_BUILD
    COMMAND echo ${CALCULATOR_SOURCE_DIR}
)

