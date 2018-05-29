cmake_minimum_required(VERSION 3.5)

project(AhoCorasick)

set(CMAKE_CXX_STANDARD 11)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(PatternsSearch PatternsSearch/src/findPatterns.cpp PatternsSearch/src/AhoCorasick.cpp PatternsSearch/headers/AhoCorasick.h PatternsSearch/src/Bohr.cpp PatternsSearch/headers/Bohr.h PatternsSearch/src/Node.cpp PatternsSearch/headers/Node.h)
add_executable(WildCardSearch WildCardSearch/src/wildCardSearch.cpp WildCardSearch/src/AhoCorasick.cpp WildCardSearch/headers/AhoCorasick.h WildCardSearch/src/Bohr.cpp WildCardSearch/headers/Bohr.h WildCardSearch/src/Node.cpp WildCardSearch/headers/Node.h)

add_executable(testPatternsSearch test/testPatternsSearch.cpp PatternsSearch/src/AhoCorasick.cpp PatternsSearch/headers/AhoCorasick.h PatternsSearch/src/Bohr.cpp PatternsSearch/headers/Bohr.h PatternsSearch/src/Node.cpp PatternsSearch/headers/Node.h)
add_executable(testWildCardSearch test/testWildCardSearch.cpp WildCardSearch/src/AhoCorasick.cpp WildCardSearch/headers/AhoCorasick.h WildCardSearch/src/Bohr.cpp WildCardSearch/headers/Bohr.h WildCardSearch/src/Node.cpp WildCardSearch/headers/Node.h)

target_link_libraries(testPatternsSearch ${GTEST_LIBRARIES} pthread)
target_link_libraries(testWildCardSearch ${GTEST_LIBRARIES} pthread)

add_test(TestPatternSearch "./testPatternsSearch")
add_test(TestWildCardSearch "./testWildCardSearch")
