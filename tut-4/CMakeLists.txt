# author: sunil

cmake_minimum_required(VERSION 2.8)

project(calc_ut)

include_directories(include/)

# link_directories not be used per man page of cmake.
# This will get us into a trouble and should be avoided.
# link_directories(../lib/)

# message("CMAKE_OSX_SYSROOT = ")
# message(STATUS " "  ${CMAKE_OSX_SYSROOT})
# message(STATUS " "  ${CMAKE_CURRENT_SOURCE_DIR})

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

add_executable(calc_ut calc.cpp calc_unittest.cpp)
# target_link_libraries(calc_ut libgtest.a libgtest_main.a)
target_link_libraries(
  calc_ut
  PUBLIC ${GTEST} ${GTESTMAIN})

install(
  TARGETS calc_ut
  DESTINATION bin)
