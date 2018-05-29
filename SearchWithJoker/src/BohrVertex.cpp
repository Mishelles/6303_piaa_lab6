#include "../headers/BohrVertex.h"

BohrVertex::BohrVertex(const char& sym, const int& parentLink)
    : isEndOfPattern(false)
    , correctSuffixLink(-1)
    , suffixLink(-1)
    , sym(sym)
    , parentLink(parentLink) {}
