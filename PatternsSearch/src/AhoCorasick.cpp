#include "../headers/AhoCorasick.h"

#include <algorithm>

AhoCorasick::AhoCorasick() {
  _bohr = NULL;
}

AhoCorasick::~AhoCorasick() {
  reset();
}

void AhoCorasick::init(const std::string& text, const std::vector<std::string>& patterns, const unsigned int& numOfPatterns) {
    _text = text;
    _patterns = patterns;

    _bohr = new Bohr;

    for (unsigned int i = 0; i < numOfPatterns; i++) {
        _bohr->addString(_patterns[i], i);
    }
}

std::vector<result> AhoCorasick::solve() {
    std::vector<result> res;

    if (!_bohr) return res;

    res = _bohr->find(_text, _patterns);
    std::sort(res.begin(), res.end(), _sortComparator);

    return res;
}

void AhoCorasick::reset() {
    if (_bohr) delete _bohr;
    _patterns.clear();
    _text.clear();
}

bool AhoCorasick::_sortComparator(const result& a, const result& b) {
    return (a.first == b.first) ? (a.second < b.second) : (a.first < b.first);
}
