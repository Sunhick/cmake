# author: sunil
cmake_minimum_required(VERSION 2.8)

project(main)

add_subdirectory(graphics)
include_directories(graphics/)
add_executable(main main.cpp)
target_link_libraries(main graphics)

install(
  TARGETS main
  DESTINATION bin)
