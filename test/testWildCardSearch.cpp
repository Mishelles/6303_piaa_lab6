#include <gtest/gtest.h>
#include "../WildCardSearch/headers/AhoCorasick.h"
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
    std::wstring joker;
    wchar_t jokerSym;
    std::vector<int> results;

    friend std::wostream& operator<<(std::wostream& os, const testState& obj) {

        os << L"[" << std::endl;
        os << L"Text: " << std::endl;
        os << L"\t" << obj.text << std::endl;
        os << L"Joker: " << std::endl;
        os << L"\t" << obj.joker << std::endl;
        os << L"JokerSym: " << std::endl;
        os << L"\t" << obj.jokerSym << std::endl;

        os << L"Results: " << std::endl;

        for (auto result : obj.results) {
            os << L"\t" << result << std::endl;
        }

        os << L"]" <<std::endl;

        return os;
    }
};

struct jokerSearchTest : TestAhoCorasick, testing::WithParamInterface<testState> {
    void SetUp() {
        std::wcout << GetParam();
    }
};

TEST_P(jokerSearchTest, searchWithWildcard) {
    auto state = GetParam();
    ahoCorAlgorithm->init(state.text, state.joker, state.jokerSym);
    ASSERT_EQ(state.results, ahoCorAlgorithm->solve());
}


INSTANTIATE_TEST_CASE_P(Default, jokerSearchTest,
  testing::Values(
  testState{L"AACT", L"A$", L'$', {1, 2}},
  testState{L"AACT", L"T$", L'$', {}},
  testState{L"LOLYPOP", L"L$L$P$P", L'$', {1}},
  testState{L"MAMTREW", L"A$$", L'$', {2}},
  testState{L"AACT", L"A$$", L'$', {1, 2}},
  testState{L"KJLOHFAK", L"$$$A$", L'$', {4}},
  testState{L"KJLOHFAKFKJBVLSAEKJFBGLSAE", L"$A$", L'$', {6, 15, 24}},
  // Update: cyrillic symbols
  testState{L"ДРНOHFЖKFKJBVLSЖEKJFBGLSЖE", L"$Ж$", L'$', {6, 15, 24}}
  ));

int main(int argc, char* argv[]) {
  setlocale(LC_ALL, "ru_RU.UTF8");
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
