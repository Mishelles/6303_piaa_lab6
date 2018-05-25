cmake_minimum_required(VERSION 3.5)

project(PatternsSearch)

set(CMAKE_CXX_STANDARD 11)

#enable_testing()
#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})

add_executable(PatternsSearch PatternsSearch/src/findPatterns.cpp PatternsSearch/src/AhoCorasick.cpp PatternsSearch/headers/AhoCorasick.h PatternsSearch/src/BohrTree.cpp PatternsSearch/headers/BohrTree.h PatternsSearch/src/BohrVertex.cpp PatternsSearch/headers/BohrVertex.h)
