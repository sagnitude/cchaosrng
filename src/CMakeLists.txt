cmake_minimum_required(VERSION 2.8)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -O2")
SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -g -ggdb -pg")
SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} -s -DNDEBUG")
SET(SRC_LIST main.c cp.c cm.c scheduler.c utils.c)
MESSAGE(STATUS "This is BINARY DIR " ${cchaosrng_BINARY_DIR})
include_directories(
../include
)
ADD_EXECUTABLE(x  ${SRC_LIST})
TARGET_LINK_LIBRARIES(x m)
