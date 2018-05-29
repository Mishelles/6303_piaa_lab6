#include "../headers/AhoCorasick.h"

AhoCorasick::AhoCorasick() {
    _bohr = NULL;
}

AhoCorasick::~AhoCorasick() {
    _bohr = NULL;
}

void AhoCorasick::init(const std::string& text, const std::string& joker, const char& jokerSym) {
    _text = text;
    _joker = joker;
    _jokerSym = jokerSym;
    _bohr = new BohrTree(text.size());
}

std::vector<int> AhoCorasick::solve() {
    std::vector<int> res = _bohr->searchJocker(_text, _joker, _jokerSym);
    return res;
}

void AhoCorasick::reset() {
    if (_bohr) delete _bohr;
    _text.clear();
    _joker.clear();
}
