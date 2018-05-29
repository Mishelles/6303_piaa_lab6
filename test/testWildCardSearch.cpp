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
    std::string text;
    std::string joker;
    char jokerSym;
    std::vector<int> results;

    friend std::ostream& operator<<(std::ostream& os, const testState& obj) {

        os << "[" << std::endl;
        os << "Text: " << std::endl;
        os << "\t" << obj.text << std::endl;
        os << "Joker: " << std::endl;
        os << "\t" << obj.joker << std::endl;
        os << "JokerSym: " << std::endl;
        os << "\t" << obj.jokerSym << std::endl;

        os << "Results: " << std::endl;

        for (auto result : obj.results) {
            os << "\t" << result << std::endl;
        }

        os << "]" <<std::endl;

        return os;
    }
};

struct jokerSearchTest : TestAhoCorasick, testing::WithParamInterface<testState> {
    void SetUp() {
        std::cout << GetParam();
    }
};

TEST_P(jokerSearchTest, searchWithWildcard) {
    auto state = GetParam();
    ahoCorAlgorithm->init(state.text, state.joker, state.jokerSym);
    ASSERT_EQ(state.results, ahoCorAlgorithm->solve());
}


INSTANTIATE_TEST_CASE_P(Default, jokerSearchTest,
  testing::Values(
  testState{"AACT", "A$", '$', {1, 2}},
  testState{"AACT", "T$", '$', {}},
  testState{"LOLYPOP", "L$L$P$P", '$', {1}},
  testState{"MAMTREW", "A$$", '$', {2}},
  testState{"AACT", "A$$", '$', {1, 2}},
  testState{"KJLOHFAK", "$$$A$", '$', {4}},
  testState{"KJLOHFAKFKJBVLSAEKJFBGLSAE", "$A$", '$', {6, 15, 24}}
  ));

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
