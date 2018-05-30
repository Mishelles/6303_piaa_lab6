#include "../headers/AhoCorasick.h"
#include <iostream>

int main() {

    setlocale(LC_ALL, "ru_RU.UTF8");

    std::wstring text;
    unsigned int numOfPatterns;

    std::wcin >> text;
    std::wcin >> numOfPatterns;
    std::vector<std::wstring> patterns(numOfPatterns);

    for (unsigned int i = 0; i < numOfPatterns; i++) {
        std::wcin >> patterns[i];
    }

    AhoCorasick ahoCor;

    ahoCor.init(text, patterns, numOfPatterns);
    std::vector<result> results = ahoCor.solve();

    for (auto result : results) {
        std::wcout << result.first << " " << result.second << std::endl;
    }

    return 0;
}
