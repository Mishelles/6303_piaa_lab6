#include "../headers/Node.h"

Node::Node(const wchar_t& sym, const int& parentLink)
    : sym(sym)
    , parentLink(parentLink)
    , isEndOfPattern(false)
    , suffixLink(-1)
    , correctSuffixLink(-1)
{
    moves[sym] = -1;
    nextNodes[sym] = -1;
}
