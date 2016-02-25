CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(UNIQUEID)

SET(CMAKE_VERBOSE_MAKEFILE OFF)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(CMAKE_CXX_FLAGS "-std=c++11 -Wno-macro-redefined")

SET(THRIFT_SOURCE gen-cpp/Uniqueid.cpp gen-cpp/uniqueid_constants.cpp gen-cpp/uniqueid_types.cpp)
SET(UNIQUEID_SERVER ${THRIFT_SOURCE} source/common.cpp source/context.cpp
    source/uniqueid_worker.cpp source/uniqueid_server.cpp)
SET(UNIQUEID_CLIENT ${THRIFT_SOURCE} source/common.cpp source/context.cpp source/uniqueid_client.cpp)

INCLUDE_DIRECTORIES(
    "."
    "./include"
    "./gen-cpp"
    "/usr/local/include"
)

LINK_DIRECTORIES(
    "/usr/local/lib"
)

ADD_DEFINITIONS(
)

ADD_EXECUTABLE(uniqueid_server ${UNIQUEID_SERVER})
ADD_EXECUTABLE(uniqueid_client ${UNIQUEID_CLIENT})

TARGET_LINK_LIBRARIES(uniqueid_server thrift boost_filesystem boost_system glog)
TARGET_LINK_LIBRARIES(uniqueid_client thrift boost_filesystem boost_system glog)

ADD_CUSTOM_COMMAND(
    TARGET uniqueid_server
    POST_BUILD
    COMMAND cp -r ${UNIQUEID_SOURCE_DIR}/config ${UNIQUEID_BINARY_DIR}
    COMMAND mkdir -p ${UNIQUEID_BINARY_DIR}/log
)
