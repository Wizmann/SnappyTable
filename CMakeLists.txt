cmake_minimum_required(VERSION 3.2)
project(SnappyTable)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(include)
include_directories(third-src)

aux_source_directory(src SRC_LIST)
aux_source_directory(ut  UT_LIST)


set(SOURCE_FILES src/main.cpp)
add_executable(SnappyTable ${SOURCE_FILES} src/SnappyTable.cpp include/SnappyTable.h include/logging.h src/logging.cpp)

target_link_libraries(SnappyTable pthread)
target_link_libraries(SnappyTable expat)
target_link_libraries(SnappyTable ${CMAKE_SOURCE_DIR}/lib/liblog4c.a)
target_link_libraries(SnappyTable ${CMAKE_SOURCE_DIR}/lib/libsnappy.a)