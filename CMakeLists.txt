cmake_minimum_required(VERSION 3.5)

project(AhoCorasick)

set(CMAKE_CXX_STANDARD 11)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(PatternsSearch PatternsSearch/src/findPatterns.cpp PatternsSearch/src/AhoCorasick.cpp PatternsSearch/headers/AhoCorasick.h PatternsSearch/src/BohrTree.cpp PatternsSearch/headers/BohrTree.h PatternsSearch/src/BohrVertex.cpp PatternsSearch/headers/BohrVertex.h)
add_executable(JokerSearch SearchWithJoker/src/searchWithJoker.cpp SearchWithJoker/src/AhoCorasick.cpp SearchWithJoker/headers/AhoCorasick.h SearchWithJoker/src/BohrTree.cpp SearchWithJoker/headers/BohrTree.h SearchWithJoker/src/BohrVertex.cpp SearchWithJoker/headers/BohrVertex.h)

add_executable(testPatternsSearch test/testPatternsSearch.cpp PatternsSearch/src/AhoCorasick.cpp PatternsSearch/headers/AhoCorasick.h PatternsSearch/src/BohrTree.cpp PatternsSearch/headers/BohrTree.h PatternsSearch/src/BohrVertex.cpp PatternsSearch/headers/BohrVertex.h)

target_link_libraries(testPatternsSearch ${GTEST_LIBRARIES} pthread)
add_test(TestPatternSearch "./testPatternsSearch")
