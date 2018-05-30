#ifndef AHO_CORASICK_H
#define AHO_CORASICK_H

#include "Bohr.h"

class AhoCorasick {

public:

    AhoCorasick();
    ~AhoCorasick();

    void init(const std::wstring& text, const std::wstring& joker, const wchar_t& jokerSym);
    std::vector<int> solve();
    void reset();

private:

    Bohr* _bohr;
    std::wstring _text;
    std::wstring _joker;
    wchar_t _jokerSym;

};

#endif
