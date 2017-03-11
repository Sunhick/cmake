# author : Sunil
cmake_minimum_required(VERSION 2.8)

project(graphics)

add_library(graphics STATIC Pencil.cpp)

set(INCLUDE_DIR, include/)
# include_directories(include/)

install(
  TARGETS graphics
  DESTINATION lib)

install(
  FILES include/Pencil.h
  DESTINATION inc)
