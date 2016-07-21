CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(CODE_SNIPS)

SET(CMAKE_VERBOSE_MAKEFILE OFF)
SET(CMAKE_CXX_FLAGS "-g -std=c++11")

SET(
    SOURCES
    join_to_string.hpp
    blocking_queue.hpp
    blocking_unordered_map.hpp
    host_ip.hpp
    main.cpp
)

INCLUDE_DIRECTORIES(
    "."
    "/usr/local/include"
)

LINK_DIRECTORIES(
    "/usr/local/lib"
)

ADD_EXECUTABLE(code_snips ${SOURCES})

TARGET_LINK_LIBRARIES(code_snips boost_system boost_thread)

ADD_CUSTOM_COMMAND(
    TARGET code_snips
    POST_BUILD
    COMMAND echo ${CODE_SNIPS_SOURCE_DIR}
)
