# Author: Sunil
cmake_minimum_required(VERSION 2.8)

# mac os needs c++11 and linux needs gnu++11
# if (APPLE OR WIN32)
#   # activae c++11 features
#   SET(CMAKE_CXX_FLAGS "-std=c++11")
# elseif (UNIX)
#   SET(CMAKE_CXX_FLAGS "-std=gnu++11")
# endif()

# SET(CMAKE_EXE_LINKER_FLAGS)
SET(CMAKE_CXX_STANDARD 11) # C++11...
SET(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
# list(APPEND CMAKE_CXX_FLAGS "-std=c++11" ${CMAKE_CXX_FLAGS})

SET(TARGET rbtree_main)
SET(TEST_TARGET rbtree_tests)
SET(RBTREE_LIB rbtree)

# catch all warnings, no optimization and generate debug symbols
add_definitions("-Wall" "-O0 -g")

project(${TARGET})

add_library(${RBTREE_LIB} STATIC rbtree.cpp rbtree.hpp rbnode.cpp rbnode.hpp)

include_directories(./)
# add_executable(${TARGET} ${TARGET_SRC})
add_executable(${TARGET} main.cpp)
target_link_libraries(${TARGET} ${RBTREE_LIB})

include_directories(utest/libs/include/)

if (APPLE)
  SET(OS_TYPE macos)
elseif (UNIX) 
  SET(OS_TYPE linux)
else ()
  SET(OS_TYPE win)
endif ()

message(STATUS "using lib path:" ${CMAKE_CURRENT_SOURCE_DIR}/utest/libs/${OS_TYPE}/)

find_library(
  GTEST googletest
  NAMES gtest
  PATHS ${CMAKE_CURRENT_SOURCE_DIR}/utest/libs/${OS_TYPE}/
  NO_DEFAULT_PATH)

find_library(
  GTESTMAIN googletest
  NAMES gtest_main
  PATHS ${CMAKE_CURRENT_SOURCE_DIR}/utest/libs/${OS_TYPE}/
  NO_DEFAULT_PATH)

include_directories(../)
add_executable(${TEST_TARGET} ../utest/rbtree_tests.cpp)
target_link_libraries(
  ${TEST_TARGET}
  PUBLIC ${GTEST} ${GTESTMAIN} ${RBTREE_LIB} pthread)

# install executable
install(
  TARGETS ${TARGET}
  DESTINATION bin)

# install test
install(
  TARGETS ${TEST_TARGET}
  DESTINATION bin)