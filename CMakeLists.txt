cmake_minimum_required(VERSION 3.5)

project(KMP)

set(CMAKE_CXX_STANDARD 11)

#enable_testing()
#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})

add_executable(findPatterns src/findPatterns.cpp src/AhoCorasick.cpp src/AhoCorasick.h src/BohrTree.cpp src/BohrTree.h src/BohrVertex.cpp src/BohrVertex.h)
