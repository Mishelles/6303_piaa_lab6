#include "../headers/AhoCorasick.h"
#include <iostream>

int main() {

    std::string text;
    std::string joker;
    char jokerSym;

    std::cin >> text;
    std::cin >> joker;
    std::cin >> jokerSym;

    AhoCorasick ahoCorAlgorithm;

    ahoCorAlgorithm.init(text, joker, jokerSym);
    std::vector<int> res = ahoCorAlgorithm.solve();

    for (int result : res) {
        std::cout << result << std::endl;
    }

    return 0;
}
