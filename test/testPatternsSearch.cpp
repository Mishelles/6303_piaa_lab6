#include <gtest/gtest.h>
#include "../PatternsSearch/headers/AhoCorasick.h"
#include <iostream>

struct TestAhoCorasick : testing::Test {
    AhoCorasick* ahoCorAlgorithm;
    TestAhoCorasick();
    ~TestAhoCorasick();
};

TestAhoCorasick::TestAhoCorasick() {
    ahoCorAlgorithm = new AhoCorasick;
}

TestAhoCorasick::~TestAhoCorasick() {
    delete ahoCorAlgorithm;
}

struct testState {
    std::string text;
    unsigned int numOfPatterns;
    std::vector<std::string> patterns;
    std::vector<result> results;

    friend std::ostream& operator<<(std::ostream& os, const testState& obj) {

        os << "[" << std::endl;
        os << "Text: " << std::endl;
        os << "\t" << obj.text << std::endl;
        os << "numOfPatterns: " << std::endl;
        os << "\t" << obj.numOfPatterns << std::endl;
        os << "Patterns: " << std::endl;
        for (auto pattern : obj.patterns) {
            os << "\t" << pattern << std::endl;
        }
        os << "Results: " << std::endl;

        for (auto result : obj.results) {
            os << "\t" << result.first << " " << result.second << std::endl;
        }

        os << "]" <<std::endl;

        return os;
    }
};

struct patternsSearchTest : TestAhoCorasick, testing::WithParamInterface<testState> {
    void SetUp() {
        std::cout << GetParam();
    }
};

TEST_P(patternsSearchTest, searchPatternsInText) {
    auto state = GetParam();
    ahoCorAlgorithm->init(state.text, state.patterns, state.numOfPatterns);
    ASSERT_EQ(state.results, ahoCorAlgorithm->solve());
}


INSTANTIATE_TEST_CASE_P(Default, patternsSearchTest,
  testing::Values(
  testState{"CCCA", 1, {"CC"}, {{1, 1}, {2, 1}}},
  testState{"CCCA", 1, {"ACC"}, {}},
  testState{"ACIRDJHRDLJSDNCJOPQLMZ", 5, {"ACI", "HRLD", "L", "OPQ", "DN"}, {{1, 1}, {10, 3}, {13, 5}, {17, 4}, {20, 3}}},
  testState{"LOLYPLOLYPOPLOL", 5, {"LOL", "LOLY", "LOLYP", "LOLYPOP", "L"}, {{1, 1}, {1, 2}, {1, 3}, {1, 5}, {3, 5}, {6, 1}, {6, 2}, {6, 3}, {6, 4}, {6, 5}, {8, 5}, {13, 1}, {13, 5}, {15, 5}}}
  // testState{"АФАФ", 1, {"АФ"}, {{1, 1}, {3, 1}}}
  ));

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
