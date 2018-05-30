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
    std::wstring text;
    unsigned int numOfPatterns;
    std::vector<std::wstring> patterns;
    std::vector<result> results;

    friend std::wostream& operator<<(std::wostream& os, const testState& obj) {
        os << L"[" << std::endl;
        os << L"Text: " << std::endl;
        os << L"\t" << obj.text << std::endl;
        os << L"numOfPatterns: " << std::endl;
        os << L"\t" << obj.numOfPatterns << std::endl;
        os << L"Patterns: " << std::endl;
        for (auto pattern : obj.patterns) {
            os << L"\t" << pattern << std::endl;
        }
        os << L"Results: " << std::endl;

        for (auto result : obj.results) {
            os << L"\t" << result.first << L" " << result.second << std::endl;
        }

        os << L"]" <<std::endl;

        return os;
    }
};

struct patternsSearchTest : TestAhoCorasick, testing::WithParamInterface<testState> {
    void SetUp() {
        std::wcout << GetParam();
    }
};

TEST_P(patternsSearchTest, searchPatternsInText) {
    auto state = GetParam();
    ahoCorAlgorithm->init(state.text, state.patterns, state.numOfPatterns);
    ASSERT_EQ(state.results, ahoCorAlgorithm->solve());
}


INSTANTIATE_TEST_CASE_P(Default, patternsSearchTest,
  testing::Values(
<<<<<<< HEAD
  testState{L"CCCA", 1, {L"CC"}, {{1, 1}, {2, 1}}},
  testState{L"CCCA", 1, {L"ACC"}, {}},
  testState{L"ACIRDJHRDLJSDNCJOPQLMZ", 5, {L"ACI", L"HRLD", L"L", L"OPQ", L"DN"}, {{1, 1}, {10, 3}, {13, 5}, {17, 4}, {20, 3}}},
  testState{L"LOLYPLOLYPOPLOL", 5, {L"LOL", L"LOLY", L"LOLYP", L"LOLYPOP", L"L"}, {{1, 1}, {1, 2}, {1, 3}, {1, 5}, {3, 5}, {6, 1}, {6, 2}, {6, 3}, {6, 4}, {6, 5}, {8, 5}, {13, 1}, {13, 5}, {15, 5}}},
  // Update: cyrillic symbols
  testState{L"CФCЙ", 1, {L"Й"}, {{4, 1}}}
=======
  testState{"CCCA", 1, {"CC"}, {{1, 1}, {2, 1}}},
  testState{"CCCA", 1, {"ACC"}, {}},
  testState{"ACIRDJHRDLJSDNCJOPQLMZ", 5, {"ACI", "HRLD", "L", "OPQ", "DN"}, {{1, 1}, {10, 3}, {13, 5}, {17, 4}, {20, 3}}},
  testState{"LOLYPLOLYPOPLOL", 5, {"LOL", "LOLY", "LOLYP", "LOLYPOP", "L"}, {{1, 1}, {1, 2}, {1, 3}, {1, 5}, {3, 5}, {6, 1}, {6, 2}, {6, 3}, {6, 4}, {6, 5}, {8, 5}, {13, 1}, {13, 5}, {15, 5}}}
>>>>>>> 3c164f495dc5b48a221e3a6da5a0505f5e037ee8
  ));

int main(int argc, char* argv[]) {
  std::locale::global(std::locale("ru_RU.UTF8"));
  std::wcin.imbue(std::locale("ru_RU.UTF8"));
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
