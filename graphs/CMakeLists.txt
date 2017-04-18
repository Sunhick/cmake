# Author: Sunil
cmake_minimum_required(VERSION 2.8)

# activae c++11 features
SET(CMAKE_CXX_FLAGS "-std=c++11")
SET(CMAKE_EXE_LINKER_FLAGS)
SET(TARGET Assignment12)

# catch all warnings, no optimization and generate debug symbols
add_definitions("-Wall" "-O0 -g")

project(${TARGET})

add_executable(${TARGET} main.cpp)

# install executable
install(
  TARGETS ${TARGET}
  DESTINATION bin)
