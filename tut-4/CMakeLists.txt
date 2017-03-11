# author: sunil

cmake_minimum_required(VERSION 2.8)

project(calc_ut)

include_directories(include/)
link_directories(../lib/)

add_executable(calc_ut calc.cpp calc_unittest.cpp)
target_link_libraries(calc_ut libgtest.a libgtest_main.a)

install(
  TARGETS calc_ut
  DESTINATION bin)
