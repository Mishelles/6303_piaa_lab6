#include "../headers/Node.h"

Node::Node(const char& sym, const int& parentLink)
    : isEndOfPattern(false)
    , correctSuffixLink(-1)
    , suffixLink(-1)
    , sym(sym)
    , parentLink(parentLink) {}
