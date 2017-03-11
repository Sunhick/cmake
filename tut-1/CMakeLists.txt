# author: sunil
cmake_minimum_required(VERSION 2.8)

project(helloWorld)
add_executable(hello hello.cpp)
install(TARGETS hello DESTINATION bin)
