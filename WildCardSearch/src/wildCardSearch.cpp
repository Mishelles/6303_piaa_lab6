#include "../headers/AhoCorasick.h"
#include <iostream>

int main() {

    setlocale(LC_ALL, "ru_RU.UTF8");

    std::wstring text;
    std::wstring joker;
    wchar_t jokerSym;

    std::wcin >> text;
    std::wcin >> joker;
    std::wcin >> jokerSym;

    AhoCorasick ahoCorAlgorithm;

    ahoCorAlgorithm.init(text, joker, jokerSym);
    std::vector<int> res = ahoCorAlgorithm.solve();

    for (int result : res) {
        std::wcout << result << std::endl;
    }

    return 0;
}
