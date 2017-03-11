# author: sunil
# set(CMAKE_VERBOSE_MAKEFILE ON)
cmake_minimum_required(VERSION 2.8)

project(tut-2)

set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_MACOSX_RPATH 1)

add_library(math SHARED math.cpp)

# To create dynamic library
# add_library(math SHARED math.cpp)

install(
  TARGETS math
  RUNTIME DESTINATION lib
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib)

include_directories(install/lib/)
add_executable(main main.cpp)

target_link_libraries(main math)

install(
  TARGETS main
  DESTINATION bin)
  
