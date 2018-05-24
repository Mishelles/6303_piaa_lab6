#include "AhoCorasick.h"
#include <iostream>

int main() {

    std::string text;
    unsigned int numOfPatterns;

    std::cin >> text;
    std::cin >> numOfPatterns;
    std::vector<std::string> patterns(numOfPatterns);

    for (unsigned int i = 0; i < numOfPatterns; i++) {
        std::cin >> patterns[i];
    }

    AhoCorasick ahoCor;

    ahoCor.init(text, patterns, numOfPatterns);
    std::vector<result> results = ahoCor.solve();

    for (auto result : results) {
        std::cout << result.first << " " << result.second << std::endl;
    }

    return 0;
}
