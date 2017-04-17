# Author: Sunil
cmake_minimum_required(VERSION 2.8)

# activae c++11 features
SET(CMAKE_CXX_FLAGS "-std=c++11")
SET(CMAKE_EXE_LINKER_FLAGS)
SET(TARGET assignment8)

# catch all warnings, no optimization and generate debug symbols
add_definitions("-Wall" "-O0 -g")

# file(GLOB TARGET_SRC ${CMAKE_SOURCE_DIR}/*.cpp)

project(${TARGET})

# add_executable(${TARGET} ${TARGET_SRC})
add_executable(${TARGET} MovieTree.cpp MovieTree.hpp main.cpp)
# target_link_libraries(${TARGET} gcov)

include_directories(lib/include/)

find_library(
  GTEST googletest
  NAMES gtest
  PATHS ${CMAKE_CURRENT_SOURCE_DIR}/lib/
  NO_DEFAULT_PATH)

find_library(
  GTESTMAIN googletest
  NAMES gtest_main
  PATHS ${CMAKE_CURRENT_SOURCE_DIR}/lib/
  NO_DEFAULT_PATH)

message(STATUS "GTEST LIBS = " ${GTEST})
message(STATUS "GTEST MAIN LIBS = " ${GTESTMAIN})

add_executable(assignment8tests MovieTreeTests.cpp MovieTree.cpp MovieTree.hpp)
target_link_libraries(
  assignment8tests
  PUBLIC ${GTEST} ${GTESTMAIN} pthread)

# install executable
install(
  TARGETS ${TARGET}
  DESTINATION bin)

# install test
install(
  TARGETS assignment8tests
  DESTINATION bin)

# install supported files
install(
  FILES Assignment8Movies.txt
  DESTINATION bin)
