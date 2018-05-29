#ifndef AHO_CORASICK_H
#define AHO_CORASICK_H

#include "BohrTree.h"

class AhoCorasick {

public:

    AhoCorasick();
    ~AhoCorasick();

    void init(const std::string& text, const std::string& joker, const char& jokerSym);
    std::vector<int> solve();
    void reset();

private:

    BohrTree* _bohr;
    std::string _text;
    std::string _joker;
    char _jokerSym;

};

#endif
