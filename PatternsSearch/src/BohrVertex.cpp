#include "../headers/BohrVertex.h"

BohrVertex::BohrVertex(const char& sym, const int& parentLink)
    : sym(sym)
    , parentLink(parentLink)
    , isEndOfPattern(false)
    , suffixLink(-1)
    , correctSuffixLink(-1)
{
    moves[sym] = -1;
    nextVertices[sym] = -1;
}
